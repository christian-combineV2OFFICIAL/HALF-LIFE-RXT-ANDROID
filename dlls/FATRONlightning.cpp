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
// ElectricLightning.cpp - tiny, jumpy alien parasite
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"game.h"
#include    "weapons.h"
#include    "nodes.h"
#include    "soundent.h"
#include    "decals.h"
#include	"customentity.h"
#include	"effects.h"
#include	"explode.h"
#include	"func_break.h"
#include    "shake.h"

//=========================================================
// Monster's Anim Events Go Here
//=========================================================
#define		HC_AE_JUMPATTACK	( 2 )
#define     VOLTIGORE_MAX_BEAMS		10
#define     VOLTIGORE_ZAP_RED 255
#define     VOLTIGORE_ZAP_GREEN 0
#define     VOLTIGORE_ZAP_BLUE 0
#define     VOLTIGORE_ZAP_BEAM "sprites/lgtning.spr"
#define     VOLTIGORE_ZAP_NOISE 80
#define     VOLTIGORE_ZAP_WIDTH 30
#define     VOLTIGORE_ZAP_BRIGHTNESS 255
#define     VOLTIGORE_ZAP_DISTANCE 2000
#define     LASER1_ZAP_BEAM "sprites/laserlighting1.spr"
#define     LASER2_ZAP_BEAM "sprites/laserlighting2.spr"

class CFatronLightning : public CBaseMonster
{
public:

#ifndef CLIENT_DLL
	int		Save( CSave &save );
	int		Restore( CRestore &restore );
	static	TYPEDESCRIPTION m_SaveData[];
#endif	
	
	void Spawn( void );
	void Precache( void );
	void RunTask ( Task_t *pTask );
	void StartTask ( Task_t *pTask );
	void SetYawSpeed ( void );
	void EXPORT LeapTouch ( CBaseEntity *pOther );
	Vector Center( void );
	Vector BodyTarget( const Vector &posSrc );
	void PrescheduleThink( void );
	int  Classify ( void );
	void HandleAnimEvent( MonsterEvent_t *pEvent );
	int TakeDamage( entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType );

	CBeam* m_pBeam[VOLTIGORE_MAX_BEAMS];

	int m_iBeams;
	float m_timeToDie;
	int m_beamTexture;
	int m_LightningTexture1;
	int m_LightningTexture2;

	virtual void Laser(void);
	virtual void Laser2(void);	
	virtual void Laser3(void);
	virtual void Laser4(void);
	virtual void Laser5(void);
	virtual void Laser6(void);
	virtual void Laser7(void);
	virtual void Laser8(void);
	virtual void Laser9(void);
	virtual void Laser10(void);
	virtual void Laser11(void);		
	void EXPORT LaserTime(void);
 	void EXPORT LaserTime2(void);
 	void EXPORT LaserTime3(void);
 	void EXPORT LaserTime4(void);
 	void EXPORT LaserTime5(void);
 	void EXPORT LaserTime6(void);
 	void EXPORT LaserTime7(void);
 	void EXPORT LaserTime8(void);
 	void EXPORT LaserTime9(void);
 	void EXPORT LaserTime10(void);
 	void EXPORT LaserTime11(void);

	virtual int GetVoicePitch( void ) { return 100; }
	virtual float GetSoundVolue( void ) { return 1.0; }
};
LINK_ENTITY_TO_CLASS( monster_FATRONlightning, CFatronLightning );

TYPEDESCRIPTION	CFatronLightning::m_SaveData[] =
{
	DEFINE_ARRAY(CFatronLightning, m_pBeam, FIELD_CLASSPTR, VOLTIGORE_MAX_BEAMS),
	DEFINE_FIELD(CFatronLightning, m_iBeams, FIELD_INTEGER),
	DEFINE_FIELD(CFatronLightning, m_timeToDie, FIELD_TIME),
};
IMPLEMENT_SAVERESTORE(CFatronLightning, CBaseEntity)

//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CFatronLightning :: Classify ( void )
{
	return	CLASS_ALIEN_PREY;
}

//=========================================================
// Center - returns the real center of the ElectricLightning.  The 
// bounding box is much larger than the actual creature so 
// this is needed for targeting
//=========================================================
Vector CFatronLightning :: Center ( void )
{
	return Vector( pev->origin.x, pev->origin.y, pev->origin.z + 6 );
}


Vector CFatronLightning :: BodyTarget( const Vector &posSrc ) 
{ 
	return Center( );
}

//=========================================================
// SetYawSpeed - allows each sequence to have a different
// turn rate associated with it.
//=========================================================
void CFatronLightning :: SetYawSpeed ( void )
{
	int ys;

	switch ( m_Activity )
	{
	case ACT_IDLE:			
		ys = 30;
		break;
	case ACT_RUN:			
	case ACT_WALK:			
		ys = 20;
		break;
	case ACT_TURN_LEFT:
	case ACT_TURN_RIGHT:
		ys = 60;
		break;
	case ACT_RANGE_ATTACK1:	
		ys = 30;
		break;
	default:
		ys = 30;
		break;
	}

	pev->yaw_speed = ys;
}

//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//=========================================================
void CFatronLightning :: HandleAnimEvent( MonsterEvent_t *pEvent )
{
}

