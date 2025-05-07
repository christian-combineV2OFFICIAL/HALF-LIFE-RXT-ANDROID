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

===== generic FATRONgrenade.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"


//===================FATRONgrenade


LINK_ENTITY_TO_CLASS( FATRONgrenade, CFATRONGrenade );

// Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges
#define SF_DETONATE		0x0001

//
// FATRONGrenade Explode
//
void CFATRONGrenade::Explode( Vector vecSrc, Vector vecAim )
{
	TraceResult tr;
	UTIL_TraceLine ( pev->origin, pev->origin + Vector ( 0, 0, -32 ),  ignore_monsters, ENT(pev), & tr);

	Explode( &tr, DMG_BLAST );
}

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CFATRONGrenade::Explode( TraceResult *pTrace, int bitsDamageType )
{
	SetThink( Fase1 );
	pev->nextthink = gpGlobals->time + 1.0;
}

void CFATRONGrenade::Fase1( void )
{
 	entvars_t	*pevOwner;
	
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set  
	
	CBaseEntity::Create( "monster_FATRONlightning", pev->origin, pev->angles, edict() );	
	RadiusDamage ( pev->origin, pev, pevOwner, 1, 1, CLASS_NONE );		
	
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );    
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	
	
	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );	
	
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket01.wav", 1, ATTN_NORM);
	SetThink( Fase2 );
	pev->nextthink = gpGlobals->time + 1.5;
}

void CFATRONGrenade::Fase2( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
	
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket02.wav", 1, ATTN_NORM);
	SetThink( Fase3 );
	pev->nextthink = gpGlobals->time + 2.0;
}

void CFATRONGrenade::Fase3( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket01.wav", 1, ATTN_NORM);
	SetThink( Fase4 );
	pev->nextthink = gpGlobals->time + 2.5;
}

void CFATRONGrenade::Fase4( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket02.wav", 1, ATTN_NORM);
	SetThink( Fase5 );
	pev->nextthink = gpGlobals->time + 3.0;
}

void CFATRONGrenade::Fase5( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket01.wav", 1, ATTN_NORM);
	SetThink( Fase6 );
	pev->nextthink = gpGlobals->time + 3.5;
}

void CFATRONGrenade::Fase6( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket02.wav", 1, ATTN_NORM);
	SetThink( Fase7 );
	pev->nextthink = gpGlobals->time + 4.0;
}

void CFATRONGrenade::Fase7( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
	
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket01.wav", 1, ATTN_NORM);
	SetThink( Fase8 );
	pev->nextthink = gpGlobals->time + 4.5;
}

void CFATRONGrenade::Fase8( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket02.wav", 1, ATTN_NORM);
	SetThink( Fase9 );
	pev->nextthink = gpGlobals->time + 5.0;
}

void CFATRONGrenade::Fase9( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket01.wav", 1, ATTN_NORM);
	SetThink( Fase10 );
	pev->nextthink = gpGlobals->time + 5.5;
}

void CFATRONGrenade::Fase10( void )
{
	UTIL_ScreenShake( pev->origin, 5.0, 150.0, 0.75, 500.0 );       
	
	MESSAGE_BEGIN( MSG_PAS, SVC_TEMPENTITY, pev->origin );
    WRITE_BYTE( TE_SPRITE );
    WRITE_COORD( pev->origin.x );
    WRITE_COORD( pev->origin.y );
    WRITE_COORD( pev->origin.z );
    WRITE_SHORT( g_sModelIndexLaserDot );
    WRITE_BYTE( 40 );
    WRITE_BYTE( 255 );
    MESSAGE_END();	

	MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin  );
		WRITE_BYTE(TE_DLIGHT);
		WRITE_COORD( pev->origin.x );	// X
		WRITE_COORD( pev->origin.y );	// Y
		WRITE_COORD( pev->origin.z );	// Z
		WRITE_BYTE( 20 );		// radius * 0.1
		WRITE_BYTE( 255 );		// r
		WRITE_BYTE( 0 );		// g
		WRITE_BYTE( 0 );		// b
		WRITE_BYTE( 1 );		// time * 10
		WRITE_BYTE( 10 );		// decay * 0.1
	MESSAGE_END( );		
		
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/messagepacket02.wav", 1, ATTN_NORM);

}

void CFATRONGrenade::Smoke( void )
{
	if (UTIL_PointContents ( pev->origin ) == CONTENTS_WATER)
	{
		UTIL_Bubbles( pev->origin - Vector( 64, 64, 64 ), pev->origin + Vector( 64, 64, 64 ), 100 );
	}
	else
	{
		MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
			WRITE_BYTE( TE_SMOKE );
			WRITE_COORD( pev->origin.x );
			WRITE_COORD( pev->origin.y );
			WRITE_COORD( pev->origin.z );
			WRITE_SHORT( g_sModelIndexSmoke );
			WRITE_BYTE( (pev->dmg - 50) * 0.80 ); // scale * 10
			WRITE_BYTE( 12  ); // framerate
		MESSAGE_END();
	}
	UTIL_Remove( this );
}

