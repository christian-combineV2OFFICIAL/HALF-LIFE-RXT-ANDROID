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
#include "../hud.h"
#include "../cl_util.h"
#include "event_api.h"

extern "C"
{
// HLDM
void EV_FireGlock1( struct event_args_s *args  );
void EV_FireShotGunSingle( struct event_args_s *args  );
void EV_FireMP5( struct event_args_s *args  );
void EV_FireMP52( struct event_args_s *args  );
void EV_FirePython( struct event_args_s *args  );
void EV_FirePython2( struct event_args_s *args  );
void EV_FireGauss( struct event_args_s *args  );
void EV_SpinGauss( struct event_args_s *args  );
void EV_Crowbar( struct event_args_s *args );
void EV_FireCrossbow( struct event_args_s *args );
void EV_FireCrossbow2( struct event_args_s *args );
void EV_FireRpg( struct event_args_s *args );
void EV_FireEgon( struct event_args_s *args  );
void EV_FireEgon2( struct event_args_s *args  );
void EV_FireEgon3( struct event_args_s *args  );
void EV_FireEgon4( struct event_args_s *args  );
void EV_FireEgon2_1( struct event_args_s *args  );
void EV_FireEgon2_2( struct event_args_s *args  );
void EV_FireEgon2_3( struct event_args_s *args  );
void EV_FireEgon2_4( struct event_args_s *args  );
void EV_SpinEgon( struct event_args_s *args  );
void EV_FireM249( struct event_args_s *args );
void EV_TripmineFire( struct event_args_s *args );
void EV_TripmineFire2( struct event_args_s *args );
void EV_SnarkFire( struct event_args_s *args );
void EV_FireGlauncher( struct event_args_s *args  );
void EV_FireM16( struct event_args_s *args  );
void EV_FireM162( struct event_args_s *args  );
void EV_Reflector1Fire( struct event_args_s *args  );
void EV_Reflector1Spin( struct event_args_s *args  );
void EV_FireEtherial( struct event_args_s *args  );
void EV_SpinEtherial( struct event_args_s *args  );
void EV_FireMinigun( struct event_args_s *args  );
void EV_PlasmaFire( struct event_args_s *args );
void EV_PlasmaGunFire( struct event_args_s *args );
void EV_FireCyclone( struct event_args_s *args  );
void EV_SpinCyclone( struct event_args_s *args  );
void EV_Displacer( struct event_args_s *args );
void EV_Knife( struct event_args_s *args );
void EV_PipeWrench( struct event_args_s *args );
void EV_FireEagle( struct event_args_s *args );
void EV_FireSniper( struct event_args_s *args );
void EV_PenguinFire( struct event_args_s *args );
void EV_SporeFire( struct event_args_s *args );
void EV_ShockFire( struct event_args_s *args );
void EV_ShockFire2( struct event_args_s *args );
void EV_FireCrossbowboom( struct event_args_s *args );
void EV_FireCrossbowboom2( struct event_args_s *args );
void EV_Fists( struct event_args_s *args );
void EV_Fists2( struct event_args_s *args );
void EV_Fists3( struct event_args_s *args );
void EV_Fists4( struct event_args_s *args );
void EV_Katana( struct event_args_s *args );



void EV_TrainPitchAdjust( struct event_args_s *args );
}

