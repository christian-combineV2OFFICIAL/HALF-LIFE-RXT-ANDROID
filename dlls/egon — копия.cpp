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
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "soundent.h"
#include "shake.h"
#include "gamerules.h"
#include "decals.h"


#define	EGON_PRIMARY_CHARGE_VOLUME	256// how loud egon is while charging
#define EGON_PRIMARY_FIRE_VOLUME	450// how loud egon is when discharged

enum egon_e {
	EGON_IDLE1,
	EGON_FIRE_ALL,
	EGON_FIRE_ALL_SOLID,
	EGON_FIRE_BARREL1,
	EGON_FIRE_BARREL2,
	EGON_FIRE_BARREL3,
	EGON_FIRE_BARREL4,
	EGON_FIRE_BARREL1_SOLID,
	EGON_FIRE_BARREL2_SOLID,
	EGON_FIRE_BARREL3_SOLID,
	EGON_FIRE_BARREL4_SOLID,
	EGON_RELOAD,
	EGON_DRAW,
	EGON_HOLSTER
};

LINK_ENTITY_TO_CLASS( weapon_egon, CEgon );

float CEgon::GetFullChargeTime( void )
{
#ifdef CLIENT_DLL
	if ( bIsMultiplayer() )
#else
	if ( g_pGameRules->IsMultiplayer() )
#endif
	{
		return 1.5;
	}

	return 4;
}

#ifdef CLIENT_DLL
extern int g_irunningegonpred;
#endif

void CEgon::Spawn( )
{
	Precache( );
	m_iId = WEAPON_EGON;
	SET_MODEL(ENT(pev), "models/w_photongun.mdl");

	m_iDefaultAmmo = PHOTON_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CEgon::Precache( void )
{
	PRECACHE_MODEL("models/w_photongun.mdl");
	PRECACHE_MODEL("models/v_photongun.mdl");
	PRECACHE_MODEL("models/p_photongun.mdl");
    PRECACHE_MODEL ("models/w_photongunammo.mdl");
    PRECACHE_MODEL ("models/null.mdl");

	PRECACHE_SOUND("items/9mmclip1.wav");

	PRECACHE_SOUND("weapons/photongun_fire.wav");
	PRECACHE_SOUND("weapons/photongun_fire2.wav");
	PRECACHE_SOUND("weapons/photon_hitwall.wav");	
	PRECACHE_SOUND("weapons/photon_hitwall2.wav");
	PRECACHE_SOUND("weapons/DOOM.wav");

	m_iGlow = PRECACHE_MODEL( "sprites/hotglowblue.spr" );
	m_iGlow2 = PRECACHE_MODEL( "sprites/anim_spr3.spr" );//precache the sprite for disc		
	m_iBalls = PRECACHE_MODEL( "sprites/hotglowblue.spr" );
	m_iBeam = PRECACHE_MODEL( "sprites/anim_spr3.spr" );
	m_iModelSprite = PRECACHE_MODEL( "sprites/ef_smoke_poison_blue.spr" );
    m_iModelSprite2 = PRECACHE_MODEL( "sprites/white.spr" );//precache the sprite for disc
	m_iMazzleFlash1 = PRECACHE_MODEL( "sprites/particlebluephotongun.spr" );
	m_iMazzleFlash2 = PRECACHE_MODEL( "sprites/particlebluephotongun.spr" );
	m_iMazzleFlash3 = PRECACHE_MODEL( "sprites/particlebluephotongun.spr" );
	m_iMazzleFlash4 = PRECACHE_MODEL( "sprites/particlebluephotongun.spr" );
	m_iMazzleFlash2_1 = PRECACHE_MODEL( "sprites/anim_spr2_violet.spr" );
	m_iMazzleFlash2_2 = PRECACHE_MODEL( "sprites/anim_spr2_violet.spr" );
	m_iMazzleFlash2_3 = PRECACHE_MODEL( "sprites/anim_spr2_violet.spr" );
	m_iMazzleFlash2_4 = PRECACHE_MODEL( "sprites/anim_spr2_violet.spr" );

	m_usEgonFire = PRECACHE_EVENT( 1, "events/egon_fire.sc" );
	m_usEgonFire2 = PRECACHE_EVENT( 1, "events/egon_fire2.sc" );	
	m_usEgonFire3 = PRECACHE_EVENT( 1, "events/egon_fire3.sc" );		
	m_usEgonFire4 = PRECACHE_EVENT( 1, "events/egon_fire4.sc" );
	m_usEgonFire2_1 = PRECACHE_EVENT( 1, "events/egon_fire2_1.sc" );
	m_usEgonFire2_2 = PRECACHE_EVENT( 1, "events/egon_fire2_2.sc" );	
	m_usEgonFire2_3 = PRECACHE_EVENT( 1, "events/egon_fire2_3.sc" );		
	m_usEgonFire2_4 = PRECACHE_EVENT( 1, "events/egon_fire2_4.sc" );	
	m_usEgonSpin = PRECACHE_EVENT( 1, "events/egon_fire_spin.sc" );
}

int CEgon::AddToPlayer( CBasePlayer *pPlayer )
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

int CEgon::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "photon";
	p->iMaxAmmo1 = PHOTON_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = PHOTON_MAX_CLIP;
	p->iSlot = 3;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_EGON;
	p->iFlags = 0;
	p->iWeight = EGON_WEIGHT;

	return 1;
}

