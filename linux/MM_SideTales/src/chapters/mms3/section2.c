#include "chapters/mms3.h"

static size_t p_codellisKitchenBack = 0;
static size_t p_pamleanaRoomBack = 0;
static size_t p_codellisLivingRoomBack = 0;

static size_t p_stephinaCodelli = 0;
static size_t p_wallVox = 0;
static size_t p_streamingDevice = 0;
static size_t p_youngPamPam = 0;
static size_t p_dogBed = 0;

PLEX_SPRITE* p_stephinaSprite = NULL;
PLEX_SPRITE* p_streamingDeviceSprite = NULL;
PLEX_SPRITE* p_youngPamPamSprite = NULL;
PLEX_SPRITE* p_dogBedSprite = NULL;

static void p_wallVoxTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(255, 255, 0, message, p_wallVox, 0, true);
}

static void p_streamingDeviceTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(155, 155, 0, message, p_streamingDevice, 0, true);
}

static void p_youngPamPamTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_youngPamPam, 0, true);
}

static void p_createStephinaCodelli(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* stephinaStandAnim = NULL;
	PLEX_ANIMATION* stephinaPhoneLookAnim = NULL;
	PLEX_ANIMATION* stephinaPhoneListenAnim = NULL;
	PLEX_ANIMATION* stephinaCryAnim = NULL;
	PLEX_ANIMATION* stephinaAngerAnim = NULL;
	PLEX_ANIMATION* stephinaUp = NULL;
	PLEX_ANIMATION* stephinaRight = NULL;
	PLEX_ANIMATION* stephinaRightStreamingDevice = NULL;
	PLEX_ANIMATION* stephinaArmsCrossed = NULL;
	PLEX_ANIMATION* stephinaArmsCrossedAngry = NULL;
	PLEX_ANIMATION* stephinaArmsCrossedPaper = NULL;
	PLEX_ANIMATION* stephinaShout = NULL;
	PLEX_ANIMATION* stephinaCar = NULL;
	PLEX_ANIMATION* stephinaCarStopped = NULL;
	PLEX_ANIMATION* stephinaSitShocked = NULL;

	PLEX_ANIMATION_PLATE stephinaPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_stephinaSprite = PLEX_genSprite(&stephinaPlate);

	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaSprite, 1, PLEX_getGameTime());

	stephinaStandAnim = PLEX_getAnimation(0, p_stephinaSprite);

	PLEX_addAnimationFrame(35, stephinaStandAnim);

	stephinaPhoneLookAnim = PLEX_getAnimation(1, p_stephinaSprite);

	PLEX_addAnimationFrame(36, stephinaPhoneLookAnim);

	stephinaPhoneListenAnim = PLEX_getAnimation(2, p_stephinaSprite);

	PLEX_addAnimationFrame(37, stephinaPhoneListenAnim);

	stephinaCryAnim = PLEX_getAnimation(3, p_stephinaSprite);

	PLEX_addAnimationFrame(38, stephinaCryAnim);
	PLEX_addAnimationFrame(39, stephinaCryAnim);
	PLEX_addAnimationFrame(40, stephinaCryAnim);
	PLEX_addAnimationFrame(41, stephinaCryAnim);

	stephinaAngerAnim = PLEX_getAnimation(4, p_stephinaSprite);

	PLEX_addAnimationFrame(42, stephinaAngerAnim);

	stephinaUp = PLEX_getAnimation(5, p_stephinaSprite);

	PLEX_addAnimationFrame(43, stephinaUp);

	stephinaRight = PLEX_getAnimation(6, p_stephinaSprite);

	PLEX_addAnimationFrame(44, stephinaRight);

	stephinaRightStreamingDevice = PLEX_getAnimation(7, p_stephinaSprite);

	PLEX_addAnimationFrame(45, stephinaRightStreamingDevice);

	stephinaArmsCrossed = PLEX_getAnimation(8, p_stephinaSprite);

	PLEX_addAnimationFrame(46, stephinaArmsCrossed);

	stephinaArmsCrossedAngry = PLEX_getAnimation(9, p_stephinaSprite);

	PLEX_addAnimationFrame(47, stephinaArmsCrossedAngry);

	stephinaArmsCrossedPaper = PLEX_getAnimation(10, p_stephinaSprite);

	PLEX_addAnimationFrame(19, stephinaArmsCrossedPaper);

	stephinaShout = PLEX_getAnimation(11, p_stephinaSprite);

	PLEX_addAnimationFrame(21, stephinaShout);

	stephinaCar = PLEX_getAnimation(12, p_stephinaSprite);

	PLEX_addAnimationFrame(23, stephinaCar);
	PLEX_addAnimationFrame(24, stephinaCar);
	PLEX_addAnimationFrame(23, stephinaCar);

	stephinaCarStopped = PLEX_getAnimation(13, p_stephinaSprite);

	PLEX_addAnimationFrame(23, stephinaCarStopped);

	stephinaSitShocked = PLEX_getAnimation(14, p_stephinaSprite);

	PLEX_addAnimationFrame(26, stephinaSitShocked);

	PLEX_startSprite(PLEX_getGameTime(), p_stephinaSprite);
}

