#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static double p_workdayVolume = 0.8;

static int64_t p_workdayDrums = -1;

static int64_t p_workdayPianoA = -1;
static int64_t p_workdayPianoB = -1;

static int64_t p_workdayBassoonA = -1;
static int64_t p_workdayBassoonB = -1;
static int64_t p_workdayBassoonC = -1;

static int64_t p_workdayGlockandXyloA = -1;
static int64_t p_workdayGlockandXyloB = -1;
static int64_t p_workdayGlockandXyloC = -1;

static int64_t p_workdayTubaSaxCelloA = -1;
static int64_t p_workdayTubaSaxCelloB = -1;
static int64_t p_workdayTubaSaxCelloC = -1;

static int64_t p_workdayOcarinaA = -1;
static int64_t p_workdayOcarinaB = -1;

static size_t p_workdayIt = 0;

static PLEX_FAKESTRING_50 p_workdayThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_WORKDAY_start()
{
	p_workdayThemeStr = PLEX_createString50("Workday");
}

void MM_COMMON_THEME_WORKDAY_playTheme()
{
	p_workdayDrums = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_DRUMS);
	p_workdayPianoA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_PIANOA);
	p_workdayPianoB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_PIANOB);
	p_workdayBassoonA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_BASSOONA);
	p_workdayBassoonB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_BASSOONB);
	p_workdayBassoonC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_BASSOONC);
	p_workdayGlockandXyloA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_GLOCKANDXYLOA);
	p_workdayGlockandXyloB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_GLOCKANDXYLOB);
	p_workdayGlockandXyloC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_GLOCKANDXYLOC);
	p_workdayTubaSaxCelloA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_TUBASAXCELLOA);
	p_workdayTubaSaxCelloB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_TUBASAXCELLOB);
	p_workdayTubaSaxCelloC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_TUBASAXCELLOC);

	p_workdayOcarinaA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_OCARINAA);
	p_workdayOcarinaB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_WORKDAY_OCARINAB);

	PLEX_setVolume(p_workdayVolume, 0);
	PLEX_setVolume(p_workdayVolume, 1);
	PLEX_setVolume(p_workdayVolume, 2);
	PLEX_setVolume(p_workdayVolume, 3);
	PLEX_setVolume(p_workdayVolume, 4);

	if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 1)) MM_COMMON_musicChannelOn(false, 1);

	p_workdayIt = 0;
	p_workdayVolume = 0.8;
}

void MM_COMMON_THEME_WORKDAY_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		if(p_workdayIt < 6)
		{
			MM_COMMON_musicChannelOff(0);
			MM_COMMON_musicChannelOff(1);
			MM_COMMON_musicChannelOff(2);
			MM_COMMON_musicChannelOff(3);
			MM_COMMON_musicChannelOff(4);
			// MM_COMMON_musicChannelOff(5); < do not do
		}

		PLEX_setVolume(p_workdayVolume, 0);
		PLEX_setVolume(p_workdayVolume, 1);
		PLEX_setVolume(p_workdayVolume, 2);
		PLEX_setVolume(p_workdayVolume, 3);
		PLEX_setVolume(p_workdayVolume, 4);

		switch(p_workdayIt)
		{
			case 0:
				if(p_workdayGlockandXyloA != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloA, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 1)) MM_COMMON_musicChannelOn(true, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(true, 2);

				++p_workdayIt;
			break;


			case 1:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);

				++p_workdayIt;
			break;

			case 2:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonA != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonA, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_workdayIt;
			break;

			case 3:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonB != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonB, 3)) MM_COMMON_musicChannelOn(false, 3);
				++p_workdayIt;
			break;

			case 4:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonA != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonA, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_workdayTubaSaxCelloA != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloA, 4)) MM_COMMON_musicChannelOn(false, 4);

				++p_workdayIt;
			break;

			case 5:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonB != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonB, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_workdayTubaSaxCelloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloB, 4)) MM_COMMON_musicChannelOn(false, 4);

				p_workdayVolume += PLEX_randomNumber(0.01, 0.02);

				if(p_workdayVolume > 1)
				{
					p_workdayVolume = 1;
					++p_workdayIt;
				}else p_workdayIt = 4;
			break;

			case 6:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonB != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonB, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_workdayTubaSaxCelloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloB, 4)) MM_COMMON_musicChannelOn(false, 4);

				if(p_workdayOcarinaA != -1 && MM_COMMON_musicAssignBuffer(p_workdayOcarinaA, 5)) MM_COMMON_musicChannelOn(false, 5);

				++p_workdayIt;
			break;

			case 7:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonA != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonA, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_workdayTubaSaxCelloA != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloA, 4)) MM_COMMON_musicChannelOn(false, 4);

				++p_workdayIt;
			break;

			case 8:
				if(p_workdayDrums != -1 && MM_COMMON_musicAssignBuffer(p_workdayDrums, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayPianoA != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayBassoonB != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonB, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_workdayTubaSaxCelloB != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloB, 4)) MM_COMMON_musicChannelOn(false, 4);

				++p_workdayIt;
			break;

			case 9:
				if(!PLEX_isSoundPlaying(5)) ++p_workdayIt;
				break;

			case 10:
				if(p_workdayPianoB != -1 && MM_COMMON_musicAssignBuffer(p_workdayPianoB, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_workdayGlockandXyloC != -1 && MM_COMMON_musicAssignBuffer(p_workdayGlockandXyloC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayBassoonC != -1 && MM_COMMON_musicAssignBuffer(p_workdayBassoonC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_workdayTubaSaxCelloC != -1 && MM_COMMON_musicAssignBuffer(p_workdayTubaSaxCelloC, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_workdayOcarinaB != -1 && MM_COMMON_musicAssignBuffer(p_workdayOcarinaB, 3)) MM_COMMON_musicChannelOn(false, 3);

				p_workdayIt = 0;
				p_workdayVolume = 0.5;
			break;
		};
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_workdayThemeStr()
{
	return p_workdayThemeStr;
}