void CFATRONGrenade::Killed( entvars_t *pevAttacker, int iGib )
{
	Detonate( );
}


// Timed grenade, this think is called when time runs out.
void CFATRONGrenade::DetonateUse( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	SetThink( Detonate );
	pev->nextthink = gpGlobals->time;
}

void CFATRONGrenade::PreDetonate( void )
{
	CSoundEnt::InsertSound ( bits_SOUND_DANGER, pev->origin, 400, 0.3 );

	SetThink( Detonate );
	pev->nextthink = gpGlobals->time + 1;
}


void CFATRONGrenade::Detonate( void )
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	vecSpot = pev->origin + Vector ( 0 , 0 , 8 );
	UTIL_TraceLine ( vecSpot, vecSpot + Vector ( 0, 0, -40 ),  ignore_monsters, ENT(pev), & tr);

	Explode( &tr, DMG_BLAST );
}


//
// Contact FATRONgrenade, explode when it touches something
// 
void CFATRONGrenade::ExplodeTouch( CBaseEntity *pOther )
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	pev->enemy = pOther->edict();

	vecSpot = pev->origin - pev->velocity.Normalize() * 32;
	UTIL_TraceLine( vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr );

	Explode( &tr, DMG_BLAST );
}


void CFATRONGrenade::DangerSoundThink( void )
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


void CFATRONGrenade::BounceTouch( CBaseEntity *pOther )
{
	// don't hit the guy that launched this grenade
	if ( pOther->edict() == pev->owner )
		return;

	// only do damage if we're moving fairly fast
	if (m_flNextAttack < gpGlobals->time && pev->velocity.Length() > 100)
	{
		entvars_t *pevOwner = VARS( pev->owner );
		if (pevOwner)
		{
			TraceResult tr = UTIL_GetGlobalTrace( );
			ClearMultiDamage( );
			pOther->TraceAttack(pevOwner, 1, gpGlobals->v_forward, &tr, DMG_CLUB ); 
			ApplyMultiDamage( pev, pevOwner);
		}
		m_flNextAttack = gpGlobals->time + 1.0; // debounce
	}

	Vector vecTestVelocity;
	// pev->avelocity = Vector (300, 300, 300);

	// this is my heuristic for modulating the grenade velocity because grenades dropped purely vertical
	// or thrown very far tend to slow down too quickly for me to always catch just by testing velocity. 
	// trimming the Z velocity a bit seems to help quite a bit.
	vecTestVelocity = pev->velocity; 
	vecTestVelocity.z *= 0.45;

	if ( !m_fRegisteredSound && vecTestVelocity.Length() <= 60 )
	{
		//ALERT( at_console, "Grenade Registered!: %f\n", vecTestVelocity.Length() );

		// grenade is moving really slow. It's probably very close to where it will ultimately stop moving. 
		// go ahead and emit the danger sound.
		
		// register a radius louder than the explosion, so we make sure everyone gets out of the way
		CSoundEnt::InsertSound ( bits_SOUND_DANGER, pev->origin, pev->dmg / 0.4, 0.3 );
		m_fRegisteredSound = TRUE;
	}

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.8;

		pev->sequence = RANDOM_LONG( 1, 1 );
	}
	else
	{
		// play bounce sound
		BounceSound();
	}
	pev->framerate = pev->velocity.Length() / 200.0;
	if (pev->framerate > 1.0)
		pev->framerate = 1;
	else if (pev->framerate < 0.5)
		pev->framerate = 0;

}



void CFATRONGrenade::SlideTouch( CBaseEntity *pOther )
{
	// don't hit the guy that launched this grenade
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

void CFATRONGrenade :: BounceSound( void )
{
	switch ( RANDOM_LONG( 0, 2 ) )
	{
	case 0:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit1.wav", 0.25, ATTN_NORM);	break;
	case 1:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit2.wav", 0.25, ATTN_NORM);	break;
	case 2:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit3.wav", 0.25, ATTN_NORM);	break;
	}
}

void CFATRONGrenade :: TumbleThink( void )
{
	if (!IsInWorld())
	{
		UTIL_Remove( this );
		return;
	}

	StudioFrameAdvance( );
	pev->nextthink = gpGlobals->time + 0.1;

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


void CFATRONGrenade:: Spawn( void )
{
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING( "FATRONgrenade" );
	
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/grenade.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));

	pev->dmg = 100;
	m_fRegisteredSound = FALSE;
}