static void p_createStreamingDevice(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* streamingDeviceAnim = NULL;
	PLEX_ANIMATION* noStreamingDeviceAnim = NULL;
	PLEX_ANIMATION* streamingDeviceOpenAnim = NULL;

	PLEX_ANIMATION_PLATE streamingDevicePlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_streamingDeviceSprite = PLEX_genSprite(&streamingDevicePlate);

	PLEX_addAnimation(p_streamingDeviceSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_streamingDeviceSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_streamingDeviceSprite, 1, PLEX_getGameTime());

	streamingDeviceAnim = PLEX_getAnimation(0, p_streamingDeviceSprite);

	PLEX_addAnimationFrame(49, streamingDeviceAnim);

	noStreamingDeviceAnim = PLEX_getAnimation(1, p_streamingDeviceSprite);

	PLEX_addAnimationFrame(50, noStreamingDeviceAnim);

	streamingDeviceOpenAnim = PLEX_getAnimation(2, p_streamingDeviceSprite);

	PLEX_addAnimationFrame(51, streamingDeviceOpenAnim);
}

static void p_createYoungPamPam(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* youngPamPamLeft = NULL;
	PLEX_ANIMATION* youngPamPamDown = NULL;
	PLEX_ANIMATION* youngPamPamRight = NULL;
	PLEX_ANIMATION* youngPamPamSearching = NULL;
	PLEX_ANIMATION* youngPamPamHelmet = NULL;
	PLEX_ANIMATION* youngPamPamBlond = NULL;
	PLEX_ANIMATION* youngPamPamBlondPaper = NULL;
	PLEX_ANIMATION* youngPamPamBlondHandRaised = NULL;
	PLEX_ANIMATION* youngPamPamBlondUp = NULL;
	PLEX_ANIMATION* youngPamPamBlondUpCrying = NULL;

	PLEX_ANIMATION_PLATE youngPamPamPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_youngPamPamSprite = PLEX_genSprite(&youngPamPamPlate);

	PLEX_addAnimation(p_youngPamPamSprite, 100, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 100, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 100, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 100, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_youngPamPamSprite, 200, PLEX_getGameTime());

	youngPamPamLeft = PLEX_getAnimation(0, p_youngPamPamSprite);

	PLEX_addAnimationFrame(52, youngPamPamLeft);
	PLEX_addAnimationFrame(53, youngPamPamLeft);

	youngPamPamDown = PLEX_getAnimation(1, p_youngPamPamSprite);

	PLEX_addAnimationFrame(54, youngPamPamDown);
	PLEX_addAnimationFrame(55, youngPamPamDown);

	youngPamPamRight = PLEX_getAnimation(2, p_youngPamPamSprite);

	PLEX_addAnimationFrame(56, youngPamPamRight);
	PLEX_addAnimationFrame(57, youngPamPamRight);

	youngPamPamSearching = PLEX_getAnimation(3, p_youngPamPamSprite);

	PLEX_addAnimationFrame(60, youngPamPamSearching);
	PLEX_addAnimationFrame(61, youngPamPamSearching);
	PLEX_addAnimationFrame(62, youngPamPamSearching);
	PLEX_addAnimationFrame(63, youngPamPamSearching);
	PLEX_addAnimationFrame(64, youngPamPamSearching);
	PLEX_addAnimationFrame(65, youngPamPamSearching);
	PLEX_addAnimationFrame(66, youngPamPamSearching);

	youngPamPamHelmet = PLEX_getAnimation(4, p_youngPamPamSprite);

	PLEX_addAnimationFrame(67, youngPamPamHelmet);

	youngPamPamBlond = PLEX_getAnimation(5, p_youngPamPamSprite);

	PLEX_addAnimationFrame(68, youngPamPamBlond);

	youngPamPamBlondPaper = PLEX_getAnimation(6, p_youngPamPamSprite);

	PLEX_addAnimationFrame(69, youngPamPamBlondPaper);

	youngPamPamBlondHandRaised = PLEX_getAnimation(7, p_youngPamPamSprite);

	PLEX_addAnimationFrame(70, youngPamPamBlondHandRaised);

	youngPamPamBlondUp = PLEX_getAnimation(8, p_youngPamPamSprite);

	PLEX_addAnimationFrame(71, youngPamPamBlondUp);

	youngPamPamBlondUpCrying = PLEX_getAnimation(9, p_youngPamPamSprite);

	PLEX_addAnimationFrame(72, youngPamPamBlondUpCrying);
	PLEX_addAnimationFrame(73, youngPamPamBlondUpCrying);
	PLEX_addAnimationFrame(72, youngPamPamBlondUpCrying);
	PLEX_addAnimationFrame(74, youngPamPamBlondUpCrying);

	PLEX_startSprite(PLEX_getGameTime(), p_youngPamPamSprite);
}

