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

class CFatronLightningFASE2 : public CBaseMonster
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
	virtual void Laser22(void);		
	virtual void Laser23(void);		
	virtual void Laser24(void);		
	virtual void Laser25(void);		
	virtual void Laser26(void);		
	virtual void Laser27(void);		
	virtual void Laser28(void);		
	virtual void Laser29(void);		
	virtual void Laser30(void);		
	virtual void Laser31(void);		
	virtual void Laser32(void);		
	virtual void Laser33(void);		
	virtual void Laser34(void);		
	virtual void Laser35(void);		
	virtual void Laser36(void);		
	virtual void Laser37(void);		
	virtual void Laser38(void);		
	virtual void Laser39(void);		
	virtual void Laser40(void);		
	virtual void Laser41(void);		
	virtual void Laser42(void);		
	virtual void Laser43(void);		
	virtual void Laser44(void);		
	virtual void Laser45(void);		
	virtual void Laser46(void);		
	virtual void Laser47(void);		
	virtual void Laser48(void);		
	virtual void Laser49(void);		
	virtual void Laser50(void);		
	virtual void Laser51(void);		
	virtual void Laser52(void);		
	virtual void Laser53(void);		
	virtual void Laser54(void);		
	virtual void Laser55(void);		
	virtual void Laser56(void);		
	virtual void Laser57(void);		
	virtual void Laser58(void);		
	virtual void Laser59(void);		
	virtual void Laser60(void);		
	virtual void Laser61(void);		
	virtual void Laser62(void);		
	virtual void Laser63(void);		
	virtual void Laser64(void);		
	virtual void Laser65(void);		
	virtual void Laser66(void);		
	virtual void Laser67(void);		
	virtual void Laser68(void);		
	virtual void Laser69(void);		
	virtual void Laser70(void);		
	virtual void Laser71(void);		
	virtual void Laser72(void);		
	virtual void Laser73(void);		
	virtual void Laser74(void);		
	virtual void Laser75(void);		
	virtual void Laser76(void);		
	virtual void Laser77(void);	
	virtual void Laser78(void);		
	virtual void Laser79(void);		
	virtual void Laser80(void);		
	virtual void Laser81(void);		
	virtual void Laser82(void);		
	virtual void Laser83(void);		
	virtual void Laser84(void);		
	virtual void Laser85(void);		
	virtual void Laser86(void);		
	virtual void Laser87(void);		
	virtual void Laser88(void);		
	virtual void Laser89(void);		
	virtual void Laser90(void);		
	virtual void Laser91(void);		
	virtual void Laser92(void);		
	virtual void Laser93(void);		
	virtual void Laser94(void);		
	virtual void Laser95(void);		
	virtual void Laser96(void);		
	virtual void Laser97(void);		
	virtual void Laser98(void);		
	virtual void Laser99(void);		
	virtual void Laser100(void);		
	virtual void Laser101(void);		
	virtual void Laser102(void);	
	virtual void Laser103(void);	
	virtual void Laser104(void);	
	virtual void Laser105(void);	
	virtual void Laser106(void);	
	virtual void Laser107(void);	
	virtual void Laser108(void);	
	virtual void Laser109(void);	
	virtual void Laser110(void);	
	virtual void Laser111(void);	
	virtual void Laser112(void);	
	virtual void Laser113(void);	
	virtual void Laser114(void);	
	virtual void Laser115(void);	
	virtual void Laser116(void);	
	virtual void Laser117(void);	
	virtual void Laser118(void);	
	virtual void Laser119(void);	
	virtual void Laser120(void);	
	virtual void Laser121(void);	
	virtual void Laser122(void);	
	virtual void Laser123(void);	
	virtual void Laser124(void);	
	virtual void Laser125(void);	
	virtual void Laser126(void);	
	virtual void Laser127(void);	
	virtual void Laser128(void);	
	virtual void Laser129(void);	
	virtual void Laser130(void);	
	virtual void Laser131(void);	
	virtual void Laser132(void);	
	virtual void Laser133(void);	
	virtual void Laser134(void);	
	virtual void Laser135(void);	
	virtual void Laser136(void);	
	virtual void Laser137(void);	
	virtual void Laser138(void);	
	virtual void Laser139(void);
	virtual void Laser140(void);	
	virtual void Laser141(void);	
	virtual void Laser142(void);	
	virtual void Laser143(void);	
	virtual void Laser144(void);	
	virtual void Laser145(void);	
	virtual void Laser146(void);	
	virtual void Laser147(void);	
	virtual void Laser148(void);	
	virtual void Laser149(void);	
	virtual void Laser150(void);	
	virtual void Laser151(void);	
	virtual void Laser152(void);	
	virtual void Laser153(void);	
	virtual void Laser154(void);	
	virtual void Laser155(void);	
	virtual void Laser156(void);	
	virtual void Laser157(void);	
	virtual void Laser158(void);	
	virtual void Laser159(void);	
	virtual void Laser160(void);	
	virtual void Laser161(void);	
	virtual void Laser162(void);	
	virtual void Laser163(void);	
	virtual void Laser164(void);	
	virtual void Laser165(void);	
	virtual void Laser166(void);	
	virtual void Laser167(void);	
	virtual void Laser168(void);	
	virtual void Laser169(void);
	virtual void Laser170(void);
	virtual void Laser171(void);
	virtual void Laser172(void);
	virtual void Laser173(void);
	virtual void Laser174(void);
	virtual void Laser175(void);
	virtual void Laser176(void);
	virtual void Laser177(void);
	virtual void Laser178(void);
	virtual void Laser179(void);
	virtual void Laser180(void);
	virtual void Laser181(void);
	virtual void Laser182(void);
	virtual void Laser183(void);
	virtual void Laser184(void);
	virtual void Laser185(void);
	virtual void Laser186(void);
	virtual void Laser187(void);
	virtual void Laser188(void);
	virtual void Laser189(void);
	virtual void Laser190(void);
	virtual void Laser191(void);
	virtual void Laser192(void);
	virtual void Laser193(void);
	virtual void Laser194(void);
	virtual void Laser195(void);
	virtual void Laser196(void);
	virtual void Laser197(void);
	virtual void Laser198(void);
	virtual void Laser199(void);
	virtual void Laser200(void);		
	virtual void Laser201(void);		
	virtual void Laser202(void);	
	virtual void Laser203(void);	
	virtual void Laser204(void);	
	virtual void Laser205(void);	
	virtual void Laser206(void);	
	virtual void Laser207(void);	
	virtual void Laser208(void);	
	virtual void Laser209(void);	
	virtual void Laser210(void);	
	virtual void Laser211(void);	
	virtual void Laser212(void);	
	virtual void Laser213(void);	
	virtual void Laser214(void);	
	virtual void Laser215(void);	
	virtual void Laser216(void);	
	virtual void Laser217(void);	
	virtual void Laser218(void);	
	virtual void Laser219(void);	
	virtual void Laser220(void);	
	virtual void Laser221(void);	
	virtual void Laser222(void);	
	virtual void Laser223(void);	
	virtual void Laser224(void);	
	virtual void Laser225(void);	
	virtual void Laser226(void);	
	virtual void Laser227(void);	
	virtual void Laser228(void);	
	virtual void Laser229(void);	
	virtual void Laser230(void);	
	virtual void Laser231(void);	
	virtual void Laser232(void);	
	virtual void Laser233(void);	
	virtual void Laser234(void);	
	virtual void Laser235(void);	
	virtual void Laser236(void);	
	virtual void Laser237(void);	
	virtual void Laser238(void);	
	virtual void Laser239(void);
	virtual void Laser240(void);	
	virtual void Laser241(void);	
	virtual void Laser242(void);	
	virtual void Laser243(void);	
	virtual void Laser244(void);	
	virtual void Laser245(void);	
	virtual void Laser246(void);	
	virtual void Laser247(void);	
	virtual void Laser248(void);	
	virtual void Laser249(void);	
	virtual void Laser250(void);	
	virtual void Laser251(void);	
	virtual void Laser252(void);	
	virtual void Laser253(void);	
	virtual void Laser254(void);	
	virtual void Laser255(void);	
	virtual void Laser256(void);	
	virtual void Laser257(void);	
	virtual void Laser258(void);	
	virtual void Laser259(void);	
	virtual void Laser260(void);	
	virtual void Laser261(void);	
	virtual void Laser262(void);	
	virtual void Laser263(void);	
	virtual void Laser264(void);	
	virtual void Laser265(void);	
	virtual void Laser266(void);	
	virtual void Laser267(void);	
	virtual void Laser268(void);	
	virtual void Laser269(void);
	virtual void Laser270(void);
	virtual void Laser271(void);
	virtual void Laser272(void);
	virtual void Laser273(void);
	virtual void Laser274(void);
	virtual void Laser275(void);
	virtual void Laser276(void);
	virtual void Laser277(void);
	virtual void Laser278(void);
	virtual void Laser279(void);
	virtual void Laser280(void);
	virtual void Laser281(void);
	virtual void Laser282(void);
	virtual void Laser283(void);
	virtual void Laser284(void);
	virtual void Laser285(void);
	virtual void Laser286(void);
	virtual void Laser287(void);
	virtual void Laser288(void);
	virtual void Laser289(void);
	virtual void Laser290(void);
	virtual void Laser291(void);
	virtual void Laser292(void);
	virtual void Laser293(void);
	virtual void Laser294(void);
	virtual void Laser295(void);
	virtual void Laser296(void);
	virtual void Laser297(void);
	virtual void Laser298(void);
	virtual void Laser299(void);	
	virtual void Laser300(void);	
    virtual void Laser301(void);	
	virtual void Laser302(void);	
	virtual void Laser303(void);	
	virtual void Laser304(void);	
	virtual void Laser305(void);	
	virtual void Laser306(void);	
	virtual void Laser307(void);	
	virtual void Laser308(void);	
	virtual void Laser309(void);	
	virtual void Laser310(void);	
	virtual void Laser311(void);	
	virtual void Laser312(void);	
	virtual void Laser313(void);	
	virtual void Laser314(void);	
	virtual void Laser315(void);	
	virtual void Laser316(void);	
	virtual void Laser317(void);	
	virtual void Laser318(void);	
	virtual void Laser319(void);	
	virtual void Laser320(void);	
	virtual void Laser321(void);	
	virtual void Laser322(void);	
	virtual void Laser323(void);	
	virtual void Laser324(void);	
	virtual void Laser325(void);	
	virtual void Laser326(void);	
	virtual void Laser327(void);	
	virtual void Laser328(void);	
	virtual void Laser329(void);	
	virtual void Laser330(void);	
	virtual void Laser331(void);	
	virtual void Laser332(void);	
	virtual void Laser333(void);	
	virtual void Laser334(void);	
	virtual void Laser335(void);	
	virtual void Laser336(void);	
	virtual void Laser337(void);	
	virtual void Laser338(void);	
	virtual void Laser339(void);
	virtual void Laser340(void);	
	virtual void Laser341(void);	
	virtual void Laser342(void);	
	virtual void Laser343(void);	
	virtual void Laser344(void);	
	virtual void Laser345(void);	
	virtual void Laser346(void);	
	virtual void Laser347(void);	
	virtual void Laser348(void);	
	virtual void Laser349(void);	
	virtual void Laser350(void);	
	virtual void Laser351(void);    
	virtual void Laser352(void);	
	virtual void Laser353(void);	
	virtual void Laser354(void);	
	virtual void Laser355(void);	
	virtual void Laser356(void);	
	virtual void Laser357(void);	
	virtual void Laser358(void);	
	virtual void Laser359(void);	
	virtual void Laser360(void);	
	virtual void Laser361(void);		
	virtual void Laser362(void);	
	virtual void Laser363(void);	
	virtual void Laser364(void);	
	virtual void Laser365(void);	
	virtual void Laser366(void);	
	virtual void Laser367(void);	
	virtual void Laser368(void);	
	virtual void Laser369(void);	
	virtual void Laser370(void);	
	virtual void Laser371(void);	
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
 	void EXPORT LaserTime22(void);
 	void EXPORT LaserTime23(void);
 	void EXPORT LaserTime24(void);
 	void EXPORT LaserTime25(void);
 	void EXPORT LaserTime26(void);
 	void EXPORT LaserTime27(void);
 	void EXPORT LaserTime28(void);
 	void EXPORT LaserTime29(void);
 	void EXPORT LaserTime30(void);
 	void EXPORT LaserTime31(void);
 	void EXPORT LaserTime32(void);
 	void EXPORT LaserTime33(void);
 	void EXPORT LaserTime34(void);
 	void EXPORT LaserTime35(void);
 	void EXPORT LaserTime36(void);
 	void EXPORT LaserTime37(void);
 	void EXPORT LaserTime38(void);
 	void EXPORT LaserTime39(void);
 	void EXPORT LaserTime40(void);
 	void EXPORT LaserTime41(void);
 	void EXPORT LaserTime42(void);
 	void EXPORT LaserTime43(void);
 	void EXPORT LaserTime44(void);
 	void EXPORT LaserTime45(void);
 	void EXPORT LaserTime46(void);
 	void EXPORT LaserTime47(void);
 	void EXPORT LaserTime48(void);
 	void EXPORT LaserTime49(void);
 	void EXPORT LaserTime50(void);
 	void EXPORT LaserTime51(void);
 	void EXPORT LaserTime52(void);
 	void EXPORT LaserTime53(void);
 	void EXPORT LaserTime54(void);
 	void EXPORT LaserTime55(void);
 	void EXPORT LaserTime56(void);
 	void EXPORT LaserTime57(void);
 	void EXPORT LaserTime58(void);
 	void EXPORT LaserTime59(void);
 	void EXPORT LaserTime60(void);
 	void EXPORT LaserTime61(void);
 	void EXPORT LaserTime62(void);
 	void EXPORT LaserTime63(void);
 	void EXPORT LaserTime64(void);
 	void EXPORT LaserTime65(void);
 	void EXPORT LaserTime66(void);
 	void EXPORT LaserTime67(void);
 	void EXPORT LaserTime68(void);
 	void EXPORT LaserTime69(void);
 	void EXPORT LaserTime70(void);
 	void EXPORT LaserTime71(void);
 	void EXPORT LaserTime72(void);
 	void EXPORT LaserTime73(void);
 	void EXPORT LaserTime74(void);
 	void EXPORT LaserTime75(void);
 	void EXPORT LaserTime76(void);
 	void EXPORT LaserTime77(void);
 	void EXPORT LaserTime78(void);
 	void EXPORT LaserTime79(void);
 	void EXPORT LaserTime80(void);
 	void EXPORT LaserTime81(void);
 	void EXPORT LaserTime82(void);
 	void EXPORT LaserTime83(void);
 	void EXPORT LaserTime84(void);
 	void EXPORT LaserTime85(void);
 	void EXPORT LaserTime86(void);
 	void EXPORT LaserTime87(void);
 	void EXPORT LaserTime88(void);
 	void EXPORT LaserTime89(void);
 	void EXPORT LaserTime90(void);
 	void EXPORT LaserTime91(void);
 	void EXPORT LaserTime92(void);
 	void EXPORT LaserTime93(void);
 	void EXPORT LaserTime94(void);
 	void EXPORT LaserTime95(void);
 	void EXPORT LaserTime96(void);
 	void EXPORT LaserTime97(void);
 	void EXPORT LaserTime98(void);
 	void EXPORT LaserTime99(void);
 	void EXPORT LaserTime100(void);
 	void EXPORT LaserTime101(void); 	
 	void EXPORT LaserTime102(void);	
 	void EXPORT LaserTime103(void);	
 	void EXPORT LaserTime104(void);	
 	void EXPORT LaserTime105(void);	
 	void EXPORT LaserTime106(void);	
 	void EXPORT LaserTime107(void);	
 	void EXPORT LaserTime108(void);	
 	void EXPORT LaserTime109(void);	
 	void EXPORT LaserTime110(void);	
 	void EXPORT LaserTime111(void);	
 	void EXPORT LaserTime112(void);	
 	void EXPORT LaserTime113(void);	
 	void EXPORT LaserTime114(void);	
 	void EXPORT LaserTime115(void);	
 	void EXPORT LaserTime116(void);	
 	void EXPORT LaserTime117(void);	
 	void EXPORT LaserTime118(void);	
 	void EXPORT LaserTime119(void);	
 	void EXPORT LaserTime120(void);	
 	void EXPORT LaserTime121(void);		
 	void EXPORT LaserTime122(void);		
 	void EXPORT LaserTime123(void);		
 	void EXPORT LaserTime124(void);		
 	void EXPORT LaserTime125(void);		
 	void EXPORT LaserTime126(void);		
 	void EXPORT LaserTime127(void);		
 	void EXPORT LaserTime128(void);		
 	void EXPORT LaserTime129(void);		
 	void EXPORT LaserTime130(void);		
 	void EXPORT LaserTime131(void);	
 	void EXPORT LaserTime132(void);	
 	void EXPORT LaserTime133(void);	
 	void EXPORT LaserTime134(void);	
 	void EXPORT LaserTime135(void);	
 	void EXPORT LaserTime136(void);	
 	void EXPORT LaserTime137(void);	
 	void EXPORT LaserTime138(void);	
 	void EXPORT LaserTime139(void);	
 	void EXPORT LaserTime140(void);	
 	void EXPORT LaserTime141(void);		
 	void EXPORT LaserTime142(void);		
 	void EXPORT LaserTime143(void);		
 	void EXPORT LaserTime144(void);		
 	void EXPORT LaserTime145(void);		
 	void EXPORT LaserTime146(void);		
 	void EXPORT LaserTime147(void);		
 	void EXPORT LaserTime148(void);		
 	void EXPORT LaserTime149(void);		
 	void EXPORT LaserTime150(void);		
 	void EXPORT LaserTime151(void);		
 	void EXPORT LaserTime152(void);		
 	void EXPORT LaserTime153(void);		
 	void EXPORT LaserTime154(void);		
 	void EXPORT LaserTime155(void);		
 	void EXPORT LaserTime156(void);		
 	void EXPORT LaserTime157(void);		
 	void EXPORT LaserTime158(void);		
 	void EXPORT LaserTime159(void);		
 	void EXPORT LaserTime160(void);		
 	void EXPORT LaserTime161(void);		
 	void EXPORT LaserTime162(void);		
 	void EXPORT LaserTime163(void);		
 	void EXPORT LaserTime164(void);		
	void EXPORT LaserTime165(void);	
 	void EXPORT LaserTime166(void);		
 	void EXPORT LaserTime167(void);		
 	void EXPORT LaserTime168(void);		
 	void EXPORT LaserTime169(void);		
 	void EXPORT LaserTime170(void);		
 	void EXPORT LaserTime171(void);	
 	void EXPORT LaserTime172(void);		
 	void EXPORT LaserTime173(void);		
 	void EXPORT LaserTime174(void);		
 	void EXPORT LaserTime175(void);		
 	void EXPORT LaserTime176(void);		
 	void EXPORT LaserTime177(void);		
 	void EXPORT LaserTime178(void);		
 	void EXPORT LaserTime179(void);		
 	void EXPORT LaserTime180(void);		
 	void EXPORT LaserTime181(void);	
 	void EXPORT LaserTime182(void);	
 	void EXPORT LaserTime183(void);	
 	void EXPORT LaserTime184(void);	
 	void EXPORT LaserTime185(void);	
 	void EXPORT LaserTime186(void);	
 	void EXPORT LaserTime187(void);	
 	void EXPORT LaserTime188(void);	
 	void EXPORT LaserTime189(void);	
 	void EXPORT LaserTime190(void);	
 	void EXPORT LaserTime191(void);		
 	void EXPORT LaserTime192(void);		
 	void EXPORT LaserTime193(void);		
 	void EXPORT LaserTime194(void);		
 	void EXPORT LaserTime195(void);		
 	void EXPORT LaserTime196(void);		
 	void EXPORT LaserTime197(void);		
 	void EXPORT LaserTime198(void);		
 	void EXPORT LaserTime199(void);		
 	void EXPORT LaserTime200(void);		
 	void EXPORT LaserTime201(void); 	
 	void EXPORT LaserTime202(void);	
 	void EXPORT LaserTime203(void);	
 	void EXPORT LaserTime204(void);	
 	void EXPORT LaserTime205(void);	
 	void EXPORT LaserTime206(void);	
 	void EXPORT LaserTime207(void);	
 	void EXPORT LaserTime208(void);	
 	void EXPORT LaserTime209(void);	
 	void EXPORT LaserTime210(void);	
 	void EXPORT LaserTime211(void);	
 	void EXPORT LaserTime212(void);	
 	void EXPORT LaserTime213(void);	
 	void EXPORT LaserTime214(void);	
 	void EXPORT LaserTime215(void);	
 	void EXPORT LaserTime216(void);	
 	void EXPORT LaserTime217(void);	
 	void EXPORT LaserTime218(void);	
 	void EXPORT LaserTime219(void);	
 	void EXPORT LaserTime220(void);	
 	void EXPORT LaserTime221(void);		
 	void EXPORT LaserTime222(void);		
 	void EXPORT LaserTime223(void);		
 	void EXPORT LaserTime224(void);		
 	void EXPORT LaserTime225(void);		
 	void EXPORT LaserTime226(void);		
 	void EXPORT LaserTime227(void);		
 	void EXPORT LaserTime228(void);		
 	void EXPORT LaserTime229(void);		
 	void EXPORT LaserTime230(void);		
 	void EXPORT LaserTime231(void);	
 	void EXPORT LaserTime232(void);	
 	void EXPORT LaserTime233(void);	
 	void EXPORT LaserTime234(void);	
 	void EXPORT LaserTime235(void);	
 	void EXPORT LaserTime236(void);	
 	void EXPORT LaserTime237(void);	
 	void EXPORT LaserTime238(void);	
 	void EXPORT LaserTime239(void);	
 	void EXPORT LaserTime240(void);	
 	void EXPORT LaserTime241(void);		
 	void EXPORT LaserTime242(void);		
 	void EXPORT LaserTime243(void);		
 	void EXPORT LaserTime244(void);		
 	void EXPORT LaserTime245(void);		
 	void EXPORT LaserTime246(void);		
 	void EXPORT LaserTime247(void);		
 	void EXPORT LaserTime248(void);		
 	void EXPORT LaserTime249(void);		
 	void EXPORT LaserTime250(void);		
 	void EXPORT LaserTime251(void);		
 	void EXPORT LaserTime252(void);		
 	void EXPORT LaserTime253(void);		
 	void EXPORT LaserTime254(void);		
 	void EXPORT LaserTime255(void);		
 	void EXPORT LaserTime256(void);		
 	void EXPORT LaserTime257(void);		
 	void EXPORT LaserTime258(void);		
 	void EXPORT LaserTime259(void);		
 	void EXPORT LaserTime260(void);		
 	void EXPORT LaserTime261(void);		
 	void EXPORT LaserTime262(void);		
 	void EXPORT LaserTime263(void);		
 	void EXPORT LaserTime264(void);		
	void EXPORT LaserTime265(void);	
 	void EXPORT LaserTime266(void);		
 	void EXPORT LaserTime267(void);		
 	void EXPORT LaserTime268(void);		
 	void EXPORT LaserTime269(void);		
 	void EXPORT LaserTime270(void);		
 	void EXPORT LaserTime271(void);	
 	void EXPORT LaserTime272(void);		
 	void EXPORT LaserTime273(void);		
 	void EXPORT LaserTime274(void);		
 	void EXPORT LaserTime275(void);		
 	void EXPORT LaserTime276(void);		
 	void EXPORT LaserTime277(void);		
 	void EXPORT LaserTime278(void);		
 	void EXPORT LaserTime279(void);		
 	void EXPORT LaserTime280(void);		
 	void EXPORT LaserTime281(void);	
 	void EXPORT LaserTime282(void);	
 	void EXPORT LaserTime283(void);	
 	void EXPORT LaserTime284(void);	
 	void EXPORT LaserTime285(void);	
 	void EXPORT LaserTime286(void);	
 	void EXPORT LaserTime287(void);	
 	void EXPORT LaserTime288(void);	
 	void EXPORT LaserTime289(void);	
 	void EXPORT LaserTime290(void);	
 	void EXPORT LaserTime291(void);		
 	void EXPORT LaserTime292(void);		
 	void EXPORT LaserTime293(void);		
 	void EXPORT LaserTime294(void);		
 	void EXPORT LaserTime295(void);		
 	void EXPORT LaserTime296(void);		
 	void EXPORT LaserTime297(void);		
 	void EXPORT LaserTime298(void);		
 	void EXPORT LaserTime299(void);		
 	void EXPORT LaserTime300(void);		    
    void EXPORT LaserTime301(void);
	void EXPORT LaserTime302(void);	
 	void EXPORT LaserTime303(void);	
 	void EXPORT LaserTime304(void);	
 	void EXPORT LaserTime305(void);	
 	void EXPORT LaserTime306(void);	
 	void EXPORT LaserTime307(void);	
 	void EXPORT LaserTime308(void);	
 	void EXPORT LaserTime309(void);	
 	void EXPORT LaserTime310(void);	
 	void EXPORT LaserTime311(void);	
 	void EXPORT LaserTime312(void);	
 	void EXPORT LaserTime313(void);	
 	void EXPORT LaserTime314(void);	
 	void EXPORT LaserTime315(void);	
 	void EXPORT LaserTime316(void);	
 	void EXPORT LaserTime317(void);	
 	void EXPORT LaserTime318(void);	
 	void EXPORT LaserTime319(void);	
 	void EXPORT LaserTime320(void);	
 	void EXPORT LaserTime321(void);		
 	void EXPORT LaserTime322(void);		
 	void EXPORT LaserTime323(void);		
 	void EXPORT LaserTime324(void);		
 	void EXPORT LaserTime325(void);		
 	void EXPORT LaserTime326(void);		
 	void EXPORT LaserTime327(void);		
 	void EXPORT LaserTime328(void);		
 	void EXPORT LaserTime329(void);		
 	void EXPORT LaserTime330(void);		
 	void EXPORT LaserTime331(void);	
 	void EXPORT LaserTime332(void);	
 	void EXPORT LaserTime333(void);	
 	void EXPORT LaserTime334(void);	
 	void EXPORT LaserTime335(void);	
 	void EXPORT LaserTime336(void);	
 	void EXPORT LaserTime337(void);	
 	void EXPORT LaserTime338(void);	
 	void EXPORT LaserTime339(void);	
 	void EXPORT LaserTime340(void);	
 	void EXPORT LaserTime341(void);		
 	void EXPORT LaserTime342(void);		
 	void EXPORT LaserTime343(void);		
 	void EXPORT LaserTime344(void);		
 	void EXPORT LaserTime345(void);		
 	void EXPORT LaserTime346(void);		
 	void EXPORT LaserTime347(void);		
 	void EXPORT LaserTime348(void);		
 	void EXPORT LaserTime349(void);		
 	void EXPORT LaserTime350(void);		
 	void EXPORT LaserTime351(void);	
 	void EXPORT LaserTime352(void);		
 	void EXPORT LaserTime353(void);		
 	void EXPORT LaserTime354(void);		
 	void EXPORT LaserTime355(void);		
 	void EXPORT LaserTime356(void);		
 	void EXPORT LaserTime357(void);		
 	void EXPORT LaserTime358(void);		
 	void EXPORT LaserTime359(void);		
 	void EXPORT LaserTime360(void);		
 	void EXPORT LaserTime361(void);		
 	void EXPORT LaserTime362(void);	
 	void EXPORT LaserTime363(void);	
 	void EXPORT LaserTime364(void);	
 	void EXPORT LaserTime365(void);	
 	void EXPORT LaserTime366(void);	
 	void EXPORT LaserTime367(void);	
 	void EXPORT LaserTime368(void);	
 	void EXPORT LaserTime369(void);	
 	void EXPORT LaserTime370(void);	
 	void EXPORT LaserTime371(void);

	virtual int GetVoicePitch( void ) { return 100; }
	virtual float GetSoundVolue( void ) { return 1.0; }
};
LINK_ENTITY_TO_CLASS( monster_FATRONlightning2, CFatronLightningFASE2 );

