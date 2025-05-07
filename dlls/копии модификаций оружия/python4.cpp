/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#if !defined( OEM_BUILD ) && !defined( HLDEMO_BUILD )

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "monsters.h"
#include "player.h"
#include "gamerules.h"
#include "shake.h"
#include "decals.h"


enum python_e {
	PYTHON_IDLE1 = 0,
	PYTHON_IDLE2,
	PYTHON_IDLE3,
	PYTHON_SHOOT,
	PYTHON_SHOOT_EMPTY,
	PYTHON_RELOAD,
	PYTHON_RELOAD_NOT_EMPTY,
	PYTHON_DRAW,
	PYTHON_HOLSTER,
	PYTHON_ADD_SILENCER
};

#ifndef CLIENT_DLL

LINK_ENTITY_TO_CLASS( LaserFire, CLaserFire );

//=========================================================
//=========================================================
CLaserFire *CLaserFire::CreateLaserFire( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, CPython *pLauncher )
{
	CLaserFire *pLaserFire = GetClassPtr( (CLaserFire *)NULL );

	UTIL_SetOrigin( pLaserFire->pev, vecOrigin );
	pLaserFire->pev->angles = vecAngles;
	pLaserFire->Spawn();
	pLaserFire->SetTouch( CLaserFire::RocketTouch );
	pLaserFire->m_pLauncher = pLauncher;// remember what RPG fired me. 
	pLaserFire->m_pLauncher->m_cActiveLaser++;// register this missile as active for the launcher
	pLaserFire->pev->owner = pOwner->edict();

	return pLaserFire;
}

//=========================================================
//=========================================================
void CLaserFire :: Spawn( void )
{
	Precache( );
	// motor
	pev->movetype = MOVETYPE_BOUNCE;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "sprites/glow01.spr");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING("LaserFire");

	pev->rendermode = kRenderGlow;
	pev->renderfx = kRenderFxNoDissipation;
	pev->renderamt = 255;
	pev->rendercolor.x = 0;
	pev->rendercolor.y = 255;
	pev->rendercolor.z = 0;
	pev->scale = 0.3;

	SetThink( IgniteThink );
	SetTouch( RocketTouch );

	pev->angles.x -= 0;
	UTIL_MakeVectors( pev->angles );
	pev->angles.x = -(pev->angles.x + 0);

	pev->velocity = gpGlobals->v_forward * 0;
	pev->gravity = 0.5;

	pev->nextthink = gpGlobals->time + 0.0;

	pev->dmg = gSkillData.plrDmgGauss;
}

//=========================================================
//=========================================================
void CLaserFire :: RocketTouch ( CBaseEntity *pOther )
{
	if ( pOther && pOther->pev->takedamage )
	{// do the damage		
		pOther->TakeDamage( pev, VARS( pev->owner ), pev->dmg, DMG_BULLET );
	}

	pev->modelindex = 0;// so will disappear for the 0.1 secs we wait until NEXTTHINK gets rid
	pev->solid = SOLID_NOT;

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 10 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 2 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );

	TraceResult tr;

	UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
    UTIL_Ricochet( pev->origin, 1.0 );
	UTIL_Sparks( pev->origin );
	DecalGunshot( &tr, BULLET_PLAYER_9MM );
	SetThink ( SUB_Remove );
	pev->nextthink = gpGlobals->time + 1;// stick around long enough for the sound to finish!
}

//=========================================================
//=========================================================
void CLaserFire :: Precache( void )
{
	PRECACHE_MODEL("models/null.mdl");
	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
	m_iLaser = PRECACHE_MODEL("sprites/laserglow_n.spr");
	PRECACHE_SOUND ("weapons/rocket1.wav");
	PRECACHE_MODEL("sprites/glow01.spr");
}


void CLaserFire :: IgniteThink( void  )
{
	// pev->movetype = MOVETYPE_TOSS;

	pev->movetype = MOVETYPE_FLY;
 
	// rocket trail
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );

		WRITE_BYTE( TE_BEAMFOLLOW );
		WRITE_SHORT(entindex());	// entity
		WRITE_SHORT(m_iTrail );	// model
		WRITE_BYTE( 3 ); // life
		WRITE_BYTE( 2 );  // width
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness

	MESSAGE_END();  // move PHS/PVS data sending into here (SEND_ALL, SEND_PVS, SEND_PHS)

	m_flIgniteTime = gpGlobals->time;

	// set to follow laser spot
	SetThink( FollowThink );
	pev->nextthink = gpGlobals->time + 0.01;
}


