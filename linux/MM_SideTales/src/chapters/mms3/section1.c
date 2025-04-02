#include "chapters/mms3.h"

static size_t p_pollocksOfficeBack = 0;
static size_t p_pollocksOfficeBackNight = 0;
static size_t p_mcConnimonOfficeBack = 0;

static size_t p_pollockCodelli = 0;
static size_t p_pollocksChair = 0;
static size_t p_officeBill = 0;
static size_t p_officeCourier = 0;
static size_t p_mrMcConnimon = 0;

PLEX_SPRITE* p_pollockSprite = NULL;
PLEX_SPRITE* p_pollockChairSprite = NULL;
PLEX_SPRITE* p_billSprite = NULL;

PLEX_SPRITE* p_courierSprite = NULL;
PLEX_SPRITE* p_mcConnimonSprite = NULL;

static void p_billTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(175, 172, 150, message, p_officeBill, 0, true);
}

static void p_courierTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(200, 200, 200, message, p_officeCourier, 0, true);
}

static void p_mcConnimonTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(200, 150, 50, message, p_mrMcConnimon, 0, true);
}

static void p_createPollockCodelli(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION_PLATE pollockPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	PLEX_ANIMATION_PLATE pollocksChairPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	PLEX_ANIMATION* pollockStandAnim = NULL;
	PLEX_ANIMATION* pollockLaughAnim = NULL;
	PLEX_ANIMATION* pollockShakeHeadAnim = NULL;
	PLEX_ANIMATION* pollockAngryAnim = NULL;
	PLEX_ANIMATION* pollockAngryAnim2 = NULL;
	PLEX_ANIMATION* pollockUpAnim = NULL;
	PLEX_ANIMATION* pollockCelebrateAnim = NULL;
	PLEX_ANIMATION* pollockShameAnim = NULL;
	PLEX_ANIMATION* pollockPhoneAnim = NULL;
	PLEX_ANIMATION* pollockUpPaper = NULL;
	PLEX_ANIMATION* pollockAngryPointUp = NULL;
	PLEX_ANIMATION* pollockHangUp = NULL;
	PLEX_ANIMATION* pollockSitShocked = NULL;
	PLEX_ANIMATION* pollockSitOld = NULL;
	PLEX_ANIMATION* pollockSitOldPaper = NULL;

	PLEX_ANIMATION* pollockChairAnim = NULL;

	p_pollockSprite = PLEX_genSprite(&pollockPlate);

	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 2000, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 250, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 2000, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_pollockSprite, 1, PLEX_getGameTime());

	pollockStandAnim = PLEX_getAnimation(0, p_pollockSprite);

	PLEX_addAnimationFrame(0, pollockStandAnim);

	pollockLaughAnim = PLEX_getAnimation(1, p_pollockSprite);

	PLEX_addAnimationFrame(0, pollockLaughAnim);
	PLEX_addAnimationFrame(1, pollockLaughAnim);
	PLEX_addAnimationFrame(0, pollockLaughAnim);
	PLEX_addAnimationFrame(1, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(4, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(4, pollockLaughAnim);
	PLEX_addAnimationFrame(3, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(5, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(3, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(5, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(3, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(5, pollockLaughAnim);
	PLEX_addAnimationFrame(2, pollockLaughAnim);
	PLEX_addAnimationFrame(6, pollockLaughAnim);
	PLEX_addAnimationFrame(7, pollockLaughAnim);
	PLEX_addAnimationFrame(6, pollockLaughAnim);
	PLEX_addAnimationFrame(7, pollockLaughAnim);
	PLEX_addAnimationFrame(6, pollockLaughAnim);
	PLEX_addAnimationFrame(7, pollockLaughAnim);
	PLEX_addAnimationFrame(6, pollockLaughAnim);
	PLEX_addAnimationFrame(7, pollockLaughAnim);

	pollockShakeHeadAnim = PLEX_getAnimation(2, p_pollockSprite);

	PLEX_addAnimationFrame(8, pollockShakeHeadAnim);
	PLEX_addAnimationFrame(9, pollockShakeHeadAnim);
	PLEX_addAnimationFrame(8, pollockShakeHeadAnim);
	PLEX_addAnimationFrame(10, pollockShakeHeadAnim);

	pollockAngryAnim = PLEX_getAnimation(3, p_pollockSprite);

	PLEX_addAnimationFrame(11, pollockAngryAnim);

	pollockAngryAnim2 = PLEX_getAnimation(4, p_pollockSprite);

	PLEX_addAnimationFrame(12, pollockAngryAnim2);
	PLEX_addAnimationFrame(13, pollockAngryAnim2);

	pollockUpAnim = PLEX_getAnimation(5, p_pollockSprite);

	PLEX_addAnimationFrame(14, pollockUpAnim);

	pollockCelebrateAnim = PLEX_getAnimation(6, p_pollockSprite);

	PLEX_addAnimationFrame(15, pollockCelebrateAnim);
	PLEX_addAnimationFrame(0, pollockCelebrateAnim);
	PLEX_addAnimationFrame(16, pollockCelebrateAnim);
	PLEX_addAnimationFrame(0, pollockCelebrateAnim);

	pollockShameAnim = PLEX_getAnimation(7, p_pollockSprite);

	PLEX_addAnimationFrame(17, pollockShameAnim);

	pollockPhoneAnim = PLEX_getAnimation(8, p_pollockSprite);

	PLEX_addAnimationFrame(18, pollockPhoneAnim);

	pollockUpPaper = PLEX_getAnimation(9, p_pollockSprite);

	PLEX_addAnimationFrame(20, pollockUpPaper);

	pollockAngryPointUp = PLEX_getAnimation(10, p_pollockSprite);

	PLEX_addAnimationFrame(22, pollockAngryPointUp);

	pollockHangUp = PLEX_getAnimation(11, p_pollockSprite);

	PLEX_addAnimationFrame(18, pollockHangUp);
	PLEX_addAnimationFrame(0, pollockHangUp);

	pollockSitShocked = PLEX_getAnimation(12, p_pollockSprite);

	PLEX_addAnimationFrame(25, pollockSitShocked);

	pollockSitOld = PLEX_getAnimation(13, p_pollockSprite);

	PLEX_addAnimationFrame(28, pollockSitOld);

	pollockSitOldPaper = PLEX_getAnimation(14, p_pollockSprite);

	PLEX_addAnimationFrame(29, pollockSitOldPaper);

	// CHAIR STUFF:

	p_pollockChairSprite = PLEX_genSprite(&pollocksChairPlate);

	PLEX_addAnimation(p_pollockChairSprite, 1, PLEX_getGameTime());

	pollockChairAnim = PLEX_getAnimation(0, p_pollockChairSprite);

	PLEX_addAnimationFrame(48, pollockChairAnim);

	PLEX_startSprite(PLEX_getGameTime(), p_pollockSprite);
}

static void p_createOfficeBill(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* billAnim = NULL;

	PLEX_ANIMATION_PLATE billPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_billSprite = PLEX_genSprite(&billPlate);

	PLEX_addAnimation(p_billSprite, 1, PLEX_getGameTime());

	billAnim = PLEX_getAnimation(0, p_billSprite);

	PLEX_addAnimationFrame(32, billAnim);
}

static void p_addOfficeBill(const double x, const double y, bool hidden)
{
	p_officeBill = PLEX_createActor(p_billSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

static void p_loadPollocksOfficeBack()
{
	if(!p_pollocksOfficeBack) p_pollocksOfficeBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_POLLOCKSOFFICE, MMS3_FILEPATH_HEADERLESS_POLLOCKSOFFICE);
}

static void p_loadPollocksOfficeBackNight()
{
	if(!p_pollocksOfficeBackNight) p_pollocksOfficeBackNight = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_POLLOCKSOFFICENIGHT, MMS3_FILEPATH_HEADERLESS_POLLOCKSOFFICENIGHT);
}

static void p_loadMcConnimonOfficeBack()
{
	if(!p_mcConnimonOfficeBack) p_mcConnimonOfficeBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_MIBSOFFICE, MMS1_FILEPATH_HEADERLESS_MIBSOFFICE);
}

void MMS3_addPollockCodelli(const double x, const double y, const bool seated, bool hidden)
{
	if(seated) p_pollocksChair = PLEX_createActor(p_pollockChairSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);

	p_pollockCodelli = PLEX_createActor(p_pollockSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

void MMS3_pollockCodelliActorAnimationActionChange(const size_t index)
{
	PLEX_changeActor(p_pollockCodelli, index);
}

void MMS3_pollockTalkWait(const char* const message, const uint64_t wait)
{
	PLEX_addSpriteTheaterSlide(180, 180, 180, message, p_pollockCodelli, wait, false);
}

void MMS3_pollockTalk(const char* const message)
{
	MMS3_pollockTalkWait(message, 0);
}

void MMS3_pollockHideActor()
{
	PLEX_hideActor(p_pollockCodelli);
}

void MMS3_pollockUnhideActor()
{
	PLEX_unhideActor(p_pollockCodelli);
}

void MMS3_startSceneA(const size_t chapter3SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE courierPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	// COURIER ANIMS

	PLEX_ANIMATION* courierAnim = NULL;

	p_courierSprite = PLEX_genSprite(&courierPlate);

	PLEX_addAnimation(p_courierSprite, 1, PLEX_getGameTime());

	courierAnim = PLEX_getAnimation(0, p_courierSprite);

	PLEX_addAnimationFrame(33, courierAnim);

	MMS3_clearBackTextures();
	p_loadPollocksOfficeBack();

	// BEGIN SPRITE THEATER

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_POLLOCKSOFFICE, p_pollocksOfficeBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_WORKDAY);

	// ACTORS

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6, true, false);

	p_addOfficeBill(PLEX_WIDTHUNITMAX()/2 + 3, PLEX_HEIGHTUNITMAX() * 0.75 - 1, false);

	p_officeCourier = PLEX_createActor(p_courierSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 4)), true);

	// EVENTS

	MMS_narration(MMS3_LANGUAGE_SCENEA00);

	MMS_narration(MMS3_LANGUAGE_SCENEA01);

	p_billTalk(MMS3_LANGUAGE_SCENEA02);

	PLEX_changeActor(p_pollockCodelli, 2);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA03);

	PLEX_changeActor(p_pollockCodelli, 0);

	p_billTalk(MMS3_LANGUAGE_SCENEA04);

	PLEX_changeActor(p_pollockCodelli, 3);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA05);

	p_billTalk(MMS3_LANGUAGE_SCENEA06);

	PLEX_changeActor(p_pollockCodelli, 4);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA07);

	PLEX_changeActor(p_pollockCodelli, 0);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA08);

	p_billTalk(MMS3_LANGUAGE_SCENEA09);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA10);

	p_billTalk(MMS3_LANGUAGE_SCENEA11);

	PLEX_changeActor(p_pollockCodelli, 4);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEA12);

	PLEX_changeActor(p_pollockCodelli, 0);

	PLEX_unhideActor(p_officeCourier);

	p_courierTalk(MMS3_LANGUAGE_SCENEA13);

	PLEX_hideActor(p_officeCourier);

	p_billTalk(MMS3_LANGUAGE_SCENEA14);
}

