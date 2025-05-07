/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
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
//=========================================================
// teleport.cpp - tiny, jumpy alien parasite
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"game.h"

class CShakemonster3 : public CBaseMonster
{
public:
	void Spawn( void );
	void Precache( void );

	void EXPORT Remove( void );
};
LINK_ENTITY_TO_CLASS( monster_shake3, CShakemonster3 );

//=========================================================
// Spawn
//=========================================================
void CShakemonster3 :: Spawn()
{
	Precache( );

	SET_MODEL(ENT(pev), "models/null.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->solid			= SOLID_SLIDEBOX;
	pev->movetype		= MOVETYPE_STEP;
	m_bloodColor		= BLOOD_COLOR_GREEN;
	pev->effects		= 0;
	pev->health			= 1000000000000;	
	pev->view_ofs		= Vector ( 0, 0, 20 );// position of the eyes relative to monster's origin.
	pev->yaw_speed		= 5;//!!! should we put this in the monster's changeanim function since turn rates may vary with state/anim?
	m_flFieldOfView		= 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState		= MONSTERSTATE_NONE;

	MonsterInit();

	SetThink ( Remove );
	pev->nextthink = gpGlobals->time + 5.0;
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CShakemonster3 :: Precache()
{
	PRECACHE_MODEL("models/null.mdl");
}	

void CShakemonster3 :: Remove ( void )
{
	UTIL_Remove( this );
}
