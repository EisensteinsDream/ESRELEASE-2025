#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_FAKESTRING_50 p_noThemeStr;
static PLEX_FAKESTRING_50 p_lastThemeStr;

static MM_COMMON_THEMEID p_themeID = MM_COMMON_THEMEID_NONE;

static bool p_musicLoop[PLEX_LIMIT_SOUNDCHANNELS];
static bool p_musicBuffers[PLEX_LIMIT_PREBUFFERCOUNT];

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_playTheme(const MM_COMMON_THEMEID themeID)
{
	if(themeID == p_themeID) return;

	MM_COMMON_clearTheme();

	switch(themeID)
	{
		case MM_COMMON_THEMEID_NONE: break;
		case MM_COMMON_THEMEID_MAIN: MM_COMMON_playThemeMain(); break;
		case MM_COMMON_THEMEID_EXTRAPLOCAN: MM_COMMON_THEME_EXTRAP_playTheme(); break;
		case MM_COMMON_THEMEID_NEWSROOM: MM_COMMON_THEME_NEWSROOM_playTheme(); break;
		case MM_COMMON_THEMEID_COMEDY: MM_COMMON_THEME_COMEDY_playTheme(); break;
		case MM_COMMON_THEMEID_PANIC: MM_COMMON_THEME_PANIC_playTheme(); break;
		case MM_COMMON_THEMEID_DARKCITY: MM_COMMON_THEME_DARKCITY_playTheme(); break;
		case MM_COMMON_THEMEID_PAMALEANA: MM_COMMON_THEME_PAMALEANA_playTheme(); break;
		case MM_COMMON_THEMEID_SUSPENSE: MM_COMMON_THEME_SUSPENSE_playTheme(); break;
		case MM_COMMON_THEMEID_DAYTODAY: MM_COMMON_THEME_DAYTODAY_playTheme(); break;
		case MM_COMMON_THEMEID_DREAM: MM_COMMON_THEME_DREAM_playTheme(); break;
		case MM_COMMON_THEMEID_DESERTWINDS: MM_COMMON_THEME_DESERTWINDS_playTheme(); break;
		case MM_COMMON_THEMEID_DESERTTOWN: MM_COMMON_THEME_DESERTTOWN_playTheme(); break;
		case MM_COMMON_THEMEID_AGGRESSION: MM_COMMON_THEME_AGGRESSION_playTheme(); break;
		case MM_COMMON_THEMEID_WORKDAY: MM_COMMON_THEME_WORKDAY_playTheme(); break;
		case MM_COMMON_THEMEID_FEAR: MM_COMMON_THEME_FEAR_playTheme(); break;
		case MM_COMMON_THEMEID_PUNK: MM_COMMON_THEME_PUNK_playTheme(); break;
		case MM_COMMON_THEMEID_METAL: MM_COMMON_THEME_METAL_playTheme(); break;
		case MM_COMMON_THEMEID_STRIFE: MM_COMMON_THEME_STRIFE_playTheme(); break;
		case MM_COMMON_THEMEID_LAST: break;
	}

	p_themeID = themeID;
}

void MM_COMMON_musicChannelOnInt(const bool loop, const size_t index, const size_t errorline, const char* const errorfile)
{
	MM_COMMON_THEME_useMusicLoop(index);
	MM_COMMON_THEME_unuseSoundEffect(index);

	if(PLEX_isSoundPlaying(index)) return;

	// do not stop current sound playing here if it is //

	PLEX_soundChannelOnInt(loop, index, errorline, errorfile);
}

void MM_COMMON_musicChannelOff(const size_t index)
{
	MM_COMMON_THEME_unuseMusicLoop(index);
	MM_COMMON_THEME_unuseSoundEffect(index);

	PLEX_soundChannelOff(index);
}

bool MM_COMMON_musicAssignBuffer(const size_t buffer, const size_t index)
{
	if(PLEX_isSoundPlaying(index)) MM_COMMON_musicChannelOff(index);

	if(PLEX_assignSoundBuffer(buffer, index))
	{
		MM_COMMON_THEME_useMusicLoop(index);
		MM_COMMON_THEME_unuseSoundEffect(index);
		return true;
	}

	return false;
}

