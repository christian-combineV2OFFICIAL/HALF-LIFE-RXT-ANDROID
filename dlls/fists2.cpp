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
#include "decals.h"

void FindHullIntersection(const Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity);

#define	FISTS2_BODYHIT_VOLUME 128
#define	FISTS2_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS(weapon_fists, CFists2)

enum fists2_e {
	FISTS2_IDLE = 0,
	FISTS2_FIRE_LEFT,
	FISTS2_FIRE_RIGHT,
	FISTS2_DEPLOY,
    FISTS2_HOLSTER,
	FISTS2_KICK
};


void CFists2::Spawn()
{
	Precache();
	m_iId = WEAPON_FISTS2;
	SET_MODEL(ENT(pev), "models/null.mdl");
	m_iClip = -1;

	FallInit();// get ready to fall down.
}


void CFists2::Precache(void)
{
	PRECACHE_MODEL("models/v_fists.mdl");
	PRECACHE_MODEL("models/null.mdl");
	PRECACHE_MODEL("models/p_knife.mdl");
	// fists
	PRECACHE_SOUND("weapons/fists_detonable.wav");
	
	PRECACHE_SOUND("weapons/fists_hit1.wav");
	PRECACHE_SOUND("weapons/fists_hitbody1.wav");
	PRECACHE_SOUND("weapons/fists_hitbody2.wav");
	PRECACHE_SOUND("weapons/fists_hitbody3.wav");
    // leg
	PRECACHE_SOUND("weapons/leg_kick.wav");
	
	PRECACHE_SOUND("weapons/leg_strike1.wav");
	PRECACHE_SOUND("weapons/leg_strike2.wav");
	PRECACHE_SOUND("weapons/leg_hitbod1.wav");
	PRECACHE_SOUND("weapons/leg_hitbod2.wav");
	PRECACHE_SOUND("weapons/leg_hitbod3.wav");

	m_usFists3 = PRECACHE_EVENT(1, "events/fists3.sc");
	m_usFists4 = PRECACHE_EVENT(1, "events/fists4.sc");
}

int CFists2::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = NULL;
	p->iMaxAmmo1 = -1;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = -1;
	p->iPosition = -1;
	p->iId = WEAPON_FISTS2;
	p->iWeight = FISTS2_WEIGHT;
	return 1;
}



BOOL CFists2::Deploy()
{			
	m_pPlayer->pev->maxspeed = 800;		
	return DefaultDeploy("models/v_fists.mdl", "models/p_knife.mdl", FISTS2_DEPLOY, "fists2");
}

void CFists2::PrimaryAttack()
{
	if (!Swing(1))
	{
#ifndef CLIENT_DLL
		SetThink(&CFists2::SwingAgain);
		pev->nextthink = gpGlobals->time + 0.1;

			switch (RANDOM_LONG(0, 1))
			{
			case 0:
		m_pPlayer->pev->punchangle.x = -10; // pitch
		m_pPlayer->pev->punchangle.y = -10;	// yaw
		m_pPlayer->pev->punchangle.z = 10;	// roll
				break;
			case 1:
		m_pPlayer->pev->punchangle.x = 10; // pitch
		m_pPlayer->pev->punchangle.y = 10;	// yaw
		m_pPlayer->pev->punchangle.z = -10;	// roll
				break;			
			}		
		
		//UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );
	    Vector vecSrc	 = m_pPlayer->GetGunPosition( );
	    Vector vecAiming = m_pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );
	    Vector vecDir;
        float flZVel = m_pPlayer->pev->velocity.z;
        m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * -100;
        m_pPlayer->pev->velocity.z = flZVel;
#endif
	}
}

