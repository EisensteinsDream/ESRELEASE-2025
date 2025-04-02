#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_FAKESTRING_50 p_newsroomThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_NEWSROOM_start()
{
	p_newsroomThemeStr = PLEX_createString50("Newsroom");
}

void MM_COMMON_THEME_NEWSROOM_playTheme()
{
	const int64_t drum0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_DRUM0);
	const int64_t drum1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_DRUM1);

	const int64_t trumpet0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_TRUMPET0);
	const int64_t trumpet1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_TRUMPET1);

	const int64_t synthA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_SYNTHA);

	const int64_t synthB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_NEWSROOM_SYNTHB);

	if(drum0 != -1 && MM_COMMON_musicAssignBuffer(drum0, 0)) MM_COMMON_musicChannelOn(true, 0);
	if(trumpet0 != -1 && MM_COMMON_musicAssignBuffer(trumpet0, 1)) MM_COMMON_musicChannelOn(true, 1);

	if(synthA != -1 && MM_COMMON_musicAssignBuffer(synthA, 2)) MM_COMMON_musicChannelOn(true, 2);
	if(synthB != -1 && MM_COMMON_musicAssignBuffer(synthB, 3)) MM_COMMON_musicChannelOn(true, 3);
	if(drum1 != -1 && MM_COMMON_musicAssignBuffer(drum1, 4)) MM_COMMON_musicChannelOn(true, 4);
	if(trumpet1 != -1 && MM_COMMON_musicAssignBuffer(trumpet1, 5)) MM_COMMON_musicChannelOn(true, 5);

	PLEX_setComplexSoundSequence(true, false, false, false, false, false, false, false, 5, 0);
	PLEX_setComplexSoundSequence(true, false, false, false, false, false, false, false, 5, 1);

	PLEX_setComplexSoundSequence(false, true, true, true, true, false, false, false, 5, 2);
	PLEX_setComplexSoundSequence(false, true, true, true, true, false, false, false, 5, 3);
	PLEX_setComplexSoundSequence(false, true, true, true, true, false, false, false, 5, 4);
	PLEX_setComplexSoundSequence(false, true, true, true, true, false, false, false, 5, 5);
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_newsroomThemeStr()
{
	return p_newsroomThemeStr;
}
