#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_panicAmbience = -1;
static int64_t p_panicDrums = -1;
static int64_t p_panicPiano = -1;

static int64_t p_panicTrombone = -1;

static int64_t p_panicAmsynth0 = -1;
static int64_t p_panicAmsynth1 = -1;

static int64_t p_panicSaxRep0 = -1;
static int64_t p_panicSaxRep1 = -1;

static int64_t p_panicSaxSolo0 = -1;
static int64_t p_panicSaxSolo1 = -1;
static int64_t p_panicSaxSolo2 = -1;
static int64_t p_panicSaxSolo3 = -1;

static size_t p_panicIt = 0;
static size_t p_panicPhaseIt = 0;
static size_t p_panicSoloIt = 0;

static PLEX_FAKESTRING_50 p_panicThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_PANIC_start()
{
	p_panicThemeStr = PLEX_createString50("Panic");
}

void MM_COMMON_THEME_PANIC_playTheme()
{
	p_panicAmbience = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_AMBIENCE);
	p_panicDrums = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_DRUMS);
	p_panicPiano = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_PIANO);
	p_panicTrombone = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_TROMBONE);

	p_panicAmsynth0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_AMSYNTH0);
	p_panicAmsynth1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_AMSYNTH1);

	p_panicSaxRep0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXREP0);
	p_panicSaxRep1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXREP1);

	p_panicSaxSolo0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXSOLO0);
	p_panicSaxSolo1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXSOLO1);
	p_panicSaxSolo2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXSOLO2);
	p_panicSaxSolo3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PANIC_SAXSOLO3);

	if(p_panicAmbience != -1 && MM_COMMON_musicAssignBuffer(p_panicAmbience, 0)) MM_COMMON_musicChannelOn(false, 0);

	if(p_panicDrums != -1) MM_COMMON_musicAssignBuffer(p_panicDrums, 1);
	if(p_panicPiano != -1) MM_COMMON_musicAssignBuffer(p_panicPiano, 2);
	if(p_panicTrombone != -1) MM_COMMON_musicAssignBuffer(p_panicTrombone, 4);

	p_panicIt = 0;
	p_panicPhaseIt = 0;
	p_panicSoloIt = 0;
}

