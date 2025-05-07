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
// headcrab.cpp - tiny, jumpy alien parasite
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


//=========================================================
// Monster's Anim Events Go Here
//=========================================================
#define		HC_AE_JUMPATTACK	( 2 )
#define     VOLTIGORE_MAX_BEAMS		8
#define     VOLTIGORE_ZAP_RED 180
#define     VOLTIGORE_ZAP_GREEN 16
#define     VOLTIGORE_ZAP_BLUE 255
#define     VOLTIGORE_ZAP_BEAM "sprites/lgtning.spr"
#define     VOLTIGORE_ZAP_NOISE 80
#define     VOLTIGORE_ZAP_WIDTH 30
#define     VOLTIGORE_ZAP_BRIGHTNESS 255
#define     VOLTIGORE_ZAP_DISTANCE 512

Task_t	tlHCRangeAttack1[] =
{
	{ TASK_STOP_MOVING,			(float)0		},
	{ TASK_FACE_IDEAL,			(float)0		},
	{ TASK_RANGE_ATTACK1,		(float)0		},
	{ TASK_SET_ACTIVITY,		(float)ACT_IDLE	},
	{ TASK_FACE_IDEAL,			(float)0		},
	{ TASK_WAIT_RANDOM,			(float)0.5		},
};

Schedule_t	slHCRangeAttack1[] =
{
	{ 
		tlHCRangeAttack1,
		ARRAYSIZE ( tlHCRangeAttack1 ), 
		bits_COND_ENEMY_OCCLUDED	|
		bits_COND_NO_AMMO_LOADED,
		0,
		"HCRangeAttack1"
	},
};

Task_t	tlHCRangeAttack1Fast[] =
{
	{ TASK_STOP_MOVING,			(float)0		},
	{ TASK_FACE_IDEAL,			(float)0		},
	{ TASK_RANGE_ATTACK1,		(float)0		},
	{ TASK_SET_ACTIVITY,		(float)ACT_IDLE	},
};

Schedule_t	slHCRangeAttack1Fast[] =
{
	{ 
		tlHCRangeAttack1Fast,
		ARRAYSIZE ( tlHCRangeAttack1Fast ), 
		bits_COND_ENEMY_OCCLUDED	|
		bits_COND_NO_AMMO_LOADED,
		0,
		"HCRAFast"
	},
};

class CHeadCrab : public CBaseMonster
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
	void DeathSound( void );
	void IdleSound( void );
	void AlertSound( void );
	void PrescheduleThink( void );
	int  Classify ( void );
	void HandleAnimEvent( MonsterEvent_t *pEvent );
	BOOL CheckRangeAttack1 ( float flDot, float flDist );
	BOOL CheckRangeAttack2 ( float flDot, float flDist );
	int TakeDamage( entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType );

	CBeam* m_pBeam[VOLTIGORE_MAX_BEAMS];

	int m_iBeams;
	float m_timeToDie;
	int m_beamTexture;

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
	virtual void Laser12(void);	
	virtual void Laser13(void);
	virtual void Laser14(void);
	virtual void Laser15(void);
	virtual void Laser16(void);
	virtual void Laser17(void);
	virtual void Laser18(void);
	virtual void Laser19(void);
	virtual void Laser20(void);
 	virtual void Laser21(void);	
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
 	void EXPORT LaserTime12(void);
 	void EXPORT LaserTime13(void);
 	void EXPORT LaserTime14(void);
 	void EXPORT LaserTime15(void);
 	void EXPORT LaserTime16(void);
 	void EXPORT LaserTime17(void);
 	void EXPORT LaserTime18(void);
 	void EXPORT LaserTime19(void);
 	void EXPORT LaserTime20(void);
 	void EXPORT LaserTime21(void);

	virtual float GetDamageAmount( void ) { return gSkillData.headcrabDmgBite; }
	virtual int GetVoicePitch( void ) { return 100; }
	virtual float GetSoundVolue( void ) { return 1.0; }
	Schedule_t* GetScheduleOfType ( int Type );

	CUSTOM_SCHEDULES;

	static const char *pIdleSounds[];
	static const char *pAlertSounds[];
	static const char *pPainSounds[];
	static const char *pAttackSounds[];
	static const char *pDeathSounds[];
	static const char *pBiteSounds[];
};
LINK_ENTITY_TO_CLASS( monster_headcrab, CHeadCrab );

