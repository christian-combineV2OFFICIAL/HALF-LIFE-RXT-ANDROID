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
#include "soundent.h"

LINK_ENTITY_TO_CLASS( gasgrenade, CGASGrenade );

void CGASGrenade::Killed (entvars_t *pevAttacker, int iGib)
{
	UTIL_Remove( this );
}

void CGASGrenade::Explode( TraceResult *pTrace, int bitsDamageType )
{
	pev->velocity = g_vecZero;
	pev->origin = pev->origin + Vector(0,0,5);

	entvars_t *pevOwner = VARS( pev->owner );
	::RadiusDamage( pev->origin, pev, NULL, 20, 500, CLASS_MACHINE, DMG_NERVEGAS | DMG_POISON );

	GasStayTime = 80;
    
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/GASgrenade.wav", 1, ATTN_NORM);

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 80 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 255 );		// b
		WRITE_BYTE( 10 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ballsmoke.spr" ) );
    WRITE_BYTE( 80 );
    WRITE_BYTE( 100 );
    MESSAGE_END();	

	SetTouch(NULL);
	SetThink( Smoke );
	pev->nextthink = gpGlobals->time + 0.2;
}

void CGASGrenade::Smoke( void )
{
	if(GasStayTime <=0 )
	{
		STOP_SOUND( edict(), CHAN_VOICE, "weapons/GASgrenade_explode.wav" );
		UTIL_Remove( this );
	}
	else
		GasStayTime--;

	entvars_t *pevOwner = VARS( pev->owner );
	if (UTIL_PointContents ( pev->origin ) != CONTENTS_WATER)
	{
		::RadiusDamage( pev->origin, pev, NULL, 50, 350, CLASS_MACHINE, DMG_NERVEGAS | DMG_POISON );
		
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 30 );		// radius * 0.1
		WRITE_BYTE( 0 );		// r
		WRITE_BYTE( 255 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 80 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );

    MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( PRECACHE_MODEL( "sprites/ef_smoke_poison.spr" ) );
    WRITE_BYTE( 50 );
    WRITE_BYTE( 20 );
    MESSAGE_END();		
		
		if ( gpGlobals->time >= m_flSoundTime )
		{
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/GASgrenade_explode.wav", 0.7, ATTN_NORM);
			m_flSoundTime = gpGlobals->time + 3;
		}
	}
	pev->nextthink = gpGlobals->time + 0.2;
}

void CGASGrenade::Detonate( void )
{
	TraceResult tr;
	Vector vecSpot = pev->origin + Vector ( 0 , 0 , 8 );
	UTIL_TraceLine ( vecSpot, vecSpot + Vector ( 0, 0, -40 ),  ignore_monsters, ENT(pev), & tr);
	Explode( &tr, DMG_BLAST );
}

void CGASGrenade::BounceTouch( CBaseEntity *pOther )
{
	if (pOther->pev->takedamage == DAMAGE_AIM)
	{
		TraceResult tr;
		entvars_t *pevOwner = VARS( pev->owner );
		ClearMultiDamage( );
		pOther->TraceAttack(pevOwner, gSkillData.plrDmg357, gpGlobals->v_forward, &tr, DMG_BULLET); 
		ApplyMultiDamage( pev, pevOwner);
		SetThink( Detonate );
		return;
	}

	if (pev->flags & FL_ONGROUND)
		pev->velocity = pev->velocity * 0.8;
	else
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/chronoclip_bounce.wav", 1, ATTN_NORM);
}

void CGASGrenade :: TumbleThink( void )
{
	if (!IsInWorld())
	{
		Detonate( );
		return;
	}
	pev->nextthink = gpGlobals->time + 0.01;

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITE );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_SHORT( PRECACHE_MODEL( "sprites/ef_smoke_poison.spr" ) );
		WRITE_BYTE( 5 ); // scale * 10
		WRITE_BYTE( 150  ); // framerate
	MESSAGE_END();

	if (pev->dmgtime <= gpGlobals->time)
		SetThink( Detonate );
}

void CGASGrenade:: Spawn( void )
{
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING( "gasgrenade" );
	pev->solid = SOLID_BBOX;
	SET_MODEL(ENT(pev), "models/gasgrenade.mdl");
	pev->body = 8;
	UTIL_SetSize(pev, g_vecZero, g_vecZero );
}

CGASGrenade *CGASGrenade::ShootGASGrenade( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time )
{
	CGASGrenade *pGASGrenade = GetClassPtr( (CGASGrenade *)NULL );
	pGASGrenade->Spawn();

	UTIL_SetOrigin( pGASGrenade->pev, vecStart );
	pGASGrenade->pev->velocity = vecVelocity;
	pGASGrenade->pev->angles = UTIL_VecToAngles(pGASGrenade->pev->velocity);
	pGASGrenade->pev->owner = ENT(pevOwner); 
	pGASGrenade->SetTouch( BounceTouch ); 
	pGASGrenade->pev->dmgtime = gpGlobals->time + time;
	pGASGrenade->SetThink( TumbleThink );
	pGASGrenade->pev->nextthink = gpGlobals->time + 0.01;
	pGASGrenade->pev->gravity = 1;
	pGASGrenade->pev->friction = 0.8;
	pGASGrenade->pev->dmg = 100;
	return pGASGrenade;
}