int64_t MM_COMMON_preloadMusicFileToSpecificBuffer(const char* const path, const size_t index)
{
	if(!PLEX_preloadSoundFileToSpecificBuffer(path, index))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_BADSTYLE, MM_COMMON_THEME_ERRORMESS_ONPRELOADSPECIFIC, path);
		return -1;
	}

	MM_COMMON_THEME_useMusicBuffer(index);

	return index;
}

int64_t MM_COMMON_preloadMusicFile(const char* const path)
{
	const size_t index = PLEX_preloadSoundFile(path);

	if(index == -1)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_BADSTYLE, MM_COMMON_THEME_ERRORMESS_ONPRELOAD, path);
		return -1;
	}

	if(index >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, MM_COMMON_THEME_ERRORMESS_ONPRELOAD, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER);
		return -1;
	}

	MM_COMMON_THEME_useMusicBuffer(index);

	return index;
}

void MM_COMMON_clearTheme()
{
	for(size_t ze = 0; ze < PLEX_LIMIT_SOUNDCHANNELS; ++ze)
	{
		if(PLEX_isSoundPlaying(ze)) PLEX_soundChannelOff(ze);

		MM_COMMON_THEME_unuseMusicLoop(ze);
		MM_COMMON_THEME_unuseSoundEffect(ze);
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_PREBUFFERCOUNT; ++ze){ MM_COMMON_THEME_unuseMusicBuffer(ze); }

	PLEX_clearSoundPreloads();
}

void MM_COMMON_THEME_useMusicLoop(const size_t index)
{
	p_musicLoop[index % PLEX_LIMIT_SOUNDCHANNELS] = true;
}

void MM_COMMON_THEME_useMusicBuffer(const size_t index)
{
	p_musicBuffers[index % PLEX_LIMIT_PREBUFFERCOUNT] = true;
}

void MM_COMMON_THEME_unuseMusicLoop(const size_t index)
{
	p_musicLoop[index % PLEX_LIMIT_SOUNDCHANNELS] = false;
}

