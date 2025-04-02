#include "chapters/mms3.h"

static size_t p_deeblockGameshowBack = 0;

static size_t p_lightCone2 = 0;
static size_t p_lightCone3 = 0;

static size_t p_coworkers = 0;

PLEX_SPRITE* p_coworkersSprite = NULL;

static void p_addLightCone2(const double x, const double y)
{
	p_lightCone2 = MMS3_createLightCone(x, y);
}

static void p_addLightCone3(const double x, const double y)
{
	p_lightCone3 = MMS3_createLightCone(x, y);
}

static void p_coworkersTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(100, 100, 175, message, p_coworkers, 0, false);
}

static void p_loadDeeblockGameshowBack()
{
	if(!p_deeblockGameshowBack) p_deeblockGameshowBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKGAMESHOW, MMS3_FILEPATH_HEADERLESS_DEEBLOCKGAMESHOW);
}

static void p_createCoworkers(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* coworkers = 0;

	PLEX_ANIMATION_PLATE coworkersPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_coworkersSprite = PLEX_genSprite(&coworkersPlate);

	PLEX_addAnimation(p_coworkersSprite, 1, PLEX_getGameTime());

	coworkers = PLEX_getAnimation(0, p_coworkersSprite);

	PLEX_addAnimationFrame(118, coworkers);
}

static void p_setGameRoom(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_addHelldemon666();
	MMS3_addDeeblockPamaleana();
	MMS3_addDrDeeblock(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.5); // < after HellDemon

	MMS3_unhideHellDemon666();
	MMS3_changeActorHellDemon666(2);
	MMS3_moveHellDemon666(3, PLEX_HEIGHTUNITMAX() * 0.7);

	MMS3_unhideDeeblockPamaleana();
	MMS3_changeDeeblockPamaleana(3);
	MMS3_moveDeeblockPamaleana(PLEX_WIDTHUNITMAX() - 5, PLEX_HEIGHTUNITMAX() * 0.7);

	MMS3_changeDeeblockAnimation(6);

	// must be after other actors
	MMS3_addLightCone(PLEX_WIDTHUNITMAX()/2 - 2.5, PLEX_HEIGHTUNITMAX() * 0.5 - 5);
	MMS3_unhideLightCone();

	p_addLightCone2(1, PLEX_HEIGHTUNITMAX() * 0.7 - 5);
	p_addLightCone3(PLEX_WIDTHUNITMAX() - 6, PLEX_HEIGHTUNITMAX() * 0.7 - 5);
	//
}

static void p_addCoworkers(const double x, const double y)
{
	p_coworkers = PLEX_createActor(p_coworkersSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(4, 4)), false);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS3_startSceneS(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadDeeblockGameshowBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSGAMEROOM, p_deeblockGameshowBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_AGGRESSION);

	p_setGameRoom(fontPlate, label, bubble, arrow);

	MMS3_changeDeeblockAnimation(7);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENES00);

	MMS3_changeDeeblockAnimation(8);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENES01);

	MMS3_changeDeeblockAnimation(9);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENES02);

	MMS_pamNarration(MMS3_LANGUAGE_SCENES03);

	MMS3_changeDeeblockAnimation(6);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENES04);

	MMS3_changeDeeblockAnimation(9);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENES05);

	MMS3_changeDeeblockAnimation(6);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENES06);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENES07);

	MMS3_changeDeeblockAnimation(8);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENES08);

	MMS3_hideDeeblock();
	MMS3_hideLightCone();
	PLEX_hideActor(p_lightCone2);
	PLEX_hideActor(p_lightCone3);

	MMS3_changeActorHellDemon666(3);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_SUSPENSE);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENES09);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENES10);

	MMS3_changeDeeblockPamaleana(4);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENES11);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENES12);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENES13);
}