static void p_createDogBed(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* normalAnim = NULL;
	PLEX_ANIMATION* pamStandAnim = NULL;

	PLEX_ANIMATION_PLATE dogBedPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_dogBedSprite = PLEX_genSprite(&dogBedPlate);

	PLEX_addAnimation(p_dogBedSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_dogBedSprite, 1, PLEX_getGameTime());

	normalAnim = PLEX_getAnimation(0, p_dogBedSprite);

	PLEX_addAnimationFrame(58, normalAnim);

	pamStandAnim = PLEX_getAnimation(1, p_dogBedSprite);

	PLEX_addAnimationFrame(59, pamStandAnim);
}

static void p_addStreamingDevice(const double x, const double y)
{
	p_streamingDevice = PLEX_createActor(p_streamingDeviceSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(1.5, 3)), false);
}

static void p_addYoungPamPam(const double x, const double y, const bool hidden)
{
	p_youngPamPam = PLEX_createActor(p_youngPamPamSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

static void p_addDogBed(const double x, const double y)
{
	p_dogBed = PLEX_createActor(p_dogBedSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), false);
}

static void p_loadCodellisKitchenBack()
{
	if(!p_codellisKitchenBack) p_codellisKitchenBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_CODELLISKITCHEN, MMS3_FILEPATH_HEADERLESS_CODELLISKITCHEN);
}

static void p_loadPamaleanaRoomBack()
{
	if(!p_pamleanaRoomBack) p_pamleanaRoomBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_PAMPAMSROOM, MMS3_FILEPATH_HEADERLESS_PAMPAMSROOM);
}

void MMS3_addStephinaCodelli(const double x, const double y, bool hidden)
{
	p_stephinaCodelli = PLEX_createActor(p_stephinaSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

void MMS3_stephinaCodelliTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(60, 210, 220, message, p_stephinaCodelli, 0, true);
}

void MMS3_stephinaCodelliActorAnimationActionChange(const size_t index)
{
	PLEX_changeActor(p_stephinaCodelli, index);
}

void MMS3_loadCodellisLivingRoomBack()
{
	if(!p_codellisLivingRoomBack) p_codellisLivingRoomBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_CODELLISLIVINGROOM, MMS3_FILEPATH_HEADERLESS_CODELLISLIVINGROOM);
}

void MMS3_setSceneCodellisLivingRoom(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_CODELLISLIVINGROOM, p_codellisLivingRoomBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());
}

void MMS3_setBackgroundCodellisLivingRoom()
{
	PLEX_changeSpriteTheaterBackground(p_codellisLivingRoomBack, MMS_LANGUAGE_SETTING_CODELLISLIVINGROOM);
}

