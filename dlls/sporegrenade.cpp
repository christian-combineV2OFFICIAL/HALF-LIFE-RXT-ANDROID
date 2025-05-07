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
#include "sporegrenade.h"
#include "gearbox_weapons.h"

LINK_ENTITY_TO_CLASS( spore, CSpore );

CSpore *CSpore::CreateSporeGrenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CSpore *pSpore = GetClassPtr( (CSpore *)NULL );
	UTIL_SetOrigin( pSpore->pev, vecOrigin );
	pSpore->pev->angles = vecAngles;
	pSpore->m_iPrimaryMode = FALSE;
	pSpore->pev->angles = vecAngles;
	pSpore->pev->owner = pOwner->edict();
	pSpore->pev->classname = MAKE_STRING("spore");
	pSpore->m_bIsAI = m_bIsAI;
	pSpore->Spawn();

	return pSpore;
}

//=========================================================
//=========================================================
CSpore *CSpore::CreateSporeRocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CSpore *pSpore = GetClassPtr( (CSpore *)NULL );
	UTIL_SetOrigin( pSpore->pev, vecOrigin );
	pSpore->pev->angles = vecAngles;
	pSpore->m_iPrimaryMode = TRUE;
	pSpore->pev->angles = vecAngles;
	pSpore->pev->owner = pOwner->edict();
	pSpore->pev->classname = MAKE_STRING("spore");
	pSpore->Spawn();
 	pSpore->pev->angles = vecAngles;

	return pSpore;
}
//=========================================================
//=========================================================

void CSpore :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;
	else
		pev->movetype = MOVETYPE_BOUNCE;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/spore.mdl");
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
		SetTouch( &CSpore::RocketTouch );
	else
		SetTouch( &CSpore::BounceTouch );

	SetThink( &CSpore::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgSpore;
}
//=========================================================

void CSpore :: Precache( void )
{
	PRECACHE_MODEL("models/spore.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tinyspit.spr");
	m_iGlow = PRECACHE_MODEL("sprites/glow01.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/spore_exp_01.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/spore_exp_c_01.spr");
	PRECACHE_SOUND ("weapons/splauncher_impact.wav");
	PRECACHE_SOUND ("weapons/spore_hit1.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit2.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit3.wav");//Bounce grenade
}
//=========================================================

void CSpore :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CSpore :: FlyThink( void  )
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

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CSpore::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CSpore::BounceTouch( CBaseEntity *pOther )
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

void CSpore :: BounceSound( void )
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

void CSpore::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/splauncher_impact.wav", 1, ATTN_NORM);

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

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg, 200, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SPORESPLAT1 + RANDOM_LONG(0,2));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}

LINK_ENTITY_TO_CLASS( spore2, CSpore2 );

CSpore2 *CSpore2::CreateSpore2Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CSpore2 *pSpore2 = GetClassPtr( (CSpore2 *)NULL );
	UTIL_SetOrigin( pSpore2->pev, vecOrigin );
	pSpore2->pev->angles = vecAngles;
	pSpore2->m_iPrimaryMode = FALSE;
	pSpore2->pev->angles = vecAngles;
	pSpore2->pev->owner = pOwner->edict();
	pSpore2->pev->classname = MAKE_STRING("spore2");
	pSpore2->m_bIsAI = m_bIsAI;
	pSpore2->Spawn();

	return pSpore2;
}

//=========================================================
//=========================================================
CSpore2 *CSpore2::CreateSpore2Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CSpore2 *pSpore2 = GetClassPtr( (CSpore2 *)NULL );
	UTIL_SetOrigin( pSpore2->pev, vecOrigin );
	pSpore2->pev->angles = vecAngles;
	pSpore2->m_iPrimaryMode = TRUE;
	pSpore2->pev->angles = vecAngles;
	pSpore2->pev->owner = pOwner->edict();
	pSpore2->pev->classname = MAKE_STRING("spore2");
	pSpore2->Spawn();
 	pSpore2->pev->angles = vecAngles;

	return pSpore2;
}
//=========================================================
//=========================================================

void CSpore2 :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;
	else
		pev->movetype = MOVETYPE_BOUNCE;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/spore.mdl");
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
		SetTouch( &CSpore2::RocketTouch );
	else
		SetTouch( &CSpore2::BounceTouch );

	SetThink( &CSpore2::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgSpore;
}
//=========================================================

void CSpore2 :: Precache( void )
{
	PRECACHE_MODEL("models/spore.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tinyspit.spr");
	m_iGlow = PRECACHE_MODEL("sprites/glow01.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/spore_exp_01.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/spore_exp_c_01.spr");
	PRECACHE_SOUND ("weapons/splauncher_impact.wav");
	PRECACHE_SOUND ("weapons/spore_hit1.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit2.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit3.wav");//Bounce grenade
}
//=========================================================

void CSpore2 :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CSpore2 :: FlyThink( void  )
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

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CSpore2::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CSpore2::BounceTouch( CBaseEntity *pOther )
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

void CSpore2 :: BounceSound( void )
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