/*
======================
Game_HookEvents

Associate script file name with callback functions.  Callback's must be extern "C" so
 the engine doesn't get confused about name mangling stuff.  Note that the format is
 always the same.  Of course, a clever mod team could actually embed parameters, behavior
 into the actual .sc files and create a .sc file parser and hook their functionality through
 that.. i.e., a scripting system.

That was what we were going to do, but we ran out of time...oh well.
======================
*/
void Game_HookEvents( void )
{
	gEngfuncs.pfnHookEvent( "events/glock1.sc",					EV_FireGlock1 );
	gEngfuncs.pfnHookEvent( "events/shotgun1.sc",				EV_FireShotGunSingle );
	gEngfuncs.pfnHookEvent( "events/mp5.sc",					EV_FireMP5 );
	gEngfuncs.pfnHookEvent( "events/mp52.sc",					EV_FireMP52 );
	gEngfuncs.pfnHookEvent( "events/python.sc",					EV_FirePython );
	gEngfuncs.pfnHookEvent( "events/python2.sc",				EV_FirePython2 );	
	gEngfuncs.pfnHookEvent( "events/gauss.sc",					EV_FireGauss );
	gEngfuncs.pfnHookEvent( "events/gaussspin.sc",				EV_SpinGauss );
	gEngfuncs.pfnHookEvent( "events/train.sc",					EV_TrainPitchAdjust );
	gEngfuncs.pfnHookEvent( "events/crowbar.sc",				EV_Crowbar );
	gEngfuncs.pfnHookEvent( "events/crossbow1.sc",				EV_FireCrossbow );
	gEngfuncs.pfnHookEvent( "events/crossbow2.sc",				EV_FireCrossbow2 );
	gEngfuncs.pfnHookEvent( "events/rpg.sc",					EV_FireRpg );
	gEngfuncs.pfnHookEvent( "events/egon_fire.sc",				EV_FireEgon );
	gEngfuncs.pfnHookEvent( "events/egon_fire2.sc",				EV_FireEgon2 );
	gEngfuncs.pfnHookEvent( "events/egon_fire3.sc",				EV_FireEgon3 );
	gEngfuncs.pfnHookEvent( "events/egon_fire4.sc",				EV_FireEgon4 );
	gEngfuncs.pfnHookEvent( "events/egon_fire2_1.sc",			EV_FireEgon2_1 );
	gEngfuncs.pfnHookEvent( "events/egon_fire2_2.sc",			EV_FireEgon2_2 );
	gEngfuncs.pfnHookEvent( "events/egon_fire2_3.sc",			EV_FireEgon2_3 );
	gEngfuncs.pfnHookEvent( "events/egon_fire2_4.sc",			EV_FireEgon2_4 );
	gEngfuncs.pfnHookEvent( "events/egon_fire_spin.sc",			EV_SpinEgon );
	gEngfuncs.pfnHookEvent( "events/m249.sc",                   EV_FireM249 );
	gEngfuncs.pfnHookEvent( "events/tripfire.sc",				EV_TripmineFire );
	gEngfuncs.pfnHookEvent( "events/tripfire2.sc",				EV_TripmineFire2 );	
	gEngfuncs.pfnHookEvent( "events/snarkfire.sc",				EV_SnarkFire );
	gEngfuncs.pfnHookEvent( "events/glauncher.sc",				EV_FireGlauncher );
	gEngfuncs.pfnHookEvent( "events/m16.sc",					EV_FireM16 );
	gEngfuncs.pfnHookEvent( "events/m162.sc",					EV_FireM162 );
	gEngfuncs.pfnHookEvent( "events/reflector1.sc",				EV_Reflector1Fire );
	gEngfuncs.pfnHookEvent( "events/reflector1spin.sc",			EV_Reflector1Spin );
	gEngfuncs.pfnHookEvent( "events/etherial.sc",				EV_FireEtherial );
	gEngfuncs.pfnHookEvent( "events/etherialspin.sc",			EV_SpinEtherial );
	gEngfuncs.pfnHookEvent( "events/minigun1.sc",				EV_FireMinigun );
	gEngfuncs.pfnHookEvent( "events/plasmarifle.sc",            EV_PlasmaFire );
	gEngfuncs.pfnHookEvent( "events/plasmagun.sc",              EV_PlasmaGunFire );
	gEngfuncs.pfnHookEvent( "events/cyclone.sc",				EV_FireCyclone );
	gEngfuncs.pfnHookEvent( "events/cyclonespin.sc",			EV_SpinCyclone );	
	gEngfuncs.pfnHookEvent( "events/displacer.sc",              EV_Displacer );
	gEngfuncs.pfnHookEvent( "events/knife.sc",                  EV_Knife );
	gEngfuncs.pfnHookEvent( "events/pipewrench.sc",             EV_PipeWrench );
	gEngfuncs.pfnHookEvent( "events/eagle.sc",                  EV_FireEagle );
	gEngfuncs.pfnHookEvent( "events/sniper.sc",                 EV_FireSniper );
	gEngfuncs.pfnHookEvent( "events/penguinfire.sc",            EV_PenguinFire );
	gEngfuncs.pfnHookEvent( "events/spore.sc",                  EV_SporeFire );
	gEngfuncs.pfnHookEvent( "events/shock.sc",                  EV_ShockFire );
	gEngfuncs.pfnHookEvent( "events/shock2.sc",                 EV_ShockFire2 );
	gEngfuncs.pfnHookEvent( "events/crossbowboom1.sc",			EV_FireCrossbowboom );
	gEngfuncs.pfnHookEvent( "events/crossbowboom2.sc",			EV_FireCrossbowboom2 );
	gEngfuncs.pfnHookEvent( "events/fists.sc",			        EV_Fists );
	gEngfuncs.pfnHookEvent( "events/fists2.sc",			        EV_Fists2 );
	gEngfuncs.pfnHookEvent( "events/fists3.sc",			        EV_Fists3 );
	gEngfuncs.pfnHookEvent( "events/fists4.sc",			        EV_Fists4 );
	gEngfuncs.pfnHookEvent( "events/katana.sc",				    EV_Katana );
}