BOOL CEgon::Deploy( )
{
	m_pPlayer->pev->maxspeed = 320;	
	// Stop music sound
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/DOOM.wav" );	
	// Start music sound
    EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/DOOM.wav", 1.0, ATTN_NORM );			
	return DefaultDeploy( "models/v_photongun.mdl", "models/p_photongun.mdl", EGON_DRAW, "egon" );
}

void CEgon::Holster( int skiplocal /* = 0 */ )
{
	PLAYBACK_EVENT_FULL( FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usEgonFire, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );
	PLAYBACK_EVENT_FULL( FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usEgonFire2, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );	
	PLAYBACK_EVENT_FULL( FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usEgonFire3, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );
	PLAYBACK_EVENT_FULL( FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usEgonFire4, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );	

	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.8;
	
	SendWeaponAnim( EGON_HOLSTER );
	m_fInAttack = 0;
}


void CEgon::PrimaryAttack()
{
#ifndef CLIENT_DLL	
	UTIL_ScreenFadeAll( Vector(0,0,255), 5, 0.5, 150, FFADE_IN );
#endif		
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = 0.5;
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();
		PlayEmptySound();
		m_flNextPrimaryAttack = 0.5;
		return;
	}

	m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_FIRE_VOLUME;
	m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
	m_fPrimaryFire = TRUE;

	m_iClip--;

#ifndef CLIENT_DLL
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 250.0 );
#endif	
	
	StartFire();
	m_fInAttack = 0;
	m_pPlayer->pev->punchangle.x -= RANDOM_FLOAT(0.5,1.5);
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.09;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 5.0;

#ifndef CLIENT_DLL
		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 500 + gpGlobals->v_right * 8 + gpGlobals->v_up * -8;
		
		CDlight *pDlight = CDlight::CreateDlight( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );// RpgRocket::Create stomps on globals, so remake.
		pDlight->pev->velocity = pDlight->pev->velocity + gpGlobals->v_forward * DotProduct( m_pPlayer->pev->velocity, gpGlobals->v_forward );
#endif
}

void CEgon::SecondaryAttack()
{
#ifndef CLIENT_DLL	
	UTIL_ScreenFadeAll( Vector(255,0,255), 5, 0.5, 150, FFADE_IN );
#endif		
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextSecondaryAttack = 0.5;
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();
		PlayEmptySound();
		m_flNextSecondaryAttack = 0.5;
		return;
	}

	m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_FIRE_VOLUME;
	m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
	m_fPrimaryFire = TRUE;

	m_iClip--;

#ifndef CLIENT_DLL
	UTIL_ScreenShake( pev->origin, 10.0, 15.0, 0.75, 25.0 );
#endif	
	
	StartFire2();
	m_fInAttack = 0;
	m_pPlayer->pev->punchangle.x -= RANDOM_FLOAT(0.5,1.8);
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.1;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 5.0;