void CSpore2::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/splauncher_impact.wav", 1, ATTN_NORM);

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

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg, 200, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SPORESPLAT1 + RANDOM_LONG(0,2));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}

LINK_ENTITY_TO_CLASS( spore3, CSpore3 );

CSpore3 *CSpore3::CreateSpore3Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CSpore3 *pSpore3 = GetClassPtr( (CSpore3 *)NULL );
	UTIL_SetOrigin( pSpore3->pev, vecOrigin );
	pSpore3->pev->angles = vecAngles;
	pSpore3->m_iPrimaryMode = FALSE;
	pSpore3->pev->angles = vecAngles;
	pSpore3->pev->owner = pOwner->edict();
	pSpore3->pev->classname = MAKE_STRING("spore3");
	pSpore3->m_bIsAI = m_bIsAI;
	pSpore3->Spawn();

	return pSpore3;
}

//=========================================================
//=========================================================
CSpore3 *CSpore3::CreateSpore3Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CSpore3 *pSpore3 = GetClassPtr( (CSpore3 *)NULL );
	UTIL_SetOrigin( pSpore3->pev, vecOrigin );
	pSpore3->pev->angles = vecAngles;
	pSpore3->m_iPrimaryMode = TRUE;
	pSpore3->pev->angles = vecAngles;
	pSpore3->pev->owner = pOwner->edict();
	pSpore3->pev->classname = MAKE_STRING("spore3");
	pSpore3->Spawn();
 	pSpore3->pev->angles = vecAngles;

	return pSpore3;
}
//=========================================================
//=========================================================

void CSpore3 :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;
	else
		pev->movetype = MOVETYPE_BOUNCE;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/spore.mdl");
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
		SetTouch( &CSpore3::RocketTouch );
	else
		SetTouch( &CSpore3::BounceTouch );

	SetThink( &CSpore3::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgSpore;
}
//=========================================================

void CSpore3 :: Precache( void )
{
	PRECACHE_MODEL("models/spore.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tinyspit.spr");
	m_iGlow = PRECACHE_MODEL("sprites/glow01.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/spore_exp_01.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/spore_exp_c_01.spr");
	PRECACHE_SOUND ("weapons/splauncher_impact.wav");
	PRECACHE_SOUND ("weapons/spore_hit1.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit2.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit3.wav");//Bounce grenade
}
//=========================================================

void CSpore3 :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CSpore3 :: FlyThink( void  )
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

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CSpore3::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CSpore3::BounceTouch( CBaseEntity *pOther )
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

void CSpore3 :: BounceSound( void )
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

void CSpore3::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/splauncher_impact.wav", 1, ATTN_NORM);

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

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg, 200, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SPORESPLAT1 + RANDOM_LONG(0,2));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}

LINK_ENTITY_TO_CLASS( spore4, CSpore4 );

CSpore4 *CSpore4::CreateSpore4Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CSpore4 *pSpore4 = GetClassPtr( (CSpore4 *)NULL );
	UTIL_SetOrigin( pSpore4->pev, vecOrigin );
	pSpore4->pev->angles = vecAngles;
	pSpore4->m_iPrimaryMode = FALSE;
	pSpore4->pev->angles = vecAngles;
	pSpore4->pev->owner = pOwner->edict();
	pSpore4->pev->classname = MAKE_STRING("spore4");
	pSpore4->m_bIsAI = m_bIsAI;
	pSpore4->Spawn();

	return pSpore4;
}

//=========================================================
//=========================================================
CSpore4 *CSpore4::CreateSpore4Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CSpore4 *pSpore4 = GetClassPtr( (CSpore4 *)NULL );
	UTIL_SetOrigin( pSpore4->pev, vecOrigin );
	pSpore4->pev->angles = vecAngles;
	pSpore4->m_iPrimaryMode = TRUE;
	pSpore4->pev->angles = vecAngles;
	pSpore4->pev->owner = pOwner->edict();
	pSpore4->pev->classname = MAKE_STRING("spore4");
	pSpore4->Spawn();
 	pSpore4->pev->angles = vecAngles;

	return pSpore4;
}
//=========================================================
//=========================================================

void CSpore4 :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;
	else
		pev->movetype = MOVETYPE_BOUNCE;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/spore.mdl");
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
		SetTouch( &CSpore4::RocketTouch );
	else
		SetTouch( &CSpore4::BounceTouch );

	SetThink( &CSpore4::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgSpore;
}
//=========================================================

void CSpore4 :: Precache( void )
{
	PRECACHE_MODEL("models/spore.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tinyspit.spr");
	m_iGlow = PRECACHE_MODEL("sprites/glow01.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/spore_exp_01.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/spore_exp_c_01.spr");
	PRECACHE_SOUND ("weapons/splauncher_impact.wav");
	PRECACHE_SOUND ("weapons/spore_hit1.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit2.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit3.wav");//Bounce grenade
}
//=========================================================

void CSpore4 :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CSpore4 :: FlyThink( void  )
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

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CSpore4::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CSpore4::BounceTouch( CBaseEntity *pOther )
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