void MM_COMMON_THEME_unuseMusicBuffer(const size_t index)
{
	p_musicBuffers[index % PLEX_LIMIT_PREBUFFERCOUNT] = false;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

void MM_COMMON_startTheme()
{
	p_noThemeStr = PLEX_createString50("No Theme");

	MM_COMMON_THEME_MAIN_start();
	MM_COMMON_THEME_EXTRAP_start();
	MM_COMMON_THEME_NEWSROOM_start();
	MM_COMMON_THEME_COMEDY_start();
	MM_COMMON_THEME_PANIC_start();
	MM_COMMON_THEME_DARKCITY_start();
	MM_COMMON_THEME_PAMALEANA_start();
	MM_COMMON_THEME_DAYTODAY_start();
	MM_COMMON_THEME_SUSPENSE_start();
	MM_COMMON_THEME_DREAM_start();
	MM_COMMON_THEME_DESERTWINDS_start();
	MM_COMMON_THEME_DESERTTOWN_start();
	MM_COMMON_THEME_AGGRESSION_start();
	MM_COMMON_THEME_WORKDAY_start();
	MM_COMMON_THEME_FEAR_start();
	MM_COMMON_THEME_PUNK_start();
	MM_COMMON_THEME_METAL_start();
	MM_COMMON_THEME_STRIFE_start();

	p_lastThemeStr = PLEX_createString50("Last");
}

void MM_COMMON_updateTheme()
{
	if(!PLEX_getUniversalThemeStopSignal())
	{
		const MM_COMMON_THEMEID themeID = (MM_COMMON_THEMEID)PLEX_getUniversalThemeCueID();

		if(themeID != MM_COMMON_THEMEID_NONE) MM_COMMON_playTheme(themeID);
	}else MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);

	MM_COMMON_playSoundEffect((MM_COMMON_SOUNDEFFECT)PLEX_getUniversalSoundEffect()); // ignores sound effect none (ie. the number 0), keep AFTER the universal theme check

	switch(p_themeID)
	{
		case MM_COMMON_THEMEID_MAIN: MM_COMMON_updateMainThemeVoice(); break;
		case MM_COMMON_THEMEID_EXTRAPLOCAN: MM_COMMON_THEME_EXTRAP_updateTheme(); break;
		case MM_COMMON_THEMEID_PANIC: MM_COMMON_THEME_PANIC_updateTheme(); break;
		case MM_COMMON_THEMEID_COMEDY: MM_COMMON_THEME_COMEDY_updateTheme(); break;
		case MM_COMMON_THEMEID_DARKCITY: MM_COMMON_THEME_DARKCITY_updateTheme(); break;
		case MM_COMMON_THEMEID_PAMALEANA: MM_COMMON_THEME_PAMALEANA_updateTheme(); break;
		case MM_COMMON_THEMEID_SUSPENSE: MM_COMMON_THEME_SUSPENSE_updateTheme(); break;
		case MM_COMMON_THEMEID_DAYTODAY: MM_COMMON_THEME_DAYTODAY_updateTheme(); break;
		case MM_COMMON_THEMEID_DREAM: MM_COMMON_THEME_DREAM_updateTheme(); break;
		case MM_COMMON_THEMEID_DESERTWINDS: MM_COMMON_THEME_DESERTWINDS_updateTheme(PLEX_getGameTime()); break;
		case MM_COMMON_THEMEID_DESERTTOWN: MM_COMMON_THEME_DESERTTOWN_updateTheme(); break;
		case MM_COMMON_THEMEID_AGGRESSION: MM_COMMON_THEME_AGGRESSION_updateTheme(); break;
		case MM_COMMON_THEMEID_WORKDAY: MM_COMMON_THEME_WORKDAY_updateTheme(); break;
		case MM_COMMON_THEMEID_FEAR: MM_COMMON_THEME_FEAR_updateTheme(); break;
		case MM_COMMON_THEMEID_PUNK: MM_COMMON_THEME_PUNK_updateTheme(); break;
		case MM_COMMON_THEMEID_METAL: MM_COMMON_THEME_METAL_updateTheme(); break;
		case MM_COMMON_THEMEID_STRIFE: MM_COMMON_THEME_STRIFE_updateTheme(); break;

		default: break; // < some themes do not need to be updated
	};
}

void MM_COMMON_endTheme()
{

}

// getters ------------------------------------------------------------------------------------------------------------------

MM_COMMON_THEMEID MM_COMMON_themeByName(const char* const name)
{
	PLEX_FAKESTRING_50 nameStr;

	if(name == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, MM_COMMON_THEME_ERRORMESS_ONTHEMEBYNAME, MM_COMMON_THEME_ERRORMESS_THEMENAME);
		return MM_COMMON_THEMEID_LAST;
	}

	if(name[0] == '\0')
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, MM_COMMON_THEME_ERRORMESS_ONTHEMEBYNAME, MM_COMMON_THEME_ERRORMESS_THEMENAME);
		return MM_COMMON_THEMEID_LAST;
	}

	nameStr = PLEX_createString50(name);

	if(PLEX_compStrings50(nameStr, p_noThemeStr, true)) return MM_COMMON_THEMEID_NONE;

	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_mainThemeStr(), true)) return MM_COMMON_THEMEID_MAIN;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_extrapThemeStr(), true)) return MM_COMMON_THEMEID_EXTRAPLOCAN;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_newsroomThemeStr(), true)) return MM_COMMON_THEMEID_NEWSROOM;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_comedyThemeStr(), true)) return MM_COMMON_THEMEID_COMEDY;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_panicThemeStr(), true)) return MM_COMMON_THEMEID_PANIC;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_darkcityThemeStr(), true)) return MM_COMMON_THEMEID_DARKCITY;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_pamaleanaThemeStr(), true)) return MM_COMMON_THEMEID_PAMALEANA;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_suspenseThemeStr(), true)) return MM_COMMON_THEMEID_SUSPENSE;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_dayToDayThemeStr(), true)) return MM_COMMON_THEMEID_DAYTODAY;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_dreamThemeStr(), true)) return MM_COMMON_THEMEID_DREAM;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_desertWindsThemeStr(), true)) return MM_COMMON_THEMEID_DESERTWINDS;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_desertTownThemeStr(), true)) return MM_COMMON_THEMEID_DESERTTOWN;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_aggressionThemeStr(), true)) return MM_COMMON_THEMEID_AGGRESSION;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_workdayThemeStr(), true)) return MM_COMMON_THEMEID_WORKDAY;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_fearThemeStr(), true)) return MM_COMMON_THEMEID_FEAR;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_punkThemeStr(), true)) return MM_COMMON_THEMEID_PUNK;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_metalThemeStr(), true)) return MM_COMMON_THEMEID_METAL;
	if(PLEX_compStrings50(nameStr, MM_COMMON_THEME_strifeThemeStr(), true)) return MM_COMMON_THEMEID_STRIFE;
	return MM_COMMON_THEMEID_LAST;
}

