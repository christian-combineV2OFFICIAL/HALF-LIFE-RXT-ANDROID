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

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "gamerules.h"
#include "decals.h"
#include "explode.h"


#define	CROWBAR_BODYHIT_VOLUME 128
#define	CROWBAR_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS( weapon_crowbar, CCrowbar );


#ifndef CLIENT_DLL

LINK_ENTITY_TO_CLASS( plasma_pistol, CPlasmapPistol );

//=========================================================
//=========================================================
CPlasmapPistol *CPlasmapPistol::CreatePlasmapPistol( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, CCrowbar *pLauncher )
{
	CPlasmapPistol *pPlasmap = GetClassPtr( (CPlasmapPistol *)NULL );

	UTIL_SetOrigin( pPlasmap->pev, vecOrigin );
	pPlasmap->pev->angles = vecAngles;
	pPlasmap->Spawn();
	pPlasmap->SetTouch( CPlasmapPistol::RocketTouch );
	pPlasmap->m_pLauncher = pLauncher;// remember what RPG fired me. 
	pPlasmap->m_pLauncher->m_cActiveRockets++;// register this missile as active for the launcher
	pPlasmap->pev->owner = pOwner->edict();

	pPlasmap->pev->movetype = MOVETYPE_FLYMISSILE;
	pPlasmap->pev->solid = SOLID_BBOX;

	return pPlasmap;
}

//=========================================================
//=========================================================
void CPlasmapPistol :: Spawn( void )
{
	Precache( );

	SET_MODEL(ENT(pev), "models/rpgrocket.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING("plasma_pistol");

	SetThink( IgniteThink );
	SetTouch( ExplodeTouch );

	pev->angles.x -= 0;
	UTIL_MakeVectors( pev->angles );
	pev->angles.x = -(pev->angles.x + 0);

	pev->velocity = gpGlobals->v_forward * 1000;
	pev->gravity = 0.5;

	pev->nextthink = gpGlobals->time + 0.0;

	pev->dmg = gSkillData.plrDmgRPG;
}

//=========================================================
//=========================================================
void CPlasmapPistol :: RocketTouch ( CBaseEntity *pOther )
{
	if ( m_pLauncher )
	{
		// my launcher is still around, tell it I'm dead.
		m_pLauncher->m_cActiveRockets--;
	}

	STOP_SOUND( edict(), CHAN_VOICE, "weapons/rocket1.wav" );
	ExplodeTouch( pOther );
}

//=========================================================
//=========================================================
void CPlasmapPistol :: Precache( void )
{
	PRECACHE_MODEL("models/rpgrocket.mdl");
	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
	PRECACHE_SOUND ("weapons/rocket1.wav");
}


void CPlasmapPistol :: IgniteThink( void  )
{
	// pev->movetype = MOVETYPE_TOSS;

	pev->movetype = MOVETYPE_FLY;
	pev->effects |= EF_LIGHT;

	// make rocket sound
	EMIT_SOUND( ENT(pev), CHAN_VOICE, "weapons/rocket1.wav", 1, 0.5 );

	// rocket trail
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );

		WRITE_BYTE( TE_BEAMFOLLOW );
		WRITE_SHORT(entindex());	// entity
		WRITE_SHORT(m_iTrail );	// model
		WRITE_BYTE( 40 ); // life
		WRITE_BYTE( 5 );  // width
		WRITE_BYTE( 224 );   // r, g, b
		WRITE_BYTE( 224 );   // r, g, b
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness

	MESSAGE_END();  // move PHS/PVS data sending into here (SEND_ALL, SEND_PVS, SEND_PHS)

	m_flIgniteTime = gpGlobals->time;

	// set to follow laser spot
	SetThink( FollowThink );
	pev->nextthink = gpGlobals->time + 0.1;
}


void CPlasmapPistol :: FollowThink( void  )
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
			STOP_SOUND( ENT(pev), CHAN_VOICE, "weapons/rocket1.wav" );
		}
		pev->velocity = pev->velocity * 0.2 + vecTarget * flSpeed * 0.798;
		if (pev->waterlevel == 0 && pev->velocity.Length() < 1500)
		{
			Detonate( );
		}
	}
	// ALERT( at_console, "%.0f\n", flSpeed );

	pev->nextthink = gpGlobals->time + 0.1;
}
#endif


