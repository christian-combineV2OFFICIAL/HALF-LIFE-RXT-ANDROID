//=================================
// Opposing Forces spore ammo plant 
// Copyright Demiurge
//=================================


#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "soundent.h"
#include "gamerules.h"
#include "explode.h"
#include "fatronAIRgrenade.h"
#include "shake.h"

//=========================================================
// Opposing Forces Spore Ammo
//=========================================================
#define		SACK_GROUP			1
#define		SACK_EMPTY			0
#define		SACK_FULL			1


class CFatronFireAmmo : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );
	void EXPORT BornThink ( void );
	void EXPORT IdleThink ( void );
	void EXPORT AmmoTouch ( CBaseEntity *pOther );
	int  TakeDamage( entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType );

	int	Save( CSave &save ); 
	int Restore( CRestore &restore );
	static TYPEDESCRIPTION m_SaveData[];

	float borntime;
	float m_flTimeSporeIdle;
};


typedef enum
{
	FATRONFIREAMMO_IDLE = 0,
	FATRONFIREAMMO_SPAWNUP,
	FATRONFIREAMMO_SNATCHUP,
	FATRONFIREAMMO_SPAWNDOWN,
	FATRONFIREAMMO_SNATCHDOWN,
	FATRONFIREAMMO_IDLE1,
	FATRONFIREAMMO_IDLE2,
} FATRONFIREAMMO;

LINK_ENTITY_TO_CLASS( ammo_firefatron, CFatronFireAmmo );

TYPEDESCRIPTION	CFatronFireAmmo::m_SaveData[] = 
{
	DEFINE_FIELD( CFatronFireAmmo, m_flTimeSporeIdle, FIELD_TIME ),
	DEFINE_FIELD( CFatronFireAmmo, borntime, FIELD_FLOAT ),
};
IMPLEMENT_SAVERESTORE( CFatronFireAmmo, CBaseEntity );

void CFatronFireAmmo :: Precache( void )
{
	PRECACHE_MODEL("models/null.mdl");
}
//=========================================================
// Spawn
//=========================================================
void CFatronFireAmmo :: Spawn( void )
{
	TraceResult tr;
	Precache( );
	SET_MODEL(ENT(pev), "models/null.mdl");
	UTIL_SetSize(pev, Vector( 0, 0, 0 ), Vector( 0, 0, 0 ));
	pev->takedamage = DAMAGE_YES;
	pev->solid			= SOLID_BBOX;
	pev->movetype		= MOVETYPE_NONE;
	pev->framerate		= 1.0;
	pev->animtime		= gpGlobals->time + 0.1;
	borntime = 0;

	pev->sequence = FATRONFIREAMMO_IDLE;
	pev->body = 0;

	pev->angles.x = 0;// :3

	Vector vecOrigin = pev->origin;
	vecOrigin.z += 16;
	UTIL_SetOrigin( pev, vecOrigin );

	SetThink (&CFatronFireAmmo::BornThink);
	SetTouch (&CFatronFireAmmo::AmmoTouch);
	
	m_flTimeSporeIdle = gpGlobals->time + 0;
	pev->nextthink = gpGlobals->time + 0.1;
}
	
//=========================================================
// Override all damage
//=========================================================
int CFatronFireAmmo::TakeDamage( entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType )
{
	if (!borntime) // rigth '!borntime'  // blast in anytime 'borntime || !borntime'
	{
		CBaseEntity *attacker = GetClassPtr( (CBaseEntity*)pevAttacker );
		Vector vecSrc = pev->origin + gpGlobals->v_forward * -32;
			
		//ALERT( at_console, "angles %f %f %f\n", pev->angles.x, pev->angles.y, pev->angles.z );

		Vector angles = pev->angles;
		angles.x -= 90;
		angles.y += 180;

		Vector vecLaunchDir = angles;

		//ALERT( at_console, "angles %f %f %f\n", angles.x, angles.y, angles.z );
		//CBaseEntity *pSpore = CFatronFireGrenade::ShootTimed(attacker->pev, vecSrc, gpGlobals->v_forward * 1000, RANDOM_FLOAT(5, 6));
		//pSpore->pev->angles = vecLaunchDir;
		UTIL_MakeVectors( vecLaunchDir );
		CFatronFire *pFatronFire = CFatronFire::CreateFatronFireGrenade( vecSrc, vecLaunchDir, attacker, FALSE );
		pFatronFire->pev->velocity = pFatronFire->pev->velocity + gpGlobals->v_forward * 1000;

		pev->framerate		= 1.0;
		pev->animtime		= gpGlobals->time + 0.1;
		pev->sequence		= FATRONFIREAMMO_SNATCHDOWN;
		pev->body			= 0;
		borntime			= 1;
		m_flTimeSporeIdle = gpGlobals->time + 1;
		SetThink (&CFatronFireAmmo::IdleThink);
	
	    UTIL_ScreenFadeAll( Vector(255,0,0), 5, 0.5, 130, FFADE_IN );

		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/lightning.wav", 1, ATTN_NORM);
	}
	UTIL_Remove( this );
	return 0;
}

//=========================================================
// Thinking begin
//=========================================================
void CFatronFireAmmo :: BornThink ( void )
{
	pev->nextthink = gpGlobals->time + 0.1;

	if ( m_flTimeSporeIdle > gpGlobals->time )
		return;

	pev->sequence = 3;
	pev->framerate		= 1.0;
	pev->animtime		= gpGlobals->time + 0.1;
	pev->body = 1;
	borntime = 0;
	SetThink (&CFatronFireAmmo::IdleThink);
	
	m_flTimeSporeIdle = gpGlobals->time + 16;
}

void CFatronFireAmmo :: IdleThink ( void )
{

	pev->nextthink = gpGlobals->time + 0.1;
	if ( m_flTimeSporeIdle > gpGlobals->time )
		return;

	if (borntime)
	{
		pev->sequence = FATRONFIREAMMO_IDLE;

		m_flTimeSporeIdle = gpGlobals->time + 19;
		SetThink(&CFatronFireAmmo::BornThink);
		return;
	}
	else
	{
		pev->sequence = FATRONFIREAMMO_IDLE1;
	}
}

void CFatronFireAmmo :: AmmoTouch ( CBaseEntity *pOther )
{
}