TYPEDESCRIPTION	CFatronLightningFASE2::m_SaveData[] =
{
	DEFINE_ARRAY(CFatronLightningFASE2, m_pBeam, FIELD_CLASSPTR, VOLTIGORE_MAX_BEAMS),
	DEFINE_FIELD(CFatronLightningFASE2, m_iBeams, FIELD_INTEGER),
	DEFINE_FIELD(CFatronLightningFASE2, m_timeToDie, FIELD_TIME),
};
IMPLEMENT_SAVERESTORE(CFatronLightningFASE2, CBaseEntity)

//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CFatronLightningFASE2 :: Classify ( void )
{
	return	CLASS_ALIEN_PREY;
}

//=========================================================
// Center - returns the real center of the ElectricLightning.  The 
// bounding box is much larger than the actual creature so 
// this is needed for targeting
//=========================================================
Vector CFatronLightningFASE2 :: Center ( void )
{
	return Vector( pev->origin.x, pev->origin.y, pev->origin.z + 6 );
}


Vector CFatronLightningFASE2 :: BodyTarget( const Vector &posSrc ) 
{ 
	return Center( );
}

//=========================================================
// SetYawSpeed - allows each sequence to have a different
// turn rate associated with it.
//=========================================================
void CFatronLightningFASE2 :: SetYawSpeed ( void )
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
void CFatronLightningFASE2 :: HandleAnimEvent( MonsterEvent_t *pEvent )
{
}