void MMS3_startSceneB(const size_t chapter3SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE mcConnimonPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	PLEX_ANIMATION* mcConnimonAnim = NULL;

	p_mcConnimonSprite = PLEX_genSprite(&mcConnimonPlate);

	PLEX_addAnimation(p_mcConnimonSprite, 1, PLEX_getGameTime());

	mcConnimonAnim = PLEX_getAnimation(0, p_mcConnimonSprite);

	PLEX_addAnimationFrame(34, mcConnimonAnim);

	MMS3_clearBackTextures();
	p_loadMcConnimonOfficeBack();

	PLEX_startSpriteTheater(MMS1_LANGUAGE_SETTING_MIBS, p_mcConnimonOfficeBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_FEAR);

	p_mrMcConnimon = PLEX_createActor(p_mcConnimonSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6), PLEX_convDimens(2, 4)), false);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false, false);

	PLEX_changeActor(p_pollockCodelli, 5);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB00);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEB01);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB02);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEB03);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB04);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEB05);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB06);

	PLEX_changeActor(p_pollockCodelli, 6);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB07);

	PLEX_changeActor(p_pollockCodelli, 7);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB08);

	PLEX_changeActor(p_pollockCodelli, 5);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB09);

	PLEX_changeActor(p_pollockCodelli, 7);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB10);

	PLEX_changeActor(p_pollockCodelli, 1);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEB11);

	PLEX_changeActor(p_pollockCodelli, 5);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB12);

	p_mcConnimonTalk(MMS3_LANGUAGE_SCENEB13);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEB14);
}

