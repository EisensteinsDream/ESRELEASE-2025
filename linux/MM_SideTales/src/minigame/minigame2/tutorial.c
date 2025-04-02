#include "minigame/minigame2/minigame2.h"

static size_t p_tutorialScreen1 = 0;
static size_t p_tutorialScreen2 = 0;
static size_t p_tutorialScreen3 = 0;
static size_t p_tutorialScreen4 = 0;
static size_t p_tutorialScreen5 = 0;

static size_t p_tutorialSection = 0;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemTutorial()
{

}

void MMS2_initSystemTutorial()
{
	p_tutorialSection = 0;
}

bool MMS2_checkRunSystemTutorial(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time)
{
	if(p_tutorialSection > 6) return false;

	MMS2_drawRestoreTownButton(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time);

	MMS2_checkHasSnapshotFile();

	switch(p_tutorialSection)
	{
		case 0:
			if(!p_tutorialScreen1) p_tutorialScreen1 = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TUTORIAL1, MMS2_FILEPATH_HEADERLESS_TUTORIAL1);
			if(!p_tutorialScreen2) p_tutorialScreen2 = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TUTORIAL2, MMS2_FILEPATH_HEADERLESS_TUTORIAL2);
			if(!p_tutorialScreen3) p_tutorialScreen3 = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TUTORIAL3, MMS2_FILEPATH_HEADERLESS_TUTORIAL3);
			if(!p_tutorialScreen4) p_tutorialScreen4 = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TUTORIAL4, MMS2_FILEPATH_HEADERLESS_TUTORIAL4);
			if(!p_tutorialScreen5) p_tutorialScreen5 = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TUTORIAL5, MMS2_FILEPATH_HEADERLESS_TUTORIAL5);
			++p_tutorialSection;
		break;

		case 1:
			PLEX_printTexture(1, p_tutorialScreen1, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
			if(PLEX_leftClick() || PLEX_KEY_press('\n')) ++p_tutorialSection;
		break;

		case 2:
			PLEX_printTexture(1, p_tutorialScreen2, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
			if(PLEX_leftClick() || PLEX_KEY_press('\n')) ++p_tutorialSection;
		break;

		case 3:
			PLEX_printTexture(1, p_tutorialScreen3, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
			if(PLEX_leftClick() || PLEX_KEY_press('\n')) ++p_tutorialSection;
		break;

		case 4:
			PLEX_printTexture(1, p_tutorialScreen4, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
			if(PLEX_leftClick() || PLEX_KEY_press('\n')) ++p_tutorialSection;
		break;

		case 5:
			PLEX_printTexture(1, p_tutorialScreen5, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
			if(PLEX_leftClick() || PLEX_KEY_press('\n')) ++p_tutorialSection;
		break;

		default:
			PLEX_destroyTexture(p_tutorialScreen1);
			p_tutorialScreen1 = 0;
			p_tutorialSection = 7;
		return false;
	};

	return true;
}

void MMS2_endSystemTutorial()
{

}

void MMS2_endTutorial()
{
	p_tutorialSection = 7;
}
