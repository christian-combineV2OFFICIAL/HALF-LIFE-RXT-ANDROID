//========= Copyright © 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#if !defined ( EV_HLDMH )
#define EV_HLDMH

// bullet types
typedef	enum
{
	BULLET_NONE = 0,
	BULLET_PLAYER_9MM, // glock
	BULLET_PLAYER_MP5, // mp5
	BULLET_PLAYER_357, // python
	BULLET_PLAYER_BUCKSHOT, // shotgun
	BULLET_PLAYER_CROWBAR, // crowbar swipe
	BULLET_PLAYER_556, // m249
	BULLET_PLAYER_EAGLE,
	BULLET_PLAYER_762,

	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
	BULLET_MONSTER_357,
} Bullet;

enum glock_e {
	DEAGLE_IDLE1 = 0,
	DEAGLE_FIDGET,
	DEAGLE_FIRE1,
	DEAGLE_RELOAD,
	DEAGLE_HOLSTER,
	DEAGLE_DRAW,
	DEAGLE_IDLE2,
	DEAGLE_IDLE3
};

enum shotgun_e {
	SHOTGUN_KOSHAK_HL = 0,
	SHOTGUN_SHOOT1,
	SHOTGUN_SHOOT2,
	SHOTGUN_SHOOT3,
	SHOTGUN_RELOAD,
	SHOTGUN_DRAW
};

enum ak47_e
{
	AK47_IDLE1 = 0,
	AK47_LONGIDLE,
	AK47_RELOAD,
	AK47_DEPLOY,
	AK47_GRENADE,	
	AK47_FIRE1,
	AK47_FIRE2,
	AK47_FIRE3,
};

enum m16_e
{
	M16_IDLE1 = 0,
	M16_IDLE2,	
	M16_SHOOT,
	M16_SHOOT_SOLID,
	M16_GRENADE,
	M16_GRENADE_SOLID,	
	M16_RELOAD,
	M16_DRAW,
	M16_HOLSTER,
};

enum glauncher_e
{
	GLAUNCHER_KOSHAK_HL = 0,
	GLAUNCHER_DRAW,
	GLAUNCHER_SHOOT1,
	GLAUNCHER_START_RELOAD,
	GLAUNCHER_INSERT,
	GLAUNCHER_AFTER_RELOAD,
};

enum python_e {
	PYTHON_IDLE1 = 0,
	PYTHON_IDLE2,
	PYTHON_IDLE3,
	PYTHON_SHOOT,
	PYTHON_SHOOT_EMPTY,
	PYTHON_RELOAD,
	PYTHON_RELOAD_NOT_EMPTY,
	PYTHON_DRAW,
	PYTHON_HOLSTER,
	PYTHON_ADD_SILENCER
};

#define	GAUSS_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define GAUSS_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum gauss_e {
	GAUSS_IDLE = 0,
	GAUSS_IDLE2,
	GAUSS_FIDGET,
	GAUSS_SPINUP,
	GAUSS_SPIN,
	GAUSS_FIRE,
	GAUSS_FIRE2,
	GAUSS_HOLSTER,
	GAUSS_DRAW
};

#define	EGON_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define EGON_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum egon_e {
	EGON_IDLE1,
	EGON_FIRE_ALL,
	EGON_FIRE_ALL_SOLID,
	EGON_FIRE_BARREL1,
	EGON_FIRE_BARREL2,
	EGON_FIRE_BARREL3,
	EGON_FIRE_BARREL4,
	EGON_FIRE_BARREL1_SOLID,
	EGON_FIRE_BARREL2_SOLID,
	EGON_FIRE_BARREL3_SOLID,
	EGON_FIRE_BARREL4_SOLID,
	EGON_RELOAD,
	EGON_DRAW,
	EGON_HOLSTER
};

#define	REFLECTOR1_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define REFLECTOR1_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum reflector1_e {
	REFLECTOR1_IDLE = 0,
	REFLECTOR1_IDLE2,
	REFLECTOR1_FIDGET,
	REFLECTOR1_SPINUP,
	REFLECTOR1_SPIN,
	REFLECTOR1_FIRE,
	REFLECTOR1_FIRE2,
	REFLECTOR1_HOLSTER,
	REFLECTOR1_DRAW
};

#define	ETHERIAL_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define ETHERIAL_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum etherial_e {
	ETHERIAL_IDLE = 0,
	ETHERIAL_RELOAD,
	ETHERIAL_DRAW,
	ETHERIAL_FIRE_1,
	ETHERIAL_FIRE_2,
	ETHERIAL_FIRE_3
};

#define	MINIGUN_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define MINIGUN_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum minigun_e {
	MINIGUN_IDLE1,
	MINIGUN_IDLE2,
	MINIGUN_SPINUP,
	MINIGUN_SPINDOWN,
	MINIGUN_FIRE,
	MINIGUN_FIRE_SOLID,
	MINIGUN_RELOAD,
	MINIGUN_DRAW,
	MINIGUN_HOLSTER,
	MINIGUN_SPIN
};

#define	CYCLONE_PRIMARY_CHARGE_VOLUME	256// how loud gauss is while charging
#define CYCLONE_PRIMARY_FIRE_VOLUME	450// how loud gauss is when discharged

enum cyclone_e {
	CYCLONE_IDLE = 0,
	CYCLONE_SHOOT1,
	CYCLONE_SHOOT_END,
    CYCLONE_RELOAD,	
	CYCLONE_DRAW
};

void EV_HLDM_GunshotDecalTrace( pmtrace_t *pTrace, char *decalName );
void EV_HLDM_DecalGunshot( pmtrace_t *pTrace, int iBulletType );
int EV_HLDM_CheckTracer( int idx, float *vecSrc, float *end, float *forward, float *right, int iBulletType, int iTracerFreq, int *tracerCount );
void EV_HLDM_FireBullets( int idx, float *forward, float *right, float *up, int cShots, float *vecSrc, float *vecDirShooting, float flDistance, int iBulletType, int iTracerFreq, int *tracerCount, float flSpreadX, float flSpreadY );

#endif // EV_HLDMH