void CLaserFire :: FollowThink( void  )
{
	CBaseEntity *pOther = NULL;
	Vector vecTarget;
	Vector vecDir;
	float flDist, flMax, flDot;
	TraceResult tr;

	UTIL_MakeAimVectors( pev->angles );

	vecTarget = gpGlobals->v_forward;
	flMax = 4096;
	
	// Examine all entities within a reasonable radius
	while ((pOther = UTIL_FindEntityByClassname( pOther, "laser_spot" )) != NULL)
	{
		UTIL_TraceLine ( pev->origin, pOther->pev->origin, dont_ignore_monsters, ENT(pev), &tr );
		// ALERT( at_console, "%f\n", tr.flFraction );
		if (tr.flFraction >= 0.90)
		{
			vecDir = pOther->pev->origin - pev->origin;
			flDist = vecDir.Length( );
			vecDir = vecDir.Normalize( );
			flDot = DotProduct( gpGlobals->v_forward, vecDir );
			if ((flDot > 0) && (flDist * (1 - flDot) < flMax))
			{
				flMax = flDist * (1 - flDot);
				vecTarget = vecDir;
			}
		}
	}

	pev->angles = UTIL_VecToAngles( vecTarget );

	// this acceleration and turning math is totally wrong, but it seems to respond well so don't change it.
	float flSpeed = pev->velocity.Length();
	if (gpGlobals->time - m_flIgniteTime < 1.0)
	{
		pev->velocity = pev->velocity * 0.2 + vecTarget * (flSpeed * 0.8 + 400);
		if (pev->waterlevel == 3)
		{
			// go slow underwater
			if (pev->velocity.Length() > 300)
			{
				pev->velocity = pev->velocity.Normalize() * 300;
			}
			UTIL_BubbleTrail( pev->origin - pev->velocity * 0.1, pev->origin, 4 );
		} 
		else 
		{
			if (pev->velocity.Length() > 2000)
			{
				pev->velocity = pev->velocity.Normalize() * 2000;
			}
		}
	}
	else
	{
		if (pev->effects & EF_LIGHT)
		{
			pev->effects = 0;
		}
		pev->velocity = pev->velocity * 0.2 + vecTarget * flSpeed * 0.798;
		if (pev->waterlevel == 0 && pev->velocity.Length() < 1500)
		{
		}
	}
	// ALERT( at_console, "%.0f\n", flSpeed );

	pev->nextthink = gpGlobals->time + 0.01;
}

LINK_ENTITY_TO_CLASS( LaserFire2, CLaserFire2 );

//=========================================================
//=========================================================
CLaserFire2 *CLaserFire2::CreateLaserFire2( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, CPython *pLauncher )
{
	CLaserFire2 *pLaserFire2 = GetClassPtr( (CLaserFire2 *)NULL );

	UTIL_SetOrigin( pLaserFire2->pev, vecOrigin );
	pLaserFire2->pev->angles = vecAngles;
	pLaserFire2->Spawn();
	pLaserFire2->SetTouch( CLaserFire2::RocketTouch );
	pLaserFire2->m_pLauncher = pLauncher;// remember what RPG fired me. 
	pLaserFire2->m_pLauncher->m_cActiveLaser++;// register this missile as active for the launcher
	pLaserFire2->pev->owner = pOwner->edict();

	return pLaserFire2;
}

//=========================================================
//=========================================================
void CLaserFire2 :: Spawn( void )
{
	Precache( );
	// motor
	pev->movetype = MOVETYPE_BOUNCE;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "sprites/glow01.spr");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING("LaserFire");

	pev->rendermode = kRenderGlow;
	pev->renderfx = kRenderFxNoDissipation;
	pev->renderamt = 255;
	pev->rendercolor.x = 0;
	pev->rendercolor.y = 255;
	pev->rendercolor.z = 0;
	pev->scale = 0.5;

	SetThink( IgniteThink );
	SetTouch( RocketTouch );

	pev->angles.x -= 0;
	UTIL_MakeVectors( pev->angles );
	pev->angles.x = -(pev->angles.x + 0);

	pev->velocity = gpGlobals->v_forward * 0;
	pev->gravity = 0.5;

	pev->nextthink = gpGlobals->time + 0.0;

	pev->dmg = gSkillData.plrDmgRPG;
}

