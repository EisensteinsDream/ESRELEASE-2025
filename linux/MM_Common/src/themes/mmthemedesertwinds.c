#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static const char* const p_desertWindsAtmosphere[12] = { MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE00, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE01, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE02, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE03, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE04, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE05, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE06, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE07, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE08, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE09, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE10, MM_COMMON_MUSICPATH_DESERTWINDS_ATMOSPHERE11 };

static int64_t p_desertWindsBellsA = -1;
static int64_t p_desertWindsBellsB = -1;
static int64_t p_desertWindsGuitar = -1;
static int64_t p_desertWindsWhistle = -1;

static size_t p_desertWindsWhistleRep = 0;
static size_t p_desertWindsSoundRep = 0;
static size_t p_desertWindsWhistleIt = 0;
static size_t p_desertWindsSoundIt = 0;
static uint64_t p_desertWindsWhistleMark = 0;
static uint64_t p_desertWindsWhistleDuration = 0;

static bool p_desertWindsIntro = false;

static PLEX_FAKESTRING_50 p_desertWindsThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_DESERTWINDS_start()
{
	p_desertWindsThemeStr = PLEX_createString50("Desert Winds");
}

void MM_COMMON_THEME_DESERTWINDS_playTheme()
{
	p_desertWindsBellsA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTWINDS_BELL0);
	p_desertWindsBellsB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTWINDS_BELL1);
	p_desertWindsGuitar = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTWINDS_GUITAR);
	p_desertWindsWhistle = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTWINDS_TRAINWHISTLE);

	if(p_desertWindsBellsA != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsBellsA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_desertWindsGuitar != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsGuitar, 1)) MM_COMMON_musicChannelOn(false, 1);

	p_desertWindsIntro = false;

	p_desertWindsWhistleRep = 0;
	p_desertWindsSoundRep = 0;
	p_desertWindsWhistleMark = 0;
	p_desertWindsWhistleDuration = 0;
	p_desertWindsWhistleIt = 0;
	p_desertWindsSoundIt = 0;
}

void MM_COMMON_THEME_DESERTWINDS_updateTheme(const uint64_t time)
{
	if(!PLEX_isSoundPlaying(1) && !p_desertWindsIntro)
	{
		if(p_desertWindsBellsB != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsBellsB, 0)) MM_COMMON_musicChannelOn(false, 0);
		if(p_desertWindsWhistle != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsWhistle, 1)) MM_COMMON_musicChannelOn(false, 1);

		p_desertWindsWhistleRep = PLEX_randomNumber(2, 4);
		p_desertWindsSoundRep = PLEX_randomNumber(3, 5);
		p_desertWindsWhistleMark = time;
		p_desertWindsWhistleDuration = PLEX_randomNumber(2000, 15000);
		p_desertWindsWhistleIt = 0;
		p_desertWindsSoundIt = 0;

		p_desertWindsIntro = true;
	}else{
		if(p_desertWindsWhistleMark && time - p_desertWindsWhistleMark > p_desertWindsWhistleDuration)
		{
			MM_COMMON_musicChannelOff(2);

			if(p_desertWindsSoundIt < p_desertWindsSoundRep)
			{
				const size_t buffer = PLEX_LIMIT_SOUNDCHANNELS - PLEX_LIMIT_SOUNDEFFECTS - 1;

				const size_t index = PLEX_randomNumber(0, 11);

				const double volume = PLEX_randomNumber(0.2, 1);

				PLEX_clearSoundBuffer(buffer);

				MM_COMMON_preloadMusicFileToSpecificBuffer(p_desertWindsAtmosphere[index], buffer);

				MM_COMMON_musicAssignBuffer(buffer, 2);
				PLEX_setVolume(volume, 2);
				MM_COMMON_musicChannelOn(false, 2);

				++p_desertWindsSoundIt;
			}else{
				if(p_desertWindsWhistleIt < p_desertWindsSoundIt)
				{
					if(p_desertWindsWhistleIt % 2 == 1 && p_desertWindsBellsB != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsBellsB, 0)) MM_COMMON_musicChannelOn(false, 0);

					if(p_desertWindsWhistle != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsWhistle, 1)) MM_COMMON_musicChannelOn(false, 1);

					p_desertWindsSoundIt = 0;
					p_desertWindsSoundRep = PLEX_randomNumber(3, 5);

					++p_desertWindsWhistleIt;
				}else{
					MM_COMMON_musicChannelOff(0);
					MM_COMMON_musicChannelOff(1);

					if(p_desertWindsBellsA != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsBellsA, 0)) MM_COMMON_musicChannelOn(false, 0);
					if(p_desertWindsGuitar != -1 && MM_COMMON_musicAssignBuffer(p_desertWindsGuitar, 1)) MM_COMMON_musicChannelOn(false, 1);

					p_desertWindsIntro = false;
					p_desertWindsWhistleMark = 0;
					p_desertWindsWhistleRep = PLEX_randomNumber(2, 4);
					p_desertWindsSoundRep = PLEX_randomNumber(3, 5);
					p_desertWindsWhistleIt = 0;
					p_desertWindsSoundIt = 0;
				}
			}

			p_desertWindsWhistleMark = time;
			p_desertWindsWhistleDuration = PLEX_randomNumber(2000, 15000);
		}
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_desertWindsThemeStr()
{
	return p_desertWindsThemeStr;
}
