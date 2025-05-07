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
#include "player.h"
#include "saverestore.h"
#include "trains.h"			// trigger_camera has train functionality
#include "gamerules.h"
#include "monsters.h"
#include "schedule.h"
#include "game.h"
#include "weapons.h"
#include "shake.h"

class CBaseTrigger : public CBaseToggle
{
public:
	void EXPORT ShakeTouch ( CBaseEntity *pOther );
	void EXPORT ShakeRemove( void );	
	void InitTrigger2( void );
};

//======================================
// teleport portal
//
//

void CBaseTrigger :: ShakeTouch( CBaseEntity *pOther )
{
	entvars_t* pevToucher = pOther->pev;
	edict_t	*pentTarget = NULL;

	// Only teleport monsters or clients
	if ( !FBitSet( pevToucher->flags, FL_CLIENT ) )
		return;
    
	if (!UTIL_IsMasterTriggered(m_sMaster, pOther))
		return;
 	
	if ( ( pev->spawnflags & SF_TRIGGER_ALLOWMONSTERS ) )
	{// no monsters allowed!
		if ( FBitSet( pevToucher->flags, FL_MONSTER ) )
		{
			return;
		}
	}

	if ( ( pev->spawnflags & SF_TRIGGER_NOCLIENTS ) )
	{// no clients allowed
		if ( pOther->IsPlayer() )
		{
			return;
		}
	}

	CBaseEntity::Create( "monster_shake3", pev->origin, pev->angles, edict() );
}

void CBaseTrigger :: ShakeRemove()
{
    SetThink( ShakeRemove );
    pev->nextthink = gpGlobals->time + 0.1;	
	
	edict_t	*pentTarget = NULL;

	pentTarget = FIND_ENTITY_BY_STRING( pentTarget, "classname", "monster_shake4" );
	if (FNullEnt(pentTarget))
	   return;
	UTIL_Remove( this );
}

/*
================
InitTrigger
================
*/
void CBaseTrigger::InitTrigger2( )
{
	// trigger angles are used for one-way touches.  An angle of 0 is assumed
	// to mean no restrictions, so use a yaw of 360 instead.
	if (pev->angles != g_vecZero)
		SetMovedir(pev);
	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_NONE;
	SET_MODEL(ENT(pev), STRING(pev->model));    // set size and link into world
	if ( CVAR_GET_FLOAT("showtriggers") == 0 )
		SetBits( pev->effects, EF_NODRAW );
}

class CTriggerShake : public CBaseTrigger
{
public:
	void Spawn( void );
};
LINK_ENTITY_TO_CLASS( trigger_shake, CTriggerShake );

void CTriggerShake :: Spawn( void )
{	
	UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX);	
	
	InitTrigger2();

	SetTouch( ShakeTouch );

    SetThink( ShakeRemove );
    pev->nextthink = gpGlobals->time + 0.1;	
}