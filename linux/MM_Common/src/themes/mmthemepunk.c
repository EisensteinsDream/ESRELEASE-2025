#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_punkGuitar = -1;
static int64_t p_punkBass = -1;
static int64_t p_punkDrums = -1;

static int64_t p_punkVoxA = -1;
static int64_t p_punkVoxB = -1;
static int64_t p_punkVoxC = -1;

static size_t p_punkLastIteration = 0;

static double p_punkVolume = 1;

static PLEX_FAKESTRING_50 p_punkThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_PUNK_start()
{
	p_punkThemeStr = PLEX_createString50("Punk");
}

void MM_COMMON_THEME_PUNK_playTheme()
{
	p_punkGuitar = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_GUITAR);
	p_punkBass = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_BASS);
	p_punkDrums = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_DRUMS);

	p_punkVoxA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_VOXA);
	p_punkVoxB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_VOXB);
	p_punkVoxC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PUNK_VOXC);

	if(p_punkGuitar != -1 && MM_COMMON_musicAssignBuffer(p_punkGuitar, 0)) MM_COMMON_musicChannelOn(true, 0);
	if(p_punkBass != -1 && MM_COMMON_musicAssignBuffer(p_punkBass, 1)) MM_COMMON_musicChannelOn(true, 1);
	if(p_punkDrums != -1 && MM_COMMON_musicAssignBuffer(p_punkDrums, 2)) MM_COMMON_musicChannelOn(true, 2);

	p_punkLastIteration = 0;

	// do not set volume full here //
}

void MM_COMMON_THEME_PUNK_updateTheme()
{
	const size_t iteration = PLEX_channelIteration(0) % 7;

	PLEX_setVolume(p_punkVolume, 0);
	PLEX_setVolume(p_punkVolume, 1);
	PLEX_setVolume(p_punkVolume, 2);
	PLEX_setVolume(p_punkVolume, 3);

	if(iteration != p_punkLastIteration)
	{
		MM_COMMON_musicChannelOff(3);

		switch(iteration)
		{
			case 2:
			case 3:
			case 4:
				if(p_punkVoxA != -1 && MM_COMMON_musicAssignBuffer(p_punkVoxA, 3)) MM_COMMON_musicChannelOn(true, 3);
				break;

			case 5: if(p_punkVoxB != -1 && MM_COMMON_musicAssignBuffer(p_punkVoxB, 3)) MM_COMMON_musicChannelOn(true, 3); break;
			case 6: if(p_punkVoxC != -1 && MM_COMMON_musicAssignBuffer(p_punkVoxC, 3)) MM_COMMON_musicChannelOn(true, 3); break;
		};

		p_punkLastIteration = iteration;
	}
}

// setters ------------------------------------------------------------------------------------------------------------------

void MM_COMMON_punkThemeVolume(const double volume)
{
	p_punkVolume = volume;
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_punkThemeStr()
{
	return p_punkThemeStr;
}
