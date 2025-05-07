/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "gamerules.h"
#ifndef CLIENT_DLL
#include "shock.h"
#endif
#include "soundent.h"
#include "decals.h"
#include "shake.h"

#define SHOCKRIFLE_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum shockrifle_e {
	SHOCK_IDLE1 = 0,
	SHOCK_FIRE,
	SHOCK_DRAW,
	SHOCK_HOLSTER,
	SHOCK_IDLE3,
};

LINK_ENTITY_TO_CLASS(weapon_shockrifle, CShockrifle)

void CShockrifle::Spawn()
{
	Precache();
	m_iId = WEAPON_SHOCKRIFLE;
	SET_MODEL(ENT(pev), "models/w_shock.mdl");

    pev->renderfx = kRenderFxGlowShell;
    pev->renderamt = 15;
    pev->rendercolor = Vector(0, 255, 255);	

	m_iDefaultAmmo = SHOCKRIFLE_DEFAULT_GIVE;
	m_iFirePhase = 0;

	FallInit();// get ready to fall down.
}


void CShockrifle::Precache(void)
{
	PRECACHE_MODEL("models/v_shock.mdl");
	PRECACHE_MODEL("models/w_shock.mdl");
	PRECACHE_MODEL("models/p_shock.mdl");

	PRECACHE_SOUND("weapons/shock_discharge.wav");
	PRECACHE_SOUND("weapons/shock_draw.wav");
	PRECACHE_SOUND("weapons/shock_fire.wav");
	PRECACHE_SOUND("weapons/shock_impact.wav");
	PRECACHE_SOUND("weapons/shock_recharge.wav");
	PRECACHE_SOUND("weapons/shock_discharge2.wav");

	PRECACHE_MODEL("sprites/lgtning.spr");
	PRECACHE_MODEL("sprites/flare3.spr");

	m_usShockFire = PRECACHE_EVENT(1, "events/shock.sc");
	m_usShockFire2 = PRECACHE_EVENT(1, "events/shock2.sc");

	UTIL_PrecacheOther("shock_beam");
}

int CShockrifle::AddToPlayer(CBasePlayer *pPlayer)
{
	if (CBasePlayerWeapon::AddToPlayer(pPlayer))
	{

#ifndef CLIENT_DLL
		if (g_pGameRules->IsMultiplayer())
		{
			// in multiplayer, all hivehands come full. 
			pPlayer->m_rgAmmo[PrimaryAmmoIndex()] = SHOCK_MAX_CARRY;
		}
#endif

		MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
		WRITE_BYTE(m_iId);
		MESSAGE_END();
		return TRUE;
	}
	return FALSE;
}

int CShockrifle::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "Shocks";
	p->iMaxAmmo1 = SHOCK_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 6;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_SHOCKRIFLE;
	p->iFlags = ITEM_FLAG_NOAUTOSWITCHEMPTY | ITEM_FLAG_NOAUTORELOAD;
	p->iWeight = HORNETGUN_WEIGHT;

	return 1;
}


BOOL CShockrifle::Deploy()
{
#ifdef CLIENT_DLL
	if( bIsMultiplayer() )
#else
	if( g_pGameRules->IsMultiplayer() )
#endif
		m_flRechargeTime = gpGlobals->time + 0.25;
	else
		m_flRechargeTime = gpGlobals->time + 0.5;

	m_pPlayer->pev->maxspeed = 320;	
    m_pPlayer->pev->renderfx = kRenderFxGlowShell;
    m_pPlayer->pev->renderamt = 15;
    m_pPlayer->pev->rendercolor = Vector(0, 255, 255);

	return DefaultDeploy("models/v_shock.mdl", "models/p_shock.mdl", SHOCK_DRAW, "shockrifle");
}

#ifdef CLIENT_DLL
extern int g_irunninggausspred;
#endif

void CShockrifle::Holster(int skiplocal /* = 0 */)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
	SendWeaponAnim(SHOCK_HOLSTER);

    m_pPlayer->pev->renderfx = kRenderFxGlowShell;
    m_pPlayer->pev->renderamt = 0;
    m_pPlayer->pev->rendercolor = Vector(0, 0, 0);

	//!!!HACKHACK - can't select hornetgun if it's empty! no way to get ammo for it, either.
	if (!m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()])
	{
		m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] = 1;
	}
}

void CShockrifle::PrimaryAttack()
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return;

	if (m_pPlayer->pev->waterlevel == 3)
	{
#ifndef CLIENT_DLL
		int attenuation = 150 * m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
		int dmg = 100 * m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/shock_discharge.wav", VOL_NORM, ATTN_NORM);
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] = 0;
		RadiusDamage(m_pPlayer->pev->origin, m_pPlayer->pev, m_pPlayer->pev, dmg, attenuation, CLASS_NONE, DMG_SHOCK | DMG_ALWAYSGIB );
