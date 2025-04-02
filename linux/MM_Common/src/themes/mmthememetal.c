#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_metalGuitar = -1;
static int64_t p_metalBass = -1;
static int64_t p_metalDrums = -1;

static PLEX_FAKESTRING_50 p_metalThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_METAL_start()
{
	p_metalThemeStr = PLEX_createString50("Metal");
}

void MM_COMMON_THEME_METAL_playTheme()
{
	p_metalGuitar = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_METAL_GUITAR);
	p_metalBass = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_METAL_BASS);
	p_metalDrums = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_METAL_DRUMS);

	if(p_metalGuitar != -1 && MM_COMMON_musicAssignBuffer(p_metalGuitar, 0)) MM_COMMON_musicChannelOn(true, 0);
	if(p_metalBass != -1 && MM_COMMON_musicAssignBuffer(p_metalBass, 1)) MM_COMMON_musicChannelOn(true, 1);
	if(p_metalDrums != -1 && MM_COMMON_musicAssignBuffer(p_metalDrums, 2)) MM_COMMON_musicChannelOn(true, 2);
}

void MM_COMMON_THEME_METAL_updateTheme()
{

}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_metalThemeStr()
{
	return p_metalThemeStr;
}