enum gauss_e {
	CROWBAR_IDLE1 = 0,
	CROWBAR_DRAW,
	CROWBAR_HOLSTER,
	CROWBAR_ATTACK1,
	CROWBAR_ATTACK2,
	CROWBAR_ATTACK3,
	CROWBAR_PISTOL_ATTACK
};


void CCrowbar::Spawn( )
{
	Precache( );
	m_iId = WEAPON_CROWBAR;
	SET_MODEL(ENT(pev), "models/w_lightsaber.mdl");
	m_iDefaultAmmo = CROWBAR_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CCrowbar::Precache( void )
{
	PRECACHE_MODEL("models/v_lightsaber.mdl");
	PRECACHE_MODEL("models/w_lightsaber.mdl");
	PRECACHE_MODEL("models/p_lightsaber.mdl");
	PRECACHE_SOUND("weapons/lightsaber_deploy.wav");
	PRECACHE_SOUND("weapons/lightsaber_fireplasma.wav");	
	PRECACHE_SOUND("weapons/lightsaber_hit.wav");
	PRECACHE_SOUND("weapons/lightsaber_hit2.wav");
	PRECACHE_SOUND("weapons/lightsaber_hit3.wav");
	PRECACHE_SOUND("weapons/lightsaber_holster.wav");
	PRECACHE_SOUND("weapons/lightsaber_idle.wav");
	PRECACHE_SOUND("weapons/lightsaber_miss.wav");
    PRECACHE_MODEL("sprites/hotglow.spr");
    m_iSpriteTexture = 	PRECACHE_MODEL("sprites/anim_spr4.spr");

	m_usCrowbar = PRECACHE_EVENT ( 1, "events/crowbar.sc" );
	m_usCrowbar2 = PRECACHE_EVENT ( 1, "events/crowbar2.sc" );
}

int CCrowbar::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "energy";
	p->iMaxAmmo1 = CROWBAR_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 0;
	p->iPosition = 0;
	p->iId = WEAPON_CROWBAR;
	p->iFlags = ITEM_FLAG_NOAUTOSWITCHEMPTY | ITEM_FLAG_NOAUTORELOAD;
	p->iWeight = CROWBAR_WEIGHT;
	return 1;
}



BOOL CCrowbar::Deploy( )
{
	return DefaultDeploy( "models/v_lightsaber.mdl", "models/p_lightsaber.mdl", CROWBAR_DRAW, "crowbar" );
}

void CCrowbar::Holster( int skiplocal /* = 0 */ )
{
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/lightsaber_holster.wav", 1, ATTN_NORM);
	STOP_SOUND( ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/lightsaber_idle.wav" );
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
	SendWeaponAnim( CROWBAR_HOLSTER );
	
	//!!!HACKHACK - can't select hornetgun if it's empty! no way to get ammo for it, either.
	if ( !m_pPlayer->m_rgAmmo[ PrimaryAmmoIndex() ] )
	{
		m_pPlayer->m_rgAmmo[ PrimaryAmmoIndex() ] = 1;
	}
}


void FindHullIntersection( const Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity )
{
	int			i, j, k;
	float		distance;
	float		*minmaxs[2] = {mins, maxs};
	TraceResult tmpTrace;
	Vector		vecHullEnd = tr.vecEndPos;
	Vector		vecEnd;

	distance = 1e6f;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc)*2);
	UTIL_TraceLine( vecSrc, vecHullEnd, dont_ignore_monsters, pEntity, &tmpTrace );
	if ( tmpTrace.flFraction < 1.0 )
	{
		tr = tmpTrace;
		return;
	}

	for ( i = 0; i < 2; i++ )
	{
		for ( j = 0; j < 2; j++ )
		{
			for ( k = 0; k < 2; k++ )
			{
				vecEnd.x = vecHullEnd.x + minmaxs[i][0];
				vecEnd.y = vecHullEnd.y + minmaxs[j][1];
				vecEnd.z = vecHullEnd.z + minmaxs[k][2];

				UTIL_TraceLine( vecSrc, vecEnd, dont_ignore_monsters, pEntity, &tmpTrace );
				if ( tmpTrace.flFraction < 1.0 )
				{
					float thisDistance = (tmpTrace.vecEndPos - vecSrc).Length();
					if ( thisDistance < distance )
					{
						tr = tmpTrace;
						distance = thisDistance;
					}
				}
			}
		}
	}
}