void MMS3_startSceneE(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadCodellisKitchenBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_CODELLISKITCHEN, p_codellisKitchenBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	p_wallVox = PLEX_createActor(NULL, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.75, PLEX_HEIGHTUNITMAX() * 0.5), PLEX_convDimens(2, 2)), true);

	MMS3_addStephinaCodelli(PLEX_WIDTHUNITMAX()/2 - 0.5, PLEX_HEIGHTUNITMAX() * 0.75 - 2, false);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEE00);

	PLEX_changeActor(p_stephinaCodelli, 1);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEE01);

	PLEX_changeActor(p_stephinaCodelli, 2);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEE02);

	PLEX_changeActor(p_stephinaCodelli, 3);

	MM_COMMON_punkThemeVolume(0.25);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PUNK);

	p_wallVoxTalk(MMS3_LANGUAGE_SCENEE03);

	p_wallVoxTalk(MMS3_LANGUAGE_SCENEE04);

	PLEX_changeActor(p_stephinaCodelli, 4);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEE05);
}

void MMS3_startSceneF(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadPamaleanaRoomBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_PAMLEANASROOM, p_pamleanaRoomBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MM_COMMON_punkThemeVolume(1);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PUNK);

	p_addStreamingDevice(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2);

	p_addYoungPamPam(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 1, false);

	p_addDogBed(PLEX_WIDTHUNITMAX()/2 + 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	MMS3_addStephinaCodelli(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() - 1, true);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF00);

	PLEX_changeActor(p_youngPamPam, 1);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2 - 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF01);

	PLEX_changeActor(p_youngPamPam, 2);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 4);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF02);

	PLEX_hideActor(p_youngPamPam);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2 + 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	PLEX_changeActor(p_dogBed, 1);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF03);

	PLEX_changeActor(p_dogBed, 0);
	PLEX_unhideActor(p_youngPamPam);
	PLEX_changeActor(p_youngPamPam, 0);
	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 1);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF04);

	PLEX_changeActor(p_youngPamPam, 1);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2 - 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF05);

	PLEX_changeActor(p_youngPamPam, 2);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 4);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF06);

	PLEX_hideActor(p_youngPamPam);

	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2 + 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	PLEX_changeActor(p_dogBed, 1);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF07);

	PLEX_stopSpriteTheaterMusic();

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS3_LANGUAGE_SCENEF08);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PUNK);

	p_streamingDeviceTalk(MMS3_LANGUAGE_SCENEF09);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF10);

	PLEX_changeActor(p_streamingDevice, 2);
	PLEX_moveActor(p_youngPamPam, PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 0.5);
	PLEX_changeActor(p_youngPamPam, 3);
	PLEX_changeActor(p_dogBed, 0);
	PLEX_unhideActor(p_youngPamPam);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF11);

	PLEX_stopSpriteTheaterMusic();

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_KNOCKING);

	MMS_narration(MMS3_LANGUAGE_SCENEF12);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PUNK);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF13);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF14);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PAMALEANA);

	PLEX_changeActor(p_youngPamPam, 4);

	PLEX_unhideActor(p_stephinaCodelli);
	PLEX_changeActor(p_stephinaCodelli, 5);
	PLEX_changeActor(p_streamingDevice, 0);
	PLEX_moveActor(p_stephinaCodelli, PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX() - 4);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF15);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF16);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF17);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF18);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF19);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF20);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF21);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF22);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF23);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF24);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF25);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF26);

	PLEX_moveActor(p_stephinaCodelli, PLEX_WIDTHUNITMAX()/2 - 2, PLEX_HEIGHTUNITMAX()/2 - 1);
	PLEX_changeActor(p_stephinaCodelli, 6);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF27);

	PLEX_changeActor(p_stephinaCodelli, 7);
	PLEX_changeActor(p_streamingDevice, 1);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF28);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF29);

	PLEX_changeActor(p_stephinaCodelli, 4);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF30);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF31);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF32);

	PLEX_hideActor(p_stephinaCodelli);
	PLEX_moveActor(p_stephinaCodelli, PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() - 1);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEF33);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEF34);

	PLEX_stopSpriteTheaterMusic();

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_DOORSLAM);

	MMS_narration(MMS3_LANGUAGE_SCENEF35);
}