PLEX_FAKESTRING_50 MM_COMMON_themeName(const MM_COMMON_THEMEID themeID)
{
	switch(themeID)
	{
		case MM_COMMON_THEMEID_NONE: return p_noThemeStr;

		case MM_COMMON_THEMEID_MAIN: return MM_COMMON_THEME_mainThemeStr();
		case MM_COMMON_THEMEID_EXTRAPLOCAN: return MM_COMMON_THEME_extrapThemeStr();
		case MM_COMMON_THEMEID_NEWSROOM: return MM_COMMON_THEME_newsroomThemeStr();
		case MM_COMMON_THEMEID_COMEDY: return MM_COMMON_THEME_comedyThemeStr();
		case MM_COMMON_THEMEID_PANIC: return MM_COMMON_THEME_panicThemeStr();
		case MM_COMMON_THEMEID_DARKCITY: return MM_COMMON_THEME_darkcityThemeStr();
		case MM_COMMON_THEMEID_PAMALEANA: return MM_COMMON_THEME_pamaleanaThemeStr();
		case MM_COMMON_THEMEID_SUSPENSE: return MM_COMMON_THEME_suspenseThemeStr();
		case MM_COMMON_THEMEID_DAYTODAY: return MM_COMMON_THEME_dayToDayThemeStr();
		case MM_COMMON_THEMEID_DREAM: return MM_COMMON_THEME_dreamThemeStr();
		case MM_COMMON_THEMEID_DESERTWINDS: return MM_COMMON_THEME_desertWindsThemeStr();
		case MM_COMMON_THEMEID_DESERTTOWN: return MM_COMMON_THEME_desertTownThemeStr();
		case MM_COMMON_THEMEID_AGGRESSION: return MM_COMMON_THEME_aggressionThemeStr();
		case MM_COMMON_THEMEID_WORKDAY: return MM_COMMON_THEME_workdayThemeStr();
		case MM_COMMON_THEMEID_FEAR: return MM_COMMON_THEME_fearThemeStr();
		case MM_COMMON_THEMEID_PUNK: return MM_COMMON_THEME_punkThemeStr();
		case MM_COMMON_THEMEID_METAL: return MM_COMMON_THEME_metalThemeStr();
		case MM_COMMON_THEMEID_STRIFE: return MM_COMMON_THEME_strifeThemeStr();
		case MM_COMMON_THEMEID_LAST: return p_lastThemeStr;
	}

	return PLEX_blankString50();
}

MM_COMMON_THEMEID MM_COMMON_getTheme(){ return p_themeID; }

bool MM_COMMON_THEME_usingMusicLoop(const size_t index)
{
	return p_musicLoop[index % PLEX_LIMIT_SOUNDCHANNELS];
}

bool MM_COMMON_THEME_usingMusicBuffer(const size_t index)
{
	return p_musicBuffers[index % PLEX_LIMIT_PREBUFFERCOUNT];
}
