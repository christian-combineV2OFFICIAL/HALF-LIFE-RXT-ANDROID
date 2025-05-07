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

	pev->movetype = MOVETYPE_BOUNCE;
	pev->solid = SOLID_BBOX;

	SET_MODEL( ENT( pev ), "models/null.mdl" );
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING( "effect_fatron" );

	SetThink( &CBaseEntity::SUB_Remove );

	UTIL_MakeVectors( pev->angles );
	pev->gravity = 0;		

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/anim_spr7_red.spr" ) );
    WRITE_BYTE( 50 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	
}