//=========================================================
// Spawn
//=========================================================
void CFatronLightningFASE2 :: Spawn()
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
void CFatronLightningFASE2 :: Precache()
{
	m_beamTexture = PRECACHE_MODEL(VOLTIGORE_ZAP_BEAM); 
	m_LightningTexture1 = PRECACHE_MODEL(LASER1_ZAP_BEAM);
    m_LightningTexture2 = PRECACHE_MODEL(LASER2_ZAP_BEAM);

	PRECACHE_MODEL("models/null.mdl");
}	


//=========================================================
// RunTask 
//=========================================================
void CFatronLightningFASE2 :: RunTask ( Task_t *pTask )
{
}

//=========================================================
// LeapTouch - this is the ElectricLightning's touch function when it
// is in the air
//=========================================================
void CFatronLightningFASE2 :: LeapTouch ( CBaseEntity *pOther )
{
}

//=========================================================
// PrescheduleThink
//=========================================================
void CFatronLightningFASE2 :: PrescheduleThink ( void )
{
}

void CFatronLightningFASE2 :: StartTask ( Task_t *pTask )
{
}

int CFatronLightningFASE2 :: TakeDamage( entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType )
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

void CFatronLightningFASE2::LaserTime(void)
{
	Laser();
}

void CFatronLightningFASE2::LaserTime2(void)
{
	Laser2();
}

void CFatronLightningFASE2::LaserTime3(void)
{
	Laser3();
}

void CFatronLightningFASE2::LaserTime4(void)
{
	Laser4();
}

