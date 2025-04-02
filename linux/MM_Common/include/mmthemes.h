#ifndef MM_COMMON_THEMES_H
#define MM_COMMON_THEMES_H

#include "mmcommon.h"

// This subsystem manages all of the themes for MM Common based projects. The themes in these projects are algorithmic so each one has it's own codebase.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. MM_COMMON_start, MM_COMMON_update, and MM_COMMON_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const bool loop, const size_t index)

#define MM_COMMON_musicChannelOn(loop, index) MM_COMMON_musicChannelOnInt(loop, index, __LINE__, __FILE__) // < to ensure line specificity if there's a hook error in sound.c

// structs, unions, enums ---------------------------------------------------------------------------------------------------

typedef enum
{
	MM_COMMON_THEMEID_NONE = 0,
	MM_COMMON_THEMEID_MAIN = 1,
	MM_COMMON_THEMEID_EXTRAPLOCAN = 2,
	MM_COMMON_THEMEID_NEWSROOM = 3,
	MM_COMMON_THEMEID_COMEDY = 4,
	MM_COMMON_THEMEID_PANIC = 5,
	MM_COMMON_THEMEID_DARKCITY = 6,
	MM_COMMON_THEMEID_PAMALEANA = 7,
	MM_COMMON_THEMEID_SUSPENSE = 8,
	MM_COMMON_THEMEID_DAYTODAY = 9,
	MM_COMMON_THEMEID_DREAM = 10,
	MM_COMMON_THEMEID_DESERTWINDS = 11,
	MM_COMMON_THEMEID_DESERTTOWN = 12,
	MM_COMMON_THEMEID_AGGRESSION = 13,
	MM_COMMON_THEMEID_WORKDAY = 14,
	MM_COMMON_THEMEID_FEAR = 15,
	MM_COMMON_THEMEID_PUNK = 16,
	MM_COMMON_THEMEID_METAL = 17,
	MM_COMMON_THEMEID_STRIFE = 18,
	MM_COMMON_THEMEID_LAST = 19
} MM_COMMON_THEMEID;