//=========================================================
//=========================================================
void CLaserFire2 :: RocketTouch ( CBaseEntity *pOther )
{
	if ( pOther && pOther->pev->takedamage )
	{// do the damage		
		pOther->TakeDamage( pev, VARS( pev->owner ), pev->dmg, DMG_BULLET );
	}

    EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/shock_impact.wav", 1, ATTN_NORM);

	pev->modelindex = 0;// so will disappear for the 0.1 secs we wait until NEXTTHINK gets rid
	pev->solid = SOLID_NOT;

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 30 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 2 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );

	TraceResult tr;

	UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
    UTIL_Ricochet( pev->origin, 1.0 );
	UTIL_Sparks( pev->origin );
	UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );
	SetThink ( SUB_Remove );
	pev->nextthink = gpGlobals->time + 1;// stick around long enough for the sound to finish!
}

//=========================================================
//=========================================================
void CLaserFire2 :: Precache( void )
{
	PRECACHE_MODEL("models/null.mdl");
	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
	m_iLaser = PRECACHE_MODEL("sprites/laserglow_n.spr");
	PRECACHE_SOUND ("weapons/rocket1.wav");
	PRECACHE_MODEL("sprites/glow01.spr");
}


void CLaserFire2 :: IgniteThink( void  )
{
	// pev->movetype = MOVETYPE_TOSS;

	pev->movetype = MOVETYPE_FLY;
 
	// rocket trail
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );

		WRITE_BYTE( TE_BEAMFOLLOW );
		WRITE_SHORT(entindex());	// entity
		WRITE_SHORT(m_iTrail );	// model
		WRITE_BYTE( 3 ); // life
		WRITE_BYTE( 2 );  // width
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness

	MESSAGE_END();  // move PHS/PVS data sending into here (SEND_ALL, SEND_PVS, SEND_PHS)

	m_flIgniteTime = gpGlobals->time;

	// set to follow laser spot
	SetThink( FollowThink );
	pev->nextthink = gpGlobals->time + 0.01;
}


void CLaserFire2 :: FollowThink( void  )
{
	CBaseEntity *pOther = NULL;
	Vector vecTarget;
	Vector vecDir;
	float flDist, flMax, flDot;
	TraceResult tr;

	UTIL_MakeAimVectors( pev->angles );

	vecTarget = gpGlobals->v_forward;
	flMax = 4096;
	
	// Examine all entities within a reasonable radius
	while ((pOther = UTIL_FindEntityByClassname( pOther, "laser_spot" )) != NULL)
	{
		UTIL_TraceLine ( pev->origin, pOther->pev->origin, dont_ignore_monsters, ENT(pev), &tr );
		// ALERT( at_console, "%f\n", tr.flFraction );
		if (tr.flFraction >= 0.90)
		{
			vecDir = pOther->pev->origin - pev->origin;
			flDist = vecDir.Length( );
			vecDir = vecDir.Normalize( );
			flDot = DotProduct( gpGlobals->v_forward, vecDir );
			if ((flDot > 0) && (flDist * (1 - flDot) < flMax))
			{
				flMax = flDist * (1 - flDot);
				vecTarget = vecDir;
			}
		}
	}

	pev->angles = UTIL_VecToAngles( vecTarget );

	// this acceleration and turning math is totally wrong, but it seems to respond well so don't change it.
	float flSpeed = pev->velocity.Length();
	if (gpGlobals->time - m_flIgniteTime < 1.0)
	{
		pev->velocity = pev->velocity * 0.2 + vecTarget * (flSpeed * 0.8 + 400);
		if (pev->waterlevel == 3)
		{
			// go slow underwater
			if (pev->velocity.Length() > 300)
			{
				pev->velocity = pev->velocity.Normalize() * 300;
			}
			UTIL_BubbleTrail( pev->origin - pev->velocity * 0.1, pev->origin, 4 );
		} 
		else 
		{
			if (pev->velocity.Length() > 2000)
			{
				pev->velocity = pev->velocity.Normalize() * 2000;
			}
		}
	}
	else
	{
		if (pev->effects & EF_LIGHT)
		{
			pev->effects = 0;
		}
		pev->velocity = pev->velocity * 0.2 + vecTarget * flSpeed * 0.798;
		if (pev->waterlevel == 0 && pev->velocity.Length() < 1500)
		{
		}
	}
	// ALERT( at_console, "%.0f\n", flSpeed );

	pev->nextthink = gpGlobals->time + 0.01;
}
#endif