TYPEDESCRIPTION	CHeadCrab::m_SaveData[] =
{
	DEFINE_ARRAY(CHeadCrab, m_pBeam, FIELD_CLASSPTR, VOLTIGORE_MAX_BEAMS),
	DEFINE_FIELD(CHeadCrab, m_iBeams, FIELD_INTEGER),
	DEFINE_FIELD(CHeadCrab, m_timeToDie, FIELD_TIME),
};
IMPLEMENT_SAVERESTORE(CHeadCrab, CBaseEntity)

DEFINE_CUSTOM_SCHEDULES( CHeadCrab )
{
	slHCRangeAttack1,
	slHCRangeAttack1Fast,
};

IMPLEMENT_CUSTOM_SCHEDULES( CHeadCrab, CBaseMonster );

const char *CHeadCrab::pIdleSounds[] = 
{
	"headcrab/hc_idle1.wav",
	"headcrab/hc_idle2.wav",
	"headcrab/hc_idle3.wav",
};
const char *CHeadCrab::pAlertSounds[] = 
{
	"headcrab/hc_alert1.wav",
};
const char *CHeadCrab::pAttackSounds[] = 
{
	"headcrab/hc_attack1.wav",
	"headcrab/hc_attack2.wav",
	"headcrab/hc_attack3.wav",
};

const char *CHeadCrab::pDeathSounds[] = 
{
	"headcrab/hc_die1.wav",
	"headcrab/hc_die2.wav",
};

const char *CHeadCrab::pBiteSounds[] = 
{
	"headcrab/hc_headbite.wav",
};

//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CHeadCrab :: Classify ( void )
{
	return	CLASS_ALIEN_PREY;
}

//=========================================================
// Center - returns the real center of the headcrab.  The 
// bounding box is much larger than the actual creature so 
// this is needed for targeting
//=========================================================
Vector CHeadCrab :: Center ( void )
{
	return Vector( pev->origin.x, pev->origin.y, pev->origin.z + 6 );
}


Vector CHeadCrab :: BodyTarget( const Vector &posSrc ) 
{ 
	return Center( );
}

//=========================================================
// SetYawSpeed - allows each sequence to have a different
// turn rate associated with it.
//=========================================================
void CHeadCrab :: SetYawSpeed ( void )
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
void CHeadCrab :: HandleAnimEvent( MonsterEvent_t *pEvent )
{
	switch( pEvent->event )
	{
		case HC_AE_JUMPATTACK:
		{
			ClearBits( pev->flags, FL_ONGROUND );

			UTIL_SetOrigin (pev, pev->origin + Vector ( 0 , 0 , 1) );// take him off ground so engine doesn't instantly reset onground 
			UTIL_MakeVectors ( pev->angles );

			Vector vecJumpDir;
			if (m_hEnemy != NULL)
			{
				float gravity = g_psv_gravity->value;
				if (gravity <= 1)
					gravity = 1;

				// How fast does the headcrab need to travel to reach that height given gravity?
				float height = (m_hEnemy->pev->origin.z + m_hEnemy->pev->view_ofs.z - pev->origin.z);
				if (height < 16)
					height = 16;
				float speed = sqrt( 2 * gravity * height );
				float time = speed / gravity;

				// Scale the sideways velocity to get there at the right time
				vecJumpDir = (m_hEnemy->pev->origin + m_hEnemy->pev->view_ofs - pev->origin);
				vecJumpDir = vecJumpDir * ( 1.0 / time );

				// Speed to offset gravity at the desired height
				vecJumpDir.z = speed;

				// Don't jump too far/fast
				float distance = vecJumpDir.Length();
				
				if (distance > 650)
				{
					vecJumpDir = vecJumpDir * ( 650.0 / distance );
				}
			}
			else
			{
				// jump hop, don't care where
				vecJumpDir = Vector( gpGlobals->v_forward.x, gpGlobals->v_forward.y, gpGlobals->v_up.z ) * 350;
			}

			int iSound = RANDOM_LONG(0,2);
			if ( iSound != 0 )
				EMIT_SOUND_DYN( edict(), CHAN_VOICE, pAttackSounds[iSound], GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );

			pev->velocity = vecJumpDir;
			m_flNextAttack = gpGlobals->time + 2;
		}
		break;

		default:
			CBaseMonster::HandleAnimEvent( pEvent );
			break;
	}
}

