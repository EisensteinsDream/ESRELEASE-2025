#include "chapters/mms0.h"

static size_t p_phase = 0;

static int64_t p_pamaleana = -1;

static int64_t p_extraplocan = -1;
static int64_t p_boss = -1;

static int64_t p_levine = -1;

static size_t p_chapter0SpriteTex = 0;

static PLEX_SPRITE* p_pamaleanaSprite = NULL;
static PLEX_SPRITE* p_levineSprite = NULL;

static PLEX_SPRITE* p_bossSprite = NULL;
static PLEX_SPRITE* p_extraplocanSprite = NULL;
static PLEX_SPRITE* p_deskSprite = NULL;

void MMS_narration(const char* message)
{
	PLEX_addSpriteTheaterSlide(255, 255, 255, message, -1, 0, true);
}

void MMS_genSpritePamaleana(const size_t pamaleanaSpriteTex)
{
	PLEX_ANIMATION_PLATE pamaleanaPlate = PLEX_createAnimationPlate(0.0625, 0.125, pamaleanaSpriteTex);

	if(p_pamaleanaSprite != NULL) PLEX_destroySprite(&p_pamaleanaSprite);

	p_pamaleanaSprite = PLEX_genSprite(&pamaleanaPlate);
}

void MMS_createActorPamaleana(const uint32_t x, const uint32_t y, const bool hidden)
{
	if(p_pamaleanaSprite == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS_ERRORMESS_ONCREATEPAMACTRESS, MMS_ERRORMESS_PAMACTORSPRITE);
		return;
	}

	PLEX_startSprite(PLEX_getGameTime(), p_pamaleanaSprite);

	p_pamaleana = PLEX_createActor(p_pamaleanaSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

void MMS_addPamaleanaAnimation(const uint64_t duration)
{
	PLEX_addAnimation(p_pamaleanaSprite, duration, PLEX_getGameTime());
}

PLEX_ANIMATION* MMS_getPamaleanaAnimation(const size_t index)
{
	return PLEX_getAnimation(index, p_pamaleanaSprite);
}

void MMS_pamTalkWait(const char* message, const uint64_t wait, const bool stopMusic)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_pamaleana, wait, stopMusic);
}

void MMS_pamTalk(const char* message)
{
	MMS_pamTalkWait(message, 0, false);
}

void MMS_pamNarration(const char* message)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, -1, 0, true);
}

void MMS_movePamela(const double x, const double y)
{
	PLEX_moveActor(p_pamaleana, x, y);
}

void MMS_pamChangeAnimation(const size_t index)
{
	PLEX_changeActor(p_pamaleana, index);
}

void MMS_pamHide()
{
	PLEX_hideActor(p_pamaleana);
}

void MMS_pamUnhide()
{
	PLEX_unhideActor(p_pamaleana);
}

void MMS_genSpriteLevine(const size_t levineSpriteTex)
{
	PLEX_ANIMATION_PLATE levinePlate = PLEX_createAnimationPlate(0.0625, 0.125, levineSpriteTex);

	if(p_levineSprite != NULL) PLEX_destroySprite(&p_levineSprite);

	p_levineSprite = PLEX_genSprite(&levinePlate);
}

void MMS_createActorLevine(const uint32_t x, const uint32_t y, const bool hidden)
{
	if(p_levineSprite == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS_ERRORMESS_ONCREATELEVINEACTOR, MMS_ERRORMESS_LEVINEACTORSPRITE);
		return;
	}

	PLEX_startSprite(PLEX_getGameTime(), p_levineSprite);

	p_levine = PLEX_createActor(p_levineSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

void MMS_addLevineAnimation(const uint64_t duration)
{
	PLEX_addAnimation(p_levineSprite, duration, PLEX_getGameTime());
}

PLEX_ANIMATION* MMS_getLevineAnimation(const size_t index)
{
	return PLEX_getAnimation(index, p_levineSprite);
}

void MMS_levineTalkWait(const char* message, const uint64_t wait, const bool stopMusic)
{
	PLEX_addSpriteTheaterSlide(200, 200, 0, message, p_levine, wait, stopMusic);
}

void MMS_levineTalk(const char* message)
{
	MMS_levineTalkWait(message, 0, false);
}

void MMS_levineNarration(const char* message)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, -1, 0, false);
}

void MMS_levineChangeAnimation(const size_t index)
{
	PLEX_changeActor(p_levine, index);
}

void MMS_levineHide()
{
	PLEX_hideActor(p_levine);
}

void MMS_levineUnhide()
{
	PLEX_unhideActor(p_levine);
}

void MMS_extrapTalkWait(const char* message, const uint64_t wait, const bool stopMusic)
{
	PLEX_addSpriteTheaterSlide(29, 255, 180, message, p_extraplocan, wait, stopMusic);
}

void MMS_extrapTalk(const char* message)
{
	MMS_extrapTalkWait(message, 0, false);
}

void MMS_extrapNarration(const char* message)
{
	PLEX_addSpriteTheaterSlide(29, 255, 180, message, -1, 0, true);
}

void MMS_extrapMaintenanceVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(180, 180, 180, message, p_extraplocan, 0, true);
}

void MMS_bossHide()
{
	PLEX_hideActor(p_boss);
}

void MMS_bossUnhide()
{
	PLEX_unhideActor(p_boss);
}

void MMS_bossTalk(const char* message)
{
	PLEX_addSpriteTheaterSlide(240, 59, 59, message, p_boss, 0, true);
}

