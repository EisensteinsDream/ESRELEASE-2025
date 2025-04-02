#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_desertTownHarpA = -1;
static int64_t p_desertTownHarpB = -1;
static int64_t p_desertTownHarpC = -1;
static int64_t p_desertTownHarpD = -1;

static int64_t p_desertTownOrganA = -1;
static int64_t p_desertTownOrganB = -1;
static int64_t p_desertTownOrganC = -1;
static int64_t p_desertTownOrganD = -1;

static int64_t p_desertTownPianoA = -1;
static int64_t p_desertTownPianoB = -1;
static int64_t p_desertTownPianoC = -1;
static int64_t p_desertTownPianoD = -1;

static int64_t p_desertTownGuitarA = -1;
static int64_t p_desertTownGuitarB = -1;
static int64_t p_desertTownGuitarC = -1;
static int64_t p_desertTownGuitarD = -1;

static int64_t p_desertTownHarmonicaA = -1;
static int64_t p_desertTownHarmonicaB = -1;
static int64_t p_desertTownHarmonicaC = -1;
static int64_t p_desertTownHarmonicaD = -1;

static size_t p_desertTownIterations = 0;
static size_t p_desertTownPart = 0;
static size_t p_desertTownPartIterations = 0;

static PLEX_FAKESTRING_50 p_desertTownThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_DESERTTOWN_start()
{
	p_desertTownThemeStr = PLEX_createString50("Desert Town");
}

void MM_COMMON_THEME_DESERTTOWN_playTheme()
{
	p_desertTownHarpA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARPA);
	p_desertTownHarpB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARPB);
	p_desertTownHarpC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARPC);
	p_desertTownHarpD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARPD);

	p_desertTownOrganA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_ORGANA);
	p_desertTownOrganB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_ORGANB);
	p_desertTownOrganC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_ORGANC);
	p_desertTownOrganD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_ORGAND);

	p_desertTownPianoA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_PIANOA);
	p_desertTownPianoB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_PIANOB);
	p_desertTownPianoC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_PIANOC);
	p_desertTownPianoD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_PIANOD);

	p_desertTownGuitarA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_GUITARA);
	p_desertTownGuitarB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_GUITARB);
	p_desertTownGuitarC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_GUITARC);
	p_desertTownGuitarD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_GUITARD);

	p_desertTownHarmonicaA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARMONICAA);
	p_desertTownHarmonicaB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARMONICAB);
	p_desertTownHarmonicaC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARMONICAC);
	p_desertTownHarmonicaD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_DESERTTOWN_HARMONICAD);

	if(p_desertTownHarpA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_desertTownOrganA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganA, 1)) MM_COMMON_musicChannelOn(false, 1);
	if(p_desertTownPianoA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);

	p_desertTownIterations = 1;
	p_desertTownPart = 0;
	p_desertTownPartIterations = 1;
}

void MM_COMMON_THEME_DESERTTOWN_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);
		MM_COMMON_musicChannelOff(3);
		MM_COMMON_musicChannelOff(4);

		switch(p_desertTownPart)
		{
			case 0:
				if(p_desertTownHarpA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpA, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganA, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 1:
				if(p_desertTownHarpB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpB, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoB, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 2:
				if(p_desertTownHarpC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpC, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoC, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 3:
				if(p_desertTownHarpD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpD, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganD, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoD, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_desertTownHarmonicaD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarmonicaD, 3)) MM_COMMON_musicChannelOn(false, 3);
				break;

			case 4:
				if(p_desertTownHarpA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpA, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganA, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_desertTownHarmonicaA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarmonicaA, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_desertTownGuitarA != -1 && MM_COMMON_musicAssignBuffer(p_desertTownGuitarA, 4)) MM_COMMON_musicChannelOn(false, 4);
				break;

			case 5:
				if(p_desertTownHarpB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpB, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoB, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_desertTownHarmonicaB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarmonicaB, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_desertTownGuitarB != -1 && MM_COMMON_musicAssignBuffer(p_desertTownGuitarB, 4)) MM_COMMON_musicChannelOn(false, 4);
				break;

			case 6:
				if(p_desertTownHarpC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpC, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoC, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_desertTownHarmonicaC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarmonicaC, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_desertTownGuitarC != -1 && MM_COMMON_musicAssignBuffer(p_desertTownGuitarC, 4)) MM_COMMON_musicChannelOn(false, 4);
				break;

			case 7:
				if(p_desertTownHarpD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarpD, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_desertTownOrganD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownOrganD, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_desertTownPianoD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownPianoD, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_desertTownHarmonicaD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownHarmonicaD, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_desertTownGuitarD != -1 && MM_COMMON_musicAssignBuffer(p_desertTownGuitarD, 4)) MM_COMMON_musicChannelOn(false, 4);
				break;
		}

		++p_desertTownIterations;
	}

	if(p_desertTownIterations >= p_desertTownPartIterations)
	{
		p_desertTownPart = (p_desertTownPart + 1) % 8;

		switch(p_desertTownPart)
		{
			case 0:
			case 1:
			case 2:
			case 4:
			case 5:
			case 6:
				p_desertTownPartIterations = 1;
				break;

			case 3:
			case 7:
				p_desertTownPartIterations = PLEX_randomNumber(2, 8);
				break;
		};

		p_desertTownIterations = 0;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_desertTownThemeStr()
{
	return p_desertTownThemeStr;
}
