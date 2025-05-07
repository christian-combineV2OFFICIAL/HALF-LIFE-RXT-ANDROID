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
#include "soundent.h"
#include "gamerules.h"

enum m16_e
{
	M16_IDLE1 = 0,
	M16_IDLE2,	
	M16_SHOOT,
	M16_SHOOT_SOLID,
	M16_GRENADE,
	M16_GRENADE_SOLID,	
	M16_RELOAD,
	M16_DRAW,
	M16_HOLSTER,
};



LINK_ENTITY_TO_CLASS( weapon_m16, CM16 );


//=========================================================
//=========================================================
int CM16::SecondaryAmmoIndex( void )
{
	return m_iSecondaryAmmoType;
}

void CM16::Spawn( )
{
	pev->classname = MAKE_STRING("weapon_m16"); // hack to allow for old names
	Precache( );
	SET_MODEL(ENT(pev), "models/w_M16.mdl");
	m_iId = WEAPON_M16;

	m_iDefaultAmmo = M16_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CM16::Precache( void )
{
	PRECACHE_MODEL("models/v_M16.mdl");
	PRECACHE_MODEL("models/w_M16.mdl");
	PRECACHE_MODEL("models/p_M16.mdl");

	m_iShell = PRECACHE_MODEL ("models/shell.mdl");// brass shellTE_MODEL

	PRECACHE_MODEL("models/gasgrenade.mdl");	// grenade
    PRECACHE_MODEL("sprites/ef_smoke_poison.spr"); // nggrenade sprite
    PRECACHE_MODEL("sprites/ballsmoke.spr");
	PRECACHE_SOUND("weapons/gasgrenade.wav"); 
	PRECACHE_SOUND("weapons/gasgrenade_explode.wav");
	PRECACHE_SOUND("weapons/chronoclip_bounce.wav");

	PRECACHE_MODEL("models/w_clip_m16.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");              

	PRECACHE_SOUND("items/clipinsert1.wav");
	PRECACHE_SOUND("items/cliprelease1.wav");

	PRECACHE_SOUND ("weapons/M16_fire.wav");// H to the K
	PRECACHE_SOUND ("weapons/M16_glauncher.wav");   

	PRECACHE_SOUND ("weapons/357_cock1.wav");

	m_usM16 = PRECACHE_EVENT( 1, "events/m16.sc" );
	m_usM162 = PRECACHE_EVENT( 1, "events/m162.sc" );
}

int CM16::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "m16";
	p->iMaxAmmo1 = M16_MAX_CARRY;
	p->pszAmmo2 = "GASgrenades";
	p->iMaxAmmo2 = M203_GASGRENADE_MAX_CARRY;
	p->iMaxClip = M16_MAX_CLIP;
	p->iSlot = 2;
	p->iPosition = 3;
	p->iFlags = 0;
	p->iId = m_iId = WEAPON_M16;
	p->iWeight = M16_WEIGHT;

	return 1;
}

int CM16::AddToPlayer( CBasePlayer *pPlayer )
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

BOOL CM16::Deploy( )
{
	m_pPlayer->pev->maxspeed = 320;	
	return DefaultDeploy( "models/v_M16.mdl", "models/p_M16.mdl", M16_DRAW, "m16" );
}


void CM16::PrimaryAttack()
{
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound( );
		m_flNextPrimaryAttack = 0.15;
		return;
	}

	if (m_iClip <= 0)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = 0.15;
		return;
	}

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	m_iClip--;


	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;

	// player "shoot" animation
	m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

	Vector vecSrc	 = m_pPlayer->GetGunPosition( );
	Vector vecAiming = m_pPlayer->GetAutoaimVector( AUTOAIM_5DEGREES );
	Vector vecDir;

#ifndef CLIENT_DLL
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecSrc );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(vecSrc.x);	// X
		WRITE_COORD(vecSrc.y);	// Y
		WRITE_COORD(vecSrc.z);	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 255 );		// brightness 
		WRITE_BYTE( 50 );		// time * 10
	    WRITE_BYTE( 1 );        // decay * 0.1
	MESSAGE_END( );
#endif

#ifdef CLIENT_DLL
	if ( !bIsMultiplayer() )
#else
	if ( !g_pGameRules->IsMultiplayer() )