void CCrowbar::PrimaryAttack()
{
	Reload( );	
	
	if (! Swing( 1 ))
	{
		SetThink( SwingAgain );
		pev->nextthink = gpGlobals->time + 0.1;
	}
}

void CCrowbar::SecondaryAttack( void )
{	
	CrowbarFire( 0.01, 0.3, TRUE );
}

void CCrowbar::CrowbarFire( float flSpread , float flCycleTime, BOOL fUseAutoAim )
{
	Reload();
	
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound( );
		m_flNextPrimaryAttack = 0.15;
		return;
	}

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		return;
	}

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
			
	m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;

	m_flRechargeTime = gpGlobals->time + 5;

	// player "shoot" animation
	m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

 	UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );

#ifndef CLIENT_DLL
		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 16 + gpGlobals->v_right * -8 + gpGlobals->v_up * -8;
		
		CPlasmapPistol *pPlasmap = CPlasmapPistol::CreatePlasmapPistol( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );// RpgRocket::Create stomps on globals, so remake.
		pPlasmap->pev->velocity = pPlasmap->pev->velocity + gpGlobals->v_forward * DotProduct( m_pPlayer->pev->velocity, gpGlobals->v_forward );
#endif

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT( flags, m_pPlayer->edict(), m_usCrowbar2 );
	
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 5;// idle pretty soon after shooting.

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
}

void CCrowbar::Reload( void )
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] >= CROWBAR_MAX_CARRY)
		return;

	while (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] < CROWBAR_MAX_CARRY && m_flRechargeTime < gpGlobals->time)
	{
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]++;
		m_flRechargeTime += 5;
	}
}

void CCrowbar::Smack( )
{
	UTIL_DecalTrace( &m_trHit, DECAL_SMALLSCORCH3 );
}


void CCrowbar::SwingAgain( void )
{
	Swing( 0 );
}


int CCrowbar::Swing( int fFirst )
{
	int fDidHit = FALSE;

	TraceResult tr;

	UTIL_MakeVectors (m_pPlayer->pev->v_angle);
	Vector vecSrc	= m_pPlayer->GetGunPosition( );
	Vector vecEnd	= vecSrc + gpGlobals->v_forward * 32;

	UTIL_TraceLine( vecSrc, vecEnd, dont_ignore_monsters, ENT( m_pPlayer->pev ), &tr );

#ifndef CLIENT_DLL
	if ( tr.flFraction >= 1.0 )
	{
		UTIL_TraceHull( vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT( m_pPlayer->pev ), &tr );
		if ( tr.flFraction < 1.0 )
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity *pHit = CBaseEntity::Instance( tr.pHit );
			if ( !pHit || pHit->IsBSPModel() )
				FindHullIntersection( vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict() );
			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
		}
	}
