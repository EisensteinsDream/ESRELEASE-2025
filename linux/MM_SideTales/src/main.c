#include "chapters/mms0.h"
#include "chapters/mms1.h"
#include "chapters/mms2.h"
#include "chapters/mms3.h"

static size_t p_selectionBackdrop = 0;
static size_t p_selectionFont = 0;

static const size_t p_chapterMax = 3;

static int64_t p_nextChapter = 0; // < keep signed
static int64_t p_chapterOn = -1;

static size_t p_pamaleanaSpriteTex = 0;
static size_t p_levineSpriteTex = 0;
static size_t p_venariusSpriteTex = 0;
static size_t p_extraplocanSpriteTex = 0;

static size_t p_officeBack = 0;

static size_t p_theaterLabel = 0;
static size_t p_bubble = 0;
static size_t p_arrow = 0;

static void p_selectionScreen()
{
	while(!PLEX_isTerminated())
	{
		PLEX_drawPanorama(10000, p_selectionBackdrop);

		if(PLEX_drawButton(0, MMS_LANGUAGE_SELECTION_VOL1, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(1), PLEX_UNIT(8), PLEX_WW(true) - PLEX_UNIT(2), PLEX_UNIT(2), 170, 50, 50, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_selectionFont, 0, 0, 0, 0, 0, true))
		{
			p_nextChapter = 0;
			return;
		}

		if(PLEX_drawButton(0, MMS_LANGUAGE_SELECTION_VOL2, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(1), PLEX_UNIT(11), PLEX_WW(true) - PLEX_UNIT(2), PLEX_UNIT(2), 50, 100, 50, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_selectionFont, 0, 0, 0, 0, 0, true))
		{
			p_nextChapter = 1;
			return;
		}

		if(MMS_MMS2Unlocked() && PLEX_drawButton(0, MMS_LANGUAGE_SELECTION_VOL3, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(1), PLEX_UNIT(14), PLEX_WW(true) - PLEX_UNIT(2), PLEX_UNIT(2), 75, 80, 120, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_selectionFont, 0, 0, 0, 0, 0, true))
		{
			p_nextChapter = 2;
			return;
		}

		if(MMS_MMS3Unlocked() && PLEX_drawButton(0, MMS_LANGUAGE_SELECTION_VOL4, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(1), PLEX_UNIT(17), PLEX_WW(true) - PLEX_UNIT(2), PLEX_UNIT(2), 255, 200, 0, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_selectionFont, 0,  0, 0, 0, 0, true))
		{
			p_nextChapter = 3;
			return;
		}

		if(!MMS_updateGame())
		{
			// this is not an error
			return;
		}
	}
}

static void p_updateChapter()
{
	if(p_nextChapter > p_chapterMax) return;

	if(p_nextChapter > p_chapterOn)
	{
		switch(p_nextChapter)
		{
			case 0: MMS0_startChapter(); break;
			case 1: MMS1_startChapter(); break;
			case 2: MMS2_startChapter(); break;
			case 3: MMS3_startChapter(); break;
		};

		p_chapterOn = p_nextChapter;
	}

	switch(p_chapterOn)
	{
		case 0:
			if(!MMS0_updateChapter(p_pamaleanaSpriteTex, p_levineSpriteTex, p_officeBack, p_venariusSpriteTex, p_extraplocanSpriteTex, p_selectionFont, p_theaterLabel, p_bubble, p_arrow))
			{
				MMS0_endChapter();
				++p_nextChapter;
			}
		break;

		case 1:
			if(!MMS1_updateChapter(p_pamaleanaSpriteTex, p_levineSpriteTex, p_officeBack, p_venariusSpriteTex, p_extraplocanSpriteTex, p_selectionFont, p_theaterLabel, p_bubble, p_arrow))
			{
				MMS1_endChapter();
				++p_nextChapter;
			}
		break;

		case 2:
			if(!MMS2_updateChapter(p_pamaleanaSpriteTex, p_officeBack, p_venariusSpriteTex, p_extraplocanSpriteTex, p_selectionFont, p_theaterLabel, p_bubble, p_arrow))
			{
				MMS2_endChapter();
				++p_nextChapter;
			}
		break;

		case 3:
			if(!MMS3_updateChapter(p_pamaleanaSpriteTex, p_officeBack, p_venariusSpriteTex, p_extraplocanSpriteTex, p_selectionFont, p_theaterLabel, p_bubble, p_arrow))
			{
				MMS3_endChapter();
				++p_nextChapter;
			}
		break;

		default: break;
	};
}

static void p_endChapter()
{
	MMS0_endChapter();
	MMS1_endChapter();
	MMS2_endChapter();
	MMS3_endChapter();
}

int main(const int argc, char** args)
{
	if(!MMS_startGame())
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, MMS_ERRORMESS_STARTFAIL);
		return 1;
	}

	p_selectionBackdrop = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS_FILEPATH_TEX_SELECTIONBACK, MMS_FILEPATH_HEADERLESS_SELECTIONBACK);
	p_selectionFont = PLEX_loadTextureFromFile(512, 512, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_SELECTIONFONT);

	p_pamaleanaSpriteTex = PLEX_loadTextureFromFile(512, 512, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_PAMALEANASPRITEPLATE);
	p_venariusSpriteTex = PLEX_loadTextureFromFile(512, 512, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_MRVENARIUS);
	p_extraplocanSpriteTex = PLEX_loadTextureFromFile(512, 512, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_EXTRAPLOCANSPRITEPLATE);
	p_levineSpriteTex = PLEX_loadTextureFromFile(512, 512, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_LEVINESPRITEPLATE);

	p_officeBack = PLEX_loadTextureFromFile(3840, 1640, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_OFFICEBACK);

	p_theaterLabel = PLEX_loadTextureFromFile(400, 100, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_STAGELABEL);
	p_bubble = PLEX_loadTextureFromFile(800, 200, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_BUBBLE);
	p_arrow = PLEX_loadTextureFromFile(800, 200, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_ARROW);

	if(MMS_MMS1Unlocked()) p_selectionScreen();

	while(MMS_updateGame())
	{
		p_updateChapter();

		if(PLEX_isTerminated() || p_nextChapter > p_chapterMax) break;
	}

	p_endChapter();

	PLEX_destroyTexture(p_pamaleanaSpriteTex);
	PLEX_destroyTexture(p_levineSpriteTex);
	PLEX_destroyTexture(p_venariusSpriteTex);
	PLEX_destroyTexture(p_extraplocanSpriteTex);

	PLEX_destroyTexture(p_officeBack);

	PLEX_destroyTexture(p_theaterLabel);
	PLEX_destroyTexture(p_bubble);
	PLEX_destroyTexture(p_arrow);

	PLEX_destroyTexture(p_selectionBackdrop);
	PLEX_destroyTexture(p_selectionFont);

	p_pamaleanaSpriteTex = 0;
	p_levineSpriteTex = 0;
	p_venariusSpriteTex = 0;
	p_extraplocanSpriteTex = 0;

	p_officeBack = 0;

	p_theaterLabel = 0;
	p_bubble = 0;
	p_arrow = 0;

	p_selectionBackdrop = 0;
	p_selectionFont = 0;

	MMS_endGame();

	return 0;
}

#if (PLEX_CORE_OS == PLEX_CORE_WINDOWS)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	return main(0, NULL);
}
#endif
