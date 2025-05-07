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

#ifndef PLASMA2_H
#define PLASMA2_H


class CPlasma2 : public CBaseEntity
{
public:
	void Spawn( void );
	void Precache( void );

	void Glow( void );
	void Explode( void );
	void EXPORT RocketTouch( CBaseEntity *pOther );
	void EXPORT FlyThink( void );
	void ClearEffects();	
	static CPlasma2 *CreatePlasma2Rocket( Vector vecOrigin, Vector vecAngles, CBaseEntity *pOwner );

	float m_iDrips;
	float m_iGlow;
	float m_iExplode;
	float m_iExplodeC;
	int m_iPrimaryMode;
	bool m_bIsAI;
	CSprite *m_pSprite;
};

#endif // PLASMA2_H
