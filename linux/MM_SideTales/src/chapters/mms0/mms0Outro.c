#include "chapters/mms0.h"

static int64_t p_pamaleana2 = -1;

static PLEX_SPRITE* p_pamaleanaSprite2 = NULL;
static PLEX_SPRITE* p_bellhopSprite = NULL;
static PLEX_SPRITE* p_leadTerroristSprite = NULL;
static PLEX_SPRITE* p_sideTerroristSprite = NULL;
static PLEX_SPRITE* p_muteTerroristSprite = NULL;
static PLEX_SPRITE* p_terroristLawyerSprite = NULL;

static int64_t p_bellhop = -1;

static int64_t p_leadTerrorist = -1;
static int64_t p_sideTerrorist = -1;
static int64_t p_muteTerrorist = -1;
static int64_t p_terroristLawyer = -1;

static size_t p_hotelBack = 0;

static void p_bellhopVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(205, 108, 69, message, p_bellhop, 0, true);
}

static void p_sideTerroristVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(120, 200, 149, message, p_sideTerrorist, 0, true);
}

static void p_leadTerroristVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(225, 220, 127, message, p_leadTerrorist, 0, true);
}

static void p_terroristLawyerVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(220, 220, 220, message, p_terroristLawyer, 0, true);
}

void MMS_startOutro(const size_t pamaleanaSpriteTex, const size_t levineSpriteTex, const size_t chapter0SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE pamaleanaPlate2 = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE bellhopPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE leadTerroristPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE sideTerroristPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE muteTerroristPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE terroristLawyerPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);

	PLEX_ANIMATION* levinePhoneAnim = NULL;
	PLEX_ANIMATION* levineStandAnim = NULL;
	PLEX_ANIMATION* levineShoutAnim = NULL;
	PLEX_ANIMATION* levinePointAnim = NULL;
	PLEX_ANIMATION* levinePaperAnim = NULL;

	PLEX_ANIMATION* pamaleanaUpAnim = NULL;
	PLEX_ANIMATION* pamaleanaPapersAnim = NULL;
	PLEX_ANIMATION* pamaleanaDownAnim = NULL;
	PLEX_ANIMATION* pamaleanaOpenDoorAnim = NULL;
	PLEX_ANIMATION* pamaleanaPapersAnim2 = NULL;

	PLEX_ANIMATION* bellhopUpAnim = NULL;
	PLEX_ANIMATION* bellhopWindowJump = NULL;
	PLEX_ANIMATION* windowBreakAnim = NULL;

	PLEX_ANIMATION* leadTerroristAnim = NULL;

	PLEX_ANIMATION* sideTerroristAnim = NULL;

	PLEX_ANIMATION* muteTerroristAnim = NULL;

	PLEX_ANIMATION* terroristLawyerPapersAnim = NULL;
	PLEX_ANIMATION* terroristLawyerAnim = NULL;

	p_hotelBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS_FILEPATH_TEX_HOTELROOM, MMS_FILEPATH_HEADERLESS_HOTELROOM);

	p_pamaleanaSprite2 = PLEX_genSprite(&pamaleanaPlate2);
	p_bellhopSprite = PLEX_genSprite(&bellhopPlate);
	p_leadTerroristSprite = PLEX_genSprite(&leadTerroristPlate);
	p_sideTerroristSprite = PLEX_genSprite(&sideTerroristPlate);
	p_muteTerroristSprite = PLEX_genSprite(&muteTerroristPlate);
	p_terroristLawyerSprite = PLEX_genSprite(&terroristLawyerPlate);

	MMS_genSpritePamaleana(pamaleanaSpriteTex);
	MMS_genSpriteLevine(levineSpriteTex);

	// LEVINE SPRITE

	MMS_addLevineAnimation(1);
	MMS_addLevineAnimation(1);
	MMS_addLevineAnimation(1);
	MMS_addLevineAnimation(1);
	MMS_addLevineAnimation(1);

	levinePhoneAnim = MMS_getLevineAnimation(0);

	PLEX_addAnimationFrame(0, levinePhoneAnim);

	levineStandAnim = MMS_getLevineAnimation(1);

	PLEX_addAnimationFrame(1, levineStandAnim);

	levineShoutAnim = MMS_getLevineAnimation(2);

	PLEX_addAnimationFrame(2, levineShoutAnim);

	levinePointAnim = MMS_getLevineAnimation(3);

	PLEX_addAnimationFrame(3, levinePointAnim);

	levinePaperAnim = MMS_getLevineAnimation(4);

	PLEX_addAnimationFrame(4, levinePaperAnim);

	// PAMALEANA SPRITE

	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);

	PLEX_addAnimation(p_pamaleanaSprite2, 500, PLEX_getGameTime());

	pamaleanaUpAnim = MMS_getPamaleanaAnimation(0);

	PLEX_addAnimationFrame(4, pamaleanaUpAnim);

	pamaleanaPapersAnim = MMS_getPamaleanaAnimation(1);

	PLEX_addAnimationFrame(30, pamaleanaPapersAnim);

	pamaleanaDownAnim = MMS_getPamaleanaAnimation(2);

	PLEX_addAnimationFrame(13, pamaleanaDownAnim);

	pamaleanaPapersAnim2 = MMS_getPamaleanaAnimation(3);

	PLEX_addAnimationFrame(31, pamaleanaPapersAnim2);

	pamaleanaOpenDoorAnim = PLEX_getAnimation(0, p_pamaleanaSprite2);

	PLEX_addAnimationFrame(37, pamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(38, pamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(39, pamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(40, pamaleanaOpenDoorAnim);

	// BELLBOY SPRITE

	PLEX_addAnimation(p_bellhopSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_bellhopSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_bellhopSprite, 1, PLEX_getGameTime());

	bellhopUpAnim = PLEX_getAnimation(0, p_bellhopSprite);

	PLEX_addAnimationFrame(30, bellhopUpAnim);

	bellhopWindowJump = PLEX_getAnimation(1, p_bellhopSprite);

	PLEX_addAnimationFrame(31, bellhopWindowJump);
	PLEX_addAnimationFrame(32, bellhopWindowJump);
	PLEX_addAnimationFrame(33, bellhopWindowJump);
	PLEX_addAnimationFrame(34, bellhopWindowJump);
	PLEX_addAnimationFrame(35, bellhopWindowJump);
	PLEX_addAnimationFrame(36, bellhopWindowJump);
	PLEX_addAnimationFrame(36, bellhopWindowJump);
	PLEX_addAnimationFrame(36, bellhopWindowJump);

	windowBreakAnim = PLEX_getAnimation(2, p_bellhopSprite);

	PLEX_addAnimationFrame(36, windowBreakAnim);

	// LEAD TERRORIST SPRITE

	PLEX_addAnimation(p_leadTerroristSprite, 500, PLEX_getGameTime());

	leadTerroristAnim = PLEX_getAnimation(0, p_leadTerroristSprite);

	PLEX_addAnimationFrame(22, leadTerroristAnim);
	PLEX_addAnimationFrame(23, leadTerroristAnim);
	PLEX_addAnimationFrame(24, leadTerroristAnim);
	PLEX_addAnimationFrame(25, leadTerroristAnim);

	// SIDE TERRORIST SPRITE

	PLEX_addAnimation(p_sideTerroristSprite, 1, PLEX_getGameTime());

	sideTerroristAnim = PLEX_getAnimation(0, p_sideTerroristSprite);

	PLEX_addAnimationFrame(26, sideTerroristAnim);

	// MUTE TERRORIST SPRITE

	PLEX_addAnimation(p_muteTerroristSprite, 1, PLEX_getGameTime());

	muteTerroristAnim = PLEX_getAnimation(0, p_muteTerroristSprite);

	PLEX_addAnimationFrame(27, muteTerroristAnim);

	// TERRORIST LAWYER SPRITE

	PLEX_addAnimation(p_terroristLawyerSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_terroristLawyerSprite, 1, PLEX_getGameTime());

	terroristLawyerPapersAnim = PLEX_getAnimation(0, p_terroristLawyerSprite);

	PLEX_addAnimationFrame(28, terroristLawyerPapersAnim);

	terroristLawyerAnim = PLEX_getAnimation(1, p_terroristLawyerSprite);

	PLEX_addAnimationFrame(29, terroristLawyerAnim);

	// START SPRITES

	PLEX_startSprite(PLEX_getGameTime(), p_pamaleanaSprite2);
	PLEX_startSprite(PLEX_getGameTime(), p_bellhopSprite);

	PLEX_startSprite(PLEX_getGameTime(), p_leadTerroristSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_sideTerroristSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_muteTerroristSprite);

	PLEX_startSprite(PLEX_getGameTime(), p_terroristLawyerSprite);

	// BEGIN SPRITE THEATER

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DISCREETMOTEL, p_hotelBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	// CREATE ACTORS

	MMS_createActorPamaleana(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 6, true);

	MMS_createActorLevine(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 1, false);

	p_pamaleana2 = PLEX_createActor(p_pamaleanaSprite2, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 0.1, PLEX_HEIGHTUNITMAX() - 6), PLEX_convDimens(2, 4)), true);
	p_bellhop = PLEX_createActor(p_bellhopSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 6), PLEX_convDimens(2, 4)), true);
	p_leadTerrorist = PLEX_createActor(p_leadTerroristSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 6), PLEX_convDimens(2, 4)), true);
	p_sideTerrorist = PLEX_createActor(p_sideTerroristSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX()/2 + 8), PLEX_convDimens(2, 4)), true);
	p_muteTerrorist = PLEX_createActor(p_muteTerroristSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 2, PLEX_HEIGHTUNITMAX()/2 + 8), PLEX_convDimens(2, 4)), true);
	p_terroristLawyer = PLEX_createActor(p_terroristLawyerSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 2, PLEX_HEIGHTUNITMAX()/2 + 1), PLEX_convDimens(2, 4)), true);

	// SPRITE THEATER EVENTS

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_DARKCITY);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE1);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE2);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE3);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE4);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS_LANGUAGE_OUTROA_LINE5);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE6);

	MMS_levineChangeAnimation(1);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE7);

	MMS_pamUnhide();

	MMS_levineTalkWait(MMS_LANGUAGE_OUTROA_LINE8, 500, false);

	MMS_pamChangeAnimation(1);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE9);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE10);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE11);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE12);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE13);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE14);

	MMS_pamChangeAnimation(0);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE15);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE16);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE17);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE18);

	MMS_pamChangeAnimation(2);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS_LANGUAGE_OUTROA_LINE19);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE20);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE21);

	MMS_levineChangeAnimation(2);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE22);

	MMS_levineChangeAnimation(3);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE23);

	MMS_levineChangeAnimation(1);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_SUSPENSE);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE24);

	MMS_levineChangeAnimation(2);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE25);

	MMS_levineChangeAnimation(1);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE26);

	MMS_pamHide();
	PLEX_unhideActor(p_pamaleana2);

	MMS_pamTalkWait(MMS_LANGUAGE_OUTROA_LINE27, 200, false);

	PLEX_hideActor(p_pamaleana2);
	MMS_pamUnhide();

	MMS_movePamela(PLEX_WIDTHUNITMAX()/2 + 3, PLEX_HEIGHTUNITMAX()/2 + 1);

	PLEX_unhideActor(p_bellhop);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE28);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE29);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE30);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE31);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE32);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE33);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE34);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE35);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS_LANGUAGE_OUTROA_LINE36);

	PLEX_moveActor(p_bellhop, PLEX_HEIGHTUNITMAX() * 0.333325 - 2, PLEX_HEIGHTUNITMAX()/2 - 5);

	PLEX_changeActor(p_bellhop, 1);

	p_bellhopVoice(MMS_LANGUAGE_OUTROA_LINE37);

	PLEX_changeActor(p_bellhop, 2);

	PLEX_unhideActor(p_leadTerrorist);
	PLEX_unhideActor(p_sideTerrorist);
	PLEX_unhideActor(p_muteTerrorist);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE38);

	MMS_levineTalkWait(MMS_LANGUAGE_OUTROA_LINE39, 2000, true);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE40);

	p_sideTerroristVoice(MMS_LANGUAGE_OUTROA_LINE41);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE42);

	p_sideTerroristVoice(MMS_LANGUAGE_OUTROA_LINE43);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE44);

	p_sideTerroristVoice(MMS_LANGUAGE_OUTROA_LINE45);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE46);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE47);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE48);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE49);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE50);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE51);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE52);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE53);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE54);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE55);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE56);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE57);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE58);

	PLEX_unhideActor(p_terroristLawyer);

	p_terroristLawyerVoice(MMS_LANGUAGE_OUTROA_LINE59);

	PLEX_changeActor(p_terroristLawyer, 1);
	MMS_levineChangeAnimation(4);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE60);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE61);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE62);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE63);

	p_sideTerroristVoice(MMS_LANGUAGE_OUTROA_LINE64);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE65);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE66);

	p_terroristLawyerVoice(MMS_LANGUAGE_OUTROA_LINE67);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE68);

	MMS_levineChangeAnimation(1);
	MMS_pamChangeAnimation(3);

	MMS_levineTalk(MMS_LANGUAGE_OUTROA_LINE69);

	MMS_pamChangeAnimation(2);
	PLEX_changeActor(p_terroristLawyer, 0);

	MMS_pamTalk(MMS_LANGUAGE_OUTROA_LINE70);

	p_leadTerroristVoice(MMS_LANGUAGE_OUTROA_LINE71);
}

void MMS_freeOutro()
{
	if(p_pamaleanaSprite2 != NULL) PLEX_destroySprite(&p_pamaleanaSprite2);
	if(p_bellhopSprite != NULL) PLEX_destroySprite(&p_bellhopSprite);
	if(p_leadTerroristSprite != NULL) PLEX_destroySprite(&p_leadTerroristSprite);
	if(p_sideTerroristSprite != NULL) PLEX_destroySprite(&p_sideTerroristSprite);
	if(p_muteTerroristSprite != NULL) PLEX_destroySprite(&p_muteTerroristSprite);
	if(p_terroristLawyerSprite != NULL) PLEX_destroySprite(&p_terroristLawyerSprite);

	PLEX_destroyTexture(p_hotelBack);

	p_hotelBack = 0;
}

