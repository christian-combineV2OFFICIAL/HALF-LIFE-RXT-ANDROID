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

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "gamerules.h"
#include "xen.h"
#include "plasma_2.h"

enum plasmagun_e {
	PLASMAGUN_IDLE = 0,
	PLASMAGUN_RELOAD,
	PLASMAGUN_DRAW,
	PLASMAGUN_SHOOT1,
	PLASMAGUN_SHOOT2,
	PLASMAGUN_SHOOT3,
};

LINK_ENTITY_TO_CLASS(weapon_plasmagun, CPlasmaGun);

void CPlasmaGun::Spawn()
{
	Precache();
	m_iId = WEAPON_PLASMAGUN;
	SET_MODEL(ENT(pev), "models/w_plasmagun.mdl");

	m_iDefaultAmmo = PLASMAGUN_DEFAULT_GIVE;

	FallInit();// get ready to fall
}


void CPlasmaGun::Precache(void)
{
	PRECACHE_MODEL("models/v_plasmagun.mdl");
	PRECACHE_MODEL("models/w_plasmagun.mdl");
	PRECACHE_MODEL("models/p_plasmagun.mdl");

	PRECACHE_SOUND("weapons/plasmagun-1.wav");
	PRECACHE_SOUND("weapons/plasmagun_exp.wav");
	PRECACHE_SOUND("weapons/plasmagun_clipin1.wav");
	PRECACHE_SOUND("weapons/plasmagun_clipin2.wav");
	PRECACHE_SOUND("weapons/plasmagun_clipout.wav");
	PRECACHE_SOUND("weapons/plasmagun_idle.wav");

	PRECACHE_SOUND("items/9mmclip1.wav");

	m_iSquidSpitSprite = PRECACHE_MODEL("sprites/tsplasma.spr");
	UTIL_PrecacheOther("plasma2");

	m_usPlasmaGunFire = PRECACHE_EVENT(1, "events/plasmagun.sc");
}

int CPlasmaGun::AddToPlayer(CBasePlayer *pPlayer)
{
	if (CBasePlayerWeapon::AddToPlayer(pPlayer))
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
		WRITE_BYTE(m_iId);
		MESSAGE_END();
		return TRUE;
	}
	return FALSE;
}


int CPlasmaGun::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "plasma2";
	p->iMaxAmmo1 = PLASMAGUN_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = PLASMAGUN_MAX_CLIP;
	p->iSlot = 5;
	p->iPosition = 0;
	p->iFlags = 0;
	p->iId = m_iId = WEAPON_PLASMAGUN;
	p->iWeight = PLASMAGUN_WEIGHT;

	return 1;
}



BOOL CPlasmaGun::Deploy()
{
	m_pPlayer->pev->maxspeed = 320;	
	// Start idle sound
    EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/plasmagun_idle.wav", 0.9, ATTN_NORM );		
	
	return DefaultDeploy("models/v_plasmagun.mdl", "models/p_plasmagun.mdl", PLASMAGUN_DRAW, "rpg");
}

void CPlasmaGun::Holster( int skiplocal /* = 0 */ )
{	
	// Stop idle sound
    STOP_SOUND( ENT(m_pPlayer->pev), CHAN_AUTO, "weapons/plasmagun_idle.wav" );
}

void CPlasmaGun::PrimaryAttack()
{
#ifndef CLIENT_DLL
	UTIL_ScreenShake( pev->origin, 20.0, 50.0, 0.5, 100.0 );
#endif	
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = GetNextAttackDelay(0.15);
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();
		if (m_iClip == 0)
			PlayEmptySound();
		return;
	}

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	m_iClip--;

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif


	// m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
	UTIL_MakeVectors( m_pPlayer->pev->v_angle );
	Vector vecSrc = m_pPlayer->GetGunPosition( ) + gpGlobals->v_forward * 16 + gpGlobals->v_right * 8 + gpGlobals->v_up * -8;

#ifndef CLIENT_DLL
		CPlasma2 *pPlasma2 = CPlasma2::CreatePlasma2Rocket( vecSrc, m_pPlayer->pev->v_angle, m_pPlayer );
		UTIL_MakeVectors( m_pPlayer->pev->v_angle );
		pPlasma2->pev->velocity = pPlasma2->pev->velocity + gpGlobals->v_forward * 1000;
#endif

	PLAYBACK_EVENT_FULL(
		flags,
		m_pPlayer->edict(), 
		m_usPlasmaGunFire, 
		0.0, 
		(float *)&g_vecZero, 
		(float *)&g_vecZero, 
		vecSrc.x,
		vecSrc.y,
		*(int*)&vecSrc.z,
		m_iSquidSpitSprite, 
		0,
		TRUE);


	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);

	m_flNextPrimaryAttack = GetNextAttackDelay(0.15);

#if 1
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.15;
#endif

	if (m_iClip != 0)
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.15;
	else
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.15;
	m_fInSpecialReload = 0;
}

void CPlasmaGun::Reload( void )
{
	DefaultReload( 45, PLASMAGUN_RELOAD, 3.5 );
}

void CPlasmaGun::WeaponIdle(void)
{
	ResetEmptySound( );
	
	if (m_flTimeWeaponIdle > 0.0)
	{	
		return;
	}

	SendWeaponAnim(PLASMAGUN_IDLE);
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 10.03;
}

class CPlasma2Ammo : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_plasmabox.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_plasmabox.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		if (pOther->GiveAmmo( PLASMAGUN_DEFAULT_GIVE, "plasma2", PLASMAGUN_MAX_CARRY ) != -1)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
			return TRUE;
		}
		return FALSE;
	}
};
LINK_ENTITY_TO_CLASS( ammo_plasma2, CPlasma2Ammo );