void CFists2::SecondaryAttack()
{
	if (!Swing2(1))
	{
#ifndef CLIENT_DLL
		SetThink(&CFists2::SwingAgain2);
		pev->nextthink = gpGlobals->time + 0.1;	

			switch (RANDOM_LONG(0, 5))
			{
			case 0:
		m_pPlayer->pev->punchangle.x = -15; // pitch
				break;
			case 1:
		m_pPlayer->pev->punchangle.y = -15;	// yaw
				break;			
			case 2:
		m_pPlayer->pev->punchangle.z = -15;	// roll
				break;			
			case 3:
		m_pPlayer->pev->punchangle.z = -15;	// roll
				break;
			case 4:
		m_pPlayer->pev->punchangle.y = -15;	// yaw
				break;			
			case 5:
		m_pPlayer->pev->punchangle.x = -15; // pitch
				break;				
			}	
		
		//UTIL_MakeVectors( m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle );
	    Vector vecSrc	 = m_pPlayer->GetGunPosition( );
	    Vector vecAiming = m_pPlayer->GetAutoaimVector( AUTOAIM_10DEGREES );
	    Vector vecDir;
        float flZVel = m_pPlayer->pev->velocity.z;
        m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * -200;
        m_pPlayer->pev->velocity.z = flZVel;
#endif
	}
}

void CFists2::Smack()
{
}

void CFists2::Smack2()
{
	UTIL_DecalTrace(&m_trHit, DECAL_CRACK1 + RANDOM_LONG(0,3));
}

void CFists2::SwingAgain(void)
{
	Swing(0);
}

void CFists2::SwingAgain2(void)
{
	Swing2(0);
}

int CFists2::Swing(int fFirst)
{
	int fDidHit = FALSE;

	TraceResult tr;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 32;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);

#ifndef CLIENT_DLL
	if (tr.flFraction >= 1.0)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
		if (tr.flFraction < 1.0)
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);
			if (!pHit || pHit->IsBSPModel())
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
		}
	}
#endif

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usFists3,
		0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0,
		0.0, 0, 0.0);


	if (tr.flFraction >= 1.0)
	{
		if (fFirst)
		{
			// miss
			m_flNextPrimaryAttack = GetNextAttackDelay(0.5);

			// player "shoot" animation
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		switch (((m_iSwing++) % 3) + 1)
		{
		case 0:
			SendWeaponAnim(FISTS2_FIRE_LEFT); break;
		case 1:
			SendWeaponAnim(FISTS2_FIRE_RIGHT); break;
		case 2:
			SendWeaponAnim(FISTS2_FIRE_LEFT); break;
		case 3:
			SendWeaponAnim(FISTS2_FIRE_RIGHT); break;
		}

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

#ifndef CLIENT_DLL

		// hit
		fDidHit = TRUE;
		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		// play thwack, smack, or dong sound
		float flVol = 1.0;
		int fHitWorld = TRUE;

		if (pEntity)
		{
			ClearMultiDamage();
			// If building with the clientside weapon prediction system,
			// UTIL_WeaponTimeBase() is always 0 and m_flNextPrimaryAttack is >= -1.0f, thus making
			// m_flNextPrimaryAttack + 1 < UTIL_WeaponTimeBase() always evaluate to false.
#ifdef CLIENT_WEAPONS
			if( ( m_flNextPrimaryAttack + 1 == UTIL_WeaponTimeBase() ) || g_pGameRules->IsMultiplayer() )
#else
			if( ( m_flNextPrimaryAttack + 1 < UTIL_WeaponTimeBase() ) || g_pGameRules->IsMultiplayer() )
#endif
			{
				// first swing does full damage
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists2, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			else
			{
				// subsequent swings do half
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists2 / 2, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				// play thwack or smack sound
				switch (RANDOM_LONG(0, 2))
				{
				case 0:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hitbody1.wav", 1, ATTN_NORM); break;
				case 1:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hitbody2.wav", 1, ATTN_NORM); break;				
			    case 2:
				    EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hitbody3.wav", 1, ATTN_NORM);	break;			
				}
				m_pPlayer->m_iWeaponVolume = FISTS2_BODYHIT_VOLUME;
				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1;	

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.5, 250.0 );
#endif

				fHitWorld = FALSE;				
			}
		}

		// play texture hit sound
		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line

		if (fHitWorld)
		{
			float fvolbar = TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);

			if (g_pGameRules->IsMultiplayer())
			{
				// override the volume here, cause we don't play texture sounds in multiplayer, 
				// and fvolbar is going to be 0 from the above call.

				fvolbar = 1;
			}

			// also play crowbar strike
			switch (RANDOM_LONG(0, 2))
			{
			case 0:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hit1.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
				break;
			case 1:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hit1.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
				break;
			case 2:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/fists_hit1.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
				break;			
			}

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.5, 250.0 );
#endif

			// delay the decal a bit
			m_trHit = tr;
		}

		m_pPlayer->m_iWeaponVolume = flVol * FISTS2_WALLHIT_VOLUME;

		SetThink(&CFists2::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
#endif
		m_flNextPrimaryAttack = GetNextAttackDelay(0.25);
	}
	return fDidHit;
}

