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

#define	FISTS_BODYHIT_VOLUME 128
#define	FISTS_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS(weapon_fists2, CFists)

enum fists_e {
	FISTS_IDLE1 = 0,
	FISTS_DEPLOY,
	FISTS_HOLSTER,
	FISTS_RIGHTHIT1,
	FISTS_RIGHTMISS1,
	FISTS_LEFTMISS1,
	FISTS_LEFTHIT1,
	FISTS_LEFTMISS2,
	FISTS_RIGHTHIT2,
	FISTS_KICK
};


void CFists::Spawn()
{
	Precache();
	m_iId = WEAPON_FISTS;
	SET_MODEL(ENT(pev), "models/w_fists.mdl");
	m_iClip = -1;

	FallInit();// get ready to fall down.
}


void CFists::Precache(void)
{
	PRECACHE_MODEL("models/v_fists2.mdl");
	PRECACHE_MODEL("models/w_fists.mdl");
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

	m_usFists = PRECACHE_EVENT(1, "events/fists.sc");
	m_usFists2 = PRECACHE_EVENT(1, "events/fists2.sc");
}

int CFists::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = NULL;
	p->iMaxAmmo1 = -1;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 0;
	p->iPosition = 1;
	p->iId = WEAPON_FISTS;
	p->iWeight = FISTS_WEIGHT;
	return 1;
}



BOOL CFists::Deploy()
{			
	m_pPlayer->pev->maxspeed = 800;		
	return DefaultDeploy("models/v_fists2.mdl", "models/p_knife.mdl", FISTS_DEPLOY, "fists");
}

void CFists::Holster(int skiplocal /* = 0 */)
{	
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;	
	SendWeaponAnim(FISTS_HOLSTER);
}

void CFists::PrimaryAttack()
{
	if (!Swing(1))
	{
#ifndef CLIENT_DLL
		SetThink(&CFists::SwingAgain);
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
        m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * -200;
        m_pPlayer->pev->velocity.z = flZVel;
#endif
	}
}

void CFists::SecondaryAttack()
{
	if (!Swing2(1))
	{
#ifndef CLIENT_DLL
		SetThink(&CFists::SwingAgain2);
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
        m_pPlayer->pev->velocity = m_pPlayer->pev->velocity - gpGlobals->v_forward * -500;
        m_pPlayer->pev->velocity.z = flZVel;
#endif
	}
}

void CFists::Smack()
{
	UTIL_DecalTrace(&m_trHit, DECAL_CRACK1 + RANDOM_LONG(0,3));
}

void CFists::Smack2()
{
	UTIL_DecalTrace(&m_trHit, DECAL_CRACK1 + RANDOM_LONG(0,3));
}

void CFists::SwingAgain(void)
{
	Swing(0);
}

void CFists::SwingAgain2(void)
{
	Swing2(0);
}

int CFists::Swing(int fFirst)
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

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usFists,
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
		switch (((m_iSwing++) % 2) + 1)
		{
		case 0:
			SendWeaponAnim(FISTS_RIGHTHIT1); break;
		case 1:
			SendWeaponAnim(FISTS_LEFTHIT1); break;
		case 2:
			SendWeaponAnim(FISTS_RIGHTHIT2); break;
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
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			else
			{
				// subsequent swings do half
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFists / 2, gpGlobals->v_forward, &tr, DMG_CLUB);
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
				m_pPlayer->m_iWeaponVolume = FISTS_BODYHIT_VOLUME;
				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1;

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( tr.vecEndPos.x );
    WRITE_COORD( tr.vecEndPos.y );
    WRITE_COORD( tr.vecEndPos.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ballsmoke.spr" ) );
    WRITE_BYTE( 5 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

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

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( tr.vecEndPos.x );
    WRITE_COORD( tr.vecEndPos.y );
    WRITE_COORD( tr.vecEndPos.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ballsmoke.spr" ) );
    WRITE_BYTE( 5 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.5, 250.0 );
#endif

			// delay the decal a bit
			m_trHit = tr;
		}

		m_pPlayer->m_iWeaponVolume = flVol * FISTS_WALLHIT_VOLUME;

		SetThink(&CFists::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
#endif
		m_flNextPrimaryAttack = GetNextAttackDelay(0.25);
	}
	return fDidHit;
}

int CFists::Swing2(int fFirst)
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

	PLAYBACK_EVENT_FULL(FEV_NOTHOST, m_pPlayer->edict(), m_usFists2,
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
			SendWeaponAnim(FISTS_KICK); break;
		case 1:
			SendWeaponAnim(FISTS_KICK); break;
		case 2:
			SendWeaponAnim(FISTS_KICK); break;
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
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFistsKick, gpGlobals->v_forward, &tr, DMG_CLUB);
			}
			else
			{
				// subsequent swings do half
				pEntity->TraceAttack(m_pPlayer->pev, gSkillData.plrDmgFistsKick / 2, gpGlobals->v_forward, &tr, DMG_CLUB);
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
				m_pPlayer->m_iWeaponVolume = FISTS_BODYHIT_VOLUME;
				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1;

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( tr.vecEndPos.x );
    WRITE_COORD( tr.vecEndPos.y );
    WRITE_COORD( tr.vecEndPos.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ballsmoke.spr" ) );
    WRITE_BYTE( 10 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

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

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, tr.vecEndPos );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( tr.vecEndPos.x );
    WRITE_COORD( tr.vecEndPos.y );
    WRITE_COORD( tr.vecEndPos.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ballsmoke.spr" ) );
    WRITE_BYTE( 10 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

#ifndef CLIENT_DLL	
		UTIL_ScreenShake( pev->origin, 100.0, 150.0, 1, 250.0 );
#endif

			// delay the decal a bit
			m_trHit = tr;
		}

		m_pPlayer->m_iWeaponVolume = flVol * FISTS_WALLHIT_VOLUME;

		SetThink(&CFists::Smack2);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
#endif
		m_flNextSecondaryAttack = GetNextAttackDelay(0.25);
	}
	return fDidHit;
}

void CFists::WeaponIdle( void )
{		
	if (m_flTimeWeaponIdle > gpGlobals->time)
		return;

	SendWeaponAnim( FISTS_IDLE1 );
	m_flTimeWeaponIdle = gpGlobals->time + 5.0;
}