#include "chapters/mms2.h"

// NOTE: this has not been split into multiple source files because it is less than 1000 lines

static size_t p_phase = 0;

static size_t p_chapter2SpriteTex = 0;
static size_t p_chapter2SpriteTex2 = 0;
static size_t p_chapter2SpriteTex3 = 0;
static size_t p_chapter2SpriteTex4 = 0;

void p_startIntro(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS2_LANGUAGE_INTRO_LINE1);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_EXTRAPLOCAN);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE3);

	MMS_extrapTalkWait(MMS2_LANGUAGE_INTRO_LINE4, 2000, false);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE5);

	MMS_extrapTalkWait(MMS2_LANGUAGE_INTRO_LINE6, 5000, true);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE7);

	MMS_pamChangeAnimation(0);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE8);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE9);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE10);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE11);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE12);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE13);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE14);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE15);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE16);

	MMS_pamChangeAnimation(3);

	MMS_extrapTalkWait(MMS2_LANGUAGE_INTRO_LINE17, 10000, true);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE18);

	MMS_pamChangeAnimation(3);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE19);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE20);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE21);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE22);

	MMS_pamChangeAnimation(0);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE23);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE24);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE25);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE26);

	MMS_pamChangeAnimation(3);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE27);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE28);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE29);

	MMS_pamChangeAnimation(0);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_LINE30);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_LINE31);
}

void p_startOutro(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_NEWSROOM);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO0);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO1);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO3);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO4);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO5);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO6);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO7);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO8);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO9);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO10);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO11);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO12);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO13);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO14);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO15);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO16);

	MMS_pamChangeAnimation(3);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO17);

	MMS_pamChangeAnimation(0);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO18);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO19);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO20);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO21);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO22);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO23);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO24);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO25);

	MMS_extrapTalkWait(MMS2_LANGUAGE_INTRO_OUTRO26, 1000, true);

	MMS_pamChangeAnimation(3);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO27);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO28);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO29);

	MMS_pamChangeAnimation(3);

	MMS_extrapTalk(MMS2_LANGUAGE_INTRO_OUTRO30);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS2_LANGUAGE_INTRO_OUTRO31);

	MMS_pamChangeAnimation(3);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS2_LANGUAGE_INTRO_OUTRO32);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_startChapter()
{
	p_chapter2SpriteTex = PLEX_loadTextureFromFileOrHeaderless(512, 2048, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAPTER2SPRITEPLATE, MMS2_FILEPATH_HEADERLESS_CHAPTER2SPRITEPLATE);

	p_chapter2SpriteTex2 = PLEX_loadTextureFromFileOrHeaderless(512, 2048, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAPTER2SPRITEPLATE2, MMS2_FILEPATH_HEADERLESS_CHAPTER2SPRITEPLATE2);

	p_chapter2SpriteTex3 = PLEX_loadTextureFromFileOrHeaderless(512, 2048, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAPTER2SPRITEPLATE3, MMS2_FILEPATH_HEADERLESS_CHAPTER2SPRITEPLATE3);

	p_chapter2SpriteTex4 = PLEX_loadTextureFromFileOrHeaderless(512, 2048, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAPTER2SPRITEPLATE4, MMS2_FILEPATH_HEADERLESS_CHAPTER2SPRITEPLATE4);
}

bool MMS2_updateChapter(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	switch(p_phase)
	{
		case 0:
			if(!PLEX_inSpriteTheater()) p_startIntro(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());

			if(PLEX_isSpriteTheaterOver() || (MMS_MMS2MinigameUnlocked() && MM_COMMON_skipButton(fontPlate)))
			{
				++p_phase;
				PLEX_endSpriteTheater();
			}
		break;

		case 1:
			MMS_runMinigame2(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, label, bubble, arrow, p_chapter2SpriteTex, p_chapter2SpriteTex2, p_chapter2SpriteTex3, p_chapter2SpriteTex4, fontPlate);
			++p_phase;
		break;

		case 2:
			MMS2_unsetCustomCursor();

			if(!PLEX_inSpriteTheater()) p_startOutro(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		default: return false;
	};

	return true;
}

void MMS2_endChapter()
{
	MMS2_freeMinigameSprites();

	PLEX_destroyTexture(p_chapter2SpriteTex);
	PLEX_destroyTexture(p_chapter2SpriteTex2);
	PLEX_destroyTexture(p_chapter2SpriteTex3);
	PLEX_destroyTexture(p_chapter2SpriteTex4);

	p_chapter2SpriteTex = 0;
	p_chapter2SpriteTex2 = 0;
	p_chapter2SpriteTex3 = 0;
	p_chapter2SpriteTex4 = 0;
}
