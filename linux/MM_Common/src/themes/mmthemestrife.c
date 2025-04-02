#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_strifeLeftA1 = -1;
static int64_t p_strifeLeftB1 = -1;
static int64_t p_strifeLeftC1 = -1;
static int64_t p_strifeLeftD1 = -1;

static int64_t p_strifeLeftA2 = -1;
static int64_t p_strifeLeftB2 = -1;
static int64_t p_strifeLeftC2 = -1;
static int64_t p_strifeLeftD2 = -1;

static int64_t p_strifeLeftA3 = -1;
static int64_t p_strifeLeftB3 = -1;
static int64_t p_strifeLeftC3 = -1;
static int64_t p_strifeLeftD3 = -1;

static int64_t p_strifeRight = -1;
static int64_t p_strifeOboe = -1;
static int64_t p_strifeFlute = -1;
static int64_t p_strifeBassoon = -1;
static int64_t p_strifeViolins = -1;

static size_t p_strifeVariation = 0;
static size_t p_strifeTone = 0;
static size_t p_strifeSection = 0;

PLEX_FAKESTRING_50 p_strifeThemeStr;

// static functions ---------------------------------------------------------------------------------------------------------

// The first variation. Each variation is randomly selected with each iteration of the melody.

static void p_strifeVariation0(const size_t iteration)
{
	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	if(p_strifeRight && p_strifeRight != -1 && MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(p_strifeOboe && p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(p_strifeSection > 0 && p_strifeFlute != -1 && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
	if(p_strifeSection > 1 && p_strifeBassoon != -1 && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
	if(p_strifeSection > 2 && p_strifeViolins != -1 && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
}

// The second variation

static void p_strifeVariation1(const size_t iteration)
{
	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	if(iteration < 2 && p_strifeRight != -1 && MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(!iteration)
	{
		if(p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
		if(p_strifeFlute != -1 && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
		if(p_strifeBassoon != -1 && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
		if(p_strifeViolins != -1 && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
	}
}

// The third variation

static void p_strifeVariation2(const size_t iteration)
{
	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	if(iteration > 1 && p_strifeRight != -1 && MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(iteration)
	{
		if(p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
		if(p_strifeFlute != -1 && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
		if(p_strifeBassoon != -1 && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
		if(p_strifeViolins != -1 && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
	}
}

// The fourth variation

static void p_strifeVariation3(const size_t iteration)
{
	const double sectionVolume = p_strifeSection < 8 ? p_strifeSection/8.0 : 1;

	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	PLEX_setVolume(1 - sectionVolume, 0); // left
	PLEX_setVolume(1 - sectionVolume, 1); // right
	PLEX_setVolume(0.5 + sectionVolume/2.0, 2); // oboe
	PLEX_setVolume(0.5 - sectionVolume/2.0, 3); // flute
	PLEX_setVolume(sectionVolume, 4); // bassoon
	PLEX_setVolume(sectionVolume, 5); // violins

	if(MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(p_strifeFlute != -1 && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
	if(p_strifeBassoon != -1 && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
	if(p_strifeViolins != -1 && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
}

// The fifth variation

static void p_strifeVariation4(const size_t iteration)
{
	const double sectionVolume = p_strifeSection < 8 ? p_strifeSection/8.0 : 1;

	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	PLEX_setVolume(sectionVolume, 0); // left
	PLEX_setVolume(sectionVolume, 1); // right
	PLEX_setVolume(1 - sectionVolume, 2); // oboe
	PLEX_setVolume(1 - sectionVolume, 3); // flute
	PLEX_setVolume(1 - sectionVolume, 4); // bassoon
	PLEX_setVolume(1 - sectionVolume, 5); // violins

	if(MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(p_strifeFlute != -1  && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
	if(p_strifeBassoon != -1  && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
	if(p_strifeViolins != -1  && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
}

// The sixth variation

static void p_strifeVariation5(const size_t iteration)
{
	const bool split = p_strifeSection % 2 == 1;

	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	if(!split && MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);

	if(split && p_strifeOboe != -1 && MM_COMMON_musicAssignBuffer(p_strifeOboe, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(split && p_strifeFlute != -1 && MM_COMMON_musicAssignBuffer(p_strifeFlute, 3)) MM_COMMON_musicChannelOn(false, 3);
	if(split && p_strifeBassoon != -1 && MM_COMMON_musicAssignBuffer(p_strifeBassoon, 4)) MM_COMMON_musicChannelOn(false, 4);
	if(split && p_strifeViolins != -1 && MM_COMMON_musicAssignBuffer(p_strifeViolins, 5)) MM_COMMON_musicChannelOn(false, 5);
}

// The seventh variation

static void p_strifeVariation6(const size_t iteration)
{
	const double sectionVolume = p_strifeSection < 8 ? p_strifeSection/8.0 : 1;

	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);

	PLEX_setVolume(sectionVolume, 1); // right

	if(MM_COMMON_musicAssignBuffer(p_strifeRight, 1)) MM_COMMON_musicChannelOn(false, 1);
}

// Selects current strife variation and iteration

static void p_setStrifeVariation(const size_t iteration)
{
	switch(p_strifeVariation)
	{
		case 0: p_strifeVariation0(iteration); break;
		case 1: p_strifeVariation1(iteration); break;
		case 2: p_strifeVariation2(iteration); break;
		case 3: p_strifeVariation3(iteration); break;
		case 4: p_strifeVariation4(iteration); break;
		case 5: p_strifeVariation5(iteration); break;
		case 6: p_strifeVariation6(iteration); break;
	};
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_updateStrifeVariation()
{
	const size_t iteration = p_strifeSection / 2;

	int64_t bufferChord1 = 0;
	int16_t bufferChord2 = 0;
	int16_t bufferChord3 = 0;

	p_strifeVariation = PLEX_randomNumber(0, 6);
	p_strifeTone = PLEX_randomNumber(0, 4);

	MM_COMMON_musicChannelOff(0);

	switch(p_strifeTone)
	{
		case 0:
			bufferChord1 = p_strifeLeftA1;
			bufferChord2 = p_strifeLeftA2;
			bufferChord3 = p_strifeLeftA3;
		break;

		case 1:
			bufferChord1 = p_strifeLeftB1;
			bufferChord2 = p_strifeLeftB2;
			bufferChord3 = p_strifeLeftB3;
		break;

		case 2:
			bufferChord1 = p_strifeLeftC1;
			bufferChord2 = p_strifeLeftC2;
			bufferChord3 = p_strifeLeftC3;
		break;

		case 3:
			bufferChord1 = p_strifeLeftD1;
			bufferChord2 = p_strifeLeftD2;
			bufferChord3 = p_strifeLeftD3;
		break;
	};

	switch(iteration)
	{
		case 0:
			if(bufferChord1 != -1) MM_COMMON_musicAssignBuffer(bufferChord1, 0);
		break;

		case 1:
			if(bufferChord2 != -1) MM_COMMON_musicAssignBuffer(bufferChord2, 0);
		break;

		case 2:
			if(bufferChord3 != -1) MM_COMMON_musicAssignBuffer(bufferChord3, 0);
		break;
	};

	MM_COMMON_musicChannelOn(false, 0);

	p_setStrifeVariation(iteration);
}

void MM_COMMON_THEME_STRIFE_start()
{
	p_strifeThemeStr = PLEX_createString50("Strife");
}

void MM_COMMON_THEME_STRIFE_playTheme()
{
	p_strifeLeftA1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT1A);
	p_strifeLeftB1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT1B);
	p_strifeLeftC1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT1C);
	p_strifeLeftD1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT1D);

	p_strifeLeftA2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT2A);
	p_strifeLeftB2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT2B);
	p_strifeLeftC2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT2C);
	p_strifeLeftD2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT2D);

	p_strifeLeftA3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT3A);
	p_strifeLeftB3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT3B);
	p_strifeLeftC3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT3C);
	p_strifeLeftD3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_LEFT3D);

	p_strifeRight = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_RIGHT);
	p_strifeOboe = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_OBOE);
	p_strifeFlute = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_FLUTE);
	p_strifeBassoon = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_BASSOON);
	p_strifeViolins = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_STRIFE_VIOLINS);

	MM_COMMON_THEME_updateStrifeVariation();
}

void MM_COMMON_THEME_STRIFE_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		MM_COMMON_THEME_updateStrifeVariation();

		++p_strifeSection;

		if(p_strifeSection >= 8) p_strifeSection = 0;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_strifeThemeStr()
{
	return p_strifeThemeStr;
}
