#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_dreamHarpA = -1;
static int64_t p_dreamHarpB = -1;
static int64_t p_dreamHarpC = -1;
static int64_t p_dreamHarpD = -1;
static int64_t p_dreamHarpE = -1;
static int64_t p_dreamHarpF = -1;
static int64_t p_dreamHarpG = -1;
static int64_t p_dreamHarpH = -1;

static int64_t p_dreamLoop = -1;

static size_t p_dreamHarpIt = 0;

static PLEX_FAKESTRING_50 p_dreamThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_DREAM_start()
{
	p_dreamThemeStr = PLEX_createString50("Dream");
}

void MM_COMMON_THEME_DREAM_playTheme()
{
	p_dreamHarpA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPA);
	p_dreamHarpB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPB);
	p_dreamHarpC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPC);
	p_dreamHarpD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPD);
	p_dreamHarpE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPE);
	p_dreamHarpF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPF);
	p_dreamHarpG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPG);
	p_dreamHarpH = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_HARPH);

	p_dreamLoop = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DREAM_LOOP);

	if(p_dreamHarpA != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_dreamLoop != -1 && MM_COMMON_musicAssignBuffer(p_dreamLoop, 1)) MM_COMMON_musicChannelOn(true, 1);

	p_dreamHarpIt = 0;
}

void MM_COMMON_THEME_DREAM_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		size_t index = 0;

		++p_dreamHarpIt;

		index = p_dreamHarpIt < 8 ? p_dreamHarpIt : PLEX_randomNumber(0, 7);

		switch(index)
		{
			case 0: if(p_dreamHarpA != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpA, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 1: if(p_dreamHarpB != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpB, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 2: if(p_dreamHarpC != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpC, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 3: if(p_dreamHarpD != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpD, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 4: if(p_dreamHarpE != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpE, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 5: if(p_dreamHarpF != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpF, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			case 6: if(p_dreamHarpG != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpG, 0)) MM_COMMON_musicChannelOn(false, 0); break;
			default: if(p_dreamHarpH != -1 && MM_COMMON_musicAssignBuffer(p_dreamHarpH, 0)) MM_COMMON_musicChannelOn(false, 0); break;
		};
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_dreamThemeStr()
{
	return p_dreamThemeStr;
}