#endif
		return;
	}

	CreateChargeEffect();

#ifndef CLIENT_DLL
	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
	anglesAim.x = -anglesAim.x;
	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	Vector vecSrc;
	vecSrc = m_pPlayer->GetGunPosition() + gpGlobals->v_forward * 8 + gpGlobals->v_right * 12 + gpGlobals->v_up * -12;

	CShock::Shoot(m_pPlayer->pev, anglesAim, vecSrc, gpGlobals->v_forward * 2000);

	m_flRechargeTime = gpGlobals->time + 0.1;
#endif
	m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;


	m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usShockFire, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0);

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#ifdef CLIENT_DLL
	if( bIsMultiplayer() )
#else
	if( g_pGameRules->IsMultiplayer() )
#endif
		m_flNextPrimaryAttack = GetNextAttackDelay(0.1);
	else
		m_flNextPrimaryAttack = GetNextAttackDelay(0.1);

	SetThink( &CShockrifle::ClearBeams );
	pev->nextthink = gpGlobals->time + 0.08;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
}

void CShockrifle::SecondaryAttack(void)
{
#ifndef CLIENT_DLL	
	UTIL_ScreenFadeAll( Vector(0,255,255), 5, 0.3, 150, FFADE_IN );	
	UTIL_ScreenShake( pev->origin, 200.0, 200.0, 0.3, 200.0 );
#endif		
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return;

	if (m_pPlayer->pev->waterlevel == 3)
	{
#ifndef CLIENT_DLL
		int attenuation = 150 * m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
		int dmg = 100 * m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/shock_discharge.wav", VOL_NORM, ATTN_NORM);
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] = 0;
		RadiusDamage(m_pPlayer->pev->origin, m_pPlayer->pev, m_pPlayer->pev, dmg, attenuation, CLASS_NONE, DMG_SHOCK | DMG_ALWAYSGIB );
#endif
		return;
	}

	CreateChargeEffect2();	

#ifndef CLIENT_DLL
	Vector anglesAim = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
	anglesAim.x = -anglesAim.x;
	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	Vector vecSrc;
	vecSrc = m_pPlayer->GetGunPosition();

	UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );

	Vector vecAiming = m_pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );

	Fire( vecSrc, vecAiming, 50 );

	m_flRechargeTime = gpGlobals->time + 0.1;
#endif
	m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]-=2;


	m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usShockFire2, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0);

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#ifdef CLIENT_DLL
	if( bIsMultiplayer() )
#else
	if( g_pGameRules->IsMultiplayer() )
#endif
		m_flNextSecondaryAttack = GetNextAttackDelay(0.07);
	else
		m_flNextSecondaryAttack = GetNextAttackDelay(0.07);

	SetThink( &CShockrifle::ClearBeams );
	pev->nextthink = gpGlobals->time + 0.08;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
}

void StreakSplash4( const Vector &origin, const Vector &direction, int color, int count, int speed, int velocityRange )
{
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, origin );
		WRITE_BYTE( TE_STREAK_SPLASH );
		WRITE_COORD( origin.x );		// origin
		WRITE_COORD( origin.y );
		WRITE_COORD( origin.z );
		WRITE_COORD( direction.x );	// direction
		WRITE_COORD( direction.y );
		WRITE_COORD( direction.z );
		WRITE_BYTE( color );	// Streak color 6
		WRITE_SHORT( count );	// count
		WRITE_SHORT( speed );
		WRITE_SHORT( velocityRange );	// Random velocity modifier
	MESSAGE_END();
}

