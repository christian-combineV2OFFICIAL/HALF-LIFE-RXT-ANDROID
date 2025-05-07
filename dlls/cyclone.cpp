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


#define	CYCLONE_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define CYCLONE_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum cyclone_e {
	CYCLONE_IDLE = 0,
	CYCLONE_SHOOT1,
	CYCLONE_SHOOT_END,
    CYCLONE_RELOAD,	
	CYCLONE_DRAW
};

LINK_ENTITY_TO_CLASS( weapon_cyclone, CCyclone );

float CCyclone::GetFullChargeTime( void )
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
extern int g_irunningcyclonepred;
#endif

void CCyclone::Spawn( )
{
	Precache( );
	m_iId = WEAPON_CYCLONE;
	SET_MODEL(ENT(pev), "models/w_cyclon.mdl");

	m_iDefaultAmmo = CYCLONE_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CCyclone::Precache( void )
{
	PRECACHE_MODEL("models/w_cyclon.mdl");
	PRECACHE_MODEL("models/v_cyclon.mdl");
	PRECACHE_MODEL("models/p_cyclon.mdl");

	PRECACHE_SOUND("items/9mmclip1.wav");

	PRECACHE_SOUND("weapons/sfpistol_shoot1.wav");
	PRECACHE_SOUND("weapons/sfpistol_idle.wav");

	m_iGlow = PRECACHE_MODEL( "sprites/ef_smoke_poison.spr" );
	m_iBeam = PRECACHE_MODEL( "sprites/zbeam4.spr" );

	m_usCycloneFire = PRECACHE_EVENT( 1, "events/cyclone.sc" );
	m_usCycloneSpin = PRECACHE_EVENT( 1, "events/cyclonespin.sc" );
}

int CCyclone::AddToPlayer( CBasePlayer *pPlayer )
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

int CCyclone::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "cyclone";
	p->iMaxAmmo1 = CYCLONE_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = CYCLONE_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_CYCLONE;
	p->iFlags = 0;
	p->iWeight = CYCLONE_WEIGHT;

	return 1;
}

BOOL CCyclone::Deploy( )
{
	m_pPlayer->pev->maxspeed = 320;
	m_pPlayer->m_flPlayAftershock = 0.0;
	return DefaultDeploy( "models/v_cyclon.mdl", "models/p_cyclon.mdl", CYCLONE_DRAW, "cyclone" );
}

void CCyclone::Holster( int skiplocal /* = 0 */ )
{
	PLAYBACK_EVENT_FULL( FEV_RELIABLE | FEV_GLOBAL, m_pPlayer->edict(), m_usCycloneFire, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );
	
	// Stop idle and fire sound
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/sfpistol_idle.wav" );
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/sfpistol_shoot1.wav" );

	m_fInAttack = 0;
}


void CCyclone::PrimaryAttack()
{
	// don't fire underwater
	if ( m_pPlayer->pev->waterlevel == 3 )
	{
		PlayEmptySound( );
		m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.10;
		return;
	}

	if (m_iClip <= 0)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = 0.10;
		return;
	}

	m_pPlayer->m_iWeaponVolume = CYCLONE_PRIMARY_FIRE_VOLUME;
	m_fPrimaryFire = TRUE;

	m_iClip--;

	SendWeaponAnim( CYCLONE_SHOOT_END );

	StartFire();
	m_fInAttack = 0;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.0;
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.10;	
    EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/sfpistol_shoot1.wav", 0.98, ATTN_NORM, 0, 125);
}

void CCyclone::Reload( void )
{
	DefaultReload( CYCLONE_MAX_CLIP, CYCLONE_RELOAD, 2.75 );
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/sfpistol_shoot1.wav" );
}


void CCyclone::SecondaryAttack()
{
}

//=========================================================
// StartFire- since all of this code has to run and then 
// call Fire(), it was easier at this point to rip it out 
// of weaponidle() and make its own function then to try to
// merge this into Fire(), which has some identical variable names 
//=========================================================
void CCyclone::StartFire()
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
		flDamage = gSkillData.plrDmgCyclone;
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

void CCyclone::Fire( Vector vecOrigSrc, Vector vecDir, float flDamage )
{
	m_pPlayer->m_iWeaponVolume = CYCLONE_PRIMARY_FIRE_VOLUME;

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
		 g_irunningcyclonepred = true;
#endif
	
	// The main firing event is sent unreliably so it won't be delayed.
	PLAYBACK_EVENT_FULL( FEV_NOTHOST, m_pPlayer->edict(), m_usCycloneFire, 0.0, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, flDamage, 0.0, 0, 0, m_fPrimaryFire ? 1 : 0, 0 );

	// This reliable event is used to stop the spinning sound
	// It's delayed by a fraction of second to make sure it is delayed by 1 frame on the client
	// It's sent reliably anyway, which could lead to other delays

	PLAYBACK_EVENT_FULL( FEV_NOTHOST | FEV_RELIABLE, m_pPlayer->edict(), m_usCycloneFire, 0.01, (float *)&m_pPlayer->pev->origin, (float *)&m_pPlayer->pev->angles, 0.0, 0.0, 0, 0, 0, 1 );

	
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
		WRITE_BYTE( 7 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 255 );		// time * 10
		WRITE_BYTE( 25 );		// decay * 0.1
	    WRITE_BYTE( 1 );
	MESSAGE_END( );

	MESSAGE_BEGIN(MSG_BROADCAST ,SVC_TEMPENTITY);
	    WRITE_BYTE(TE_EXPLOSION);
		WRITE_COORD(tr.vecEndPos.x);	// X
		WRITE_COORD(tr.vecEndPos.y);	// Y
		WRITE_COORD(tr.vecEndPos.z);	// Z
	    WRITE_SHORT(m_iGlow);	// sprite index
	    WRITE_BYTE(2);	// scale in 0.1's
	    WRITE_BYTE(30);	// framerate
	    WRITE_BYTE(TE_EXPLFLAG_NODLIGHTS | TE_EXPLFLAG_NOPARTICLES | TE_EXPLFLAG_NOSOUND);	// flags
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




void CCyclone::WeaponIdle( void )
{
	ResetEmptySound( );
	
	if (m_flTimeWeaponIdle > 0.0)
	{	
		return;
	}

	SendWeaponAnim(CYCLONE_IDLE);
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 10.0;
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/sfpistol_shoot1.wav" );
}






class CCycloneAmmo : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_ammo_cyclon.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_ammo_cyclon.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		if (pOther->GiveAmmo( AMMO_CYCLONEBOX_GIVE, "cyclone", CYCLONE_MAX_CARRY ) != -1)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
			return TRUE;
		}
		return FALSE;
	}
};
LINK_ENTITY_TO_CLASS( ammo_cycloneclip, CCycloneAmmo );

#endif