//=========================================================
// Spawn
//=========================================================
void CFatronLightning :: Spawn()
{
	Precache( );

	SET_MODEL(ENT(pev), "models/null.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0), Vector(0, 0, 0));

	pev->solid			= SOLID_SLIDEBOX;
	pev->movetype		= MOVETYPE_STEP;
	m_bloodColor		= BLOOD_COLOR_GREEN;
	pev->effects		= 0;
	pev->health			= gSkillData.headcrabHealth;
	pev->view_ofs		= Vector ( 0, 0, 20 );// position of the eyes relative to monster's origin.
	pev->yaw_speed		= 5;//!!! should we put this in the monster's changeanim function since turn rates may vary with state/anim?
	m_flFieldOfView		= 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState		= MONSTERSTATE_NONE;

	MonsterInit2();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CFatronLightning :: Precache()
{
	m_beamTexture = PRECACHE_MODEL(VOLTIGORE_ZAP_BEAM); 
	m_LightningTexture1 = PRECACHE_MODEL(LASER1_ZAP_BEAM);
    m_LightningTexture2 = PRECACHE_MODEL(LASER2_ZAP_BEAM);

	PRECACHE_MODEL("models/null.mdl");
}	


//=========================================================
// RunTask 
//=========================================================
void CFatronLightning :: RunTask ( Task_t *pTask )
{
}

//=========================================================
// LeapTouch - this is the ElectricLightning's touch function when it
// is in the air
//=========================================================
void CFatronLightning :: LeapTouch ( CBaseEntity *pOther )
{
}

//=========================================================
// PrescheduleThink
//=========================================================
void CFatronLightning :: PrescheduleThink ( void )
{
}

void CFatronLightning :: StartTask ( Task_t *pTask )
{
}

int CFatronLightning :: TakeDamage( entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType )
{
	// Don't take any acid damage -- BigMomma's mortar is acid
	if ( bitsDamageType & DMG_ACID )
		flDamage = 0;

    LaserTime();

	return CBaseMonster::TakeDamage( pevInflictor, pevAttacker, flDamage, bitsDamageType );
}

//=========================================================
// IdleSound
//=========================================================
#define CRAB_ATTN_IDLE (float)1.5

void CFatronLightning::LaserTime(void)
{
	Laser();
}

void CFatronLightning::LaserTime2(void)
{
	Laser2();
}

void CFatronLightning::LaserTime3(void)
{
	Laser3();
}

void CFatronLightning::LaserTime4(void)
{
	Laser4();
}

void CFatronLightning::LaserTime5(void)
{
	Laser5();
}

void CFatronLightning::LaserTime6(void)
{
	Laser6();
}

void CFatronLightning::LaserTime7(void)
{
	Laser7();
}

void CFatronLightning::LaserTime8(void)
{
	Laser8();
}

void CFatronLightning::LaserTime9(void)
{
	Laser9();
}

void CFatronLightning::LaserTime10(void)
{
	Laser10();
}

void CFatronLightning::LaserTime11(void)
{
	Laser11();
}

void CFatronLightning::Laser(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime2 );
	pev->nextthink = gpGlobals->time + 1.5;
}

void CFatronLightning::Laser2(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime3 );
	pev->nextthink = gpGlobals->time + 2.0;
}

void CFatronLightning::Laser3(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime4 );
	pev->nextthink = gpGlobals->time + 2.5;
}

void CFatronLightning::Laser4(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime5 );
	pev->nextthink = gpGlobals->time + 3.0;
}

void CFatronLightning::Laser5(void)
{		
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime6 );
	pev->nextthink = gpGlobals->time + 3.5;
}

void CFatronLightning::Laser6(void)
{		
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime7 );
	pev->nextthink = gpGlobals->time + 4.0;
}

void CFatronLightning::Laser7(void)
{		
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime8 );
	pev->nextthink = gpGlobals->time + 4.5;
}

void CFatronLightning::Laser8(void)
{		
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime9 );
	pev->nextthink = gpGlobals->time + 5.0;
}

void CFatronLightning::Laser9(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime10 );
	pev->nextthink = gpGlobals->time + 5.5;
}

void CFatronLightning::Laser10(void)
{	
	int iTimes = 0;
	int iDrawn = 0;
	const int iBeams = VOLTIGORE_MAX_BEAMS;
	
	while( iDrawn < iBeams && iTimes < ( iBeams * 3 ) )
	{
		TraceResult tr;
		const Vector vecOrigin = Center();
		const Vector vecDest = VOLTIGORE_ZAP_DISTANCE * ( Vector( RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ), RANDOM_FLOAT( -1, 1 ) ).Normalize() );
		UTIL_TraceLine( vecOrigin, vecOrigin + vecDest, ignore_monsters, ENT( pev ), &tr );		
        UTIL_DecalTrace( &tr, DECAL_SMALLSCORCH1 );		
		UTIL_Sparks(tr.vecEndPos);	

		if( tr.flFraction != 1.0 )
		{				
			// we hit something.
			iDrawn++;
			MESSAGE_BEGIN( MSG_BROADCAST, SVC_TEMPENTITY );
				WRITE_BYTE( TE_BEAMPOINTS );
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );
				WRITE_COORD( tr.vecEndPos.x );
				WRITE_COORD( tr.vecEndPos.y );
				WRITE_COORD( tr.vecEndPos.z );
				WRITE_SHORT( m_beamTexture );
				WRITE_BYTE( 0 ); // framestart
				WRITE_BYTE( 10 ); // framerate
				WRITE_BYTE( 1 ); // life
				WRITE_BYTE( VOLTIGORE_ZAP_WIDTH );  // width
				WRITE_BYTE( VOLTIGORE_ZAP_NOISE );   // noise
				WRITE_BYTE( VOLTIGORE_ZAP_RED );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_GREEN);   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BLUE );   // r, g, b
				WRITE_BYTE( VOLTIGORE_ZAP_BRIGHTNESS );	// brightness
				WRITE_BYTE( 35 );		// speed
			MESSAGE_END();		
		}
		iTimes++;
	}	

	SetThink( LaserTime11 );
	pev->nextthink = gpGlobals->time + 6.0;
}

void CFatronLightning::Laser11(void)
{	
    UTIL_Remove( this );
}