void MM_COMMON_THEME_PANIC_updateTheme()
{
	bool isSoloing = false;

	if(PLEX_isSoundPlaying(0) || PLEX_isSoundPlaying(6)) return;

	MM_COMMON_musicChannelOff(0);
	MM_COMMON_musicChannelOff(1);
	MM_COMMON_musicChannelOff(2);
	MM_COMMON_musicChannelOff(3);
	MM_COMMON_musicChannelOff(4);
	MM_COMMON_musicChannelOff(5);
	MM_COMMON_musicChannelOff(6);

	++p_panicIt;

	isSoloing = p_panicPhaseIt == 4 && p_panicIt == 1;

	if(!isSoloing)
	{
		if(p_panicAmbience != -1) MM_COMMON_musicChannelOn(false, 0);
		if(p_panicDrums != -1 && (p_panicPhaseIt || p_panicIt)) MM_COMMON_musicChannelOn(false, 1);
	}

	switch(p_panicPhaseIt)
	{
		case 0:
			p_panicPhaseIt = 1;
			p_panicIt = 0;
		break;

		case 1:
			if(p_panicIt == 1 || p_panicIt == 3)
			{
				if(p_panicAmsynth0 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth0, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_panicTrombone != -1 && MM_COMMON_musicAssignBuffer(p_panicTrombone, 4)) MM_COMMON_musicChannelOn(false, 4);
			}

			if(p_panicIt == 4)
			{
				p_panicPhaseIt = 2;
				p_panicIt = 0;
			}
		break;

		case 2:
			if(p_panicIt == 1 || p_panicIt == 3)
			{
				if(p_panicPiano != -1) MM_COMMON_musicChannelOn(false, 2);
				if(p_panicAmsynth0 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth0, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_panicTrombone != -1 && MM_COMMON_musicAssignBuffer(p_panicTrombone, 4)) MM_COMMON_musicChannelOn(false, 4);
			}

			if(p_panicIt == 4)
			{
				p_panicPhaseIt = 3;
				p_panicIt = 0;
			}
		break;

		case 3:
			if(p_panicIt == 1 || p_panicIt == 2 || p_panicIt == 4 || p_panicIt == 5 || p_panicIt == 7 || p_panicIt == 8)
			{
				if(p_panicPiano != -1 && MM_COMMON_musicAssignBuffer(p_panicPiano, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_panicTrombone != -1 && MM_COMMON_musicAssignBuffer(p_panicTrombone, 4)) MM_COMMON_musicChannelOn(false, 4);
			}

			if(p_panicIt == 1 || p_panicIt == 4 || p_panicIt == 7)
			{
				if(p_panicAmsynth0 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth0, 3)) MM_COMMON_musicChannelOn(false, 3);
			}

			if(p_panicIt == 2 || p_panicIt == 5 || p_panicIt == 8)
			{
				if(p_panicAmsynth1 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth1, 3)) MM_COMMON_musicChannelOn(false, 3);
			}

			if(p_panicIt == 1 || p_panicIt == 2 || p_panicIt == 7 || p_panicIt == 8)
			{
				if(p_panicSaxRep0 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxRep0, 5)) MM_COMMON_musicChannelOn(false, 5);
			}

			if(p_panicIt == 4 || p_panicIt == 5)
			{
				if(p_panicSaxRep1 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxRep1, 5)) MM_COMMON_musicChannelOn(false, 5);
			}

			if(p_panicIt == 9)
			{
				p_panicPhaseIt = 4;
				p_panicIt = 0;
			}
		break;

		case 4:
			if(isSoloing)
			{
				switch(p_panicSoloIt)
				{
					case 0:
						if(p_panicSaxSolo0 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxSolo0, 6)) MM_COMMON_musicChannelOn(false, 6);
					break;

					case 1:
						if(p_panicSaxSolo1 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxSolo1, 6)) MM_COMMON_musicChannelOn(false, 6);
					break;

					case 2:
						if(p_panicSaxSolo2 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxSolo2, 6)) MM_COMMON_musicChannelOn(false, 6);
					break;

					case 3:
						if(p_panicSaxSolo3 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxSolo3, 6)) MM_COMMON_musicChannelOn(false, 6);
					break;
				};

				++p_panicSoloIt;
			}else{
				if(p_panicIt == 2 || p_panicIt == 3 || p_panicIt == 5 || p_panicIt == 6 || p_panicIt == 8 || p_panicIt == 9)
				{
					if(p_panicPiano != -1) MM_COMMON_musicChannelOn(false, 2);
					if(p_panicTrombone != -1) MM_COMMON_musicChannelOn(false, 4);
				}

				if(p_panicIt == 2 || p_panicIt == 5 || p_panicIt == 8)
				{
					if(p_panicAmsynth0 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth0, 3)) MM_COMMON_musicChannelOn(false, 3);
				}

				if(p_panicIt == 3 || p_panicIt == 6 || p_panicIt == 9)
				{
					if(p_panicAmsynth1 != -1 && MM_COMMON_musicAssignBuffer(p_panicAmsynth1, 3)) MM_COMMON_musicChannelOn(false, 3);
				}

				if(p_panicIt == 2 || p_panicIt == 3 || p_panicIt == 8 || p_panicIt == 9)
				{
					if(p_panicSaxRep0 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxRep0, 5)) MM_COMMON_musicChannelOn(false, 5);
				}

				if(p_panicIt == 5 || p_panicIt == 6)
				{
					if(p_panicSaxRep1 != -1 && MM_COMMON_musicAssignBuffer(p_panicSaxRep1, 5)) MM_COMMON_musicChannelOn(false, 5);
				}

				if(p_panicIt == 10)
				{
					if(p_panicSoloIt == 4)
					{
						p_panicPhaseIt = 2;
						p_panicSoloIt = 0;
					}

					p_panicIt = 0;
				}
			}
		break;
	};
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_panicThemeStr()
{
	return p_panicThemeStr;
}