#endif
	{
		// optimized multiplayer. Widened to make it easier to hit a moving player
		vecDir = m_pPlayer->FireBulletsPlayer( 1, vecSrc, vecAiming, VECTOR_CONE_1DEGREES, 8192, BULLET_PLAYER_556, 2, 0, m_pPlayer->pev, m_pPlayer->random_seed );
	}
	else
	{
		// single player spread
		vecDir = m_pPlayer->FireBulletsPlayer( 1, vecSrc, vecAiming, VECTOR_CONE_1DEGREES, 8192, BULLET_PLAYER_556, 2, 0, m_pPlayer->pev, m_pPlayer->random_seed );
	}

  int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL( flags, m_pPlayer->edict(), m_usM16, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, 0, 0, 0, 0 );

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.1;

	if ( m_flNextPrimaryAttack < UTIL_WeaponTimeBase() )
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.1;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 );
}



void CM16::SecondaryAttack( void )
{
	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound( );
		m_flNextPrimaryAttack = 0.15;
		return;
	}

	if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] == 0)
	{
		PlayEmptySound( );
		return;
	}

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_pPlayer->m_iExtraSoundTypes = bits_SOUND_DANGER;
	m_pPlayer->m_flStopExtraSoundTime = UTIL_WeaponTimeBase() + 0.2;
			
	m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType]--;

	// player "shoot" animation
	m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

 	UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );

	// we don't add in player velocity anymore.
	CGASGrenade::ShootGASGrenade( m_pPlayer->pev, 
							m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 20, 
							gpGlobals->v_forward * 1500, 3 );

#ifndef CLIENT_DLL
	UTIL_ScreenShake( pev->origin, 20.0, 100.0, 1, 200.0 );
#endif

#ifndef CLIENT_DLL
	Vector vecSmokeOrigin;
	UTIL_MakeAimVectors(m_pPlayer->pev->v_angle);	

	vecSmokeOrigin = m_pPlayer->GetGunPosition() +
					 gpGlobals->v_forward * 16 +
					 gpGlobals->v_right * 2 +
					 gpGlobals->v_up * -26;	
	
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
			WRITE_BYTE( TE_SMOKE );
			WRITE_COORD( vecSmokeOrigin.x );
			WRITE_COORD( vecSmokeOrigin.y );
			WRITE_COORD( vecSmokeOrigin.z );
			WRITE_SHORT( g_sModelIndexSmoke );
			WRITE_BYTE( 5 ); // scale * 10
			WRITE_BYTE( 12  ); // framerate
		MESSAGE_END();
#endif

	int flags;
#if defined( CLIENT_WEAPONS )
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT( flags, m_pPlayer->edict(), m_usM162 );
	
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 5;// idle pretty soon after shooting.

	if (!m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType])
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
}

void CM16::Reload( void )
{
	DefaultReload( M16_MAX_CLIP, M16_RELOAD, 2.0 );
}


void CM16::WeaponIdle( void )
{
	ResetEmptySound( );

	m_pPlayer->GetAutoaimVector( AUTOAIM_5DEGREES );

	if ( m_flTimeWeaponIdle > UTIL_WeaponTimeBase() )
		return;

	int iAnim;
	switch ( RANDOM_LONG( 0, 1 ) )
	{
	case 0:	
		iAnim = M16_IDLE1;	
		break;
	
	default:
	case 1:
		iAnim = M16_IDLE2;
		break;
	}

	SendWeaponAnim( iAnim );

	m_flTimeWeaponIdle = UTIL_SharedRandomFloat( m_pPlayer->random_seed, 10, 15 ); // how long till we do this again.
}


class CM16AmmoClip : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_clip_m16.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_clip_m16.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		int bResult = (pOther->GiveAmmo( AMMO_M16CLIP_GIVE, "m16", M16_MAX_CARRY) != -1);
		if (bResult)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
		}
		return bResult;
	}
};
LINK_ENTITY_TO_CLASS( ammo_m16clip, CM16AmmoClip );


class CM16AmmoGrenade : public CBasePlayerAmmo
{
	void Spawn( void )
	{ 
		Precache( );
		SET_MODEL(ENT(pev), "models/w_gasgrenade.mdl");
		CBasePlayerAmmo::Spawn( );
	}
	void Precache( void )
	{
		PRECACHE_MODEL ("models/w_gasgrenade.mdl");
		PRECACHE_SOUND("items/9mmclip1.wav");
	}
	BOOL AddAmmo( CBaseEntity *pOther ) 
	{ 
		int bResult = (pOther->GiveAmmo( AMMO_M203GASBOX_GIVE, "GASgrenades", M203_GASGRENADE_MAX_CARRY ) != -1);

		if (bResult)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
		}
		return bResult;
	}
};
LINK_ENTITY_TO_CLASS( ammo_GASgrenades, CM16AmmoGrenade );


