#endif

	PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usCrowbar, 
	0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0,
	0.0, 0, 0.0 );


	if ( tr.flFraction >= 1.0 )
	{
		if (fFirst)
		{
			// miss
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.33;
			
			// player "shoot" animation
			m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
		}
	}
	else
	{
		switch( ((m_iSwing++) % 2) + 1 )
		{
		case 0:
			SendWeaponAnim( CROWBAR_ATTACK1 ); break;
		case 1:
			SendWeaponAnim( CROWBAR_ATTACK2 ); break;
		case 2:
			SendWeaponAnim( CROWBAR_ATTACK3 ); break;
		}

		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
		
#ifndef CLIENT_DLL

		// hit
		fDidHit = TRUE;
		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		ClearMultiDamage( );

		if ( (m_flNextPrimaryAttack + 1 < UTIL_WeaponTimeBase() ) || g_pGameRules->IsMultiplayer() )
		{
			// first swing does full damage
			pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbar, gpGlobals->v_forward, &tr, DMG_CLUB ); 
		}
		else
		{
			// subsequent swings do half
			pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgCrowbar / 2, gpGlobals->v_forward, &tr, DMG_CLUB ); 
		}	
		ApplyMultiDamage( m_pPlayer->pev, m_pPlayer->pev );

		// play thwack, smack, or dong sound
		float flVol = 1.0;
		int fHitWorld = TRUE;

		if (pEntity)
		{
			if ( pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE )
			{
				// play thwack or smack sound
				switch( RANDOM_LONG(0,2) )
				{
				case 0:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit.wav", 1, ATTN_NORM); break;
				case 1:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit2.wav", 1, ATTN_NORM); break;
				case 2:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit3.wav", 1, ATTN_NORM); break;
				}
				m_pPlayer->m_iWeaponVolume = CROWBAR_BODYHIT_VOLUME;
				if ( !pEntity->IsAlive() )
					  return TRUE;
				else
					  flVol = 0.1;

				fHitWorld = FALSE;
			
#ifndef CLIENT_DLL
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y + 5 );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x + 5 );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x - 5 );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y - 5 );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, tr.vecEndPos  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( tr.vecEndPos.x );	// X
		WRITE_COORD( tr.vecEndPos.y );	// Y
		WRITE_COORD( tr.vecEndPos.z );	// Z
		WRITE_BYTE( 30 );		// radius * 0.1
		WRITE_BYTE( 128 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 5 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );
#endif			

	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
	
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}	

	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}

			}
		}

		// play texture hit sound
		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line

		if (fHitWorld)
		{
			float fvolbar = TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd-vecSrc)*2, BULLET_PLAYER_CROWBAR);

			if ( g_pGameRules->IsMultiplayer() )
			{
				// override the volume here, cause we don't play texture sounds in multiplayer, 
				// and fvolbar is going to be 0 from the above call.

				fvolbar = 1;
			}

			// also play crowbar strike
			switch( RANDOM_LONG(0,2) )
			{
			case 0:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0,3)); 
				break;
			case 1:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit2.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0,3)); 
				break;
			case 2:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/lightsaber_hit3.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0,3)); 
				break;			
			}

			// delay the decal a bit
			m_trHit = tr;
		
#ifndef CLIENT_DLL
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y + 5 );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x + 5 );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x - 5 );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( tr.vecEndPos.x );	// Send to PAS because of the sound
		WRITE_COORD( tr.vecEndPos.y - 5 );
		WRITE_COORD( tr.vecEndPos.z );
		WRITE_SHORT( m_iSpriteTexture );
		WRITE_BYTE( 15 ); // scale * 10
		WRITE_BYTE( 150 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, tr.vecEndPos  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( tr.vecEndPos.x );	// X
		WRITE_COORD( tr.vecEndPos.y );	// Y
		WRITE_COORD( tr.vecEndPos.z );	// Z
		WRITE_BYTE( 30 );		// radius * 0.1
		WRITE_BYTE( 128 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 5 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );
#endif		
		
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}		
	
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}	

	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
			
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}			
					
	// draw sparks
	if ( !( pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS ) )
	{
		int sparkCount = RANDOM_LONG(0,3);

		for ( int i = 0; i < sparkCount; i++ )
		{
			Create( "spark_shower", tr.vecEndPos, tr.vecPlaneNormal, NULL );
		}
	}

		}

		m_pPlayer->m_iWeaponVolume = flVol * CROWBAR_WALLHIT_VOLUME;
#endif
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.33;
		
		SetThink( Smack );
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;

		
	}
	return fDidHit;
}

void CCrowbar::WeaponIdle( void )
{
	Reload( );
	
	if ( gpGlobals->time >= m_flShockTime )
	{
		EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/lightsaber_idle.wav", 0.9, ATTN_NORM );
		m_flShockTime = gpGlobals->time +3;
	}

	if (m_flTimeWeaponIdle > gpGlobals->time)
		return;

	SendWeaponAnim( CROWBAR_IDLE1 );
	m_flTimeWeaponIdle = gpGlobals->time + RANDOM_FLOAT (5, 7);
}

