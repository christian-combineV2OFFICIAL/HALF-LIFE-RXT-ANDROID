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
#include "fatronAIRgrenade.h"
#include "shake.h"

LINK_ENTITY_TO_CLASS( fatron, CFatronFire );

CFatronFire *CFatronFire::CreateFatronFireGrenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CFatronFire *pFatronFire = GetClassPtr( (CFatronFire *)NULL );
	UTIL_SetOrigin( pFatronFire->pev, vecOrigin );
	pFatronFire->pev->angles = vecAngles;
	pFatronFire->m_iPrimaryMode = FALSE;
	pFatronFire->pev->angles = vecAngles;
	pFatronFire->pev->owner = pOwner->edict();
	pFatronFire->pev->classname = MAKE_STRING("fatron");
	pFatronFire->m_bIsAI = m_bIsAI;
	pFatronFire->Spawn();

	return pFatronFire;
}

//=========================================================
//=========================================================
CFatronFire *CFatronFire::CreateFatronFireRocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CFatronFire *pFatronFire = GetClassPtr( (CFatronFire *)NULL );
	UTIL_SetOrigin( pFatronFire->pev, vecOrigin );
	pFatronFire->pev->angles = vecAngles;
	pFatronFire->m_iPrimaryMode = TRUE;
	pFatronFire->pev->angles = vecAngles;
	pFatronFire->pev->owner = pOwner->edict();
	pFatronFire->pev->classname = MAKE_STRING("fatron");
	pFatronFire->Spawn();
 	pFatronFire->pev->angles = vecAngles;

	return pFatronFire;
}
//=========================================================
//=========================================================

void CFatronFire :: Spawn( void )
{
	Precache( );

	pev->movetype = MOVETYPE_FLY;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/w_FATRONgrenade.mdl");
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
		SetTouch( &CFatronFire::RocketTouch );
	else
		SetTouch( &CFatronFire::BounceTouch );

	SetThink( &CFatronFire::FlyThink );
	float flDelay = m_bIsAI ? 1.5 : 1.5;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = 100;
}
//=========================================================

void CFatronFire :: Precache( void )
{
	PRECACHE_MODEL("models/w_FATRONgrenade.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/anim_spr7_red.spr");
}
//=========================================================

void CFatronFire :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CFatronFire :: FlyThink( void  )
{
	Vector vecEnd = pev->origin.Normalize();

	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY, pev->origin );
		WRITE_BYTE( TE_SPRITETRAIL );
		WRITE_COORD( pev->origin.x );
		WRITE_COORD( pev->origin.y );
		WRITE_COORD( pev->origin.z );
		WRITE_COORD( pev->velocity.x );
		WRITE_COORD( pev->velocity.y -1000 );
		WRITE_COORD( pev->velocity.z );			
		WRITE_SHORT( m_iDrips );
		WRITE_BYTE( 10 ); // количество	
		WRITE_BYTE( 1 ); // жизнь
		WRITE_BYTE( 5 ); // размер
		WRITE_BYTE( 30 ); // скорость вдоль вектора	
		WRITE_BYTE( 50 ); // случайная скорость	
	MESSAGE_END();

	// fatron trail
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMFOLLOW );
		WRITE_SHORT(entindex());	// entity
		WRITE_SHORT(m_iDrips );	// model
		WRITE_BYTE( 40 ); // life
		WRITE_BYTE( 5 );  // width
		WRITE_BYTE( 224 );   // r, g, b
		WRITE_BYTE( 224 );   // r, g, b
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
	MESSAGE_END();  // move PHS/PVS data sending into here (SEND_ALL, SEND_PVS, SEND_PHS)

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 22);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 12);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 02);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 12);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 22);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 32);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 42);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 52);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 62);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 72);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 82);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 92);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	// blast circle
	MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
		WRITE_BYTE( TE_BEAMTORUS);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z - 102);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z + 32 + pev->dmg * 2 / .2); // reach damage radius over .3 seconds
		WRITE_SHORT( PRECACHE_MODEL( "sprites/lgtning.spr" ) );
		WRITE_BYTE( 0 ); // startframe
		WRITE_BYTE( 0 ); // framerate
		WRITE_BYTE( 2 ); // life
		WRITE_BYTE( 12 );  // width
		WRITE_BYTE( 0 );   // noise
		WRITE_BYTE( 255 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 0 );   // r, g, b
		WRITE_BYTE( 255 );	// brightness
		WRITE_BYTE( 0 );		// speed
	MESSAGE_END();

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CFatronFire::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CFatronFire::BounceTouch( CBaseEntity *pOther )
{
	if ( !pOther->pev->takedamage )
	{
		if( pev->flags & FL_SWIM )
		{
			pev->velocity = pev->velocity * 0.5;
			pev->sequence = 1;
		}
		else
			BounceSound(); // play bounce sound
	}
	else
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );

		Explode();
	}

	pev->framerate = pev->velocity.Length() / 200.0;
	if (pev->framerate > 1.0)
		pev->framerate = 1;
	else if (pev->framerate < 0.5)
		pev->framerate = 0;

}

void CFatronFire :: BounceSound( void )
{
	switch (RANDOM_LONG (0, 2))
	{
		case 0: 
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/spore_hit1.wav", 0.25, ATTN_NORM); 
			break;
		case 1: 
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/spore_hit2.wav", 0.25, ATTN_NORM); 
			break;
		case 2: 
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/spore_hit3.wav", 0.25, ATTN_NORM); 
			break;
	}
}

void CFatronFire::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );

    	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	UTIL_ScreenFadeAll( Vector(255,0,0), 5, 10.0, 255, FFADE_IN );

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg = 100000, 10000, CLASS_PLAYER_BIOWEAPON, DMG_BURN | DMG_ENERGYBEAM );

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}
