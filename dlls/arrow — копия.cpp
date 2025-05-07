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
/*

===== generic arrow.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"
#include "gamerules.h"
#include "arrow.h"


//===================arrow


LINK_ENTITY_TO_CLASS( arrow, CArrow );

// Arrows flagged with this will be triggered when the owner calls detonateSatchelCharges
#define SF_DETONATE		0x0001

//
// Arrow Explode
//
void CArrow::Explode( Vector vecSrc, Vector vecAim )
{
}

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CArrow::Explode( TraceResult *pTrace, int bitsDamageType )
{
}


void CArrow::Smoke( void )
{
}

void CArrow::Killed( entvars_t *pevAttacker, int iGib )
{
	Detonate( );
}

// Timed arrow, this think is called when time runs out.
void CArrow::DetonateUse( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	SetThink( Detonate );
	pev->nextthink = gpGlobals->time;
}

void CArrow::PreDetonate( void )
{
	CSoundEnt::InsertSound ( bits_SOUND_DANGER, pev->origin, 400, 0.3 );

	SetThink( Detonate );
	pev->nextthink = gpGlobals->time + 1;
}


void CArrow::Detonate( void )
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	vecSpot = pev->origin + Vector ( 0 , 0 , 8 );
	UTIL_TraceLine ( vecSpot, vecSpot + Vector ( 0, 0, -40 ),  ignore_monsters, ENT(pev), & tr);

	Explode( &tr, DMG_BLAST );
}


//
// Contact arrow, explode when it touches something
// 
void CArrow::ExplodeTouch( CBaseEntity *pOther )
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	pev->enemy = pOther->edict();

	vecSpot = pev->origin - pev->velocity.Normalize() * 32;
	UTIL_TraceLine( vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr );

	Explode( &tr, DMG_BLAST );
}


void CArrow::DangerSoundThink( void )
{
	if (!IsInWorld())
	{
		UTIL_Remove( this );
		return;
	}

	CSoundEnt::InsertSound ( bits_SOUND_DANGER, pev->origin + pev->velocity * 0.5, pev->velocity.Length( ), 0.2 );
	pev->nextthink = gpGlobals->time + 0.2;

	if (pev->waterlevel != 0)
	{
		pev->velocity = pev->velocity * 0.5;
	}
}


void CArrow::BounceTouch( CBaseEntity *pOther )
{
	SetTouch( NULL );
	SetThink( NULL );

	if (pOther->pev->takedamage)
	{
		TraceResult tr = UTIL_GetGlobalTrace( );
		entvars_t	*pevOwner;

		pevOwner = VARS( pev->owner );

		// UNDONE: this needs to call TraceAttack instead
		ClearMultiDamage( );

		if ( pOther->IsPlayer() )
		{
			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowClient, pev->velocity.Normalize(), &tr, DMG_NEVERGIB ); 
		}
		else
		{
			pOther->TraceAttack(pevOwner, gSkillData.plrDmgCrossbowMonster, pev->velocity.Normalize(), &tr, DMG_BULLET | DMG_NEVERGIB ); 
		}

		ApplyMultiDamage( pev, pevOwner );

		pev->velocity = Vector( 0, 0, 0 );
		// play body "thwack" sound
		switch( RANDOM_LONG(0,1) )
		{
		case 0:
			EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/bow_hitbod1.wav", 1, ATTN_NORM); break;
		case 1:
			EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/bow_hitbod2.wav", 1, ATTN_NORM); break;
		}

		if ( !g_pGameRules->IsMultiplayer() )
		{
			Killed( pev, GIB_NEVER );
		}
	}
	else
	{
		EMIT_SOUND_DYN(ENT(pev), CHAN_BODY, "weapons/bow_hit1.wav", RANDOM_FLOAT(0.95, 1.0), ATTN_NORM, 0, 98 + RANDOM_LONG(0,7));
		
		SetThink( SUB_Remove );
		pev->nextthink = gpGlobals->time;// this will get changed below if the bolt is allowed to stick in what it hit.

		if ( FClassnameIs( pOther->pev, "worldspawn" ) )
		{
			// if what we hit is static architecture, can stay around for a while.
			Vector vecDir = pev->velocity.Normalize( );
			UTIL_SetOrigin( pev, pev->origin - vecDir * 12 );
			pev->angles = UTIL_VecToAngles( vecDir );
			pev->solid = SOLID_NOT;
			pev->movetype = MOVETYPE_FLY;
			pev->velocity = Vector( 0, 0, 0 );
			pev->avelocity.z = 0;
			pev->angles.z = RANDOM_LONG(0,360);
			pev->nextthink = gpGlobals->time + 10.0;
		    pev->avelocity.x = 0;
		}

		if (UTIL_PointContents(pev->origin) != CONTENTS_WATER)
		{
			UTIL_Sparks( pev->origin );
		}
	}
}



void CArrow::SlideTouch( CBaseEntity *pOther )
{
	// don't hit the guy that launched this arrow
	if ( pOther->edict() == pev->owner )
		return;

	// pev->avelocity = Vector (300, 300, 300);

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.95;

		if (pev->velocity.x != 0 || pev->velocity.y != 0)
		{
			// maintain sliding sound
		}
	}
	else
	{
		BounceSound();
	}
}

void CArrow :: BounceSound( void )
{
}

void CArrow :: TumbleThink( void )
{
	if (!IsInWorld())
	{
		UTIL_Remove( this );
		return;
	}

	StudioFrameAdvance( );
	pev->nextthink = gpGlobals->time + 1.0;

    EMIT_SOUND(ENT(pev), CHAN_BODY, "weapons/bow_fly1.wav", 1, ATTN_NORM);

	if (pev->dmgtime - 1 < gpGlobals->time)
	{
		CSoundEnt::InsertSound ( bits_SOUND_DANGER, pev->origin + pev->velocity * (pev->dmgtime - gpGlobals->time), 400, 0.1 );
	}

	if (pev->dmgtime <= gpGlobals->time)
	{
		SetThink( Detonate );
	}
	if (pev->waterlevel != 0)
	{
		pev->velocity = pev->velocity * 0.5;
		pev->framerate = 0.2;
	}
}


void CArrow:: Spawn( void )
{
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING( "arrow" );

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/arrow.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));

	pev->dmg = 100;
	m_fRegisteredSound = FALSE;
}

CArrow * CArrow:: ShootTimed( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time )
{
	CArrow *pArrow = GetClassPtr( (CArrow *)NULL );
	pArrow->Spawn();
	UTIL_SetOrigin( pArrow->pev, vecStart );
	pArrow->pev->velocity = vecVelocity;
	pArrow->pev->angles = UTIL_VecToAngles(pArrow->pev->velocity);
	pArrow->pev->owner = ENT(pevOwner);
	
	pArrow->SetTouch( BounceTouch );	// Bounce if touched
	
	// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
	// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
	// the arrow explodes after the exact amount of time specified in the call to ShootTimed(). 

	pArrow->pev->dmgtime = gpGlobals->time + time;
	pArrow->SetThink( TumbleThink );
	pArrow->pev->nextthink = gpGlobals->time + 0.1;
	if (time < 0.1)
	{
		pArrow->pev->nextthink = gpGlobals->time;
		pArrow->pev->velocity = Vector( 0, 0, 0 );
	}
		
	pArrow->pev->sequence = RANDOM_LONG( 3, 6 );
	pArrow->pev->framerate = 1.0;

	// Tumble through the air
	pArrow->pev->avelocity.x = -45;

	pArrow->pev->gravity = 0.5;
	pArrow->pev->friction = 0.8;

	SET_MODEL(ENT(pArrow->pev), "models/arrow.mdl");
	pArrow->pev->dmg = 100;

	return pArrow;
}

CArrow * CArrow:: ShootTimed2( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time )
{
	CArrow *pArrow = GetClassPtr( (CArrow *)NULL );
	pArrow->Spawn();
	UTIL_SetOrigin( pArrow->pev, vecStart );
	pArrow->pev->velocity = vecVelocity;
	pArrow->pev->angles = UTIL_VecToAngles(pArrow->pev->velocity);
	pArrow->pev->owner = ENT(pevOwner);
	
	pArrow->SetTouch( BounceTouch );	// Bounce if touched
	
	// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
	// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
	// the arrow explodes after the exact amount of time specified in the call to ShootTimed(). 

	pArrow->pev->dmgtime = gpGlobals->time + time;
	pArrow->SetThink( TumbleThink );
	pArrow->pev->nextthink = gpGlobals->time + 0.1;
	if (time < 0.1)
	{
		pArrow->pev->nextthink = gpGlobals->time;
		pArrow->pev->velocity = Vector( 0, 0, 0 );
	}
		
	pArrow->pev->sequence = RANDOM_LONG( 3, 6 );
	pArrow->pev->framerate = 1.0;

	// Tumble through the air
	pArrow->pev->avelocity.x = -22,5;

	pArrow->pev->gravity = 0.5;
	pArrow->pev->friction = 0.8;

	SET_MODEL(ENT(pArrow->pev), "models/arrow.mdl");
	pArrow->pev->dmg = 100;

	return pArrow;
}

//======================end arrow