int CFists2::Swing2(int fFirst)
{
	int fDidHit = FALSE;

	TraceResult tr;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 82;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);

#ifndef CLIENT_DLL
	if (tr.flFraction >= 1.0)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);
		if (tr.flFraction < 1.0)
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);
			if (!pHit || pHit->IsBSPModel())
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			vecEnd = tr.vecEndPos;	// This is the point on the actual surface (the hull could have hit space)
		}
	}
#endif

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usFists4,
		0.0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0,
		0.0, 0, 0.0);


	if (tr.flFraction >= 1.0)
	{
		if (fFirst)
		{
			// miss
			m_flNextSecondaryAttack = GetNextAttackDelay(0.5);

			// player "shoot" animation
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		switch (((m_iSwing++) % 2) + 1)
		{
		case 0:
			SendWeaponAnim(FISTS2_KICK); break;
		case 1:
			SendWeaponAnim(FISTS2_KICK); break;
		case 2:
			SendWeaponAnim(FISTS2_KICK); break;
		}

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

#ifndef CLIENT_DLL

		// hit
		fDidHit = TRUE;
		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		// play thwack, smack, or dong sound
		float flVol = 1.0;
		int fHitWorld = TRUE;

		if (pEntity)
		{
			ClearMultiDamage();
			// If building with the clientside weapon prediction system,
			// UTIL_WeaponTimeBase() is always 0 and m_flNextPrimaryAttack is >= -1.0f, thus making
			// m_flNextPrimaryAttack + 1 < UTIL_WeaponTimeBase() always evaluate to false.
#ifdef CLIENT_WEAPONS
			if( ( m_flNextSecondaryAttack + 1 == UTIL_WeaponTimeBase() ) || g_pGameRules->IsMultiplayer() )
#else
			if( ( m_flNextSecondaryAttack + 1 < UTIL_WeaponTimeBase() ) || g_pGameRules->IsMultiplayer() )
#endif
			{
				// first swing does full damage
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists2Kick, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			else
			{
				// subsequent swings do half
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists2Kick / 2, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				// play thwack or smack sound
				switch (RANDOM_LONG(0, 2))
				{
				case 0:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/leg_hitbod1.wav", 1, ATTN_NORM); break;
				case 1:
					EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/leg_hitbod2.wav", 1, ATTN_NORM); break;				
			    case 2:
				    EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/leg_hitbod3.wav", 1, ATTN_NORM); break;			
				}
				m_pPlayer->m_iWeaponVolume = FISTS2_BODYHIT_VOLUME;
				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1;	

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 100.0, 150.0, 1, 250.0 );
#endif

				fHitWorld = FALSE;				
			}
		}

		// play texture hit sound
		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line

		if (fHitWorld)
		{
			float fvolbar = TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);

			if (g_pGameRules->IsMultiplayer())
			{
				// override the volume here, cause we don't play texture sounds in multiplayer, 
				// and fvolbar is going to be 0 from the above call.

				fvolbar = 1;
			}

			// also play crowbar strike
			switch (RANDOM_LONG(0, 1))
			{
			case 0:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/leg_strike1.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
				break;
			case 1:
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/leg_strike2.wav", fvolbar, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
				break;		
			}
	

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 100.0, 150.0, 1, 250.0 );
#endif

			// delay the decal a bit
			m_trHit = tr;
		}

		m_pPlayer->m_iWeaponVolume = flVol * FISTS2_WALLHIT_VOLUME;

		SetThink(&CFists2::Smack2);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
#endif
		m_flNextSecondaryAttack = GetNextAttackDelay(0.25);
	}
	return fDidHit;
}

void CFists2::WeaponIdle( void )
{		
	if (m_flTimeWeaponIdle > gpGlobals->time)
		return;

	SendWeaponAnim( FISTS2_IDLE );
	m_flTimeWeaponIdle = gpGlobals->time + 5.0;
}