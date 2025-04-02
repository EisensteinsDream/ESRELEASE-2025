#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_suspenseClarinetD = -1;
static int64_t p_suspenseClarinetE = -1;
static int64_t p_suspenseClarinetF = -1;
static int64_t p_suspenseClarinetG = -1;

static int64_t p_suspensePercussA = -1;
static int64_t p_suspensePercussB = -1;
static int64_t p_suspensePercussC = -1;
static int64_t p_suspensePercussD = -1;
static int64_t p_suspensePercussE = -1;
static int64_t p_suspensePercussF = -1;
static int64_t p_suspensePercussG = -1;

static int64_t p_suspensePianoA = -1;
static int64_t p_suspensePianoC = -1;
static int64_t p_suspensePianoD = -1;
static int64_t p_suspensePianoE = -1;
static int64_t p_suspensePianoF = -1;
static int64_t p_suspensePianoG = -1;

static int64_t p_suspenseViolinA = -1;
static int64_t p_suspenseViolinB = -1;
static int64_t p_suspenseViolinC = -1;
static int64_t p_suspenseViolinD = -1;
static int64_t p_suspenseViolinE = -1;
static int64_t p_suspenseViolinF = -1;
static int64_t p_suspenseViolinG = -1;

static size_t p_suspenseIt = 0;

static PLEX_FAKESTRING_50 p_suspenseThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_SUSPENSE_start()
{
	p_suspenseThemeStr = PLEX_createString50("Suspense");
}

void MM_COMMON_THEME_SUSPENSE_playTheme()
{
	p_suspenseClarinetD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_CLARINETD);
	p_suspenseClarinetE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_CLARINETE);
	p_suspenseClarinetF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_CLARINETF);
	p_suspenseClarinetG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_CLARINETG);

	p_suspensePercussA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSA);
	p_suspensePercussB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSB);
	p_suspensePercussC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSC);
	p_suspensePercussD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSD);
	p_suspensePercussE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSE);
	p_suspensePercussF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSF);
	p_suspensePercussG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PERCUSSG);

	p_suspensePianoA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOA);
	p_suspensePianoC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOC);
	p_suspensePianoD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOD);
	p_suspensePianoE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOE);
	p_suspensePianoF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOF);
	p_suspensePianoG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_PIANOG);

	p_suspenseViolinA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLINA);
	p_suspenseViolinB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLINB);
	p_suspenseViolinC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLINC);
	p_suspenseViolinD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLIND);
	p_suspenseViolinE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLINE);
	p_suspenseViolinF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLINF);
	p_suspenseViolinG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_SUSPENSE_VIOLING);

	if(p_suspensePercussA != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_suspensePianoA != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoA, 1)) MM_COMMON_musicChannelOn(false, 1);
	if(p_suspenseViolinA != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinA, 2)) MM_COMMON_musicChannelOn(false, 2);

	p_suspenseIt = 0;
}

void MM_COMMON_THEME_SUSPENSE_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		size_t phase = 0;

		++p_suspenseIt;

		if(p_suspenseIt < 3) phase = p_suspenseIt;
		else if(p_suspenseIt < 4) phase = 3;
		else if(p_suspenseIt < 7) phase = 4;
		else if(p_suspenseIt == 7) phase = 5;
		else if(p_suspenseIt < 10) phase = 3;
		else if(p_suspenseIt < 12) phase = 4;
		else if(p_suspenseIt == 12)
		{
			phase = 6;
			p_suspenseIt = 2;
		}

		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);
		MM_COMMON_musicChannelOff(3);

		switch(phase)
		{
			// should not ever be 0

			case 1:
				if(p_suspensePercussB != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussB, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspenseViolinB != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinB, 1)) MM_COMMON_musicChannelOn(false, 1);
				break;

			case 2:
				if(p_suspensePercussC != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussC, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspensePianoC != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_suspenseViolinC != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinC, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 3:
				if(p_suspensePercussD != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussD, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspensePianoD != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoD, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_suspenseViolinD != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinD, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_suspenseClarinetD != -1 && MM_COMMON_musicAssignBuffer(p_suspenseClarinetD, 3)) MM_COMMON_musicChannelOn(false, 3);
				break;

			case 4:
				if(p_suspensePercussE != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussE, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspensePianoE != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoE, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_suspenseViolinE != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinE, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_suspenseClarinetE != -1 && MM_COMMON_musicAssignBuffer(p_suspenseClarinetE, 3)) MM_COMMON_musicChannelOn(false, 3);
				break;

			case 5:
				if(p_suspensePercussF != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussF, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspensePianoF != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoF, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_suspenseViolinF != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinF, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_suspenseClarinetF != -1 && MM_COMMON_musicAssignBuffer(p_suspenseClarinetF, 3)) MM_COMMON_musicChannelOn(false, 3);
				break;

			case 6:
				if(p_suspensePercussF != -1 && MM_COMMON_musicAssignBuffer(p_suspensePercussG, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_suspensePianoF != -1 && MM_COMMON_musicAssignBuffer(p_suspensePianoG, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_suspenseViolinF != -1 && MM_COMMON_musicAssignBuffer(p_suspenseViolinG, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_suspenseClarinetG != -1 && MM_COMMON_musicAssignBuffer(p_suspenseClarinetG, 3)) MM_COMMON_musicChannelOn(false, 3);
				break;
		}
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_suspenseThemeStr()
{
	return p_suspenseThemeStr;
}