void CFatronLightningFASE2::LaserTime5(void)
{
	Laser5();
}

void CFatronLightningFASE2::LaserTime6(void)
{
	Laser6();
}

void CFatronLightningFASE2::LaserTime7(void)
{
	Laser7();
}

void CFatronLightningFASE2::LaserTime8(void)
{
	Laser8();
}

void CFatronLightningFASE2::LaserTime9(void)
{
	Laser9();
}

void CFatronLightningFASE2::LaserTime10(void)
{
	Laser10();
}

void CFatronLightningFASE2::LaserTime11(void)
{
	Laser11();
}

void CFatronLightningFASE2::LaserTime12(void)
{
	Laser12();
}

void CFatronLightningFASE2::LaserTime13(void)
{
	Laser13();
}

void CFatronLightningFASE2::LaserTime14(void)
{
	Laser14();
}

void CFatronLightningFASE2::LaserTime15(void)
{
	Laser15();
}

void CFatronLightningFASE2::LaserTime16(void)
{
	Laser16();
}

void CFatronLightningFASE2::LaserTime17(void)
{
	Laser17();
}

void CFatronLightningFASE2::LaserTime18(void)
{
	Laser18();
}

void CFatronLightningFASE2::LaserTime19(void)
{
	Laser19();
}

void CFatronLightningFASE2::LaserTime20(void)
{
	Laser20();
}

void CFatronLightningFASE2::LaserTime21(void)
{
	Laser21();
}

void CFatronLightningFASE2::LaserTime22(void)
{
	Laser22();
}

void CFatronLightningFASE2::LaserTime23(void)
{
	Laser23();
}

void CFatronLightningFASE2::LaserTime24(void)
{
	Laser24();
}

void CFatronLightningFASE2::LaserTime25(void)
{
	Laser25();
}

void CFatronLightningFASE2::LaserTime26(void)
{
	Laser26();
}

void CFatronLightningFASE2::LaserTime27(void)
{
	Laser27();
}

void CFatronLightningFASE2::LaserTime28(void)
{
	Laser28();
}

void CFatronLightningFASE2::LaserTime29(void)
{
	Laser29();
}

void CFatronLightningFASE2::LaserTime30(void)
{
	Laser30();
}

void CFatronLightningFASE2::LaserTime31(void)
{
	Laser31();
}

void CFatronLightningFASE2::LaserTime32(void)
{
	Laser32();
}

void CFatronLightningFASE2::LaserTime33(void)
{
	Laser33();
}

void CFatronLightningFASE2::LaserTime34(void)
{
	Laser34();
}

void CFatronLightningFASE2::LaserTime35(void)
{
	Laser35();
}

void CFatronLightningFASE2::LaserTime36(void)
{
	Laser36();
}

void CFatronLightningFASE2::LaserTime37(void)
{
	Laser37();
}

void CFatronLightningFASE2::LaserTime38(void)
{
	Laser38();
}

void CFatronLightningFASE2::LaserTime39(void)
{
	Laser39();
}

void CFatronLightningFASE2::LaserTime40(void)
{
	Laser40();
}

void CFatronLightningFASE2::LaserTime41(void)
{
	Laser41();
}

void CFatronLightningFASE2::LaserTime42(void)
{
	Laser42();
}

void CFatronLightningFASE2::LaserTime43(void)
{
	Laser43();
}

void CFatronLightningFASE2::LaserTime44(void)
{
	Laser44();
}

void CFatronLightningFASE2::LaserTime45(void)
{
	Laser45();
}

void CFatronLightningFASE2::LaserTime46(void)
{
	Laser46();
}

void CFatronLightningFASE2::LaserTime47(void)
{
	Laser47();
}

void CFatronLightningFASE2::LaserTime48(void)
{
	Laser48();
}

void CFatronLightningFASE2::LaserTime49(void)
{
	Laser49();
}

void CFatronLightningFASE2::LaserTime50(void)
{
	Laser50();
}

void CFatronLightningFASE2::LaserTime51(void)
{
	Laser51();
}

void CFatronLightningFASE2::LaserTime52(void)
{
	Laser52();
}

void CFatronLightningFASE2::LaserTime53(void)
{
	Laser53();
}

void CFatronLightningFASE2::LaserTime54(void)
{
	Laser54();
}

void CFatronLightningFASE2::LaserTime55(void)
{
	Laser55();
}

void CFatronLightningFASE2::LaserTime56(void)
{
	Laser56();
}

void CFatronLightningFASE2::LaserTime57(void)
{
	Laser57();
}

void CFatronLightningFASE2::LaserTime58(void)
{
	Laser58();
}

void CFatronLightningFASE2::LaserTime59(void)
{
	Laser59();
}

void CFatronLightningFASE2::LaserTime60(void)
{
	Laser60();
}

void CFatronLightningFASE2::LaserTime61(void)
{
	Laser61();
}

void CFatronLightningFASE2::LaserTime62(void)
{
	Laser62();
}

void CFatronLightningFASE2::LaserTime63(void)
{
	Laser63();
}

void CFatronLightningFASE2::LaserTime64(void)
{
	Laser64();
}

void CFatronLightningFASE2::LaserTime65(void)
{
	Laser65();
}

void CFatronLightningFASE2::LaserTime66(void)
{
	Laser66();
}

void CFatronLightningFASE2::LaserTime67(void)
{
	Laser67();
}

void CFatronLightningFASE2::LaserTime68(void)
{
	Laser68();
}

void CFatronLightningFASE2::LaserTime69(void)
{
	Laser69();
}

void CFatronLightningFASE2::LaserTime70(void)
{
	Laser70();
}

void CFatronLightningFASE2::LaserTime71(void)
{
	Laser71();
}

void CFatronLightningFASE2::LaserTime72(void)
{
	Laser72();
}

void CFatronLightningFASE2::LaserTime73(void)
{
	Laser73();
}

void CFatronLightningFASE2::LaserTime74(void)
{
	Laser74();
}

void CFatronLightningFASE2::LaserTime75(void)
{
	Laser75();
}

void CFatronLightningFASE2::LaserTime76(void)
{
	Laser76();
}

void CFatronLightningFASE2::LaserTime77(void)
{
	Laser77();
}

void CFatronLightningFASE2::LaserTime78(void)
{
	Laser78();
}

void CFatronLightningFASE2::LaserTime79(void)
{
	Laser79();
}

void CFatronLightningFASE2::LaserTime80(void)
{
	Laser80();
}

void CFatronLightningFASE2::LaserTime81(void)
{
	Laser81();
}

void CFatronLightningFASE2::LaserTime82(void)
{
	Laser82();
}

void CFatronLightningFASE2::LaserTime83(void)
{
	Laser83();
}

void CFatronLightningFASE2::LaserTime84(void)
{
	Laser84();
}

void CFatronLightningFASE2::LaserTime85(void)
{
	Laser85();
}

void CFatronLightningFASE2::LaserTime86(void)
{
	Laser86();
}

void CFatronLightningFASE2::LaserTime87(void)
{
	Laser87();
}

void CFatronLightningFASE2::LaserTime88(void)
{
	Laser88();
}

void CFatronLightningFASE2::LaserTime89(void)
{
	Laser89();
}

void CFatronLightningFASE2::LaserTime90(void)
{
	Laser90();
}

void CFatronLightningFASE2::LaserTime91(void)
{
	Laser91();
}

void CFatronLightningFASE2::LaserTime92(void)
{
	Laser92();
}

void CFatronLightningFASE2::LaserTime93(void)
{
	Laser93();
}

void CFatronLightningFASE2::LaserTime94(void)
{
	Laser94();
}

void CFatronLightningFASE2::LaserTime95(void)
{
	Laser95();
}

void CFatronLightningFASE2::LaserTime96(void)
{
	Laser96();
}

void CFatronLightningFASE2::LaserTime97(void)
{
	Laser97();
}

void CFatronLightningFASE2::LaserTime98(void)
{
	Laser98();
}

void CFatronLightningFASE2::LaserTime99(void)
{
	Laser99();
}

void CFatronLightningFASE2::LaserTime100(void)
{
	Laser100();
}

void CFatronLightningFASE2::LaserTime101(void)
{
	Laser101();
}

void CFatronLightningFASE2::LaserTime102(void)
{
	Laser102();
}

void CFatronLightningFASE2::LaserTime103(void)
{
	Laser103();
}

void CFatronLightningFASE2::LaserTime104(void)
{
	Laser104();
}

void CFatronLightningFASE2::LaserTime105(void)
{
	Laser105();
}

void CFatronLightningFASE2::LaserTime106(void)
{
	Laser106();
}

void CFatronLightningFASE2::LaserTime107(void)
{
	Laser107();
}

void CFatronLightningFASE2::LaserTime108(void)
{
	Laser108();
}

void CFatronLightningFASE2::LaserTime109(void)
{
	Laser109();
}

void CFatronLightningFASE2::LaserTime110(void)
{
	Laser110();
}

void CFatronLightningFASE2::LaserTime111(void)
{
	Laser111();
}

void CFatronLightningFASE2::LaserTime112(void)
{
	Laser112();
}

void CFatronLightningFASE2::LaserTime113(void)
{
	Laser113();
}

void CFatronLightningFASE2::LaserTime114(void)
{
	Laser114();
}

void CFatronLightningFASE2::LaserTime115(void)
{
	Laser115();
}

void CFatronLightningFASE2::LaserTime116(void)
{
	Laser116();
}

void CFatronLightningFASE2::LaserTime117(void)
{
	Laser117();
}

void CFatronLightningFASE2::LaserTime118(void)
{
	Laser118();
}

void CFatronLightningFASE2::LaserTime119(void)
{
	Laser119();
}

void CFatronLightningFASE2::LaserTime120(void)
{
	Laser120();
}

void CFatronLightningFASE2::LaserTime121(void)
{
	Laser121();
}

void CFatronLightningFASE2::LaserTime122(void)
{
	Laser122();
}

void CFatronLightningFASE2::LaserTime123(void)
{
	Laser123();
}

void CFatronLightningFASE2::LaserTime124(void)
{
	Laser124();
}

void CFatronLightningFASE2::LaserTime125(void)
{
	Laser125();
}

void CFatronLightningFASE2::LaserTime126(void)
{
	Laser126();
}

void CFatronLightningFASE2::LaserTime127(void)
{
	Laser127();
}

void CFatronLightningFASE2::LaserTime128(void)
{
	Laser128();
}

void CFatronLightningFASE2::LaserTime129(void)
{
	Laser129();
}

