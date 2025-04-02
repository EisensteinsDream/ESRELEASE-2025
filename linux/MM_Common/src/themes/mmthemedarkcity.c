#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_darkCityA0 = -1;
static int64_t p_darkCityA1 = -1;
static int64_t p_darkCityB0 = -1;
static int64_t p_darkCityB1 = -1;
static int64_t p_darkCityC0 = -1;
static int64_t p_darkCityC1 = -1;
static int64_t p_darkCityD0 = -1;
static int64_t p_darkCityD1 = -1;
static int64_t p_darkCityE0 = -1;
static int64_t p_darkCityE1 = -1;
static int64_t p_darkCityF0 = -1;
static int64_t p_darkCityF1 = -1;
static int64_t p_darkCityG0 = -1;
static int64_t p_darkCityG1 = -1;
static int64_t p_darkCityH0 = -1;
static int64_t p_darkCityH1 = -1;
static int64_t p_darkCityI0 = -1;

static size_t p_darkCitySwitch = 0;

static int64_t p_lastDarkCitySwitch = -1;
static int64_t p_lastDarkCityMelodyChange = -1;

static PLEX_FAKESTRING_50 p_darkCityThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_DARKCITY_start()
{
	p_darkCityThemeStr = PLEX_createString50("Dark City");
}

void MM_COMMON_THEME_DARKCITY_playTheme()
{
	p_darkCityA0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_A0);
	p_darkCityA1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_A1);
	p_darkCityB0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_B0);
	p_darkCityB1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_B1);
	p_darkCityC0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_C0);
	p_darkCityC1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_C1);
	p_darkCityD0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_D0);
	p_darkCityD1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_D1);
	p_darkCityE0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_E0);
	p_darkCityE1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_E1);
	p_darkCityF0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_F0);
	p_darkCityF1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_F1);
	p_darkCityG0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_G0);
	p_darkCityG1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_G1);
	p_darkCityH0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_H0);
	p_darkCityH1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_H1);
	p_darkCityI0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DARKCITY_I0);

	if(p_darkCityA0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityA0, 0)) MM_COMMON_musicChannelOn(true, 0);
	if(p_darkCityB0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityB0, 1)) MM_COMMON_musicChannelOn(true, 1);
	if(p_darkCityC0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityC0, 2)) MM_COMMON_musicChannelOn(true, 2);
	if(p_darkCityD0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityD0, 3)) MM_COMMON_musicChannelOn(true, 3);
	if(p_darkCityE0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityE0, 4)) MM_COMMON_musicChannelOn(true, 4);
	if(p_darkCityF0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityF0, 5)) MM_COMMON_musicChannelOn(true, 5);
	if(p_darkCityG0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityG0, 6)) MM_COMMON_musicChannelOn(true, 6);
	if(p_darkCityH0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityH0, 7)) MM_COMMON_musicChannelOn(true, 7);
	if(p_darkCityI0 != -1 && MM_COMMON_musicAssignBuffer(p_darkCityI0, 8)) MM_COMMON_musicChannelOn(true, 8);

	p_darkCitySwitch = PLEX_randomNumber(3, 6);
}

void MM_COMMON_THEME_DARKCITY_updateTheme()
{
	const size_t iteration = PLEX_channelIteration(8);

	if(p_darkCitySwitch < iteration && (p_darkCitySwitch != p_lastDarkCitySwitch || p_lastDarkCitySwitch == -1))
	{
		const size_t melodyChange = PLEX_randomNumber(0, 7);
		const int64_t bufferChange = PLEX_getBuffer(melodyChange);

		MM_COMMON_musicChannelOff(melodyChange);
		if(bufferChange != -1) MM_COMMON_musicAssignBuffer(bufferChange + 1, melodyChange);
		MM_COMMON_musicChannelOn(true, melodyChange);

		p_darkCitySwitch = iteration + PLEX_randomNumber(3, 6);
		p_lastDarkCitySwitch = iteration;
		p_lastDarkCityMelodyChange = melodyChange;
	}else{
		if(iteration > p_lastDarkCitySwitch && p_lastDarkCityMelodyChange != -1 && p_lastDarkCitySwitch != -1)
		{
			const int64_t bufferChange = PLEX_getBuffer(p_lastDarkCityMelodyChange);

			MM_COMMON_musicChannelOff(p_lastDarkCityMelodyChange);
			if(bufferChange > 0) MM_COMMON_musicAssignBuffer(bufferChange - 1, p_lastDarkCityMelodyChange);
			MM_COMMON_musicChannelOn(true, p_lastDarkCityMelodyChange);

			p_lastDarkCityMelodyChange = -1;
		}
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_darkcityThemeStr()
{
	return p_darkCityThemeStr;
}
