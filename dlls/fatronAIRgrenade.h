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

#ifndef FATRON_AIRGRENADE_H
#define FATRON_AIRGRENADE_H


class CFatronFire : public CBaseEntity
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
	static CFatronFire *CreateFatronFireRocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );
	static CFatronFire *CreateFatronFireGrenade( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner, bool m_bIsAI );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

#endif // FATRON_AIRGRENADE_H