#ifndef CLIENT_DLL
		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 500 + gpGlobals->v_right * 8 + gpGlobals->v_up * -8;
		
		CDlight2 *pDlight2 = CDlight2::CreateDlight2( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer, this );

		UTIL_MakeVectors( m_pPlayer->pev->v_angle );// RpgRocket::Create stomps on globals, so remake.
		pDlight2->pev->velocity = pDlight2->pev->velocity + gpGlobals->v_forward * DotProduct( m_pPlayer->pev->velocity, gpGlobals->v_forward );
#endif
}

//=========================================================
// StartFire- since all of this code has to run and then 
// call Fire(), it was easier at this point to rip it out 
// of weaponidle() and make its own function then to try to
// merge this into Fire(), which has some identical variable names 
//=========================================================
void CEgon::StartFire( void )
{
	float flDamage;
	
	UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );
	Vector vecAiming = gpGlobals->v_forward;
	Vector vecSrc = m_pPlayer->GetGunPosition( ); // + gpGlobals->v_up * -8 + gpGlobals->v_right * 8;

	if ( gpGlobals->time - m_pPlayer->m_flStartCharge > GetFullChargeTime() )
	{
		flDamage = 200;
	}
	else
	{
		flDamage = 200 * (( gpGlobals->time - m_pPlayer->m_flStartCharge) / GetFullChargeTime() );
	}

	if ( m_fPrimaryFire )
	{
		// fixed damage on primary attack
#ifdef CLIENT_DLL
		flDamage = 20;
#else 
		flDamage = gSkillData.plrDmgGauss;
#endif
	}

	if (m_fInAttack != 3)
	{
		//ALERT ( at_console, "Time:%f Damage:%f\n", gpGlobals->time - m_pPlayer->m_flStartCharge, flDamage );

#ifndef CLIENT_DLL
		float flZVel = m_pPlayer->pev->velocity.z;

		if ( !m_fPrimaryFire )
		{
			m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * flDamage * 5;
		}

		if ( !g_pGameRules->IsMultiplayer() )

		{
			// in deathmatch, gauss can pop you up into the air. Not in single play.
			m_pPlayer->pev->velocity.z = flZVel;
		}
#endif
		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
	}

	// time until aftershock 'static discharge' sound
	m_pPlayer->m_flPlayAftershock = gpGlobals->time + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 0.3, 0.8 );

	Fire( vecSrc, vecAiming, flDamage );
}

//=========================================================
// StartFire- since all of this code has to run and then 
// call Fire(), it was easier at this point to rip it out 
// of weaponidle() and make its own function then to try to
// merge this into Fire(), which has some identical variable names 
//=========================================================
void CEgon::StartFire2( void )
{
	float flDamage;
	
	UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );
	Vector vecAiming = gpGlobals->v_forward;
	Vector vecSrc = m_pPlayer->GetGunPosition( ); // + gpGlobals->v_up * -8 + gpGlobals->v_right * 8;

	if ( gpGlobals->time - m_pPlayer->m_flStartCharge > GetFullChargeTime() )
	{
		flDamage = 200;
	}
	else
	{
		flDamage = 200 * (( gpGlobals->time - m_pPlayer->m_flStartCharge) / GetFullChargeTime() );
	}

	if ( m_fPrimaryFire )
	{
		// fixed damage on primary attack
#ifdef CLIENT_DLL
		flDamage = 20;
#else 
		flDamage = gSkillData.plrDmgGauss;
#endif
	}

	if (m_fInAttack != 3)
	{
		//ALERT ( at_console, "Time:%f Damage:%f\n", gpGlobals->time - m_pPlayer->m_flStartCharge, flDamage );

#ifndef CLIENT_DLL
		float flZVel = m_pPlayer->pev->velocity.z;

		if ( !m_fPrimaryFire )
		{
			m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * flDamage * 5;
		}

		if ( !g_pGameRules->IsMultiplayer() )

		{
			// in deathmatch, gauss can pop you up into the air. Not in single play.
			m_pPlayer->pev->velocity.z = flZVel;
		}
#endif
		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );
	}

	// time until aftershock 'static discharge' sound
	m_pPlayer->m_flPlayAftershock = gpGlobals->time + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 0.3, 0.8 );

	Fire2( vecSrc, vecAiming, flDamage );
}

