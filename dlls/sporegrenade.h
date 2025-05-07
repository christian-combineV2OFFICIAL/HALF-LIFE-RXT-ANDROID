/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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

#ifndef SPORE_GRENADE_H
#define SPORE_GRENADE_H


class CSpore : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void BounceSound( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	static CSpore *CreateSporeRocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CSpore *CreateSporeGrenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

class CSpore2 : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void BounceSound( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	static CSpore2 *CreateSpore2Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CSpore2 *CreateSpore2Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

class CSpore3 : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void BounceSound( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	static CSpore3 *CreateSpore3Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CSpore3 *CreateSpore3Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

class CSpore4 : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void BounceSound( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	static CSpore4 *CreateSpore4Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CSpore4 *CreateSpore4Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

class CSpore5 : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void BounceSound( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT BounceTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	static CSpore5 *CreateSpore5Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CSpore5 *CreateSpore5Grenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

#endif // SPORE_GRENADE_H