void CFatronLightningFASE2::LaserTime130(void)
{
	Laser130();
}

void CFatronLightningFASE2::LaserTime131(void)
{
	Laser131();
}

void CFatronLightningFASE2::LaserTime132(void)
{
	Laser132();
}

void CFatronLightningFASE2::LaserTime133(void)
{
	Laser133();
}

void CFatronLightningFASE2::LaserTime134(void)
{
	Laser134();
}

void CFatronLightningFASE2::LaserTime135(void)
{
	Laser135();
}

void CFatronLightningFASE2::LaserTime136(void)
{
	Laser136();
}

void CFatronLightningFASE2::LaserTime137(void)
{
	Laser137();
}

void CFatronLightningFASE2::LaserTime138(void)
{
	Laser138();
}

void CFatronLightningFASE2::LaserTime139(void)
{
	Laser139();
}

void CFatronLightningFASE2::LaserTime140(void)
{
	Laser140();
}

void CFatronLightningFASE2::LaserTime141(void)
{
	Laser141();
}

void CFatronLightningFASE2::LaserTime142(void)
{
	Laser142();
}

void CFatronLightningFASE2::LaserTime143(void)
{
	Laser143();
}

void CFatronLightningFASE2::LaserTime144(void)
{
	Laser144();
}

void CFatronLightningFASE2::LaserTime145(void)
{
	Laser145();
}

void CFatronLightningFASE2::LaserTime146(void)
{
	Laser146();
}

void CFatronLightningFASE2::LaserTime147(void)
{
	Laser147();
}

void CFatronLightningFASE2::LaserTime148(void)
{
	Laser148();
}

void CFatronLightningFASE2::LaserTime149(void)
{
	Laser149();
}

void CFatronLightningFASE2::LaserTime150(void)
{
	Laser150();
}

void CFatronLightningFASE2::LaserTime151(void)
{
	Laser151();
}

void CFatronLightningFASE2::LaserTime152(void)
{
	Laser152();
}

void CFatronLightningFASE2::LaserTime153(void)
{
	Laser153();
}

void CFatronLightningFASE2::LaserTime154(void)
{
	Laser154();
}

void CFatronLightningFASE2::LaserTime155(void)
{
	Laser155();
}

void CFatronLightningFASE2::LaserTime156(void)
{
	Laser156();
}

void CFatronLightningFASE2::LaserTime157(void)
{
	Laser157();
}

void CFatronLightningFASE2::LaserTime158(void)
{
	Laser158();
}

void CFatronLightningFASE2::LaserTime159(void)
{
	Laser159();
}

void CFatronLightningFASE2::LaserTime160(void)
{
	Laser160();
}

void CFatronLightningFASE2::LaserTime161(void)
{
	Laser161();
}

void CFatronLightningFASE2::LaserTime162(void)
{
	Laser162();
}

void CFatronLightningFASE2::LaserTime163(void)
{
	Laser163();
}

void CFatronLightningFASE2::LaserTime164(void)
{
	Laser164();
}

void CFatronLightningFASE2::LaserTime165(void)
{
	Laser165();
}

void CFatronLightningFASE2::LaserTime166(void)
{
	Laser166();
}

void CFatronLightningFASE2::LaserTime167(void)
{
	Laser167();
}

void CFatronLightningFASE2::LaserTime168(void)
{
	Laser168();
}

void CFatronLightningFASE2::LaserTime169(void)
{
	Laser169();
}

void CFatronLightningFASE2::LaserTime170(void)
{
	Laser170();
}

void CFatronLightningFASE2::LaserTime171(void)
{
	Laser171();
}

void CFatronLightningFASE2::LaserTime172(void)
{
	Laser172();
}

void CFatronLightningFASE2::LaserTime173(void)
{
	Laser173();
}

void CFatronLightningFASE2::LaserTime174(void)
{
	Laser174();
}

void CFatronLightningFASE2::LaserTime175(void)
{
	Laser175();
}

void CFatronLightningFASE2::LaserTime176(void)
{
	Laser176();
}

void CFatronLightningFASE2::LaserTime177(void)
{
	Laser177();
}

void CFatronLightningFASE2::LaserTime178(void)
{
	Laser178();
}

void CFatronLightningFASE2::LaserTime179(void)
{
	Laser179();
}

void CFatronLightningFASE2::LaserTime180(void)
{
	Laser180();
}

void CFatronLightningFASE2::LaserTime181(void)
{
	Laser181();
}

void CFatronLightningFASE2::LaserTime182(void)
{
	Laser182();
}

void CFatronLightningFASE2::LaserTime183(void)
{
	Laser183();
}

void CFatronLightningFASE2::LaserTime184(void)
{
	Laser184();
}

void CFatronLightningFASE2::LaserTime185(void)
{
	Laser185();
}

void CFatronLightningFASE2::LaserTime186(void)
{
	Laser186();
}

void CFatronLightningFASE2::LaserTime187(void)
{
	Laser187();
}

void CFatronLightningFASE2::LaserTime188(void)
{
	Laser188();
}

void CFatronLightningFASE2::LaserTime189(void)
{
	Laser189();
}

void CFatronLightningFASE2::LaserTime190(void)
{
	Laser190();
}

void CFatronLightningFASE2::LaserTime191(void)
{
	Laser191();
}

void CFatronLightningFASE2::LaserTime192(void)
{
	Laser192();
}

void CFatronLightningFASE2::LaserTime193(void)
{
	Laser193();
}

void CFatronLightningFASE2::LaserTime194(void)
{
	Laser194();
}

void CFatronLightningFASE2::LaserTime195(void)
{
	Laser195();
}

void CFatronLightningFASE2::LaserTime196(void)
{
	Laser196();
}

void CFatronLightningFASE2::LaserTime197(void)
{
	Laser197();
}

void CFatronLightningFASE2::LaserTime198(void)
{
	Laser198();
}

void CFatronLightningFASE2::LaserTime199(void)
{
	Laser199();
}

void CFatronLightningFASE2::LaserTime200(void)
{
	Laser200();
}

void CFatronLightningFASE2::LaserTime201(void)
{
	Laser201();
}

void CFatronLightningFASE2::LaserTime202(void)
{
	Laser202();
}

void CFatronLightningFASE2::LaserTime203(void)
{
	Laser203();
}

void CFatronLightningFASE2::LaserTime204(void)
{
	Laser204();
}

void CFatronLightningFASE2::LaserTime205(void)
{
	Laser205();
}

void CFatronLightningFASE2::LaserTime206(void)
{
	Laser206();
}

void CFatronLightningFASE2::LaserTime207(void)
{
	Laser207();
}

void CFatronLightningFASE2::LaserTime208(void)
{
	Laser208();
}

void CFatronLightningFASE2::LaserTime209(void)
{
	Laser209();
}

void CFatronLightningFASE2::LaserTime210(void)
{
	Laser210();
}

void CFatronLightningFASE2::LaserTime211(void)
{
	Laser211();
}

void CFatronLightningFASE2::LaserTime212(void)
{
	Laser212();
}

void CFatronLightningFASE2::LaserTime213(void)
{
	Laser213();
}

void CFatronLightningFASE2::LaserTime214(void)
{
	Laser214();
}

void CFatronLightningFASE2::LaserTime215(void)
{
	Laser215();
}

void CFatronLightningFASE2::LaserTime216(void)
{
	Laser216();
}

void CFatronLightningFASE2::LaserTime217(void)
{
	Laser217();
}

void CFatronLightningFASE2::LaserTime218(void)
{
	Laser218();
}

void CFatronLightningFASE2::LaserTime219(void)
{
	Laser219();
}

void CFatronLightningFASE2::LaserTime220(void)
{
	Laser220();
}

void CFatronLightningFASE2::LaserTime221(void)
{
	Laser221();
}

void CFatronLightningFASE2::LaserTime222(void)
{
	Laser222();
}

void CFatronLightningFASE2::LaserTime223(void)
{
	Laser223();
}

void CFatronLightningFASE2::LaserTime224(void)
{
	Laser224();
}

void CFatronLightningFASE2::LaserTime225(void)
{
	Laser225();
}

void CFatronLightningFASE2::LaserTime226(void)
{
	Laser226();
}

void CFatronLightningFASE2::LaserTime227(void)
{
	Laser227();
}

void CFatronLightningFASE2::LaserTime228(void)
{
	Laser228();
}

void CFatronLightningFASE2::LaserTime229(void)
{
	Laser229();
}

void CFatronLightningFASE2::LaserTime230(void)
{
	Laser230();
}

void CFatronLightningFASE2::LaserTime231(void)
{
	Laser231();
}

void CFatronLightningFASE2::LaserTime232(void)
{
	Laser232();
}

void CFatronLightningFASE2::LaserTime233(void)
{
	Laser233();
}

void CFatronLightningFASE2::LaserTime234(void)
{
	Laser234();
}

void CFatronLightningFASE2::LaserTime235(void)
{
	Laser235();
}

void CFatronLightningFASE2::LaserTime236(void)
{
	Laser236();
}

void CFatronLightningFASE2::LaserTime237(void)
{
	Laser237();
}

void CFatronLightningFASE2::LaserTime238(void)
{
	Laser238();
}

void CFatronLightningFASE2::LaserTime239(void)
{
	Laser239();
}

void CFatronLightningFASE2::LaserTime240(void)
{
	Laser240();
}

void CFatronLightningFASE2::LaserTime241(void)
{
	Laser241();
}

void CFatronLightningFASE2::LaserTime242(void)
{
	Laser242();
}

void CFatronLightningFASE2::LaserTime243(void)
{
	Laser243();
}

void CFatronLightningFASE2::LaserTime244(void)
{
	Laser244();
}

void CFatronLightningFASE2::LaserTime245(void)
{
	Laser245();
}

void CFatronLightningFASE2::LaserTime246(void)
{
	Laser246();
}

void CFatronLightningFASE2::LaserTime247(void)
{
	Laser247();
}

void CFatronLightningFASE2::LaserTime248(void)
{
	Laser248();
}

void CFatronLightningFASE2::LaserTime249(void)
{
	Laser249();
}

void CFatronLightningFASE2::LaserTime250(void)
{
	Laser250();
}

void CFatronLightningFASE2::LaserTime251(void)
{
	Laser251();
}

void CFatronLightningFASE2::LaserTime252(void)
{
	Laser252();
}

void CFatronLightningFASE2::LaserTime253(void)
{
	Laser253();
}