void MMS_startPamaleanasCubicle(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE bossPlate = PLEX_createAnimationPlate(0.0625, 0.125, venariusSpriteTex);
	PLEX_ANIMATION_PLATE extraplocanPlate = PLEX_createAnimationPlate(0.125, 0.125, extraplocanSpriteTex);
	PLEX_ANIMATION_PLATE deskPlate = PLEX_createAnimationPlate(0.125, 0.125, extraplocanSpriteTex);

	PLEX_ANIMATION* pamaleanaAnim = NULL;
	PLEX_ANIMATION* pamaleanaAnim2 = NULL;
	PLEX_ANIMATION* pamaleanaAnim3 = NULL;
	PLEX_ANIMATION* pamaleanaAnim4 = NULL;

	PLEX_ANIMATION* bossAnim = NULL;
	PLEX_ANIMATION* extraplocanAnim = NULL;

	PLEX_ANIMATION* deskAnim = NULL;

	if(p_bossSprite != NULL) PLEX_destroySprite(&p_bossSprite);
	if(p_extraplocanSprite != NULL) PLEX_destroySprite(&p_extraplocanSprite);
	if(p_deskSprite != NULL) PLEX_destroySprite(&p_deskSprite);

	p_bossSprite = PLEX_genSprite(&bossPlate);
	p_extraplocanSprite = PLEX_genSprite(&extraplocanPlate);
	p_deskSprite = PLEX_genSprite(&deskPlate);

	MMS_genSpritePamaleana(pamaleanaSpriteTex);

	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);

	PLEX_addAnimation(p_bossSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_extraplocanSprite, 5000, PLEX_getGameTime());

	PLEX_addAnimation(p_deskSprite, 1, PLEX_getGameTime());

	PLEX_startSprite(PLEX_getGameTime(), p_bossSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_extraplocanSprite);

	pamaleanaAnim = MMS_getPamaleanaAnimation(0);
	pamaleanaAnim2 = MMS_getPamaleanaAnimation(1);
	pamaleanaAnim3 = MMS_getPamaleanaAnimation(2);
	pamaleanaAnim4 = MMS_getPamaleanaAnimation(3);

	bossAnim = PLEX_getAnimation(0, p_bossSprite);
	extraplocanAnim = PLEX_getAnimation(0, p_extraplocanSprite);

	deskAnim = PLEX_getAnimation(0, p_deskSprite);

	PLEX_addAnimationFrame(0, pamaleanaAnim);
	PLEX_addAnimationFrame(1, pamaleanaAnim2);
	PLEX_addAnimationFrame(2, pamaleanaAnim3);
	PLEX_addAnimationFrame(3, pamaleanaAnim4);

	PLEX_addAnimationFrame(0, bossAnim);

	PLEX_addAnimationFrame(0, extraplocanAnim);
	PLEX_addAnimationFrame(1, extraplocanAnim);

	PLEX_addAnimationFrame(2, deskAnim);

	// START SPRITE THEATER

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_LEANASCUIBCLE, cubicleBackdrop, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	// CREATE ACTORS:

	MMS_createActorPamaleana(PLEX_WIDTHUNITMAX()/2 + 0.5, PLEX_HEIGHTUNITMAX() - 6, false);

	// the desk need not be accessed
	PLEX_createActor(p_deskSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() - 4), PLEX_convDimens(4.5, 2)), false);

	p_extraplocan = PLEX_createActor(p_extraplocanSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() - 4.5), PLEX_convDimens(1.5, 1.5)), false);

	p_boss = PLEX_createActor(p_bossSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() - 8), PLEX_convDimens(2, 4)), true);
}

void MMS0_startChapter()
{
	p_chapter0SpriteTex = PLEX_loadTextureFromFileOrHeaderless(512, 512, 255, 255, 255, 255, 0, MMS_FILEPATH_TEX_CHAPTER0SPRITEPLATE, MMS_FILEPATH_HEADERLESS_CHAPTER0SPRITEPLATE);
}

bool MMS0_updateChapter(const size_t pamaleanaSpriteTex, const size_t levineSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	switch(p_phase)
	{
		case 0:
			if(!PLEX_inSpriteTheater()) MMS_startIntro(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS0MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 1:
			if(PLEX_isSpriteTheaterOver()) MMS_startIntroB(pamaleanaSpriteTex, p_chapter0SpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS0MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 2:
			MMS_runMinigame0(p_chapter0SpriteTex, pamaleanaSpriteTex, fontPlate);
			++p_phase;
		break;

		case 3:
			if(!PLEX_inSpriteTheater()) MMS_startOutro(pamaleanaSpriteTex, levineSpriteTex, p_chapter0SpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 4:
			if(!PLEX_inSpriteTheater()) MMS_startOutroB(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		default: return false;
	}

	return true;
}

void MMS0_endChapter()
{
	MMS0_freeMinigameSprites();

	MMS_freeIntroB();
	MMS_freeOutro();

	if(p_pamaleanaSprite != NULL) PLEX_destroySprite(&p_pamaleanaSprite);
	if(p_levineSprite != NULL) PLEX_destroySprite(&p_levineSprite);

	if(p_bossSprite != NULL) PLEX_destroySprite(&p_bossSprite);
	if(p_extraplocanSprite != NULL) PLEX_destroySprite(&p_extraplocanSprite);
	if(p_deskSprite != NULL) PLEX_destroySprite(&p_deskSprite);

	PLEX_destroyTexture(p_chapter0SpriteTex);

	p_chapter0SpriteTex = 0;
}

