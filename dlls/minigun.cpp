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

// special deathmatch shotgun spreads
#define VECTOR_CONE_DM_MINIGUN	Vector( 0.08716, 0.04362, 0.00  )// 10 degrees by 5 degrees
#define VECTOR_CONE_DM_DOUBLEMINIGUN Vector( 0.17365, 0.04362, 0.00 ) // 20 degrees by 5 degrees

enum minigun_e {
	MINIGUN_IDLE1,
	MINIGUN_IDLE2,
	MINIGUN_SPINUP,
	MINIGUN_SPINDOWN,
	MINIGUN_FIRE,
	MINIGUN_FIRE_SOLID,
	MINIGUN_RELOAD,
	MINIGUN_DRAW,
	MINIGUN_HOLSTER,
	MINIGUN_SPIN
};

LINK_ENTITY_TO_CLASS( weapon_minigun, CMinigun );

void CMinigun::Spawn( )
{
	Precache( );
	m_iId = WEAPON_MINIGUN;
	SET_MODEL(ENT(pev), "models/w_minigun.mdl");

	m_iDefaultAmmo = MINIGUN_DEFAULT_GIVE;

	FallInit();// get ready to fall
}


void CMinigun::Precache( void )
{
	PRECACHE_MODEL("models/v_minigun.mdl");
	PRECACHE_MODEL("models/w_minigun.mdl");
	PRECACHE_MODEL("models/p_minigun.mdl");

	m_iShell = PRECACHE_MODEL ("models/shell.mdl");// shotgun shell

	PRECACHE_SOUND("items/9mmclip1.wav");              

	PRECACHE_SOUND ("weapons/dbarrel1.wav");//shotgun
	PRECACHE_SOUND ("weapons/sbarrel1.wav");//shotgun

	PRECACHE_SOUND ("weapons/reload1.wav");	// shotgun reload
	PRECACHE_SOUND ("weapons/reload3.wav");	// shotgun reload

//	PRECACHE_SOUND ("weapons/sshell1.wav");	// shotgun reload - played on client
//	PRECACHE_SOUND ("weapons/sshell3.wav");	// shotgun reload - played on client

////музыка/////////////
	PRECACHE_SOUND("weapons/MINIGUNMUSIC/TERMINATOR.wav");	
////конец музыки///////

	PRECACHE_SOUND ("weapons/357_cock1.wav"); // gun empty sound
	PRECACHE_SOUND ("weapons/scock1.wav");	// cock gun
	PRECACHE_SOUND ("weapons/minigun_fire.wav");
	PRECACHE_SOUND ("weapons/minigun_reload.wav");
	PRECACHE_SOUND ("weapons/minigun_spin.wav");
	PRECACHE_SOUND ("weapons/minigun_spindown.wav");
	PRECACHE_SOUND ("weapons/minigun_spinup.wav");

	m_iMazzleFlash = PRECACHE_MODEL("sprites/muzzleflashminigun.spr");
	m_iMazzleSmoke = PRECACHE_MODEL("sprites/ballsmoke.spr");

	m_usMinigunFire = PRECACHE_EVENT( 1, "events/minigun1.sc" );
}

int CMinigun::AddToPlayer( CBasePlayer *pPlayer )
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


int CMinigun::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "minigun";
	p->iMaxAmmo1 = MINIGUN_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = MINIGUN_MAX_CLIP;
	p->iSlot = 2;
	p->iPosition = 5;
	p->iFlags = 0;
	p->iId = m_iId = WEAPON_MINIGUN;
	p->iWeight = MINIGUN_WEIGHT;

	return 1;
}



BOOL CMinigun::Deploy( )
{
	m_iFirePhase++;
	switch ( m_iFirePhase )
	{
	case 1:			
	// Start music sound
    EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/MINIGUNMUSIC/TERMINATOR.wav", 1.0, ATTN_NORM );		  	   
		break;
	case 2:	  				 
	// Stop music sound
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/MINIGUNMUSIC/TERMINATOR.wav" );
	m_iFirePhase = 1;
	break;	
	}			
	
	return DefaultDeploy( "models/v_minigun.mdl", "models/p_minigun.mdl", MINIGUN_DRAW, "minigun" );
}

void CMinigun::Holster( )
{
	m_fInReload = FALSE;
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.85;
	SendWeaponAnim( MINIGUN_HOLSTER );
}

void CMinigun::DoubleAttack()
{
     PrimaryAttack();
}

