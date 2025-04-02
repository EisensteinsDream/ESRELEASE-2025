#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static size_t p_comedyBrassCello0 = -1;
static size_t p_comedyBrassCello1 = -1;
static size_t p_comedyBrassCello2 = -1;
static size_t p_comedyBrassCello3 = -1;

static size_t p_comedyDrum0 = -1;
static size_t p_comedyDrum1 = -1;
static size_t p_comedyDrum2 = -1;
static size_t p_comedyDrum3 = -1;
static size_t p_comedyDrum4A = -1;
static size_t p_comedyDrum4B = -1;
static size_t p_comedyDrum5 = -1;
static size_t p_comedyDrum6A = -1;
static size_t p_comedyDrum6B = -1;

static size_t p_comedyOrgan0 = -1;
static size_t p_comedyOrgan1 = -1;
static size_t p_comedyOrgan3 = -1;

static size_t p_comedyIteration = 0;
static size_t p_comedyRandomDrumPattern = 0;

static PLEX_FAKESTRING_50 p_comedyThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_COMEDY_start()
{
	p_comedyThemeStr = PLEX_createString50("Comedy");
}

void MM_COMMON_THEME_COMEDY_playTheme()
{
	p_comedyBrassCello0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_BC0);
	p_comedyBrassCello1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_BC1);
	p_comedyBrassCello2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_BC2);
	p_comedyBrassCello3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_BC3);

	p_comedyDrum0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D0);
	p_comedyDrum1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D1);
	p_comedyDrum2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D2);
	p_comedyDrum3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D3);
	p_comedyDrum4A = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D4A);
	p_comedyDrum4B = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D4B);
	p_comedyDrum5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D5);
	p_comedyDrum6A = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D6A);
	p_comedyDrum6B = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_D6B);

	p_comedyOrgan0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_O0);
	p_comedyOrgan1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_O1);
	p_comedyOrgan3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_COMEDY_O3);

	if(p_comedyBrassCello0 != -1 && MM_COMMON_musicAssignBuffer(p_comedyBrassCello0, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_comedyDrum0 != -1 && MM_COMMON_musicAssignBuffer(p_comedyDrum0, 1)) MM_COMMON_musicChannelOn(false, 1);
	if(p_comedyOrgan0 != -1 && MM_COMMON_musicAssignBuffer(p_comedyOrgan0, 2)) MM_COMMON_musicChannelOn(false, 2);

	p_comedyIteration = 0;
	p_comedyRandomDrumPattern = 0;
}

void MM_COMMON_THEME_COMEDY_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		size_t randomDrumPart = 0;
		size_t randomDrumPart2 = 0;

		++p_comedyIteration;

		if(p_comedyIteration >= 6)
		{
			p_comedyIteration = 2;
			p_comedyRandomDrumPattern = PLEX_randomNumber(0, 100);
		}

		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);

		if(p_comedyRandomDrumPattern < 50)
		{
			randomDrumPart = p_comedyDrum1;
			randomDrumPart2 = p_comedyDrum1;
		}else if(p_comedyRandomDrumPattern < 75){
			randomDrumPart = p_comedyDrum2;
			randomDrumPart2 = p_comedyDrum2;
		}else if(p_comedyRandomDrumPattern < 87){
			randomDrumPart = p_comedyDrum3;
			randomDrumPart2 = p_comedyDrum3;
		}else if(p_comedyRandomDrumPattern < 94){
			randomDrumPart = p_comedyDrum4A;
			randomDrumPart2 = p_comedyDrum4B;
		}else if(p_comedyRandomDrumPattern < 97){
			randomDrumPart = p_comedyDrum5;
			randomDrumPart2 = p_comedyDrum5;
		}else{
			randomDrumPart = p_comedyDrum6A;
			randomDrumPart2 = p_comedyDrum6B;
		}

		switch(p_comedyIteration)
		{
			case 1:
				if(p_comedyBrassCello1 != -1 && MM_COMMON_musicAssignBuffer(p_comedyBrassCello1, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_comedyOrgan1 != -1 && MM_COMMON_musicAssignBuffer(p_comedyOrgan1, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 2:
			case 4:
				if(p_comedyBrassCello2 != -1 && MM_COMMON_musicAssignBuffer(p_comedyBrassCello2, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(randomDrumPart != -1 && MM_COMMON_musicAssignBuffer(randomDrumPart, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_comedyOrgan1 != -1 && MM_COMMON_musicAssignBuffer(p_comedyOrgan1, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 3:
				if(p_comedyBrassCello1 != -1 && MM_COMMON_musicAssignBuffer(p_comedyBrassCello1, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(randomDrumPart2 != -1 && MM_COMMON_musicAssignBuffer(randomDrumPart2, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_comedyOrgan1 != -1 && MM_COMMON_musicAssignBuffer(p_comedyOrgan1, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;

			case 5:
				if(p_comedyBrassCello3 != -1 && MM_COMMON_musicAssignBuffer(p_comedyBrassCello3, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(randomDrumPart2 != -1 && MM_COMMON_musicAssignBuffer(randomDrumPart2, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_comedyOrgan3 != -1 && MM_COMMON_musicAssignBuffer(p_comedyOrgan3, 2)) MM_COMMON_musicChannelOn(false, 2);
				break;
		};
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_comedyThemeStr()
{
	return p_comedyThemeStr;
}