void CEgon::Fire( Vector vecOrigSrc, Vector vecDir, float flDamage )
{
	m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_FIRE_VOLUME;

	Vector vecSrc = vecOrigSrc;
	Vector vecDest = vecSrc + vecDir * 8192;
	edict_t		*pentIgnore;
	TraceResult tr, beam_tr;
	float flMaxFrac = 1.0;
	int	nTotal = 0;
	int fHasPunched = 0;
	int fFirstBeam = 1;
	int	nMaxHits = 10;

	pentIgnore = ENT( m_pPlayer->pev );

#ifdef CLIENT_DLL
	if ( m_fPrimaryFire == false )
		 g_irunningegonpred = true;
#endif

	// The main firing event is sent unreliably so it won't be delayed.
	m_iFirePhase++;
	switch ( m_iFirePhase )
	{
	case 1:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 2:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire2, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 3:
		PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire3, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 4:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire4, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		m_iFirePhase = 0;
		break;
	}
	
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

	    Vector vecSrc = m_pPlayer->GetGunPosition( ); // + gpGlobals->v_up * -8 + gpGlobals->v_right * 8;

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecSrc );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(vecSrc.x);	// X
		WRITE_COORD(vecSrc.y);	// Y
		WRITE_COORD(vecSrc.z);	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 255 );		// b
		WRITE_BYTE( 255 );		// brightness 
		WRITE_BYTE( 25 );		// time * 10
	    WRITE_BYTE( 1 );        // decay * 0.1
	MESSAGE_END( );

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( tr.vecEndPos.x );
    WRITE_COORD( tr.vecEndPos.y );
    WRITE_COORD( tr.vecEndPos.z );
    WRITE_SHORT( m_iModelSprite );
    WRITE_BYTE( 7 );
    WRITE_BYTE( 20 );
    MESSAGE_END();

	// blast circle "The Infamous Disc of Death"
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, tr.vecEndPos );
	WRITE_BYTE( TE_BEAMCYLINDER );
	WRITE_COORD( tr.vecEndPos.x);//center of effect on x axis
	WRITE_COORD( tr.vecEndPos.y);//center of effect on y axis
	WRITE_COORD( tr.vecEndPos.z + 5);//center of effect on z axis
	WRITE_COORD( tr.vecEndPos.x);//axis of effect on x axis
	WRITE_COORD( tr.vecEndPos.y);//axis of effect on y axis
	WRITE_COORD( tr.vecEndPos.z + 300 ); // z axis and Radius of effect
	WRITE_SHORT( m_iModelSprite2 );//Name of the sprite to use, as defined at begining of tut
	WRITE_BYTE( 0 ); // startframe
	WRITE_BYTE( 0 ); //framerate in 0.1's
	WRITE_BYTE( 3 ); //Life in 0.1's
	WRITE_BYTE( 10 ); //Line Width in .1 units
	WRITE_BYTE( 0 ); //Noise Amplitude in 0.01's
	WRITE_BYTE( 0 ); // Red Color Value
	WRITE_BYTE( 0 ); // Green Color Value
	WRITE_BYTE( 255 ); // Blue Color Value
	WRITE_BYTE( 100 ); // brightness
	WRITE_BYTE( 0 ); // speed
	MESSAGE_END();

	UTIL_ScreenShake( tr.vecEndPos, 12.0, 10.0, 2.0, 100 );

	UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH3 + RANDOM_LONG(0,0) );

    ::RadiusDamage( tr.vecEndPos, pev, NULL, 30, 130, CLASS_NONE, DMG_BLAST|DMG_ALWAYSGIB );

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
		
		if (pEntity->pev->takedamage)
		{
			ClearMultiDamage();
			pEntity->TraceAttack( m_pPlayer->pev, flDamage, vecDir, &tr, DMG_BULLET );
			ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);
		}
	}
#endif
	// ALERT( at_console, "%d bytes\n", nTotal );
}