LINK_ENTITY_TO_CLASS( weapon_python, CPython );
LINK_ENTITY_TO_CLASS( weapon_357, CPython );

int CPython::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "357";
	p->iMaxAmmo1 = _357_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = PYTHON_MAX_CLIP;
	p->iFlags = 0;
	p->iSlot = 1;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_PYTHON;
	p->iWeight = PYTHON_WEIGHT;

	return 1;
}

int CPython::AddToPlayer( CBasePlayer *pPlayer )
{
	if ( CBasePlayerWeapon::AddToPlayer( pPlayer ) )
	{
		MESSAGE_BEGIN( MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev );
			WRITE_BYTE( m_iId );
		MESSAGE_END();
		return TRUE;
	}
	return FALSE;
}

void CPython::Spawn( )
{
	pev->classname = MAKE_STRING("weapon_357"); // hack to allow for old names
	Precache( );
	m_iId = WEAPON_PYTHON;
	SET_MODEL(ENT(pev), "models/w_9mmhandgun.mdl");

	m_iDefaultAmmo = PYTHON_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CPython::Precache( void )
{
	PRECACHE_MODEL("models/v_9mmhandgun.mdl");
	PRECACHE_MODEL("models/w_9mmhandgun.mdl");
	PRECACHE_MODEL("models/p_9mmhandgun.mdl");
	PRECACHE_MODEL("models/null.mdl");
    PRECACHE_MODEL("sprites/laserglow_n.spr");
	PRECACHE_MODEL("sprites/glow01.spr");

	PRECACHE_MODEL("models/w_357ammobox.mdl");         
	PRECACHE_SOUND("items/9mmclip1.wav");      	
	PRECACHE_SOUND ("weapons/laserglock.wav");//laserhandgun
	PRECACHE_SOUND ("weapons/shock_impact.wav");

	PRECACHE_SOUND ("weapons/357_reload1.wav");
	PRECACHE_SOUND ("weapons/357_cock1.wav");
	PRECACHE_SOUND ("weapons/357_shot1.wav");
	PRECACHE_SOUND ("weapons/357_shot2.wav");
	
	m_usFirePython = PRECACHE_EVENT( 1, "events/python.sc" );
	m_usFirePython2 = PRECACHE_EVENT( 1, "events/python2.sc" );
}

BOOL CPython::Deploy( )
{
	pev->body = 1;
    m_pPlayer->pev->renderfx = kRenderFxGlowShell;
    m_pPlayer->pev->renderamt = 15;
    m_pPlayer->pev->rendercolor = Vector(0, 255, 0);	
	return DefaultDeploy( "models/v_9mmhandgun.mdl", "models/p_9mmhandgun.mdl", PYTHON_DRAW, "onehanded", UseDecrement(), pev->body );
}


void CPython::Holster( int skiplocal /* = 0 */ )
{
    m_pPlayer->pev->renderfx = kRenderFxGlowShell;
    m_pPlayer->pev->renderamt = 0;
    m_pPlayer->pev->rendercolor = Vector(0, 0, 0);
	SendWeaponAnim( PYTHON_HOLSTER );
}

void CPython::SecondaryAttack( void )
{
        MuzzleLight2();
	    
        if (m_iClip <= 0 + 23)
		{
          return;
		}

#ifndef CLIENT_DLL
		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 16 + gpGlobals->v_right * 0 + gpGlobals->v_up * 0;
		
		CLaserFire2 *pLaserFire2 = CLaserFire2::CreateLaserFire2( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );// RpgRocket::Create stomps on globals, so remake.
		pLaserFire2->pev->velocity = pLaserFire2->pev->velocity + gpGlobals->v_forward * DotProduct( m_pPlayer->pev->velocity, gpGlobals->v_forward );
#endif

	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usFirePython2, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0, 0.0, 0, 0.0 );

	    m_iClip -= 24;

		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
	    m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 );
}