CFATRONGrenade *CFATRONGrenade::ShootContact( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity )
{
	CFATRONGrenade *pFATRONGrenade = GetClassPtr( (CFATRONGrenade *)NULL );
	pFATRONGrenade->Spawn();
	// contact grenades arc lower
	pFATRONGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	UTIL_SetOrigin( pFATRONGrenade->pev, vecStart );
	pFATRONGrenade->pev->velocity = vecVelocity;
	pFATRONGrenade->pev->angles = UTIL_VecToAngles (pFATRONGrenade->pev->velocity);
	pFATRONGrenade->pev->owner = ENT(pevOwner);
	
	// make monsters afaid of it while in the air
	pFATRONGrenade->SetThink( DangerSoundThink );
	pFATRONGrenade->pev->nextthink = gpGlobals->time;
	
	// Tumble in air
	pFATRONGrenade->pev->avelocity.x = RANDOM_FLOAT ( -100, -500 );
	
	// Explode on contact
	pFATRONGrenade->SetTouch( ExplodeTouch );

	pFATRONGrenade->pev->dmg = gSkillData.plrDmgM203Grenade;

	return pFATRONGrenade;
}


CFATRONGrenade * CFATRONGrenade:: ShootTimed( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time )
{
	CFATRONGrenade *pFATRONGrenade = GetClassPtr( (CFATRONGrenade *)NULL );
	pFATRONGrenade->Spawn();
	UTIL_SetOrigin( pFATRONGrenade->pev, vecStart );
	pFATRONGrenade->pev->velocity = vecVelocity;
	pFATRONGrenade->pev->angles = UTIL_VecToAngles(pFATRONGrenade->pev->velocity);
	pFATRONGrenade->pev->owner = ENT(pevOwner);
	
	pFATRONGrenade->SetTouch( BounceTouch );	// Bounce if touched
	
	// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
	// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
	// the grenade explodes after the exact amount of time specified in the call to ShootTimed(). 

	pFATRONGrenade->pev->dmgtime = gpGlobals->time + time;
	pFATRONGrenade->SetThink( TumbleThink );
	pFATRONGrenade->pev->nextthink = gpGlobals->time + 0.1;
	if (time < 0.1)
	{
		pFATRONGrenade->pev->nextthink = gpGlobals->time;
		pFATRONGrenade->pev->velocity = Vector( 0, 0, 0 );
	}
		
	pFATRONGrenade->pev->sequence = RANDOM_LONG( 3, 6 );
	pFATRONGrenade->pev->framerate = 1.0;

	// Tumble through the air
	// pFATRONGrenade->pev->avelocity.x = -400;

	pFATRONGrenade->pev->gravity = 0.5;
	pFATRONGrenade->pev->friction = 0.8;

	SET_MODEL(ENT(pFATRONGrenade->pev), "models/w_FATRONgrenade.mdl");
	pFATRONGrenade->pev->dmg = 100;

	return pFATRONGrenade;
}


CFATRONGrenade * CFATRONGrenade :: ShootSatchelCharge( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity )
{
	CFATRONGrenade *pFATRONGrenade = GetClassPtr( (CFATRONGrenade *)NULL );
	pFATRONGrenade->pev->movetype = MOVETYPE_BOUNCE;
	pFATRONGrenade->pev->classname = MAKE_STRING( "FATRONgrenade" );
	
	pFATRONGrenade->pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pFATRONGrenade->pev), "models/grenade.mdl");	// Change this to satchel charge model

	UTIL_SetSize(pFATRONGrenade->pev, Vector( 0, 0, 0), Vector(0, 0, 0));

	pFATRONGrenade->pev->dmg = 200;
	UTIL_SetOrigin( pFATRONGrenade->pev, vecStart );
	pFATRONGrenade->pev->velocity = vecVelocity;
	pFATRONGrenade->pev->angles = g_vecZero;
	pFATRONGrenade->pev->owner = ENT(pevOwner);
	
	// Detonate in "time" seconds
	pFATRONGrenade->SetThink( SUB_DoNothing );
	pFATRONGrenade->SetUse( DetonateUse );
	pFATRONGrenade->SetTouch( SlideTouch );
	pFATRONGrenade->pev->spawnflags = SF_DETONATE;

	pFATRONGrenade->pev->friction = 0.9;

	return pFATRONGrenade;
}



void CFATRONGrenade :: UseSatchelCharges( entvars_t *pevOwner, SATCHELCODE code )
{
	edict_t *pentFind;
	edict_t *pentOwner;

	if ( !pevOwner )
		return;

	CBaseEntity	*pOwner = CBaseEntity::Instance( pevOwner );

	pentOwner = pOwner->edict();

	pentFind = FIND_ENTITY_BY_CLASSNAME( NULL, "FATRONgrenade" );
	while ( !FNullEnt( pentFind ) )
	{
		CBaseEntity *pEnt = Instance( pentFind );
		if ( pEnt )
		{
			if ( FBitSet( pEnt->pev->spawnflags, SF_DETONATE ) && pEnt->pev->owner == pentOwner )
			{
				if ( code == SATCHEL_DETONATE )
					pEnt->Use( pOwner, pOwner, USE_ON, 0 );
				else	// SATCHEL_RELEASE
					pEnt->pev->owner = NULL;
			}
		}
		pentFind = FIND_ENTITY_BY_CLASSNAME( pentFind, "FATRONgrenade" );
	}
}

//======================end FATRONgrenade

