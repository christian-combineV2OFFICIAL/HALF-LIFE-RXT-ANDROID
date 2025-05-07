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
#include "soundent.h"
#include "gamerules.h"
#include "decals.h"
#include "plasma_2.h"
#include "plasmagun_weapons.h"

LINK_ENTITY_TO_CLASS( plasma2, CPlasma2 );

CPlasma2 *CPlasma2::CreatePlasma2Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CPlasma2 *pPlasma2 = GetClassPtr( (CPlasma2 *)NULL );
	UTIL_SetOrigin( pPlasma2->pev, vecOrigin );
	pPlasma2->pev->angles = vecAngles;
	pPlasma2->m_iPrimaryMode = TRUE;
	pPlasma2->pev->angles = vecAngles;
	pPlasma2->pev->owner = pOwner->edict();
	pPlasma2->pev->classname = MAKE_STRING("plasma2");
	pPlasma2->Spawn();
 	pPlasma2->pev->angles = vecAngles;

	return pPlasma2;
}
//=========================================================
//=========================================================

void CPlasma2 :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;

	pev->solid = SOLID_BSP;

	SET_MODEL(ENT(pev), "models/plasmanull.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));
	UTIL_SetOrigin( pev, pev->origin );
	UTIL_MakeVectors( pev->angles );
	if( m_bIsAI )
	{
		pev->gravity = 0.5;
		pev->friction = 0.7;
	}
	Glow();

	if (m_iPrimaryMode)
		SetTouch( &CPlasma2::RocketTouch );

	SetThink( &CPlasma2::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgPlasmaGun;
}
//=========================================================

void CPlasma2 :: Precache( void )
{
	PRECACHE_MODEL("models/plasmanull.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tsplasma.spr");
	m_iGlow = PRECACHE_MODEL("sprites/plasmaball.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/plasmabomb.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/plasmabomb.spr");
	PRECACHE_SOUND ("weapons/plasmagun_exp.wav");
}
//=========================================================

void CPlasma2 :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/plasmaball.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CPlasma2 :: FlyThink( void  )
{
	Vector vecEnd = pev->origin.Normalize();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITE_SPRAY );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( pev->origin.x );	// Send to PAS because of the sound
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( vecEnd.x );
		WRITE_COORD( vecEnd.y );
		WRITE_COORD( vecEnd.z );
		WRITE_SHORT( m_iDrips );
		WRITE_BYTE( 2 ); // count
		WRITE_BYTE( 20 ); // speed
		WRITE_BYTE( 80 );
	MESSAGE_END();

	if (pev->waterlevel == 3)
	{
		entvars_t *pevOwner = VARS(pev->owner);
		ClearEffects();
		SetThink( &CBaseEntity::SUB_Remove );
		pev->nextthink = gpGlobals->time;
	}

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CPlasma2::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC | DMG_POISON | DMG_PARALYZE | DMG_ENERGYBEAM | DMG_RADIATION | DMG_SHOCK | DMG_POISON );
	}

	Explode();
}

void CPlasma2::Explode( void )
{
	if (pev->waterlevel == 3)
	{
		ClearEffects();
		SetThink( &CBaseEntity::SUB_Remove );
		pev->nextthink = gpGlobals->time;
	}

	if ( UTIL_PointContents(pev->origin) == CONTENT_WATER )
	{
		UTIL_Remove( this );
		return;
	}	

	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/plasmagun_exp.wav", 1, ATTN_NORM);

	TraceResult tr;
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITE );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( pev->origin.x );	// Send to PAS because of the sound
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		switch ( RANDOM_LONG( 0, 1 ) )
		{
			case 0:	
				WRITE_SHORT( m_iExplode );
				break;
			default:
			case 1:
				WRITE_SHORT( m_iExplodeC );
				break;
		}
		WRITE_BYTE( 20 ); // scale * 10
		WRITE_BYTE( 128 ); // framerate
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITE_SPRAY );		// This makes a dynamic light and the explosion sprites/sound
		WRITE_COORD( pev->origin.x );	// Send to PAS because of the sound
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( tr.vecPlaneNormal.x );
		WRITE_COORD( tr.vecPlaneNormal.y );
		WRITE_COORD( tr.vecPlaneNormal.z );
		WRITE_SHORT( m_iDrips );
		WRITE_BYTE( 2  ); // count
		WRITE_BYTE( 40 ); // speed
		WRITE_BYTE( 80 );
	MESSAGE_END();

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 10 );		// radius * 0.1
		WRITE_BYTE( 15 );		// r
		WRITE_BYTE( 220 );		// g
		WRITE_BYTE( 40 );		// b
		WRITE_BYTE( 5 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITE_SPRAY );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( RANDOM_FLOAT( -1, 1 ) );
		WRITE_COORD( 1 );
		WRITE_COORD( RANDOM_FLOAT( -1, 1 ) );
		WRITE_SHORT( m_iDrips );
		WRITE_BYTE( 2 );
		WRITE_BYTE( 20 );
		WRITE_BYTE( 80 );
	MESSAGE_END();

    	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg = 50, 300, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC | DMG_ENERGYBEAM | DMG_SHOCK | DMG_RADIATION );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SMALLSCORCH1 + RANDOM_LONG(0,1));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}

void CPlasma2::ClearEffects()
{
	if (m_pSprite)
	{
		UTIL_Remove( m_pSprite );
		m_pSprite = NULL;
	}
}