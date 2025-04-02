#include "minigame/minigame2/minigame2.h"

static PLEX_SPRITE* p_cowgirlPamaleanaSprite = NULL;
static PLEX_SPRITE* p_cowguyLevineSprite = NULL;
static PLEX_SPRITE* p_conciergeSprite = NULL;
static PLEX_SPRITE* p_leadOutlawSprite = NULL;
static PLEX_SPRITE* p_sideOutlawSprite = NULL;
static PLEX_SPRITE* p_muteOutlawSprite = NULL;
static PLEX_SPRITE* p_outlawLawyerSprite = NULL;

static size_t p_hotelBack = 0;
static size_t p_penultimateSpriteTex = 0;

static size_t p_cowgirlPamaleana = 0;
static size_t p_cowguyLevine = 0;
static size_t p_concierge = 0;
static size_t p_leadOutlaw = 0;
static size_t p_sideOutlaw = 0;
static size_t p_muteOutlaw = 0;
static size_t p_outlawLawyer = 0;

static bool p_penultimateCutPlay = false;
static bool p_penultimateCutIsPlaying = false;

// sprite theater talking slides:

static void p_cowgirlPamTalkWait(const char* message, const uint64_t wait, const bool stopMusic)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_cowgirlPamaleana, wait, stopMusic);
}

static void p_cowgirlPamTalk(const char* message)
{
	p_cowgirlPamTalkWait(message, 0, false);
}

static void p_cowguyLevineTalkWait(const char* message, const uint64_t wait, const bool stopMusic)
{
	PLEX_addSpriteTheaterSlide(200, 200, 0, message, p_cowguyLevine, wait, stopMusic);
}

static void p_cowguyLevineTalk(const char* message)
{
	p_cowguyLevineTalkWait(message, 0, false);
}

static void p_conciergeVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(205, 108, 69, message, p_concierge, 0, true);
}

static void p_sideOutlawVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(120, 200, 149, message, p_sideOutlaw, 0, true);
}

static void p_leadOutlawVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(225, 220, 127, message, p_leadOutlaw, 0, true);
}

static void p_outlawLawyerVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(220, 220, 220, message, p_outlawLawyer, 0, true);
}

static void p_drawSkipPenultimateButton(const size_t fontPlate)
{
	if(PLEX_drawButton(MMS2_DRAWLAYER_GUI, "Skip Cutscene", PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_WW(false) - PLEX_UNIT(5), PLEX_UNIT(1.5), PLEX_UNIT(5), PLEX_UNIT(1), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.08), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, false))
	{
		PLEX_endSpriteTheater();
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemPenultimateCutscene()
{
	p_penultimateCutPlay = false;
	p_penultimateCutIsPlaying = false;
}

void MMS2_initSystemPenultimateCutscene()
{

}

bool MMS2_checkRunSystemPenultimateCutscene(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	if(MMS2_penultimateCutPlay() && !MMS2_mayorCutaway())
	{
		MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);

		MMS2_penultimateCutscene(fontPlate, label, bubble, arrow);

		MMS2_markPenultimateCustcenePlaying();
	}

	if(MMS2_penultimateCutIsPlaying())
	{
		if(MMS2_lastTownGotBoss()) p_drawSkipPenultimateButton(fontPlate);

		if((!PLEX_isSpriteTheaterOver() && !MMS2_terminateConfirm()) || MM_COMMON_skipButton(fontPlate))
		{
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			MM_COMMON_update();
			return true;
		}

		if(PLEX_inSpriteTheater()) PLEX_endSpriteTheater();

		MMS2_readyLevineFight();
		MMS2_clearPenultimateCutscene();
		return true;
	}

	return false;
}

void MMS2_endSystemPenultimateCutscene()
{
	MMS2_clearPenultimateCutsceneSprites();
}