void CShockrifle::Fire( Vector vecOrigSrc, Vector vecDir, float flDamage )
{
	m_pPlayer->m_iWeaponVolume = SHOCKRIFLE_PRIMARY_FIRE_VOLUME;

	Vector vecSrc = vecOrigSrc;
	Vector vecDest = vecSrc + vecDir * 8192;
	edict_t		*pentIgnore;
	TraceResult tr, beam_tr;
    TraceResult	trace;	
	float flMaxFrac = 1.0;
	int	nTotal = 0;
	int fHasPunched = 0;
	int fFirstBeam = 1;
	int	nMaxHits = 10;

	pentIgnore = ENT( m_pPlayer->pev );

#ifdef CLIENT_DLL
	if ( m_fPrimaryFire == false )
		 g_irunninggausspred = true;
#endif
	
	/*ALERT( at_console, "%f %f %f\n%f %f %f\n", 
		vecSrc.x, vecSrc.y, vecSrc.z, 
		vecDest.x, vecDest.y, vecDest.z );*/
	

//	ALERT( at_console, "%f %f\n", tr.flFraction, flMaxFrac );

#ifndef CLIENT_DLL
	while (flDamage > 10 && nMaxHits > 0)
	{
		nMaxHits--;

		// ALERT( at_console, "." );
		UTIL_TraceLine(vecSrc, vecDest, dont_ignore_monsters, pentIgnore, &tr);

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, tr.vecEndPos );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(tr.vecEndPos.x);	// X
		WRITE_COORD(tr.vecEndPos.y);	// Y
		WRITE_COORD(tr.vecEndPos.z);	// Z
		WRITE_BYTE( 30 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 255 );		// b
		WRITE_BYTE( 255 );		// time * 10
		WRITE_BYTE( 25 );		// decay * 0.1
	    WRITE_BYTE( 1 );
	MESSAGE_END( );

		if (tr.fAllSolid)
			break;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		if (pEntity == NULL)
			break;

		if ( fFirstBeam )
		{
			m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
			fFirstBeam = 0;
	
			nTotal += 26;
		}

	    if (UTIL_PointContents(tr.vecEndPos) != CONTENTS_SKY)
		{
		if (tr.flFraction != 1.0)
		UTIL_DecalTrace(&tr, DECAL_SMALLSCORCH1 + RANDOM_LONG(0,2));
	    StreakSplash4( tr.vecEndPos, trace.vecPlaneNormal, 10, 50, 50, 500 );
		UTIL_Sparks(tr.vecEndPos);				
		}		

		if (pEntity->pev->takedamage)
		{
			ClearMultiDamage();
			pEntity->TraceAttack( m_pPlayer->pev, flDamage, vecDir, &tr, DMG_ENERGYBEAM | DMG_ALWAYSGIB );
			ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);
		}
	}
#endif
	// ALERT( at_console, "%d bytes\n", nTotal );
}

void CShockrifle::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] >= SHOCK_MAX_CARRY)
		return;

	while (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] < SHOCK_MAX_CARRY && m_flRechargeTime < gpGlobals->time)
	{
		EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/shock_recharge.wav", 1, ATTN_NORM);

		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]++;
#ifndef CLIENT_DLL
		if( g_pGameRules->IsMultiplayer() )
			m_flRechargeTime += 0.3;
		else
			m_flRechargeTime += 0.3;
#endif
	}
}

void CShockrifle::WeaponIdle(void)
{
	Reload();

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	float flRand = UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0, 1);
	if (flRand <= 0.8) {
		SendWeaponAnim(SHOCK_IDLE3);
	} else {
		SendWeaponAnim(SHOCK_IDLE1);
	}
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.3f;
}

void CShockrifle::CreateChargeEffect( void )
{
#ifndef CLIENT_DLL
	if( g_pGameRules->IsMultiplayer())
		return;
	int iBeam = 0;

	for( int i = 2; i < 5; i++)
	{
		if( !m_pBeam[iBeam] )
			m_pBeam[iBeam] = CBeam::BeamCreate("sprites/lgtning.spr", 16);
		m_pBeam[iBeam]->EntsInit( m_pPlayer->entindex(), m_pPlayer->entindex() );
		m_pBeam[iBeam]->SetStartAttachment(1);
		m_pBeam[iBeam]->SetEndAttachment(i);
		m_pBeam[iBeam]->SetNoise( 75 );
		m_pBeam[iBeam]->pev->scale= 10;
		m_pBeam[iBeam]->SetColor( 0, 253, 253 );
		m_pBeam[iBeam]->SetScrollRate( 30 );
		m_pBeam[iBeam]->SetBrightness( 190 );
		iBeam++;
	}
#endif
}

void CShockrifle::CreateChargeEffect2( void )
{
#ifndef CLIENT_DLL
	if( g_pGameRules->IsMultiplayer())
		return;
	int iBeam = 0;

	for( int i = 2; i < 5; i++)
	{
		if( !m_pBeam[iBeam] )
			m_pBeam[iBeam] = CBeam::BeamCreate("sprites/lgtning.spr", 1000);
		m_pBeam[iBeam]->PointEntInit( m_pPlayer->GetGunPosition() + gpGlobals->v_forward * 500, m_pPlayer->entindex() );
		m_pBeam[iBeam]->SetStartAttachment(1);
		m_pBeam[iBeam]->SetEndAttachment(i);
		m_pBeam[iBeam]->SetNoise( 75 );
		m_pBeam[iBeam]->pev->scale= 10;
		m_pBeam[iBeam]->SetColor( 0, 253, 253 );
		m_pBeam[iBeam]->SetScrollRate( 30 );
		m_pBeam[iBeam]->SetBrightness( 190 );
		iBeam++;	
	}
#endif
}

void CShockrifle::ClearBeams( void )
{
#ifndef CLIENT_DLL
	if( g_pGameRules->IsMultiplayer())
		return;

	for( int i = 0; i < 3; i++ )
	{
		if( m_pBeam[i] )
		{
			UTIL_Remove( m_pBeam[i] );
			m_pBeam[i] = NULL;
		}
	}
	SetThink( NULL );
#endif
}

#endif