void CPython::PrimaryAttack()
{
        MuzzleLight2();
	
	    if (m_iClip <= 0 )
		{
          return;
		}

#ifndef CLIENT_DLL
		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 16 + gpGlobals->v_right * 0 + gpGlobals->v_up * 0;
		
		CLaserFire *pLaserFire = CLaserFire::CreateLaserFire( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );// RpgRocket::Create stomps on globals, so remake.
		pLaserFire->pev->velocity = pLaserFire->pev->velocity + gpGlobals->v_forward * DotProduct( m_pPlayer->pev->velocity, gpGlobals->v_forward );
#endif

	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usFirePython2, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0, 0.0, 0, 0.0 );

	    m_iClip -= 1;

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.3;
	    m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 );
}


void CPython::Reload( void )
{
    MuzzleLight2();	
	
	if ( m_pPlayer->ammo_357 <= 0 )
		return;

	if ( m_pPlayer->pev->fov != 0 )
	{
		m_fInZoom = FALSE;
		m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 0;  // 0 means reset to default fov
	}

	int bUseScope = FALSE;
#ifdef CLIENT_DLL
	bUseScope = bIsMultiplayer();
#else
	bUseScope = g_pGameRules->IsMultiplayer();
#endif

	if (DefaultReload( PYTHON_MAX_CLIP, PYTHON_RELOAD, 2.0, pev->body = 1 ))
	{
		m_flSoundDelay = 1.5;
	}
}

void CPython::MuzzleLight2( void )
{
#ifndef CLIENT_DLL
	if ( gpGlobals->time >= m_flShockTime )
	{
		UTIL_MuzzleLight( pev->origin, 200.0f, 0, 255, 0, 999.0f, 100.0f );
		UTIL_ScreenFadeAll( Vector(0,255,0), 5, 0.5, 80, FFADE_IN );
		m_flShockTime = gpGlobals->time + 0;
	}
#endif
}

void CPython::MuzzleLight( void )
{
#ifndef CLIENT_DLL
	if ( gpGlobals->time >= m_flShockTime )
	{
		UTIL_MuzzleLight( pev->origin, 200.0f, 0, 255, 0, 0.0f, 100.0f );
		UTIL_ScreenFadeAll( Vector(0,255,0), 5, 0.5, 80, FFADE_IN );
		m_flShockTime = gpGlobals->time + 0;
	}
#endif
}

void CPython::WeaponIdle( void )
{
    MuzzleLight();	
	
	ResetEmptySound( );

	m_pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );

	if ( m_flTimeWeaponIdle > UTIL_WeaponTimeBase() )
		return;

	// only idle if the slid isn't back
	if (m_iClip != 0)
	{
		int iAnim;
		float flRand = UTIL_SharedRandomFloat( m_pPlayer->random_seed, 0.0, 1.0 );

		if (flRand <= 0.3 + 0 * 0.75)
		{
			iAnim = PYTHON_IDLE3;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 100;
		}
		else if (flRand <= 0.6 + 0 * 0.875)
		{
			iAnim = PYTHON_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 100;
		}
		else
		{
			iAnim = PYTHON_IDLE2;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 100;
		}		
	
		SendWeaponAnim( iAnim, UseDecrement() ? 0 : 0, pev->body = 1 );
	}
}



class CPythonAmmo : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_357ammobox.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_357ammobox.mdl");
		PRECACHE_SOUND("weapons/laserglock.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		if (pOther->GiveAmmo( AMMO_357BOX_GIVE, "357", _357_MAX_CARRY ) != -1)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/laserglock.wav", 1, ATTN_NORM);
			return TRUE;
		}
		return FALSE;
	}
};
LINK_ENTITY_TO_CLASS( ammo_357, CPythonAmmo );


#endif