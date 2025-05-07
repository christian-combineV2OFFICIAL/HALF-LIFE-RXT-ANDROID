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
#include	"FATRONeffect_2.h"
#include	"weapons.h"
#include	"gamerules.h"

LINK_ENTITY_TO_CLASS( effect_fatron2, CFATRONRocket2 );

CFATRONRocket2 *CFATRONRocket2::FATRONCreate2( const Vector &pOrigin, const Vector &pAngles, edict_t *pevOwner )
{
	// Create a new entity with CEinarFlameRocket private data
	CFATRONRocket2 *pFATRON2 = GetClassPtr( (CFATRONRocket2 *)NULL );
	UTIL_SetOrigin( pFATRON2->pev, pOrigin );
	pFATRON2->pev->angles = pAngles;
	pFATRON2->Spawn();
	pFATRON2->pev->owner = pevOwner;

	return pFATRON2;
}

void CFATRONRocket2::Spawn()
{
	Precache();

	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;

	SET_MODEL( ENT( pev ), "models/null.mdl" );
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );

	pev->classname = MAKE_STRING( "effect_fatron2" );

	pev->speed = g_pGameRules->IsMultiplayer() ? 500 : 400;

	SetThink( &CBaseEntity::SUB_Remove );

	UTIL_MakeVectors( pev->angles );
	pev->velocity = gpGlobals->v_forward - gpGlobals->v_right * pev->speed;	
	pev->gravity = 0;		

	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITETRAIL );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( pev->velocity.x );
		WRITE_COORD( pev->velocity.y );
		WRITE_COORD( pev->velocity.z );		
		WRITE_SHORT( PRECACHE_MODEL("sprites/anim_spr7_red.spr") );
		WRITE_BYTE( 2 ); // количество	
		WRITE_BYTE( 2 ); // жизнь
		WRITE_BYTE( 10 ); // размер
		WRITE_BYTE( 70 ); // скорость вдоль вектора	
		WRITE_BYTE( 70 ); // случайная скорость	
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITETRAIL );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( pev->velocity.x );
		WRITE_COORD( pev->velocity.y );
		WRITE_COORD( pev->velocity.z );		
		WRITE_SHORT( PRECACHE_MODEL("sprites/anim_spr7_red.spr") );
		WRITE_BYTE( 2 ); // количество	
		WRITE_BYTE( 2 ); // жизнь
		WRITE_BYTE( 10 ); // размер
		WRITE_BYTE( 70 ); // скорость вдоль вектора	
		WRITE_BYTE( 70 ); // случайная скорость	
	MESSAGE_END();
}

