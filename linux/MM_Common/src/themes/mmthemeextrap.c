#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_extrapIntroOrcB = -1;
static int64_t p_extrapIntroPercB = -1;

static int64_t p_extrapPercA = -1;
static int64_t p_extrapPercB = -1;
static int64_t p_extrapPercC = -1;
static int64_t p_extrapPercD = -1;
static int64_t p_extrapPercE = -1;

static int64_t p_extrapOrcA = -1;
static int64_t p_extrapOrcB = -1;
static int64_t p_extrapOrcC = -1;
static int64_t p_extrapOrcD = -1;
static int64_t p_extrapOrcE = -1;

static int64_t p_extrapVoxA = -1;
static int64_t p_extrapVoxB = -1;
static int64_t p_extrapVoxC = -1;
static int64_t p_extrapVoxD = -1;
static int64_t p_extrapVoxE = -1;

static size_t p_extrapIt = 0;

static PLEX_FAKESTRING_50 p_extrapThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_EXTRAP_start()
{
	p_extrapThemeStr = PLEX_createString50("Extraplocan");
}

void MM_COMMON_THEME_EXTRAP_playTheme()
{
	const int64_t introOrcA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_INTROORCHA);
	const int64_t introPercA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_INTROPERCA);

	p_extrapIntroOrcB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_INTROORCHB);
	p_extrapIntroPercB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_INTROPERCB);

	p_extrapPercA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_PERCA);
	p_extrapPercB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_PERCB);
	p_extrapPercC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_PERCC);
	p_extrapPercD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_PERCD);
	p_extrapPercE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_PERCE);

	p_extrapOrcA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_ORCHA);
	p_extrapOrcB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_ORCHB);
	p_extrapOrcC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_ORCHC);
	p_extrapOrcD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_ORCHD);
	p_extrapOrcE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_ORCHE);

	p_extrapVoxA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_VOXA);
	p_extrapVoxB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_VOXB);
	p_extrapVoxC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_VOXC);
	p_extrapVoxD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_VOXD);
	p_extrapVoxE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_EXTRAP_VOXE);

	if(introOrcA != -1 && MM_COMMON_musicAssignBuffer(introOrcA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(introPercA != -1 && MM_COMMON_musicAssignBuffer(introPercA, 1)) MM_COMMON_musicChannelOn(false, 1);

	p_extrapIt = 0;
}

void MM_COMMON_THEME_EXTRAP_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);

		switch(p_extrapIt)
		{
			case 0:
				MM_COMMON_musicAssignBuffer(p_extrapIntroOrcB, 0);
				MM_COMMON_musicAssignBuffer(p_extrapIntroPercB, 1);
				break;

			case 1:
				MM_COMMON_musicAssignBuffer(p_extrapOrcA, 0);
				MM_COMMON_musicAssignBuffer(p_extrapPercA, 1);
				MM_COMMON_musicAssignBuffer(p_extrapVoxA, 2);
				break;

			case 2:
				MM_COMMON_musicAssignBuffer(p_extrapOrcB, 0);
				MM_COMMON_musicAssignBuffer(p_extrapPercB, 1);
				MM_COMMON_musicAssignBuffer(p_extrapVoxB, 2);
				break;

			case 3:
				MM_COMMON_musicAssignBuffer(p_extrapOrcC, 0);
				MM_COMMON_musicAssignBuffer(p_extrapPercC, 1);
				MM_COMMON_musicAssignBuffer(p_extrapVoxC, 2);
				break;

			case 4:
				MM_COMMON_musicAssignBuffer(p_extrapOrcD, 0);
				MM_COMMON_musicAssignBuffer(p_extrapPercD, 1);
				MM_COMMON_musicAssignBuffer(p_extrapVoxD, 2);
				break;

			case 5:
				MM_COMMON_musicAssignBuffer(p_extrapOrcE, 0);
				MM_COMMON_musicAssignBuffer(p_extrapPercE, 1);
				MM_COMMON_musicAssignBuffer(p_extrapVoxE, 2);
				break;
		};

		MM_COMMON_musicChannelOn(false, 0);
		MM_COMMON_musicChannelOn(false, 1);
		if(p_extrapIt) MM_COMMON_musicChannelOn(false, 2);

		++p_extrapIt;
		if(p_extrapIt >= 6) p_extrapIt = 1;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_extrapThemeStr()
{
	return p_extrapThemeStr;
}
