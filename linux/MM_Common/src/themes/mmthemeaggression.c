#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_aggressionDrums = -1;
static int64_t p_aggressionOrgan1 = -1;
static int64_t p_aggressionOrgan2 = -1;
static int64_t p_aggressionCelloHarspi = -1;
static int64_t p_aggressionAMSynth1 = -1;
static int64_t p_aggressionAMSynth2A = -1;
static int64_t p_aggressionAMSynth2B = -1;
static int64_t p_aggressionAMSynth2C = -1;
static int64_t p_aggressionAMSynth2D = -1;
static int64_t p_aggressionAMSynth2E = -1;
static int64_t p_aggressionAMSynth2F = -1;
static int64_t p_aggressionAMSynth2G = -1;

static size_t p_aggressionIterations = 0;

static PLEX_FAKESTRING_50 p_aggressionThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_AGGRESSION_start()
{
	p_aggressionThemeStr = PLEX_createString50("Aggression");
}

void MM_COMMON_THEME_AGGRESSION_playTheme()
{
	p_aggressionDrums = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_DRUMS);
	p_aggressionOrgan1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_ORGAN1);
	p_aggressionOrgan2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_ORGAN2);
	p_aggressionCelloHarspi = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_CELLOHARPSI);
	p_aggressionAMSynth1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH1);
	p_aggressionAMSynth2A = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2A);
	p_aggressionAMSynth2B = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2B);
	p_aggressionAMSynth2C = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2C);
	p_aggressionAMSynth2D = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2D);
	p_aggressionAMSynth2E = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2E);
	p_aggressionAMSynth2F = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2F);
	p_aggressionAMSynth2G = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_AGGRESSION_AMSYNTH2G);

	if(p_aggressionDrums != -1 && MM_COMMON_musicAssignBuffer(p_aggressionDrums, 0)) MM_COMMON_musicChannelOn(false, 0);

	p_aggressionIterations = 0;
}

void MM_COMMON_THEME_AGGRESSION_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		const size_t songMid = p_aggressionIterations % 4;

		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);
		MM_COMMON_musicChannelOff(3);
		MM_COMMON_musicChannelOff(4);
		MM_COMMON_musicChannelOff(5);

		if(p_aggressionDrums != -1 && MM_COMMON_musicAssignBuffer(p_aggressionDrums, 0)) MM_COMMON_musicChannelOn(false, 0);

		if(p_aggressionIterations > 0)
		{
			if(p_aggressionOrgan1 != -1 && MM_COMMON_musicAssignBuffer(p_aggressionOrgan1, 1)) MM_COMMON_musicChannelOn(false, 1);
			if(p_aggressionOrgan2 != -1 && MM_COMMON_musicAssignBuffer(p_aggressionOrgan2, 2)) MM_COMMON_musicChannelOn(false, 2);
			if(p_aggressionAMSynth1 != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth1, 3)) MM_COMMON_musicChannelOn(false, 3);
		}

		if(songMid > 1)
		{
			if(p_aggressionCelloHarspi != -1 && MM_COMMON_musicAssignBuffer(p_aggressionCelloHarspi, 4)) MM_COMMON_musicChannelOn(false, 4);
		}

		if(p_aggressionIterations == 3 || p_aggressionIterations == 5)
		{
			const size_t choice = PLEX_randomNumber(0, 6);

			switch(choice)
			{
				case 0:
					if(p_aggressionAMSynth2A != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2A, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				case 1:
					if(p_aggressionAMSynth2B != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2B, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				case 2:
					if(p_aggressionAMSynth2D != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2C, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				case 3:
					if(p_aggressionAMSynth2D != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2D, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				case 4:
					if(p_aggressionAMSynth2E != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2E, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				case 5:
					if(p_aggressionAMSynth2F != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2F, 5)) MM_COMMON_musicChannelOn(false, 5);
					break;

				default:
					if(p_aggressionAMSynth2G != -1 && MM_COMMON_musicAssignBuffer(p_aggressionAMSynth2G, 5)) MM_COMMON_musicChannelOn(false, 5);
			};
		}

		p_aggressionIterations = (p_aggressionIterations + 1) % 6;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_aggressionThemeStr()
{
	return p_aggressionThemeStr;
}