void CMinigun::PrimaryAttack()
{
	if ( m_fInAttack == 0)
	{
		if (m_pPlayer->pev->waterlevel == 3 || m_iClip <= 0)
	 	{
			PlayEmptySound( );
			m_flNextPrimaryAttack = gpGlobals->time + 0.5;
			return;
		}

		// spin up
		SendWeaponAnim(MINIGUN_SPINUP);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
		m_fInAttack = 1;
	}
	else if (m_fInAttack == 1)
	{
		if ( m_iClip <= 0 )
		{
			WeaponIdle();
			return;
		}
		if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
			m_fInAttack = 2;
	}
	else if (m_fInAttack == 2)
	{
		if ( m_iClip <= 0 )
		{
			WeaponIdle();
			return;
		}
		if ( m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
		{
			UTIL_MakeVectors (m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
			float flZVel = m_pPlayer->pev->velocity.z;
			m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * 50;
			m_pPlayer->pev->velocity.z = flZVel;

			m_iClip --;
			m_iFiredAmmo++;
			m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

				if ( gpGlobals->time >= m_flShockTime )
				{
					SendWeaponAnim((m_pPlayer->pev)?MINIGUN_FIRE_SOLID:MINIGUN_FIRE);
					m_flShockTime = gpGlobals->time + 0.15;
				}

			UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
			
	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif


	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;

	Vector vecSrc	 = m_pPlayer->GetGunPosition( );
	Vector vecAiming = m_pPlayer->GetAutoaimVector( AUTOAIM_5DEGREES );

	Vector vecDir;

#ifdef CLIENT_DLL
	if ( bIsMultiplayer() )
#else
	if ( g_pGameRules->IsMultiplayer() )
#endif
	{
		vecDir = m_pPlayer->FireBulletsPlayer( 4, vecSrc, vecAiming, VECTOR_CONE_DM_MINIGUN, 2048, BULLET_PLAYER_BUCKSHOT, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed );
	}
	else
	{
		// regular old, untouched spread. 
		vecDir = m_pPlayer->FireBulletsPlayer( 6, vecSrc, vecAiming, VECTOR_CONE_10DEGREES, 2048, BULLET_PLAYER_BUCKSHOT, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed );
	}

	PLAYBACK_EVENT_FULL( flags, m_pPlayer->edict(), m_usMinigunFire, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, 0, 0, 0, 0 );			
		
	#ifndef CLIENT_DLL
	UTIL_ScreenShake( pev->origin, 50.0, 200.0, 0.75, 300.0 );

	Vector vecSrcMazzle = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 50 + gpGlobals->v_right * 8 + gpGlobals->v_up * -12;

	TraceResult tr;
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, vecSrcMazzle );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( vecSrcMazzle.x );	// Send to PAS because of the sound
		WRITE_COORD( vecSrcMazzle.y );
		WRITE_COORD( vecSrcMazzle.z );
		WRITE_SHORT( m_iMazzleFlash );
		WRITE_BYTE( 5 ); // scale * 10
		WRITE_BYTE( 50 ); // framerate
	MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, vecSrcMazzle );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( vecSrcMazzle.x );	// Send to PAS because of the sound
		WRITE_COORD( vecSrcMazzle.y );
		WRITE_COORD( vecSrcMazzle.z );
		WRITE_SHORT( m_iMazzleSmoke );
		WRITE_BYTE( 10 ); // scale * 10
		WRITE_BYTE( 15 ); // framerate
	MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(pev->origin.x);	// X
		WRITE_COORD(pev->origin.y);	// Y
		WRITE_COORD(pev->origin.z);	// Z
		WRITE_BYTE( 280 );		// radius * 0.1
		WRITE_BYTE( 180 );		// r
		WRITE_BYTE( 100 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 255 );		// brightness 
		WRITE_BYTE( 50 );		// time * 10
	    WRITE_BYTE( 1 );        // decay * 0.1
	MESSAGE_END( );
    #endif	

			m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.05;
		}
	}
}


void CMinigun::SecondaryAttack( void )
{
	if ( m_fInAttack == 0)
	{
		if (m_pPlayer->pev->waterlevel == 3 || m_iClip <= 0)
	 	{
			PlayEmptySound( );
			m_flNextPrimaryAttack = gpGlobals->time + 0.5;
			return;
		}

		// spin up
		SendWeaponAnim(MINIGUN_SPINUP);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.0;
		m_fInAttack = 1;
	}
	else if (m_fInAttack == 1)
	{
		if ( m_iClip <= 0 )
		{
			WeaponIdle();
			return;
		}
		if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
			m_fInAttack = 2;
	}
	if (m_fInAttack == 2)
	{
		if ( m_iClip <= 0 )
		{
			WeaponIdle();
			return;
		}
		if ( m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
		{
			if ( gpGlobals->time >= m_flShockTime )
			{
				SendWeaponAnim(MINIGUN_SPIN);
				m_flShockTime = gpGlobals->time + 0.15;
			}
		}
	}
}


void CMinigun::Reload( void )
{
	DefaultReload( MINIGUN_MAX_CLIP, MINIGUN_RELOAD, 5.5, 2.0 );
}


void CMinigun::WeaponIdle( void )
{
	m_pPlayer->pev->maxspeed = 100;
	if (m_fInAttack!=0)
	{
		SendWeaponAnim(MINIGUN_SPINDOWN);
		m_fInAttack = 0;
		m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1.0;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
		return;
	}
}



class CMinigunAmmo : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_minigunclip.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_minigunclip.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		if (pOther->GiveAmmo( AMMO_MINIGUNBOX_GIVE, "minigun", MINIGUN_MAX_CARRY ) != -1)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
			return TRUE;
		}
		return FALSE;
	}
};
LINK_ENTITY_TO_CLASS( ammo_minigun, CMinigunAmmo );