void MMS3_startSceneT(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadDeeblockGameshowBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSGAMEROOM, 0, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	p_setGameRoom(fontPlate, label, bubble, arrow);

	MMS3_hideLightCone();
	PLEX_hideActor(p_lightCone2);
	PLEX_hideActor(p_lightCone3);
	MMS3_hideDeeblock();
	MMS3_hideHellDemon666();
	MMS3_hideDeeblockPamaleana();

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PAMALEANA);

	MMS_pamNarration(MMS3_LANGUAGE_SCENET00);

	PLEX_changeSpriteTheaterBackground(p_deeblockGameshowBack, MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_AGGRESSION);

	MMS3_unhideLightCone();
	PLEX_unhideActor(p_lightCone2);
	PLEX_unhideActor(p_lightCone3);
	MMS3_unhideDeeblock();
	MMS3_unhideHellDemon666();
	MMS3_unhideDeeblockPamaleana();

	MMS3_changeActorHellDemon666(3);
	MMS3_changeDeeblockPamaleana(4);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET01);

	MMS3_changeDeeblockAnimation(8);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET02);

	MMS3_changeDeeblockAnimation(6);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENET03);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENET04);

	MMS3_changeDeeblockAnimation(9);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET05);

	MMS3_hideLightCone();
	PLEX_hideActor(p_lightCone2);
	PLEX_hideActor(p_lightCone3);
	MMS3_hideDeeblock();

	MMS3_changeActorHellDemon666(4);
	MMS3_changeDeeblockPamaleana(5);

	PLEX_playSpriteTheaterSoundEffect(MM_COMMON_SOUNDEFFECT_ELECTRICSHOCK);

	MMS_narration(MMS3_LANGUAGE_SCENET06);

	MMS3_changeActorHellDemon666(3);
	MMS3_changeDeeblockPamaleana(4);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DREAM);

	MMS_pamNarration(MMS3_LANGUAGE_SCENET07);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_AGGRESSION);

	MMS3_unhideLightCone();
	PLEX_unhideActor(p_lightCone2);
	PLEX_unhideActor(p_lightCone3);
	MMS3_unhideDeeblock();

	MMS3_changeDeeblockAnimation(6);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET08);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENET09);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET10);

	MMS3_changeDeeblockAnimation(10);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET11);

	MMS3_changeDeeblockAnimation(11);
	MMS3_moveDeeblock(3.5, PLEX_HEIGHTUNITMAX() * 0.7);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENET12);

	MMS3_changeActorHellDemon666(5);
	MMS3_changeDeeblockPamaleana(5);

	PLEX_playSpriteTheaterSoundEffect(MM_COMMON_SOUNDEFFECT_ELECTRICSHOCK);

	MMS_narration(MMS3_LANGUAGE_SCENET13);
}

void MMS3_startSceneU(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	MMS3_loadDeeblockOfficeBack();

	MMS3_setSceneDeeblockOffice(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PAMALEANA);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false, false);
	MMS3_pollockCodelliActorAnimationActionChange(13);

	MMS3_addDrDeeblock(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6);
	MMS3_addDeeblockChairs();

	MMS3_addDeeblockPamaleana();

	MMS3_moveDeeblockPamaleana(PLEX_WIDTHUNITMAX()/2 + 5, PLEX_HEIGHTUNITMAX() * 0.75 - 6);
	MMS3_unhideDeeblockPamaleana();
	MMS3_changeDeeblockPamaleana(1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEU00);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU01);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU02);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU03);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU04);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEU05);

	MMS3_pollockCodelliActorAnimationActionChange(14);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU06);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU07);

	MMS3_changeDeeblockAnimation(1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEU08);

	MMS3_changeDeeblockAnimation(0);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU09);

	MMS3_pollockCodelliActorAnimationActionChange(13);
	MMS3_changeDeeblockAnimation(3);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU10);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU11);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU12);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU13);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU14);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU15);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU16);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU17);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEU18);

	MMS3_changeDeeblockAnimation(0);
	MMS3_changeDeeblockPamaleana(6);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU19);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEU20);

	MMS3_changeDeeblockPamaleana(1);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEU21);
}

void MMS3_outro(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_NEWSROOM);

	p_addCoworkers(PLEX_WIDTHUNITMAX() * 0.7 - 4, PLEX_HEIGHTUNITMAX() * 0.6 + 1);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV00);

	MMS_extrapTalk(MMS3_LANGUAGE_SCENEV01);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV02);

	p_coworkersTalk(MMS3_LANGUAGE_SCENEV03);

	MMS_pamChangeAnimation(3);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV04);

	p_coworkersTalk(MMS3_LANGUAGE_SCENEV05);

	MMS_pamChangeAnimation(0);

	PLEX_hideActor(p_coworkers);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV06);

	MMS_extrapTalk(MMS3_LANGUAGE_SCENEV07);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV08);

	MMS_extrapTalk(MMS3_LANGUAGE_SCENEV09);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV10);

	MMS_pamTalk(MMS3_LANGUAGE_SCENEV11);

	MMS_extrapMaintenanceVoice(MMS3_LANGUAGE_SCENEV12);

	MMS_extrapTalk(MMS3_LANGUAGE_SCENEV13);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS3_LANGUAGE_SCENEV14);

	MMS_narration(MMS3_LANGUAGE_SCENEV15);
}

void MMS3_createSection5(const size_t chapter3SpriteTex)
{
	p_createCoworkers(chapter3SpriteTex);
}

void MMS3_freeSection5()
{
	if(p_deeblockGameshowBack) PLEX_destroyTexture(p_deeblockGameshowBack);

	p_deeblockGameshowBack = 0;
}

void MMS3_finalFreeSection5()
{
	PLEX_destroySprite(&p_coworkersSprite);
}