//=========================================================
// Spawn
//=========================================================
void CHeadCrab :: Spawn()
{
	Precache( );

	SET_MODEL(ENT(pev), "models/null.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->solid			= SOLID_SLIDEBOX;
	pev->movetype		= MOVETYPE_STEP;
	m_bloodColor		= BLOOD_COLOR_GREEN;
	pev->effects		= 0;
	pev->health			= gSkillData.headcrabHealth;
	pev->view_ofs		= Vector ( 0, 0, 20 );// position of the eyes relative to monster's origin.
	pev->yaw_speed		= 5;//!!! should we put this in the monster's changeanim function since turn rates may vary with state/anim?
	m_flFieldOfView		= 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState		= MONSTERSTATE_NONE;

	MonsterInit();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CHeadCrab :: Precache()
{
	PRECACHE_SOUND_ARRAY(pIdleSounds);
	PRECACHE_SOUND_ARRAY(pAlertSounds);
	PRECACHE_SOUND_ARRAY(pAttackSounds);
	PRECACHE_SOUND_ARRAY(pDeathSounds);
	PRECACHE_SOUND_ARRAY(pBiteSounds);
	m_beamTexture = PRECACHE_MODEL(VOLTIGORE_ZAP_BEAM);

	PRECACHE_MODEL("models/null.mdl");
}	


//=========================================================
// RunTask 
//=========================================================
void CHeadCrab :: RunTask ( Task_t *pTask )
{
	switch ( pTask->iTask )
	{
	case TASK_RANGE_ATTACK1:
	case TASK_RANGE_ATTACK2:
		{
			if ( m_fSequenceFinished )
			{
				TaskComplete();
				SetTouch( NULL );
				m_IdealActivity = ACT_IDLE;
			}
			break;
		}
	default:
		{
			CBaseMonster :: RunTask(pTask);
		}
	}
}

//=========================================================
// LeapTouch - this is the headcrab's touch function when it
// is in the air
//=========================================================
void CHeadCrab :: LeapTouch ( CBaseEntity *pOther )
{
	if ( !pOther->pev->takedamage )
	{
		return;
	}

	if ( pOther->Classify() == Classify() )
	{
		return;
	}

	// Don't hit if back on ground
	if ( !FBitSet( pev->flags, FL_ONGROUND ) )
	{
		EMIT_SOUND_DYN( edict(), CHAN_WEAPON, RANDOM_SOUND_ARRAY(pBiteSounds), GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );
		
		pOther->TakeDamage( pev, pev, GetDamageAmount(), DMG_SLASH );
	}

	SetTouch( NULL );
}

//=========================================================
// PrescheduleThink
//=========================================================
void CHeadCrab :: PrescheduleThink ( void )
{
	// make the crab coo a little bit in combat state
	if ( m_MonsterState == MONSTERSTATE_COMBAT && RANDOM_FLOAT( 0, 5 ) < 0.1 )
	{
		IdleSound();
	}
}

void CHeadCrab :: StartTask ( Task_t *pTask )
{
	m_iTaskStatus = TASKSTATUS_RUNNING;

	switch ( pTask->iTask )
	{
	case TASK_RANGE_ATTACK1:
		{
			EMIT_SOUND_DYN( edict(), CHAN_WEAPON, pAttackSounds[0], GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );
			m_IdealActivity = ACT_RANGE_ATTACK1;
			SetTouch ( LeapTouch );
			break;
		}
	default:
		{
			CBaseMonster :: StartTask( pTask );
		}
	}
}


//=========================================================
// CheckRangeAttack1
//=========================================================
BOOL CHeadCrab :: CheckRangeAttack1 ( float flDot, float flDist )
{
	if ( FBitSet( pev->flags, FL_ONGROUND ) && flDist <= 256 && flDot >= 0.65 )
	{
		return TRUE;
	}
	return FALSE;
}

//=========================================================
// CheckRangeAttack2
//=========================================================
BOOL CHeadCrab :: CheckRangeAttack2 ( float flDot, float flDist )
{
	return FALSE;
	// BUGBUG: Why is this code here?  There is no ACT_RANGE_ATTACK2 animation.  I've disabled it for now.
#if 0
	if ( FBitSet( pev->flags, FL_ONGROUND ) && flDist > 64 && flDist <= 256 && flDot >= 0.5 )
	{
		return TRUE;
	}
	return FALSE;
#endif
}

int CHeadCrab :: TakeDamage( entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType )
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
void CHeadCrab :: IdleSound ( void )
{
	EMIT_SOUND_DYN( edict(), CHAN_VOICE, RANDOM_SOUND_ARRAY(pIdleSounds), GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );
}

//=========================================================
// AlertSound 
//=========================================================
void CHeadCrab :: AlertSound ( void )
{
	EMIT_SOUND_DYN( edict(), CHAN_VOICE, RANDOM_SOUND_ARRAY(pAlertSounds), GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );
}

//=========================================================
// DeathSound 
//=========================================================
void CHeadCrab :: DeathSound ( void )
{
	EMIT_SOUND_DYN( edict(), CHAN_VOICE, RANDOM_SOUND_ARRAY(pDeathSounds), GetSoundVolue(), ATTN_IDLE, 0, GetVoicePitch() );
}

Schedule_t* CHeadCrab :: GetScheduleOfType ( int Type )
{
	switch	( Type )
	{
		case SCHED_RANGE_ATTACK1:
		{
			return &slHCRangeAttack1[ 0 ];
		}
		break;
	}

	return CBaseMonster::GetScheduleOfType( Type );
}





void CHeadCrab::LaserTime(void)
{
	Laser();
}

void CHeadCrab::LaserTime2(void)
{
	Laser2();
}

void CHeadCrab::LaserTime3(void)
{
	Laser3();
}

void CHeadCrab::LaserTime4(void)
{
	Laser4();
}

void CHeadCrab::LaserTime5(void)
{
	Laser5();
}

void CHeadCrab::LaserTime6(void)
{
	Laser6();
}

void CHeadCrab::LaserTime7(void)
{
	Laser7();
}

void CHeadCrab::LaserTime8(void)
{
	Laser8();
}

void CHeadCrab::LaserTime9(void)
{
	Laser9();
}

void CHeadCrab::LaserTime10(void)
{
	Laser10();
}

void CHeadCrab::LaserTime11(void)
{
	Laser11();
}

void CHeadCrab::LaserTime12(void)
{
	Laser12();
}

void CHeadCrab::LaserTime13(void)
{
	Laser13();
}

void CHeadCrab::LaserTime14(void)
{
	Laser14();
}

void CHeadCrab::LaserTime15(void)
{
	Laser15();
}

void CHeadCrab::LaserTime16(void)
{
	Laser16();
}

void CHeadCrab::LaserTime17(void)
{
	Laser17();
}

void CHeadCrab::LaserTime18(void)
{
	Laser18();
}

void CHeadCrab::LaserTime19(void)
{
	Laser19();
}

void CHeadCrab::LaserTime20(void)
{
	Laser20();
}

void CHeadCrab::LaserTime21(void)
{
	Laser21();
}

void CHeadCrab::Laser(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser2(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser3(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser4(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser5(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser6(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser7(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser8(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser9(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser10(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser11(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime12 );
	pev->nextthink = gpGlobals->time + 0.1;
}


void CHeadCrab::Laser12(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime13 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser13(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime14 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser14(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime15 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser15(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime16 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser16(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime17 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser17(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime18 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser18(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime19 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser19(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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
	
	SetThink( LaserTime20 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CHeadCrab::Laser20(void)
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
		DecalGunshot( &tr, BULLET_PLAYER_CROWBAR );		

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

	SetThink( LaserTime21 );
	pev->nextthink = gpGlobals->time + 0.1;
}


void CHeadCrab::Laser21(void)
{	
    UTIL_Remove( this );
}
