#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_dayToDayDrum0 = -1;
static int64_t p_dayToDayDrum1 = -1;
static int64_t p_dayToDayDrum2 = -1;

static int64_t p_dayToDayMonosynth0 = -1;
static int64_t p_dayToDayMonosynth1 = -1;

static int64_t p_dayToDayOrganA0 = -1;
static int64_t p_dayToDayOrganA1 = -1;
static int64_t p_dayToDayOrganA2 = -1;

static int64_t p_dayToDayOrganB0 = -1;
static int64_t p_dayToDayOrganB1 = -1;
static int64_t p_dayToDayOrganB2 = -1;

static size_t p_dayToDayIt = 0;

static PLEX_FAKESTRING_50 p_dayToDayThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_DAYTODAY_start()
{
	p_dayToDayThemeStr = PLEX_createString50("Day to Day");
}

void MM_COMMON_THEME_DAYTODAY_playTheme()
{
	p_dayToDayDrum0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_DRUM0);
	p_dayToDayDrum1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_DRUM1);
	p_dayToDayDrum2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_DRUM2);

	p_dayToDayMonosynth0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_MONOSYNTH0);
	p_dayToDayMonosynth1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_MONOSYNTH1);

	p_dayToDayOrganA0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANA0);
	p_dayToDayOrganA1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANA1);
	p_dayToDayOrganA2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANA2);

	p_dayToDayOrganB0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANB0);
	p_dayToDayOrganB1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANB1);
	p_dayToDayOrganB2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DAYTODAY_ORGANB2);

	if(p_dayToDayDrum0 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayDrum0, 0)) MM_COMMON_musicChannelOn(false, 0);

	p_dayToDayIt = 0;
}

void MM_COMMON_THEME_DAYTODAY_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);
		MM_COMMON_musicChannelOff(3);

		if(p_dayToDayIt != 10)
		{
			if(p_dayToDayIt == 9)
			{
				// DO NOT PUT DRUMS IN SPOT 0 HERE

				if(p_dayToDayIt == 9 && p_dayToDayOrganA2 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayOrganA2, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_dayToDayIt == 9 && p_dayToDayOrganB2 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayOrganB2, 1)) MM_COMMON_musicChannelOn(false, 1);

				if(p_dayToDayDrum2 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayDrum2, 2)) MM_COMMON_musicChannelOn(false, 2);
			}else{
				if(p_dayToDayIt < 5)
				{
					if(p_dayToDayDrum1 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayDrum1, 0)) MM_COMMON_musicChannelOn(false, 0);

					if(p_dayToDayOrganA0 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayOrganA0, 1)) MM_COMMON_musicChannelOn(false, 1);

					if(p_dayToDayIt % 2 == 1 && p_dayToDayMonosynth0 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayMonosynth0, 2)) MM_COMMON_musicChannelOn(false, 2);
				}else{
					if(p_dayToDayDrum1 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayDrum1, 0)) MM_COMMON_musicChannelOn(false, 0);

					if(p_dayToDayIt >= 6 && p_dayToDayMonosynth1 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayMonosynth1, 1)) MM_COMMON_musicChannelOn(false, 1);

					if(p_dayToDayIt == 8 && p_dayToDayOrganA1 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayOrganA1, 2)) MM_COMMON_musicChannelOn(false, 2);
					if(p_dayToDayIt == 8 && p_dayToDayOrganB1 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayOrganB1, 3)) MM_COMMON_musicChannelOn(false, 3);
				}
			}
		}else if(p_dayToDayDrum0 != -1 && MM_COMMON_musicAssignBuffer(p_dayToDayDrum0, 0)) MM_COMMON_musicChannelOn(false, 0);

		p_dayToDayIt = (p_dayToDayIt + 1) % 11;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_dayToDayThemeStr()
{
	return p_dayToDayThemeStr;
}