void CFatronLightningFASE2::LaserTime254(void)
{
	Laser254();
}

void CFatronLightningFASE2::LaserTime255(void)
{
	Laser255();
}

void CFatronLightningFASE2::LaserTime256(void)
{
	Laser256();
}

void CFatronLightningFASE2::LaserTime257(void)
{
	Laser257();
}

void CFatronLightningFASE2::LaserTime258(void)
{
	Laser258();
}

void CFatronLightningFASE2::LaserTime259(void)
{
	Laser259();
}

void CFatronLightningFASE2::LaserTime260(void)
{
	Laser260();
}

void CFatronLightningFASE2::LaserTime261(void)
{
	Laser261();
}

void CFatronLightningFASE2::LaserTime262(void)
{
	Laser262();
}

void CFatronLightningFASE2::LaserTime263(void)
{
	Laser263();
}

void CFatronLightningFASE2::LaserTime264(void)
{
	Laser264();
}

void CFatronLightningFASE2::LaserTime265(void)
{
	Laser265();
}

void CFatronLightningFASE2::LaserTime266(void)
{
	Laser266();
}

void CFatronLightningFASE2::LaserTime267(void)
{
	Laser267();
}

void CFatronLightningFASE2::LaserTime268(void)
{
	Laser268();
}

void CFatronLightningFASE2::LaserTime269(void)
{
	Laser269();
}

void CFatronLightningFASE2::LaserTime270(void)
{
	Laser270();
}

void CFatronLightningFASE2::LaserTime271(void)
{
	Laser271();
}

void CFatronLightningFASE2::LaserTime272(void)
{
	Laser272();
}

void CFatronLightningFASE2::LaserTime273(void)
{
	Laser273();
}

void CFatronLightningFASE2::LaserTime274(void)
{
	Laser274();
}

void CFatronLightningFASE2::LaserTime275(void)
{
	Laser275();
}

void CFatronLightningFASE2::LaserTime276(void)
{
	Laser276();
}

void CFatronLightningFASE2::LaserTime277(void)
{
	Laser277();
}

void CFatronLightningFASE2::LaserTime278(void)
{
	Laser278();
}

void CFatronLightningFASE2::LaserTime279(void)
{
	Laser279();
}

void CFatronLightningFASE2::LaserTime280(void)
{
	Laser280();
}

void CFatronLightningFASE2::LaserTime281(void)
{
	Laser281();
}

void CFatronLightningFASE2::LaserTime282(void)
{
	Laser282();
}

void CFatronLightningFASE2::LaserTime283(void)
{
	Laser283();
}

void CFatronLightningFASE2::LaserTime284(void)
{
	Laser284();
}

void CFatronLightningFASE2::LaserTime285(void)
{
	Laser285();
}

void CFatronLightningFASE2::LaserTime286(void)
{
	Laser286();
}

void CFatronLightningFASE2::LaserTime287(void)
{
	Laser287();
}

void CFatronLightningFASE2::LaserTime288(void)
{
	Laser288();
}

void CFatronLightningFASE2::LaserTime289(void)
{
	Laser289();
}

void CFatronLightningFASE2::LaserTime290(void)
{
	Laser290();
}

void CFatronLightningFASE2::LaserTime291(void)
{
	Laser291();
}

void CFatronLightningFASE2::LaserTime292(void)
{
	Laser292();
}

void CFatronLightningFASE2::LaserTime293(void)
{
	Laser293();
}

void CFatronLightningFASE2::LaserTime294(void)
{
	Laser294();
}

void CFatronLightningFASE2::LaserTime295(void)
{
	Laser295();
}

void CFatronLightningFASE2::LaserTime296(void)
{
	Laser296();
}

void CFatronLightningFASE2::LaserTime297(void)
{
	Laser297();
}

void CFatronLightningFASE2::LaserTime298(void)
{
	Laser298();
}

void CFatronLightningFASE2::LaserTime299(void)
{
	Laser299();
}

void CFatronLightningFASE2::LaserTime300(void)
{
	Laser300();
}

void CFatronLightningFASE2::LaserTime301(void)
{
	Laser301();
}

void CFatronLightningFASE2::LaserTime302(void)
{
	Laser302();
}

void CFatronLightningFASE2::LaserTime303(void)
{
	Laser303();
}

void CFatronLightningFASE2::LaserTime304(void)
{
	Laser304();
}

void CFatronLightningFASE2::LaserTime305(void)
{
	Laser305();
}

void CFatronLightningFASE2::LaserTime306(void)
{
	Laser306();
}

void CFatronLightningFASE2::LaserTime307(void)
{
	Laser307();
}

void CFatronLightningFASE2::LaserTime308(void)
{
	Laser308();
}

void CFatronLightningFASE2::LaserTime309(void)
{
	Laser309();
}

void CFatronLightningFASE2::LaserTime310(void)
{
	Laser310();
}

void CFatronLightningFASE2::LaserTime311(void)
{
	Laser311();
}

void CFatronLightningFASE2::LaserTime312(void)
{
	Laser312();
}

void CFatronLightningFASE2::LaserTime313(void)
{
	Laser313();
}

void CFatronLightningFASE2::LaserTime314(void)
{
	Laser314();
}

void CFatronLightningFASE2::LaserTime315(void)
{
	Laser315();
}

void CFatronLightningFASE2::LaserTime316(void)
{
	Laser316();
}

void CFatronLightningFASE2::LaserTime317(void)
{
	Laser317();
}

void CFatronLightningFASE2::LaserTime318(void)
{
	Laser318();
}

void CFatronLightningFASE2::LaserTime319(void)
{
	Laser319();
}

void CFatronLightningFASE2::LaserTime320(void)
{
	Laser320();
}

void CFatronLightningFASE2::LaserTime321(void)
{
	Laser321();
}

void CFatronLightningFASE2::LaserTime322(void)
{
	Laser322();
}

void CFatronLightningFASE2::LaserTime323(void)
{
	Laser323();
}

void CFatronLightningFASE2::LaserTime324(void)
{
	Laser324();
}

void CFatronLightningFASE2::LaserTime325(void)
{
	Laser325();
}

void CFatronLightningFASE2::LaserTime326(void)
{
	Laser326();
}

void CFatronLightningFASE2::LaserTime327(void)
{
	Laser327();
}

void CFatronLightningFASE2::LaserTime328(void)
{
	Laser328();
}

void CFatronLightningFASE2::LaserTime329(void)
{
	Laser329();
}

void CFatronLightningFASE2::LaserTime330(void)
{
	Laser330();
}

void CFatronLightningFASE2::LaserTime331(void)
{
	Laser331();
}

void CFatronLightningFASE2::LaserTime332(void)
{
	Laser332();
}

void CFatronLightningFASE2::LaserTime333(void)
{
	Laser333();
}

void CFatronLightningFASE2::LaserTime334(void)
{
	Laser334();
}

void CFatronLightningFASE2::LaserTime335(void)
{
	Laser335();
}

void CFatronLightningFASE2::LaserTime336(void)
{
	Laser336();
}

void CFatronLightningFASE2::LaserTime337(void)
{
	Laser337();
}

void CFatronLightningFASE2::LaserTime338(void)
{
	Laser338();
}

void CFatronLightningFASE2::LaserTime339(void)
{
	Laser339();
}

void CFatronLightningFASE2::LaserTime340(void)
{
	Laser340();
}

void CFatronLightningFASE2::LaserTime341(void)
{
	Laser341();
}

void CFatronLightningFASE2::LaserTime342(void)
{
	Laser342();
}

void CFatronLightningFASE2::LaserTime343(void)
{
	Laser343();
}

void CFatronLightningFASE2::LaserTime344(void)
{
	Laser344();
}

void CFatronLightningFASE2::LaserTime345(void)
{
	Laser345();
}

void CFatronLightningFASE2::LaserTime346(void)
{
	Laser346();
}

void CFatronLightningFASE2::LaserTime347(void)
{
	Laser347();
}

void CFatronLightningFASE2::LaserTime348(void)
{
	Laser348();
}

void CFatronLightningFASE2::LaserTime349(void)
{
	Laser349();
}

void CFatronLightningFASE2::LaserTime350(void)
{
	Laser350();
}

void CFatronLightningFASE2::LaserTime351(void)
{
	Laser351();
}	

void CFatronLightningFASE2::LaserTime352(void)
{
	Laser352();
}

void CFatronLightningFASE2::LaserTime353(void)
{
	Laser353();
}

void CFatronLightningFASE2::LaserTime354(void)
{
	Laser354();
}

void CFatronLightningFASE2::LaserTime355(void)
{
	Laser355();
}

void CFatronLightningFASE2::LaserTime356(void)
{
	Laser356();
}

void CFatronLightningFASE2::LaserTime357(void)
{
	Laser357();
}

void CFatronLightningFASE2::LaserTime358(void)
{
	Laser358();
}

void CFatronLightningFASE2::LaserTime359(void)
{
	Laser359();
}

void CFatronLightningFASE2::LaserTime360(void)
{
	Laser360();
}

void CFatronLightningFASE2::LaserTime361(void)
{
	Laser361();
}

void CFatronLightningFASE2::LaserTime362(void)
{
	Laser362();
}

void CFatronLightningFASE2::LaserTime363(void)
{
	Laser363();
}

void CFatronLightningFASE2::LaserTime364(void)
{
	Laser364();
}

void CFatronLightningFASE2::LaserTime365(void)
{
	Laser365();
}

void CFatronLightningFASE2::LaserTime366(void)
{
	Laser366();
}

void CFatronLightningFASE2::LaserTime367(void)
{
	Laser367();
}

void CFatronLightningFASE2::LaserTime368(void)
{
	Laser368();
}

void CFatronLightningFASE2::LaserTime369(void)
{
	Laser369();
}

void CFatronLightningFASE2::LaserTime370(void)
{
	Laser370();
}

void CFatronLightningFASE2::LaserTime371(void)
{
	Laser371();
}