void MMS3_startSceneC(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadPollocksOfficeBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_POLLOCKSOFFICE, p_pollocksOfficeBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_WORKDAY);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6, true, false);

	p_addOfficeBill(PLEX_WIDTHUNITMAX()/2 + 3, PLEX_HEIGHTUNITMAX() * 0.75 - 1, false);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC00);

	p_billTalk(MMS3_LANGUAGE_SCENEC01);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC02);

	p_billTalk(MMS3_LANGUAGE_SCENEC03);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC04);

	p_billTalk(MMS3_LANGUAGE_SCENEC05);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC06);

	p_billTalk(MMS3_LANGUAGE_SCENEC07);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC08);

	p_billTalk(MMS3_LANGUAGE_SCENEC09);

	PLEX_changeActor(p_pollockCodelli, 4);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC10);

	p_billTalk(MMS3_LANGUAGE_SCENEC11);

	PLEX_hideActor(p_officeBill);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC12);

	PLEX_changeActor(p_pollockCodelli, 7);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEC13);
}

void MMS3_startSceneD(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadPollocksOfficeBackNight();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_POLLOCKSOFFICE, p_pollocksOfficeBackNight, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_SUSPENSE);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6, true, false);

	PLEX_changeActor(p_pollockCodelli, 7);

	MMS_narration(MMS3_LANGUAGE_SCENED00);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENED01);

	PLEX_changeActor(p_pollockCodelli, 8);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENED02);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENED03);

	PLEX_changeActor(p_pollockCodelli, 0);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENED04);
}

void MMS3_createSection1(const size_t chapter3SpriteTex)
{
	p_createPollockCodelli(chapter3SpriteTex);
	p_createOfficeBill(chapter3SpriteTex);
}

void MMS3_freeSection1()
{
	if(p_pollocksOfficeBack) PLEX_destroyTexture(p_pollocksOfficeBack);
	if(p_pollocksOfficeBackNight) PLEX_destroyTexture(p_pollocksOfficeBackNight);
	if(p_mcConnimonOfficeBack) PLEX_destroyTexture(p_mcConnimonOfficeBack);

	p_pollocksOfficeBack = 0;
	p_pollocksOfficeBackNight = 0;
	p_mcConnimonOfficeBack = 0;
}

void MMS3_finalFreeSection1()
{
	if(p_pollockSprite != NULL) PLEX_destroySprite(&p_pollockSprite);
	if(p_pollockChairSprite != NULL) PLEX_destroySprite(&p_pollockChairSprite);
	if(p_billSprite != NULL) PLEX_destroySprite(&p_billSprite);
	if(p_courierSprite != NULL) PLEX_destroySprite(&p_courierSprite);
	if(p_mcConnimonSprite != NULL) PLEX_destroySprite(&p_mcConnimonSprite);
}