void MMS3_startSceneG(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	MMS3_loadCodellisLivingRoomBack();

	MMS3_setSceneCodellisLivingRoom(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_STRIFE);

	MMS3_addStephinaCodelli(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX() * 0.75 - 3, false);
	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX() * 0.75 + 2, false, false);
	p_addYoungPamPam(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75 - 3, true);

	PLEX_changeActor(p_stephinaCodelli, 8);
	MMS3_pollockCodelliActorAnimationActionChange(5);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG00);

	PLEX_changeActor(p_stephinaCodelli, 9);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG01);

	MMS3_pollockTalkWait(MMS3_LANGUAGE_SCENEG02, 3000);

	PLEX_changeActor(p_stephinaCodelli, 8);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG03);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG04);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG05);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG06);

	PLEX_changeActor(p_stephinaCodelli, 9);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG07);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG08);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG09);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG10);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG11);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG12);

	PLEX_changeActor(p_stephinaCodelli, 4);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG13);

	PLEX_changeActor(p_stephinaCodelli, 9);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG14);

	PLEX_changeActor(p_stephinaCodelli, 8);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG15);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG16);

	MMS3_pollockCodelliActorAnimationActionChange(1);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG17);

	MMS3_pollockCodelliActorAnimationActionChange(5);
	PLEX_changeActor(p_stephinaCodelli, 10);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG18);

	MMS3_pollockCodelliActorAnimationActionChange(9);
	PLEX_changeActor(p_stephinaCodelli, 8);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG19);

	MMS3_pollockCodelliActorAnimationActionChange(5);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG20);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG21);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG22);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG23);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG24);

	PLEX_changeActor(p_stephinaCodelli, 11);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG25);

	PLEX_changeActor(p_stephinaCodelli, 8);
	MMS3_pollockCodelliActorAnimationActionChange(5);

	PLEX_unhideActor(p_youngPamPam);

	PLEX_changeActor(p_youngPamPam, 5);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG26);

	PLEX_changeActor(p_youngPamPam, 6);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG27);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEG28);

	PLEX_changeActor(p_youngPamPam, 5);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG29);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG30);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG31);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG32);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG33);

	PLEX_changeActor(p_youngPamPam, 7);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEG34);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG35);

	PLEX_changeActor(p_youngPamPam, 5);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEG36);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG37);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG38);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG39);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEG40);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG41);

	PLEX_hideActor(p_youngPamPam);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG42);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG43);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG44);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEG45);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEG46);
}

void MMS3_startSceneH(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadPamaleanaRoomBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_PAMLEANASROOM, p_pamleanaRoomBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	p_addStreamingDevice(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2);

	p_addYoungPamPam(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 4, false);

	p_addDogBed(PLEX_WIDTHUNITMAX()/2 + 7, PLEX_HEIGHTUNITMAX()/2 + 2);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 1, false, false);

	PLEX_changeActor(p_streamingDevice, 1);

	PLEX_changeActor(p_youngPamPam, 8);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH00);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH01);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH02);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH03);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH04);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH05);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH06);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH07);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH08);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH09);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH10);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH11);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH12);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH13);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH14);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH15);

	PLEX_playSpriteTheaterSoundEffect(MM_COMMON_SOUNDEFFECT_CRUELTWIST);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PANIC);

	MMS3_pollockCodelliActorAnimationActionChange(4);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH16);

	PLEX_changeActor(p_youngPamPam, 9);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH17);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH18);

	p_youngPamPamTalk(MMS3_LANGUAGE_SCENEH19);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH20);

	MMS3_pollockCodelliActorAnimationActionChange(10);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH21);

	MMS3_pollockCodelliActorAnimationActionChange(3);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH22);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEH23);
}

void MMS3_createSection2(const size_t chapter3SpriteTex)
{
	p_createStephinaCodelli(chapter3SpriteTex);
	p_createStreamingDevice(chapter3SpriteTex);
	p_createYoungPamPam(chapter3SpriteTex);
	p_createDogBed(chapter3SpriteTex);
}

void MMS3_freeSection2()
{
	if(p_codellisKitchenBack) PLEX_destroyTexture(p_codellisKitchenBack);
	if(p_pamleanaRoomBack) PLEX_destroyTexture(p_pamleanaRoomBack);
	if(p_codellisLivingRoomBack) PLEX_destroyTexture(p_codellisLivingRoomBack);

	p_codellisKitchenBack = 0;
	p_pamleanaRoomBack = 0;
	p_codellisLivingRoomBack = 0;
}

void MMS3_finalFreeSection2()
{
	PLEX_destroySprite(&p_stephinaSprite);
	PLEX_destroySprite(&p_streamingDeviceSprite);
	PLEX_destroySprite(&p_youngPamPamSprite);
	PLEX_destroySprite(&p_dogBedSprite);
}
