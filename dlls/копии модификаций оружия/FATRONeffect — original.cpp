/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"nodes.h"
#include	"effects.h"
#include	"decals.h"
#include	"soundent.h"
#include	"game.h"
#include	"FATRONeffect.h"
#include	"weapons.h"
#include	"gamerules.h"

LINK_ENTITY_TO_CLASS( effect_fatron, CFATRONRocket );

CFATRONRocket *CFATRONRocket::FATRONCreate( const Vector &pOrigin, const Vector &pAngles, edict_t *pevOwner )
{
	// Create a new entity with CEinarFlameRocket private data
	CFATRONRocket *pFATRON = GetClassPtr( (CFATRONRocket *)NULL );
	UTIL_SetOrigin( pFATRON->pev, pOrigin );
	pFATRON->pev->angles = pAngles;
	pFATRON->Spawn();
	pFATRON->pev->owner = pevOwner;

	return pFATRON;
}

void CFATRONRocket::Spawn()
{
	Precache();

	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;
	pev->rendermode = kRenderTransTexture;
	pev->renderamt = 0;
	pev->effects |= EF_DIMLIGHT;

	SET_MODEL( ENT( pev ), "sprites/fthrow.spr" );
	UTIL_SetSize( pev, g_vecZero, g_vecZero );
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING( "effect_fatron" );
	pev->speed = g_pGameRules->IsMultiplayer() ? 500 : 400;

	SetTouch( &CFATRONRocket::FATRONTouch );
	SetThink( &CBaseEntity::SUB_Remove );
	pev->nextthink = gpGlobals->time + 1.1f;

	UTIL_MakeVectors( pev->angles );
	pev->velocity = gpGlobals->v_forward * pev->speed;
	pev->gravity = 0;

	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_PROJECTILE );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( pev->velocity.x );
		WRITE_COORD( pev->velocity.y );
		WRITE_COORD( pev->velocity.z );
		WRITE_SHORT( pev->modelindex );
		WRITE_BYTE( 1 );
		WRITE_BYTE( 0 );
	MESSAGE_END();	
}

void CFATRONRocket::FATRONTouch( CBaseEntity *pOther )
{
}

void CFATRONRocket::Precache()
{
	PRECACHE_MODEL( "sprites/fthrow.spr" );
}