typedef enum
{
	MM_COMMON_SOUNDEFFECT_NONE = 0,
	MM_COMMON_SOUNDEFFECT_KNOCKING = 1,
	MM_COMMON_SOUNDEFFECT_SHOCK = 2,
	MM_COMMON_SOUNDEFFECT_SURREALHONKHONK = 3,
	MM_COMMON_SOUNDEFFECT_PAMENGINEREV = 4,
	MM_COMMON_SOUNDEFFECT_PAMENGINERUN = 5,
	MM_COMMON_SOUNDEFFECT_PAMENGINESTRUGGLE = 6,
	MM_COMMON_SOUNDEFFECT_CRASH = 7,
	MM_COMMON_SOUNDEFFECT_SURREALGLASSCRACK = 8,
	MM_COMMON_SOUNDEFFECT_ZOOMBY = 9,
	MM_COMMON_SOUNDEFFECT_TABLESCREECH = 10,
	MM_COMMON_SOUNDEFFECT_CLUB = 11,
	MM_COMMON_SOUNDEFFECT_GROAN = 12,
	MM_COMMON_SOUNDEFFECT_QUICKGROAN = 13,
	MM_COMMON_SOUNDEFFECT_SHOT = 14,
	MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER = 15,
	MM_COMMON_SOUNDEFFECT_RELOAD = 16,
	MM_COMMON_SOUNDEFFECT_GULP = 17,
	MM_COMMON_SOUNDEFFECT_SMALLSHOT = 18,
	MM_COMMON_SOUNDEFFECT_RAPIDSHOT = 19,
	MM_COMMON_SOUNDEFFECT_SHOTMISS = 20,
	MM_COMMON_SOUNDEFFECT_COWBOYBIRTH = 21,
	MM_COMMON_SOUNDEFFECT_SHOTGUNSHOT = 22,
	MM_COMMON_SOUNDEFFECT_SLASH = 23,
	MM_COMMON_SOUNDEFFECT_RAYGUN = 24,
	MM_COMMON_SOUNDEFFECT_EXPLOSION = 25,
	MM_COMMON_SOUNDEFFECT_CHAINSAWCUT = 26,
	MM_COMMON_SOUNDEFFECT_ARROW = 27,
	MM_COMMON_SOUNDEFFECT_EXPLOSIONLOOP = 28,
	MM_COMMON_SOUNDEFFECT_DOORSLAM = 29,
	MM_COMMON_SOUNDEFFECT_CRUELTWIST = 30,
	MM_COMMON_SOUNDEFFECT_ELECTRICSHOCK = 31,
	MM_COMMON_SOUNDEFFECT_PHONE = 32,
	MM_COMMON_SOUNDEFFECT_LAST = 33
} MM_COMMON_SOUNDEFFECT;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// MAIN THEME

	extern void MM_COMMON_reloadMainTheme(const size_t voiceIndex, const size_t sampleIndex);

	// A function that the MM theme unit uses to start the 'Main' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_MAIN)'

	extern void MM_COMMON_THEME_MAIN_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_updateMainThemeVoice();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_playThemeMain();

	// A function that returns the name of the 'Main' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_mainThemeStr();

	// EXTRAPLOCAN THEME

	// A function that the MM theme unit uses to start the 'Extraplocan' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_EXTRAPLOCAN)'

	extern void MM_COMMON_THEME_EXTRAP_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_EXTRAP_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_EXTRAP_updateTheme();

	// A function that returns the name of the 'Extraplocan' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_extrapThemeStr();

	// NEWSROOM THEME

	// A function that the MM theme unit uses to start the 'Newsroom' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_NEWSROOM)'

	extern void MM_COMMON_THEME_NEWSROOM_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_NEWSROOM_playTheme();

	// A function that returns the name of the 'Newsroom' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_newsroomThemeStr();

	// COMEDY THEME

	// A function that the MM theme unit uses to start the 'Comedy' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_COMEDY)'

	extern void MM_COMMON_THEME_COMEDY_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_COMEDY_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_COMEDY_updateTheme();

	// A function that returns the name of the 'Comedy' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_comedyThemeStr();

	// PANIC

	// A function that the MM theme unit uses to start the 'Panic' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_PANIC)'

	extern void MM_COMMON_THEME_PANIC_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PANIC_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PANIC_updateTheme();

	// A function that returns the name of the 'Panic' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_panicThemeStr();

	// DARK CITY

	// A function that the MM theme unit uses to start the 'Dark City' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_DARKCITY)'

	extern void MM_COMMON_THEME_DARKCITY_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DARKCITY_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DARKCITY_updateTheme();

	// A function that returns the name of the 'Dark City' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_darkcityThemeStr();

	// PAMALEANA

	// A function that the MM theme unit uses to start the 'Pamaleana' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_PAMALEANA)'

	extern void MM_COMMON_THEME_PAMALEANA_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PAMALEANA_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PAMALEANA_updateTheme();

	// A function that returns the name of the 'Pamaleana' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_pamaleanaThemeStr();

	// SUSPENSE

	// A function that the MM theme unit uses to start the 'Suspense' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_SUSPENSE)'

	extern void MM_COMMON_THEME_SUSPENSE_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_SUSPENSE_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_SUSPENSE_updateTheme();

	// A function that returns the name of the 'Suspense' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_suspenseThemeStr();

	// DAY-TO-DAY

	// A function that the MM theme unit uses to start the 'Day-To-Day' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_DAYTODAY)'

	extern void MM_COMMON_THEME_DAYTODAY_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DAYTODAY_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DAYTODAY_updateTheme();

	// A function that returns the name of the 'Day-To-Day' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_dayToDayThemeStr();

	// DREAM

	// A function that the MM theme unit uses to start the 'Dream' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_DREAM)'

	extern void MM_COMMON_THEME_DREAM_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DREAM_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DREAM_updateTheme();

	// A function that returns the name of the 'Dream' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_dreamThemeStr();

	// DESERT WINDS

	// A function that the MM theme unit uses to start the 'Desert Winds' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_DESERTWINDS)'

	extern void MM_COMMON_THEME_DESERTWINDS_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DESERTWINDS_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DESERTWINDS_updateTheme(const uint64_t time);

	// A function that returns the name of the 'Desert Winds' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_desertWindsThemeStr();

	// DESERT TOWN

	// A function that the MM theme unit uses to start the 'Desert Town' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_DESERTTOWN)'

	extern void MM_COMMON_THEME_DESERTTOWN_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DESERTTOWN_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_DESERTTOWN_updateTheme();

	// A function that returns the name of the 'Desert Town' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_desertTownThemeStr();

	// AGGRESSION

	// A function that the MM theme unit uses to start the 'Aggression' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_AGGRESSION)'

	extern void MM_COMMON_THEME_AGGRESSION_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_AGGRESSION_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_AGGRESSION_updateTheme();

	// A function that returns the name of the 'Aggression' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_aggressionThemeStr();

	// WORKDAY

	// A function that the MM theme unit uses to start the 'Workday' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_WORKDAY)'

	extern void MM_COMMON_THEME_WORKDAY_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_WORKDAY_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_WORKDAY_updateTheme();

	// A function that returns the name of the 'Workday' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_workdayThemeStr();

	// FEAR

	// A function that the MM theme unit uses to start the 'Fear' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_FEAR)'

	extern void MM_COMMON_THEME_FEAR_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_FEAR_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_FEAR_updateTheme();

	// A function that returns the name of the 'Fear' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_fearThemeStr();

	// PUNK

	// A function that the MM theme unit uses to start the 'Punk' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_PUNK)'

	extern void MM_COMMON_THEME_PUNK_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PUNK_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_PUNK_updateTheme();

	// A function that changes the volume by percentage of the punk theme if it's playing. (0.0-1.0).

	extern void MM_COMMON_punkThemeVolume(const double volume);

	// A function that returns the name of the 'Punk' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_punkThemeStr();

	// METAL

	// A function that the MM theme unit uses to start the 'Metal' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_METAL)'

	extern void MM_COMMON_THEME_METAL_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_METAL_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_METAL_updateTheme();

	// A function that returns the name of the 'Metal' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_metalThemeStr();

	// STRIFE

	// A function that the MM theme unit uses to start the 'Strife' theme. You never need to call this manually. In fact, calling it manually will not do anything useful. To actually play this theme you would call 'MM_COMMON_playTheme(MM_COMMON_THEMEID_STRIFE)'

	extern void MM_COMMON_THEME_STRIFE_start();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_STRIFE_playTheme();

	// another internal function. You never should call this manually.

	extern void MM_COMMON_THEME_STRIFE_updateTheme();

	// A function that returns the name of the 'Strife' theme as a string.

	extern PLEX_FAKESTRING_50 MM_COMMON_THEME_strifeThemeStr();

	// SOUND EFFECT

	// plays the sound effect by it's 'MM_COMMON_SOUNDEFFECT' enumerator.

	extern int64_t MM_COMMON_playSoundEffect(const MM_COMMON_SOUNDEFFECT effect);

	// plays the sound effect by it's 'MM_COMMON_SOUNDEFFECT' enumerator. But also gates volume by percentage (0.0-1.0).

	extern int64_t MM_COMMON_playSoundEffectVolume(const double volume, const MM_COMMON_SOUNDEFFECT effect);

	// loops the sound effect by it's 'MM_COMMON_SOUNDEFFECT' enumerator. Returns an index to the looping sound. Returns -1 on failure.

	extern int64_t MM_COMMON_loopSoundEffect(const MM_COMMON_SOUNDEFFECT effect);

	// loops the sound effect by it's 'MM_COMMON_SOUNDEFFECT' enumerator. Returns an index to the looping sound. Returns -1 on failure. But also gates volume by percentage (0.0-1.0).

	extern int64_t MM_COMMON_loopSoundEffectVolume(const double volume, const MM_COMMON_SOUNDEFFECT effect);

	// stops the looping sound effect at index.

	extern void MM_COMMON_stopSoundEffect(const int64_t index);

	// gates the looping sound effect at index by volume.

	extern void MM_COMMON_setSoundEffectVolume(const double volume, const int64_t index);

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_useSoundEffect(const size_t index);

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_unuseSoundEffect(const size_t index);

	// returns a string with the name of a sound effect by enumerator.

	extern PLEX_FAKESTRING_50 MM_COMMON_SEName(const MM_COMMON_SOUNDEFFECT effect);

	// returns true if sound effect at index is being used.

	extern bool MM_COMMON_THEME_usingSoundEffect(const size_t index);

	// UNIVERSAL FUNCTIONS

	// Most important function. Here's how you get a theme played. Passing in a 'MM_COMMON_THEMEID_NONE' will also stop the current theme entirely.

	extern void MM_COMMON_playTheme(const MM_COMMON_THEMEID themeID);

	// internal function. No need to call manually.

	extern void MM_COMMON_musicChannelOnInt(const bool loop, const size_t index, const size_t errorline, const char* const errorfile);

	// internal function. No need to call manually.

	extern void MM_COMMON_musicChannelOff(const size_t index);

	// internal function. No need to call manually.

	extern bool MM_COMMON_musicAssignBuffer(const size_t buffer, const size_t index);

	// internal function. No need to call manually.

	extern int64_t MM_COMMON_preloadMusicFileToSpecificBuffer(const char* const path, const size_t index);

	// internal function. No need to call manually.

	extern int64_t MM_COMMON_preloadMusicFile(const char* const path);

	// internal function. No need to call manually.

	extern void MM_COMMON_clearTheme();

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_useMusicLoop(const size_t index);

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_useMusicBuffer(const size_t index);

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_unuseMusicLoop(const size_t index);

	// internal function. No need to call manually.

	extern void MM_COMMON_THEME_unuseMusicBuffer(const size_t index);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// Starts MM Theme system. You really don't need to call this since 'MM_COMMON_start' already does.

	extern void MM_COMMON_startTheme();

	// Updates MM Theme system. You really don't need to call this since 'MM_COMMON_update' already does.

	extern void MM_COMMON_updateTheme();

	// End MM Theme system. You really don't need to call this since 'MM_COMMON_end' already does.

	extern void MM_COMMON_endTheme();

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the theme by name passed in as a string. Returns 'MM_COMMON_THEMEID_LAST' on failure.

	extern MM_COMMON_THEMEID MM_COMMON_themeByName(const char* const name);

	// returns the string name of the theme ID passed in by enumerator.

	extern PLEX_FAKESTRING_50 MM_COMMON_themeName(const MM_COMMON_THEMEID themeID);

	// returns the ID of the theme currently running

	extern MM_COMMON_THEMEID MM_COMMON_getTheme();

	// internal function. No need to call manually.

	extern bool MM_COMMON_THEME_usingMusicLoop(const size_t index);

	// internal function. No need to call manually.

	extern bool MM_COMMON_THEME_usingMusicBuffer(const size_t index);
#ifdef __cplusplus
}
#endif

#endif