void CEgon::Fire2( Vector vecOrigSrc, Vector vecDir, float flDamage )
{
	m_pPlayer->m_iWeaponVolume = EGON_PRIMARY_FIRE_VOLUME;

	Vector vecSrc = vecOrigSrc;
	Vector vecDest = vecSrc + vecDir * 8192;
	edict_t		*pentIgnore;
	TraceResult tr, beam_tr;
	float flMaxFrac = 1.0;
	int	nTotal = 0;
	int fHasPunched = 0;
	int fFirstBeam = 1;
	int	nMaxHits = 10;

	pentIgnore = ENT( m_pPlayer->pev );

#ifdef CLIENT_DLL
	if ( m_fPrimaryFire == false )
		 g_irunningegonpred = true;
#endif

	// The main firing event is sent unreliably so it won't be delayed.
	m_iFirePhase++;
	switch ( m_iFirePhase )
	{
	case 1:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire2_1, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 2:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire2_2, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 3:
		PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire2_3, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		break;
	case 4:
	    PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usEgonFire2_4, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );
		m_iFirePhase = 0;
		break;
	}
	
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

	    Vector vecSrc = m_pPlayer->GetGunPosition( ); // + gpGlobals->v_up * -8 + gpGlobals->v_right * 8;

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecSrc );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(vecSrc.x);	// X
		WRITE_COORD(vecSrc.y);	// Y
		WRITE_COORD(vecSrc.z);	// Z
		WRITE_BYTE( 10 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 255 );		// b
		WRITE_BYTE( 255 );		// brightness 
		WRITE_BYTE( 25 );		// time * 10
	    WRITE_BYTE( 1 );        // decay * 0.1
	MESSAGE_END( );

	// blast circle "The Infamous Disc of Death"
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, tr.vecEndPos );
	WRITE_BYTE( TE_BEAMCYLINDER );
	WRITE_COORD( tr.vecEndPos.x);//center of effect on x axis
	WRITE_COORD( tr.vecEndPos.y);//center of effect on y axis
	WRITE_COORD( tr.vecEndPos.z + 5);//center of effect on z axis
	WRITE_COORD( tr.vecEndPos.x);//axis of effect on x axis
	WRITE_COORD( tr.vecEndPos.y);//axis of effect on y axis
	WRITE_COORD( tr.vecEndPos.z + 300 ); // z axis and Radius of effect
	WRITE_SHORT( m_iModelSprite2 );//Name of the sprite to use, as defined at begining of tut
	WRITE_BYTE( 0 ); // startframe
	WRITE_BYTE( 0 ); //framerate in 0.1's
	WRITE_BYTE( 2 ); //Life in 0.1's
	WRITE_BYTE( 10 ); //Line Width in .1 units
	WRITE_BYTE( 0 ); //Noise Amplitude in 0.01's
	WRITE_BYTE( 255 ); // Red Color Value
	WRITE_BYTE( 0 ); // Green Color Value
	WRITE_BYTE( 255 ); // Blue Color Value
	WRITE_BYTE( 100 ); // brightness
	WRITE_BYTE( 0 ); // speed
	MESSAGE_END();

	UTIL_ScreenShake( tr.vecEndPos, 10.0, 10.0, 2.0, 50 );

	UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 + RANDOM_LONG(0,0));

    ::RadiusDamage( tr.vecEndPos, pev, NULL, 15, 100, CLASS_NONE, DMG_BLAST|DMG_ALWAYSGIB );

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
		
		if (pEntity->pev->takedamage)
		{
			ClearMultiDamage();
			pEntity->TraceAttack( m_pPlayer->pev, flDamage, vecDir, &tr, DMG_BULLET );
			ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);
		}
	}
#endif
	// ALERT( at_console, "%d bytes\n", nTotal );
}

void CEgon::Reload( void )
{
	if (m_iClip)
	return;

	DefaultReload( 60, EGON_RELOAD, 4.7, 2.1 );
}

void CEgon::WeaponIdle( void )
{
	ResetEmptySound( );

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

		int iAnim;
		float flRand = RANDOM_FLOAT(0, 1);
		if (flRand <= 0.5)
		{
			iAnim = EGON_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 );
		}
		else if (flRand <= 0.75)
		{
			iAnim = EGON_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 );
		}
		else
		{
			iAnim = EGON_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3;
		}

		return;
		SendWeaponAnim( iAnim );
}






class CEgonAmmo : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_photongunammo.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_photongunammo.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		if (pOther->GiveAmmo( AMMO_PHOTONBOX_GIVE, "photon", PHOTON_MAX_CARRY ) != -1)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
			return TRUE;
		}
		return FALSE;
	}
};
LINK_ENTITY_TO_CLASS( ammo_photonclip, CEgonAmmo );

#endif