void CFatronLightningFASE2::Laser(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser2(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser3(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser4(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser5(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser6(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser7(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser8(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser9(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser10(void)
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
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser11(void)
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

	SetThink( LaserTime12 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser12(void)
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

	SetThink( LaserTime13 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser13(void)
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

	SetThink( LaserTime14 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser14(void)
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

	SetThink( LaserTime15 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser15(void)
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

	SetThink( LaserTime16 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser16(void)
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

	SetThink( LaserTime17 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser17(void)
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

	SetThink( LaserTime18 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser18(void)
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

	SetThink( LaserTime19 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser19(void)
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

	SetThink( LaserTime20 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser20(void)
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

	SetThink( LaserTime21 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser21(void)
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

	SetThink( LaserTime22 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser22(void)
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

	SetThink( LaserTime23 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser23(void)
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

	SetThink( LaserTime24 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser24(void)
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

	SetThink( LaserTime25 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser25(void)
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

	SetThink( LaserTime26 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser26(void)
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

	SetThink( LaserTime27 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser27(void)
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

	SetThink( LaserTime28 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser28(void)
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

	SetThink( LaserTime29 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser29(void)
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

	SetThink( LaserTime30 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser30(void)
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

	SetThink( LaserTime31 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser31(void)
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

	SetThink( LaserTime32 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser32(void)
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

	SetThink( LaserTime33 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser33(void)
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

	SetThink( LaserTime34 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser34(void)
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

	SetThink( LaserTime35 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser35(void)
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

	SetThink( LaserTime36 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser36(void)
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

	SetThink( LaserTime37 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser37(void)
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

	SetThink( LaserTime38 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser38(void)
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

	SetThink( LaserTime39 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser39(void)
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

	SetThink( LaserTime40 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser40(void)
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

	SetThink( LaserTime41 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser41(void)
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

	SetThink( LaserTime42 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser42(void)
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

	SetThink( LaserTime43 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser43(void)
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

	SetThink( LaserTime44 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser44(void)
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

	SetThink( LaserTime45 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser45(void)
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

	SetThink( LaserTime46 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser46(void)
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

	SetThink( LaserTime47 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser47(void)
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

	SetThink( LaserTime48 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser48(void)
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

	SetThink( LaserTime49 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser49(void)
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

	SetThink( LaserTime50 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser50(void)
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

	SetThink( LaserTime51 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser51(void)
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

	SetThink( LaserTime52 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser52(void)
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

	SetThink( LaserTime53 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser53(void)
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

	SetThink( LaserTime54 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser54(void)
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

	SetThink( LaserTime55 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser55(void)
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

	SetThink( LaserTime56 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser56(void)
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

	SetThink( LaserTime57 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser57(void)
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

	SetThink( LaserTime58 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser58(void)
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

	SetThink( LaserTime59 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser59(void)
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

	SetThink( LaserTime60 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser60(void)
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

	SetThink( LaserTime61 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser61(void)
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

	SetThink( LaserTime62 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser62(void)
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

	SetThink( LaserTime63 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser63(void)
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

	SetThink( LaserTime64 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser64(void)
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

	SetThink( LaserTime65 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser65(void)
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

	SetThink( LaserTime66 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser66(void)
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

	SetThink( LaserTime67 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser67(void)
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

	SetThink( LaserTime68 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser68(void)
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

	SetThink( LaserTime69 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser69(void)
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

	SetThink( LaserTime70 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser70(void)
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

	SetThink( LaserTime71 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser71(void)
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

	SetThink( LaserTime72 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser72(void)
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

	SetThink( LaserTime73 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser73(void)
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

	SetThink( LaserTime74 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser74(void)
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

	SetThink( LaserTime75 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser75(void)
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

	SetThink( LaserTime76 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser76(void)
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

	SetThink( LaserTime77 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser77(void)
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

	SetThink( LaserTime78 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser78(void)
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

	SetThink( LaserTime79 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser79(void)
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

	SetThink( LaserTime80 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser80(void)
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

	SetThink( LaserTime81 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser81(void)
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

	SetThink( LaserTime82 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser82(void)
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

	SetThink( LaserTime83 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser83(void)
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

	SetThink( LaserTime84 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser84(void)
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

	SetThink( LaserTime85 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser85(void)
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

	SetThink( LaserTime86 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser86(void)
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

	SetThink( LaserTime87 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser87(void)
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

	SetThink( LaserTime88 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser88(void)
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

	SetThink( LaserTime89 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser89(void)
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

	SetThink( LaserTime90 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser90(void)
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

	SetThink( LaserTime91 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser91(void)
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

	SetThink( LaserTime92 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser92(void)
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

	SetThink( LaserTime93 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser93(void)
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

	SetThink( LaserTime94 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser94(void)
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

	SetThink( LaserTime95 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser95(void)
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

	SetThink( LaserTime96 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser96(void)
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

	SetThink( LaserTime97 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser97(void)
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

	SetThink( LaserTime98 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser98(void)
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

	SetThink( LaserTime99 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser99(void)
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

	SetThink( LaserTime100 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser100(void)
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

	SetThink( LaserTime101 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser101(void)
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

	SetThink( LaserTime102 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser102(void)
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

	SetThink( LaserTime103 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser103(void)
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

	SetThink( LaserTime104 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser104(void)
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

	SetThink( LaserTime105 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser105(void)
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

	SetThink( LaserTime106 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser106(void)
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

	SetThink( LaserTime107 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser107(void)
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

	SetThink( LaserTime108 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser108(void)
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

	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

    ::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg = 1000, 1000, CLASS_PLAYER_BIOWEAPON, DMG_BURN );

    EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/BeamShort.wav", 1, ATTN_NORM);

	SetThink( LaserTime109 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser109(void)
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

	SetThink( LaserTime110 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser110(void)
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

	SetThink( LaserTime111 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser111(void)
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

	SetThink( LaserTime112 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser112(void)
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

	SetThink( LaserTime113 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser113(void)
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

	SetThink( LaserTime114 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser114(void)
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

	SetThink( LaserTime115 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser115(void)
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

	SetThink( LaserTime116 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser116(void)
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

	SetThink( LaserTime117 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser117(void)
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

	SetThink( LaserTime118 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser118(void)
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

	SetThink( LaserTime119 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser119(void)
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

	SetThink( LaserTime120 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser120(void)
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

	SetThink( LaserTime121 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser121(void)
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

	SetThink( LaserTime122 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser122(void)
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

	SetThink( LaserTime123 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser123(void)
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

	SetThink( LaserTime124 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser124(void)
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

	SetThink( LaserTime125 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser125(void)
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

	SetThink( LaserTime126 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser126(void)
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

	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

    ::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg = 1000, 1000, CLASS_PLAYER_BIOWEAPON, DMG_BURN );

    EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/BeamShort.wav", 1, ATTN_NORM);

	SetThink( LaserTime127 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser127(void)
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

	SetThink( LaserTime128 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser128(void)
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

	SetThink( LaserTime129 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser129(void)
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

	SetThink( LaserTime130 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser130(void)
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

	SetThink( LaserTime131 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser131(void)
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

	SetThink( LaserTime132 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser132(void)
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

	SetThink( LaserTime133 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser133(void)
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

	SetThink( LaserTime134 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser134(void)
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

	SetThink( LaserTime135 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser135(void)
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

	SetThink( LaserTime136 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser136(void)
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

	SetThink( LaserTime137 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser137(void)
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

	SetThink( LaserTime138 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser138(void)
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

	SetThink( LaserTime139 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser139(void)
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

	SetThink( LaserTime140 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser140(void)
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

	SetThink( LaserTime141 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser141(void)
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

	entvars_t *pevOwner;
	if ( pev->owner )
		pevOwner = VARS( pev->owner );
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set

    ::RadiusDamage ( pev->origin, pev, pevOwner, pev->dmg = 1000, 1000, CLASS_PLAYER_BIOWEAPON, DMG_BURN );

    EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/fatrongrenade/BeamShort.wav", 1, ATTN_NORM);

	SetThink( LaserTime142 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser142(void)
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

	SetThink( LaserTime143 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser143(void)
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

	SetThink( LaserTime144 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser144(void)
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

	SetThink( LaserTime145 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser145(void)
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

	SetThink( LaserTime146 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser146(void)
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

	SetThink( LaserTime147 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser147(void)
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

	SetThink( LaserTime148 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser148(void)
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

	SetThink( LaserTime149 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser149(void)
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

	SetThink( LaserTime150 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser150(void)
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

	SetThink( LaserTime151 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser151(void)
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

	SetThink( LaserTime152 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser152(void)
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

	SetThink( LaserTime153 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser153(void)
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

	SetThink( LaserTime154 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser154(void)
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

	SetThink( LaserTime155 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser155(void)
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

	SetThink( LaserTime156 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser156(void)
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

	SetThink( LaserTime157 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser157(void)
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

	SetThink( LaserTime158 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser158(void)
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

	SetThink( LaserTime159 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser159(void)
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

	SetThink( LaserTime160 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser160(void)
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

	SetThink( LaserTime161 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser161(void)
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

	SetThink( LaserTime162 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser162(void)
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

	SetThink( LaserTime163 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser163(void)
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

	SetThink( LaserTime164 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser164(void)
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

	SetThink( LaserTime165 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser165(void)
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

	SetThink( LaserTime166 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser166(void)
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

	SetThink( LaserTime167 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser167(void)
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

	SetThink( LaserTime168 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser168(void)
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

	SetThink( LaserTime169 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser169(void)
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

	SetThink( LaserTime170 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser170(void)
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

	SetThink( LaserTime171 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser171(void)
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

	SetThink( LaserTime172 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser172(void)
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

	SetThink( LaserTime173 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser173(void)
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

	SetThink( LaserTime174 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser174(void)
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

	SetThink( LaserTime175 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser175(void)
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

	SetThink( LaserTime176 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser176(void)
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

	SetThink( LaserTime177 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser177(void)
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

	SetThink( LaserTime178 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser178(void)
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

	SetThink( LaserTime179 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser179(void)
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

	SetThink( LaserTime180 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser180(void)
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

	SetThink( LaserTime181 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser181(void)
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

	SetThink( LaserTime182 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser182(void)
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

	SetThink( LaserTime183 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser183(void)
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

	SetThink( LaserTime184 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser184(void)
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

	SetThink( LaserTime185 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser185(void)
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

	SetThink( LaserTime186 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser186(void)
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

	SetThink( LaserTime187 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser187(void)
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

	SetThink( LaserTime188 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser188(void)
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

	SetThink( LaserTime189 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser189(void)
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

	SetThink( LaserTime190 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser190(void)
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

	SetThink( LaserTime191 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser191(void)
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

	SetThink( LaserTime192 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser192(void)
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

	SetThink( LaserTime193 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser193(void)
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

	SetThink( LaserTime194 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser194(void)
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

	SetThink( LaserTime195 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser195(void)
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

	SetThink( LaserTime196 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser196(void)
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

	SetThink( LaserTime197 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser197(void)
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

	SetThink( LaserTime198 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser198(void)
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

	SetThink( LaserTime199 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser199(void)
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

	SetThink( LaserTime200 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser200(void)
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

	SetThink( LaserTime201 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser201(void)
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

	SetThink( LaserTime202 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser202(void)
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

	SetThink( LaserTime203 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser203(void)
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

	SetThink( LaserTime204 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser204(void)
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

	SetThink( LaserTime205 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser205(void)
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

	SetThink( LaserTime206 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser206(void)
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

	SetThink( LaserTime207 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser207(void)
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

	SetThink( LaserTime208 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser208(void)
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

	SetThink( LaserTime209 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser209(void)
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

	SetThink( LaserTime210 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser210(void)
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

	SetThink( LaserTime211 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser211(void)
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

	SetThink( LaserTime212 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser212(void)
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

	SetThink( LaserTime213 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser213(void)
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

	SetThink( LaserTime214 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser214(void)
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

	SetThink( LaserTime215 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser215(void)
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

	SetThink( LaserTime216 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser216(void)
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

	SetThink( LaserTime217 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser217(void)
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

	SetThink( LaserTime218 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser218(void)
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

	SetThink( LaserTime219 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser219(void)
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

	SetThink( LaserTime220 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser220(void)
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

	SetThink( LaserTime221 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser221(void)
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

	SetThink( LaserTime222 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser222(void)
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

	SetThink( LaserTime223 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser223(void)
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

	SetThink( LaserTime224 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser224(void)
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

	SetThink( LaserTime225 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser225(void)
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

	SetThink( LaserTime226 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser226(void)
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

	SetThink( LaserTime227 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser227(void)
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

	SetThink( LaserTime228 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser228(void)
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

	SetThink( LaserTime229 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser229(void)
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

	SetThink( LaserTime230 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser230(void)
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

	SetThink( LaserTime231 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser231(void)
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

	SetThink( LaserTime232 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser232(void)
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

	SetThink( LaserTime233 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser233(void)
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

	SetThink( LaserTime234 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser234(void)
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

	SetThink( LaserTime235 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser235(void)
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

	SetThink( LaserTime236 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser236(void)
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

	SetThink( LaserTime237 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser237(void)
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

	SetThink( LaserTime238 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser238(void)
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

	SetThink( LaserTime239 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser239(void)
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

	SetThink( LaserTime240 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser240(void)
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

	SetThink( LaserTime241 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser241(void)
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

	SetThink( LaserTime242 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser242(void)
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

	SetThink( LaserTime243 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser243(void)
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

	SetThink( LaserTime244 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser244(void)
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

	SetThink( LaserTime245 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser245(void)
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

	SetThink( LaserTime246 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser246(void)
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

	SetThink( LaserTime247 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser247(void)
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

	SetThink( LaserTime248 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser248(void)
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

	SetThink( LaserTime249 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser249(void)
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

	SetThink( LaserTime250 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser250(void)
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

	SetThink( LaserTime251 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser251(void)
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

	SetThink( LaserTime252 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser252(void)
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

	SetThink( LaserTime253 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser253(void)
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

	SetThink( LaserTime254 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser254(void)
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

	SetThink( LaserTime255 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser255(void)
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

	SetThink( LaserTime256 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser256(void)
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

	SetThink( LaserTime257 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser257(void)
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

	SetThink( LaserTime258 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser258(void)
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

	SetThink( LaserTime259 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser259(void)
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

	SetThink( LaserTime260 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser260(void)
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

	SetThink( LaserTime261 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser261(void)
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

	SetThink( LaserTime262 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser262(void)
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

	SetThink( LaserTime263 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser263(void)
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

	SetThink( LaserTime264 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser264(void)
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

	SetThink( LaserTime265 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser265(void)
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

	SetThink( LaserTime266 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser266(void)
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

	SetThink( LaserTime267 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser267(void)
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

	SetThink( LaserTime268 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser268(void)
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

	SetThink( LaserTime269 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser269(void)
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

	SetThink( LaserTime270 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser270(void)
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

	SetThink( LaserTime271 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser271(void)
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

	SetThink( LaserTime272 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser272(void)
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

	SetThink( LaserTime273 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser273(void)
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

	SetThink( LaserTime274 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser274(void)
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

	SetThink( LaserTime275 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser275(void)
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

	SetThink( LaserTime276 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser276(void)
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

	SetThink( LaserTime277 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser277(void)
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

	SetThink( LaserTime278 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser278(void)
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

	SetThink( LaserTime279 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser279(void)
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

	SetThink( LaserTime280 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser280(void)
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

	SetThink( LaserTime281 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser281(void)
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

	SetThink( LaserTime282 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser282(void)
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

	SetThink( LaserTime283 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser283(void)
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

	SetThink( LaserTime284 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser284(void)
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

	SetThink( LaserTime285 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser285(void)
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

	SetThink( LaserTime286 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser286(void)
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

	SetThink( LaserTime287 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser287(void)
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

	SetThink( LaserTime288 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser288(void)
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

	SetThink( LaserTime289 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser289(void)
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

	SetThink( LaserTime290 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser290(void)
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

	SetThink( LaserTime291 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser291(void)
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

	SetThink( LaserTime292 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser292(void)
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

	SetThink( LaserTime293 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser293(void)
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

	SetThink( LaserTime294 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser294(void)
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

	SetThink( LaserTime295 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser295(void)
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

	SetThink( LaserTime296 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser296(void)
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

	SetThink( LaserTime297 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser297(void)
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

	SetThink( LaserTime298 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser298(void)
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

	SetThink( LaserTime299 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser299(void)
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

	SetThink( LaserTime300 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser300(void)
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

	SetThink( LaserTime301 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser301(void)
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

	SetThink( LaserTime302 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser302(void)
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

	SetThink( LaserTime303 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser303(void)
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

	SetThink( LaserTime304 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser304(void)
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

	SetThink( LaserTime305 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser305(void)
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

	SetThink( LaserTime306 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser306(void)
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

	SetThink( LaserTime307 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser307(void)
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

	SetThink( LaserTime308 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser308(void)
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

	SetThink( LaserTime309 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser309(void)
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

	SetThink( LaserTime310 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser310(void)
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

	SetThink( LaserTime311 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser311(void)
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

	SetThink( LaserTime312 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser312(void)
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

	SetThink( LaserTime313 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser313(void)
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

	SetThink( LaserTime314 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser314(void)
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

	SetThink( LaserTime315 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser315(void)
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

	SetThink( LaserTime316 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser316(void)
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

	SetThink( LaserTime317 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser317(void)
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

	SetThink( LaserTime318 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser318(void)
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

	SetThink( LaserTime319 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser319(void)
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

	SetThink( LaserTime320 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser320(void)
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

	SetThink( LaserTime321 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser321(void)
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

	SetThink( LaserTime322 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser322(void)
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

	SetThink( LaserTime323 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser323(void)
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

	SetThink( LaserTime324 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser324(void)
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

	SetThink( LaserTime325 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser325(void)
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

	SetThink( LaserTime326 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser326(void)
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

	SetThink( LaserTime327 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser327(void)
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

	SetThink( LaserTime328 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser328(void)
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

	SetThink( LaserTime329 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser329(void)
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

	SetThink( LaserTime330 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser330(void)
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

	SetThink( LaserTime331 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser331(void)
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

	SetThink( LaserTime332 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser332(void)
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

	SetThink( LaserTime333 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser333(void)
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

	SetThink( LaserTime334 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser334(void)
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

	SetThink( LaserTime335 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser335(void)
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

	SetThink( LaserTime336 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser336(void)
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

	SetThink( LaserTime337 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser337(void)
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

	SetThink( LaserTime338 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser338(void)
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

	SetThink( LaserTime339 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser339(void)
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

	SetThink( LaserTime340 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser340(void)
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

	SetThink( LaserTime341 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser341(void)
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

	SetThink( LaserTime342 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser342(void)
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

	SetThink( LaserTime343 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser343(void)
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

	SetThink( LaserTime344 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser344(void)
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

	SetThink( LaserTime345 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser345(void)
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

	SetThink( LaserTime346 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser346(void)
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

	SetThink( LaserTime347 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser347(void)
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

	SetThink( LaserTime348 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser348(void)
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

	SetThink( LaserTime349 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser349(void)
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

	SetThink( LaserTime350 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser350(void)
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

	SetThink( LaserTime351 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser351(void)
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

	SetThink( LaserTime352 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser352(void)
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

	SetThink( LaserTime353 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser353(void)
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

	SetThink( LaserTime354 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser354(void)
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

	SetThink( LaserTime355 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser355(void)
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

	SetThink( LaserTime356 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser356(void)
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

	SetThink( LaserTime357 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser357(void)
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

	SetThink( LaserTime358 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser358(void)
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

	SetThink( LaserTime359 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser359(void)
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

	SetThink( LaserTime360 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser360(void)
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

	SetThink( LaserTime361 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser361(void)
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

	SetThink( LaserTime362 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser362(void)
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

	SetThink( LaserTime363 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser363(void)
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

	SetThink( LaserTime364 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser364(void)
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

	SetThink( LaserTime365 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser365(void)
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

	SetThink( LaserTime366 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser366(void)
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

	SetThink( LaserTime367 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser367(void)
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

	SetThink( LaserTime368 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser368(void)
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

	SetThink( LaserTime369 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser369(void)
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

	SetThink( LaserTime370 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser370(void)
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

	SetThink( LaserTime371 );
	pev->nextthink = gpGlobals->time + 0.1;
}

void CFatronLightningFASE2::Laser371(void)
{	
    UTIL_Remove( this );
}