void CSpore4 :: BounceSound( void )
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

void CSpore4::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/splauncher_impact.wav", 1, ATTN_NORM);

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

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg, 200, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SPORESPLAT1 + RANDOM_LONG(0,2));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}

LINK_ENTITY_TO_CLASS( spore5, CSpore5 );

CSpore5 *CSpore5::CreateSpore5Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI )
{
	CSpore5 *pSpore5 = GetClassPtr( (CSpore5 *)NULL );
	UTIL_SetOrigin( pSpore5->pev, vecOrigin );
	pSpore5->pev->angles = vecAngles;
	pSpore5->m_iPrimaryMode = FALSE;
	pSpore5->pev->angles = vecAngles;
	pSpore5->pev->owner = pOwner->edict();
	pSpore5->pev->classname = MAKE_STRING("spore5");
	pSpore5->m_bIsAI = m_bIsAI;
	pSpore5->Spawn();

	return pSpore5;
}

//=========================================================
//=========================================================
CSpore5 *CSpore5::CreateSpore5Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner )
{
	CSpore5 *pSpore5 = GetClassPtr( (CSpore5 *)NULL );
	UTIL_SetOrigin( pSpore5->pev, vecOrigin );
	pSpore5->pev->angles = vecAngles;
	pSpore5->m_iPrimaryMode = TRUE;
	pSpore5->pev->angles = vecAngles;
	pSpore5->pev->owner = pOwner->edict();
	pSpore5->pev->classname = MAKE_STRING("spore5");
	pSpore5->Spawn();
 	pSpore5->pev->angles = vecAngles;

	return pSpore5;
}
//=========================================================
//=========================================================

void CSpore5 :: Spawn( void )
{
	Precache( );

	if (m_iPrimaryMode)
		pev->movetype = MOVETYPE_FLY;
	else
		pev->movetype = MOVETYPE_BOUNCE;

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/spore.mdl");
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
		SetTouch( &CSpore5::RocketTouch );
	else
		SetTouch( &CSpore5::BounceTouch );

	SetThink( &CSpore5::FlyThink );
	float flDelay = m_bIsAI ? 4.0 : 2.0;
	pev->dmgtime = gpGlobals->time + flDelay;
	pev->nextthink = gpGlobals->time + 0.1;

	pev->dmg = gSkillData.plrDmgSpore;
}
//=========================================================

void CSpore5 :: Precache( void )
{
	PRECACHE_MODEL("models/spore.mdl");
	m_iDrips = PRECACHE_MODEL("sprites/tinyspit.spr");
	m_iGlow = PRECACHE_MODEL("sprites/glow01.spr");
	m_iExplode = PRECACHE_MODEL ("sprites/spore_exp_01.spr");
	m_iExplodeC = PRECACHE_MODEL ("sprites/spore_exp_c_01.spr");
	PRECACHE_SOUND ("weapons/splauncher_impact.wav");
	PRECACHE_SOUND ("weapons/spore_hit1.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit2.wav");//Bounce grenade
	PRECACHE_SOUND ("weapons/spore_hit3.wav");//Bounce grenade
}
//=========================================================

void CSpore5 :: Glow( void )
{
	m_pSprite = CSprite::SpriteCreate( "sprites/glow01.spr", pev->origin, FALSE );
	m_pSprite->SetAttachment( edict(), 0 );
	m_pSprite->pev->scale = 0.8;
	m_pSprite->SetTransparency( kRenderTransAdd, 180, 180, 40, 100, kRenderFxDistort );
}
//=========================================================

void CSpore5 :: FlyThink( void  )
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

	if (!m_iPrimaryMode)
	{
		if (pev->dmgtime <= gpGlobals->time)
			Explode();
	}
	pev->nextthink = gpGlobals->time + 0.03;
}

void CSpore5::RocketTouch( CBaseEntity *pOther )
{
	if(pOther->pev->takedamage)
	{
		entvars_t *pevOwner;
		pevOwner = VARS( pev->owner );

		pOther->TakeDamage( pev, pevOwner, pev->dmg, DMG_GENERIC );
	}

	Explode();
}

void CSpore5::BounceTouch( CBaseEntity *pOther )
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

void CSpore5 :: BounceSound( void )
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

void CSpore5::Explode( void )
{
	SetTouch( NULL );
	SetThink( NULL );
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "weapons/splauncher_impact.wav", 1, ATTN_NORM);

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

	::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg, 200, CLASS_PLAYER_BIOWEAPON, DMG_GENERIC );

	if (m_iPrimaryMode)
	{
		TraceResult tr;
		UTIL_TraceLine( pev->origin, pev->origin + pev->velocity * 10, dont_ignore_monsters, ENT( pev ), &tr );
		UTIL_DecalTrace(&tr, DECAL_SPORESPLAT1 + RANDOM_LONG(0,2));
	}

	pev->velocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.3;
	UTIL_Remove ( this );
	UTIL_Remove( m_pSprite );
	m_pSprite = NULL;
}