void MMS2_clearPenultimateCutsceneSprites()
{
	if(p_cowguyLevineSprite != NULL) PLEX_destroySprite(&p_cowguyLevineSprite);
	if(p_cowgirlPamaleanaSprite != NULL) PLEX_destroySprite(&p_cowgirlPamaleanaSprite);
	if(p_conciergeSprite != NULL) PLEX_destroySprite(&p_conciergeSprite);
	if(p_leadOutlawSprite != NULL) PLEX_destroySprite(&p_leadOutlawSprite);
	if(p_sideOutlawSprite != NULL) PLEX_destroySprite(&p_sideOutlawSprite);
	if(p_muteOutlawSprite != NULL) PLEX_destroySprite(&p_muteOutlawSprite);
	if(p_outlawLawyerSprite != NULL) PLEX_destroySprite(&p_outlawLawyerSprite);

	if(!p_penultimateSpriteTex) PLEX_destroyTexture(p_penultimateSpriteTex);

	if(!p_hotelBack) PLEX_destroyTexture(p_hotelBack);

	p_penultimateSpriteTex = 0;

	p_hotelBack = 0;
}

void MMS2_penultimateCutscene(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE conciergePlate;
	PLEX_ANIMATION_PLATE leadOutlawPlate;
	PLEX_ANIMATION_PLATE sideOutlawPlate;
	PLEX_ANIMATION_PLATE muteOutlawPlate;
	PLEX_ANIMATION_PLATE outlawLawyerPlate;
	PLEX_ANIMATION_PLATE cowgirlPamaleanaPlate;
	PLEX_ANIMATION_PLATE cowguyLevinePlate;

	PLEX_ANIMATION* cowguyLevinePhoneAnim = NULL;
	PLEX_ANIMATION* cowguyLevineStandAnim = NULL;
	PLEX_ANIMATION* cowguyLevineShoutAnim = NULL;
	PLEX_ANIMATION* cowguyLevinePointAnim = NULL;
	PLEX_ANIMATION* cowguyLevinePaperAnim = NULL;

	PLEX_ANIMATION* cowgirlPamaleanaUpAnim = NULL;
	PLEX_ANIMATION* cowgirlPamaleanaPapersAnim = NULL;
	PLEX_ANIMATION* cowgirlPamaleanaDownAnim = NULL;
	PLEX_ANIMATION* cowgirlPamaleanaOpenDoorAnim = NULL;
	PLEX_ANIMATION* cowgirlPamaleanaPapersAnim2 = NULL;

	PLEX_ANIMATION* conciergeUpAnim = NULL;
	PLEX_ANIMATION* conciergeWindowJump = NULL;
	PLEX_ANIMATION* windowBreakAnim = NULL;

	PLEX_ANIMATION* leadOutlawAnim = NULL;

	PLEX_ANIMATION* sideOutlawAnim = NULL;

	PLEX_ANIMATION* muteOutlawAnim = NULL;

	PLEX_ANIMATION* outlawLawyerPapersAnim = NULL;
	PLEX_ANIMATION* outlawLawyerAnim = NULL;

	MMS2_clearPenultimateCutsceneSprites();

	if(!p_hotelBack) p_hotelBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_HOTELBACK, MMS2_FILEPATH_HEADERLESS_HOTELBACK);

	if(!p_penultimateSpriteTex) p_penultimateSpriteTex = PLEX_loadTextureFromFileOrHeaderless(512, 128, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_ACTORPLATE, MMS2_FILEPATH_HEADERLESS_ACTORPLATE);

	cowgirlPamaleanaPlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	cowguyLevinePlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	conciergePlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	leadOutlawPlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	sideOutlawPlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	muteOutlawPlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);
	outlawLawyerPlate = PLEX_createAnimationPlate(0.0625, 0.5, p_penultimateSpriteTex);

	p_cowgirlPamaleanaSprite = PLEX_genSprite(&cowgirlPamaleanaPlate);
	p_cowguyLevineSprite = PLEX_genSprite(&cowguyLevinePlate);
	p_conciergeSprite = PLEX_genSprite(&conciergePlate);
	p_leadOutlawSprite = PLEX_genSprite(&leadOutlawPlate);
	p_sideOutlawSprite = PLEX_genSprite(&sideOutlawPlate);
	p_muteOutlawSprite = PLEX_genSprite(&muteOutlawPlate);
	p_outlawLawyerSprite = PLEX_genSprite(&outlawLawyerPlate);

	// LEVINE SPRITE

	PLEX_addAnimation(p_cowguyLevineSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowguyLevineSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowguyLevineSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowguyLevineSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowguyLevineSprite, 1, PLEX_getGameTime());

	cowguyLevinePhoneAnim = PLEX_getAnimation(0, p_cowguyLevineSprite);

	PLEX_addAnimationFrame(0, cowguyLevinePhoneAnim);

	cowguyLevineStandAnim = PLEX_getAnimation(1, p_cowguyLevineSprite);

	PLEX_addAnimationFrame(1, cowguyLevineStandAnim);

	cowguyLevineShoutAnim = PLEX_getAnimation(2, p_cowguyLevineSprite);

	PLEX_addAnimationFrame(2, cowguyLevineShoutAnim);

	cowguyLevinePointAnim = PLEX_getAnimation(3, p_cowguyLevineSprite);

	PLEX_addAnimationFrame(3, cowguyLevinePointAnim);

	cowguyLevinePaperAnim = PLEX_getAnimation(4, p_cowguyLevineSprite);

	PLEX_addAnimationFrame(4, cowguyLevinePaperAnim);

	// PAMALEANA SPRITE

	PLEX_addAnimation(p_cowgirlPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowgirlPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowgirlPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowgirlPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cowgirlPamaleanaSprite, 500, PLEX_getGameTime());

	cowgirlPamaleanaUpAnim = PLEX_getAnimation(0, p_cowgirlPamaleanaSprite);

	PLEX_addAnimationFrame(5, cowgirlPamaleanaUpAnim);

	cowgirlPamaleanaPapersAnim = PLEX_getAnimation(1, p_cowgirlPamaleanaSprite);

	PLEX_addAnimationFrame(6, cowgirlPamaleanaPapersAnim);

	cowgirlPamaleanaDownAnim = PLEX_getAnimation(2, p_cowgirlPamaleanaSprite);

	PLEX_addAnimationFrame(8, cowgirlPamaleanaDownAnim);

	cowgirlPamaleanaPapersAnim2 = PLEX_getAnimation(3, p_cowgirlPamaleanaSprite);

	PLEX_addAnimationFrame(7, cowgirlPamaleanaPapersAnim2);

	cowgirlPamaleanaOpenDoorAnim = PLEX_getAnimation(4, p_cowgirlPamaleanaSprite);

	PLEX_addAnimationFrame(9, cowgirlPamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(10, cowgirlPamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(11, cowgirlPamaleanaOpenDoorAnim);
	PLEX_addAnimationFrame(12, cowgirlPamaleanaOpenDoorAnim);

	// BELLBOY SPRITE

	PLEX_addAnimation(p_conciergeSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_conciergeSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_conciergeSprite, 1, PLEX_getGameTime());

	conciergeUpAnim = PLEX_getAnimation(0, p_conciergeSprite);

	PLEX_addAnimationFrame(21, conciergeUpAnim);

	conciergeWindowJump = PLEX_getAnimation(1, p_conciergeSprite);

	PLEX_addAnimationFrame(22, conciergeWindowJump);
	PLEX_addAnimationFrame(23, conciergeWindowJump);
	PLEX_addAnimationFrame(24, conciergeWindowJump);
	PLEX_addAnimationFrame(25, conciergeWindowJump);
	PLEX_addAnimationFrame(26, conciergeWindowJump);
	PLEX_addAnimationFrame(27, conciergeWindowJump);
	PLEX_addAnimationFrame(27, conciergeWindowJump);
	PLEX_addAnimationFrame(27, conciergeWindowJump);

	windowBreakAnim = PLEX_getAnimation(2, p_conciergeSprite);

	PLEX_addAnimationFrame(27, windowBreakAnim);

	// LEAD OUTLAW SPRITE

	PLEX_addAnimation(p_leadOutlawSprite, 500, PLEX_getGameTime());

	leadOutlawAnim = PLEX_getAnimation(0, p_leadOutlawSprite);

	PLEX_addAnimationFrame(13, leadOutlawAnim);
	PLEX_addAnimationFrame(14, leadOutlawAnim);
	PLEX_addAnimationFrame(15, leadOutlawAnim);
	PLEX_addAnimationFrame(16, leadOutlawAnim);

	// SIDE OUTLAW SPRITE

	PLEX_addAnimation(p_sideOutlawSprite, 1, PLEX_getGameTime());

	sideOutlawAnim = PLEX_getAnimation(0, p_sideOutlawSprite);

	PLEX_addAnimationFrame(17, sideOutlawAnim);

	// MUTE OUTLAW SPRITE

	PLEX_addAnimation(p_muteOutlawSprite, 1, PLEX_getGameTime());

	muteOutlawAnim = PLEX_getAnimation(0, p_muteOutlawSprite);

	PLEX_addAnimationFrame(18, muteOutlawAnim);

	// OUTLAW LAWYER SPRITE

	PLEX_addAnimation(p_outlawLawyerSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_outlawLawyerSprite, 1, PLEX_getGameTime());

	outlawLawyerPapersAnim = PLEX_getAnimation(0, p_outlawLawyerSprite);

	PLEX_addAnimationFrame(19, outlawLawyerPapersAnim);

	outlawLawyerAnim = PLEX_getAnimation(1, p_outlawLawyerSprite);

	PLEX_addAnimationFrame(20, outlawLawyerAnim);

	// START SPRITES

	PLEX_startSprite(PLEX_getGameTime(), p_cowguyLevineSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_cowgirlPamaleanaSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_conciergeSprite);

	PLEX_startSprite(PLEX_getGameTime(), p_leadOutlawSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_sideOutlawSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_muteOutlawSprite);

	PLEX_startSprite(PLEX_getGameTime(), p_outlawLawyerSprite);

	// BEGIN SPRITE THEATER

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_OLDISCREETMOTEL, p_hotelBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	// CREATE ACTORS

	p_cowguyLevine = PLEX_createActor(p_cowguyLevineSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 1), PLEX_convDimens(2, 4)), false);
	p_cowgirlPamaleana = PLEX_createActor(p_cowgirlPamaleanaSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 0.1, PLEX_HEIGHTUNITMAX() - 6), PLEX_convDimens(2, 4)), true);
	p_concierge = PLEX_createActor(p_conciergeSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 6), PLEX_convDimens(2, 4)), true);
	p_leadOutlaw = PLEX_createActor(p_leadOutlawSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 6), PLEX_convDimens(2, 4)), true);
	p_sideOutlaw = PLEX_createActor(p_sideOutlawSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX()/2 + 8), PLEX_convDimens(2, 4)), true);
	p_muteOutlaw = PLEX_createActor(p_muteOutlawSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 2, PLEX_HEIGHTUNITMAX()/2 + 8), PLEX_convDimens(2, 4)), true);
	p_outlawLawyer = PLEX_createActor(p_outlawLawyerSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 2, PLEX_HEIGHTUNITMAX()/2 + 1), PLEX_convDimens(2, 4)), true);

	// SPRITE THEATER EVENTS

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_DARKCITY);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE1);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE2);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE3);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE4);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS2_LANGUAGE_PENULT_LINE5);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE6);

	PLEX_changeActor(p_cowguyLevine, 1);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE7);

	PLEX_unhideActor(p_cowgirlPamaleana);

	p_cowguyLevineTalkWait(MMS2_LANGUAGE_PENULT_LINE8, 500, false);

	PLEX_changeActor(p_cowgirlPamaleana, 1);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE9);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE10);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE11);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE12);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE13);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE14);

	PLEX_changeActor(p_cowgirlPamaleana, 0);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE15);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE16);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE17);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE18);

	PLEX_changeActor(p_cowgirlPamaleana, 2);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS2_LANGUAGE_PENULT_LINE19);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE20);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE21);

	PLEX_changeActor(p_cowguyLevine, 2);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE22);

	PLEX_changeActor(p_cowguyLevine, 3);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE23);

	PLEX_changeActor(p_cowguyLevine, 1);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_SUSPENSE);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE24);

	PLEX_changeActor(p_cowguyLevine, 2);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE25);

	PLEX_changeActor(p_cowguyLevine, 1);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE26);

	PLEX_changeActor(p_cowgirlPamaleana, 4);

	p_cowgirlPamTalkWait(MMS2_LANGUAGE_PENULT_LINE27, 200, false);

	PLEX_changeActor(p_cowgirlPamaleana, 2);

	PLEX_moveActor(p_cowgirlPamaleana, PLEX_WIDTHUNITMAX()/2 + 3, PLEX_HEIGHTUNITMAX()/2 + 1);

	PLEX_unhideActor(p_concierge);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE28);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE29);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE30);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE31);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE32);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE33);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE34);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE35);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS2_LANGUAGE_PENULT_LINE36);

	PLEX_moveActor(p_concierge, PLEX_HEIGHTUNITMAX() * 0.333325 - 2, PLEX_HEIGHTUNITMAX()/2 - 5);

	PLEX_changeActor(p_concierge, 1);

	p_conciergeVoice(MMS2_LANGUAGE_PENULT_LINE37);

	PLEX_changeActor(p_concierge, 2);

	PLEX_unhideActor(p_leadOutlaw);
	PLEX_unhideActor(p_sideOutlaw);
	PLEX_unhideActor(p_muteOutlaw);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE38);

	p_cowguyLevineTalkWait(MMS2_LANGUAGE_PENULT_LINE39, 2000, true);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE40);

	p_sideOutlawVoice(MMS2_LANGUAGE_PENULT_LINE41);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE42);

	p_sideOutlawVoice(MMS2_LANGUAGE_PENULT_LINE43);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE44);

	p_sideOutlawVoice(MMS2_LANGUAGE_PENULT_LINE45);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE46);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE47);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE48);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE49);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE50);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE51);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE52);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE53);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE54);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE55);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE56);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE57);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE58);

	PLEX_unhideActor(p_outlawLawyer);

	p_outlawLawyerVoice(MMS2_LANGUAGE_PENULT_LINE59);

	PLEX_changeActor(p_outlawLawyer, 1);
	PLEX_changeActor(p_cowguyLevine, 4);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE60);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE61);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE62);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE63);

	p_sideOutlawVoice(MMS2_LANGUAGE_PENULT_LINE64);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE65);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE66);

	p_outlawLawyerVoice(MMS2_LANGUAGE_PENULT_LINE67);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE68);

	PLEX_changeActor(p_cowguyLevine, 1);
	PLEX_changeActor(p_cowgirlPamaleana, 3);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE69);

	PLEX_changeActor(p_cowgirlPamaleana, 2);
	PLEX_changeActor(p_outlawLawyer, 0);

	p_cowgirlPamTalk(MMS2_LANGUAGE_PENULT_LINE70);

	p_leadOutlawVoice(MMS2_LANGUAGE_PENULT_LINE71);

	PLEX_hideActor(p_cowgirlPamaleana);
	PLEX_hideActor(p_leadOutlaw);
	PLEX_hideActor(p_outlawLawyer);
	PLEX_hideActor(p_sideOutlaw);
	PLEX_hideActor(p_muteOutlaw);

	p_cowguyLevineTalk(MMS2_LANGUAGE_PENULT_LINE72);
}

void MMS2_clearPenultimateCutscene()
{
	p_penultimateCutPlay = false;
	p_penultimateCutIsPlaying = false;
}

void MMS2_markPenultimateCutscene(){ p_penultimateCutPlay = true; }

void MMS2_markPenultimateCustcenePlaying()
{
	p_penultimateCutPlay = false;
	p_penultimateCutIsPlaying = true;
}

bool MMS2_penultimateCutPlay(){ return p_penultimateCutPlay; }
bool MMS2_penultimateCutIsPlaying(){ return p_penultimateCutIsPlaying; }
