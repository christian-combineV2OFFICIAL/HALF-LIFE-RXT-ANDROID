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

===== generic grenade.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"

#ifndef CLIENT_DLL

TYPEDESCRIPTION	CDlight::m_SaveData[] = 
{
	DEFINE_FIELD( CDlight, m_flIgniteTime, FIELD_TIME ),
	DEFINE_FIELD( CDlight, m_pLauncher2, FIELD_CLASSPTR ),
};
IMPLEMENT_SAVERESTORE( CDlight, CGrenade );

LINK_ENTITY_TO_CLASS( dlight, CDlight );

//=========================================================
//=========================================================
CDlight *CDlight::CreateDlight( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, CEgon *pLauncher2 )
{
	CDlight *pDlight = GetClassPtr( (CDlight *)NULL );

	UTIL_SetOrigin( pDlight->pev, vecOrigin );
	pDlight->pev->angles = vecAngles;
	pDlight->Spawn();
	pDlight->SetTouch( CDlight::RocketTouch );
	pDlight->m_pLauncher2 = pLauncher2;// remember what RPG fired me. 
	pDlight->m_pLauncher2->m_cActiveRockets++;// register this missile as active for the launcher
	pDlight->pev->owner = pOwner->edict();
	pDlight->pev->movetype = MOVETYPE_FLYMISSILE;
	pDlight->pev->solid = SOLID_BBOX;

	return pDlight;
}

//=========================================================
//=========================================================
void CDlight :: Spawn( void )
{
	Precache( );
	// motor
	pev->movetype = MOVETYPE_BOUNCE;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/null.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING("dlight");

	SetThink( IgniteThink );
	SetTouch( ExplodeTouch );

	pev->angles.x -= 0;
	UTIL_MakeVectors( pev->angles );
	pev->angles.x = -(pev->angles.x + 0);

	pev->velocity = gpGlobals->v_forward * 2100;
	pev->gravity = 0.5;

	pev->nextthink = gpGlobals->time + 0.4;

	pev->dmg = gSkillData.plrDmgRPG;
}

//=========================================================
//=========================================================
void CDlight :: RocketTouch ( CBaseEntity *pOther )
{
	if ( m_pLauncher2 )
	{
		// my launcher is still around, tell it I'm dead.
		m_pLauncher2->m_cActiveRockets--;
	}

	STOP_SOUND( edict(), CHAN_VOICE, "weapons/rocket1.wav" );
	ExplodeTouchDlight( pOther );
}

void CDlight::Explode2( Vector vecSrc, Vector vecAim )
{
	TraceResult tr;
	UTIL_TraceLine ( pev->origin, pev->origin + Vector ( 0, 0, -32 ),  ignore_monsters, ENT(pev), & tr);

	Explode2( &tr, DMG_BLAST );
}

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CDlight::Explode2( TraceResult *pTrace, int bitsDamageType )
{
	float		flRndSound;// sound randomizer

	pev->model = iStringNull;//invisible
	pev->solid = SOLID_NOT;// intangible

	pev->takedamage = DAMAGE_NO;

	// Pull out of the wall a bit
	if ( pTrace->flFraction != 1.0 )
	{
		pev->origin = pTrace->vecEndPos + (pTrace->vecPlaneNormal * (pev->dmg - 24) * 0.6);
	}

	int iContents = UTIL_PointContents ( pev->origin );

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD(pev->origin.x);	// X
		WRITE_COORD(pev->origin.y);	// Y
		WRITE_COORD(pev->origin.z);	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 255 );		// b
		WRITE_BYTE( 255 );		// brightness 
		WRITE_BYTE( 20 );		// time * 10
	    WRITE_BYTE( 1 );        // decay * 0.1
	MESSAGE_END( );

	CSoundEnt::InsertSound ( bits_SOUND_COMBAT, pev->origin, NORMAL_EXPLOSION_VOLUME, 3.0 );
	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

	flRndSound = RANDOM_FLOAT( 0 , 1 );

	pev->effects |= EF_NODRAW;
	SetThink( Smoke2 );
	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
}

void CDlight::Smoke2( void )
{
	UTIL_Remove( this );
}

//
// Contact grenade, explode when it touches something
// 
void CDlight::ExplodeTouchDlight( CBaseEntity *pOther )
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	pev->enemy = pOther->edict();

	vecSpot = pev->origin - pev->velocity.Normalize() * 32;
	UTIL_TraceLine( vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr );

	Explode2( &tr, DMG_BLAST );
}

//=========================================================
//=========================================================
void CDlight :: Precache( void )
{
	PRECACHE_MODEL("models/null.mdl");
	m_iTrail = PRECACHE_MODEL("sprites/smoke.spr");
}


void CDlight :: IgniteThink( void  )
{
	// pev->movetype = MOVETYPE_TOSS;

	pev->movetype = MOVETYPE_FLY;

	m_flIgniteTime = gpGlobals->time;

	// set to follow laser spot
	SetThink( FollowThink );
	pev->nextthink = gpGlobals->time + 0.1;
}


void CDlight :: FollowThink( void  )
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




