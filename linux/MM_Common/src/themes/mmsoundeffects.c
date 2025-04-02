#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static bool p_soundEffect[PLEX_LIMIT_SOUNDCHANNELS];

// static functions ---------------------------------------------------------------------------------------------------------

// A function that is the base of all sound effect functions. Can effect BOTH loop and volume.

static int64_t p_playSoundEffectBase(const MM_COMMON_SOUNDEFFECT effect, const bool loop, const double volume)
{
	const size_t bottom = PLEX_LIMIT_SOUNDCHANNELS - PLEX_LIMIT_SOUNDEFFECTS;
	const size_t bufferBottom = PLEX_LIMIT_PREBUFFERCOUNT - PLEX_LIMIT_SOUNDEFFECTS;

	int64_t buffer = -1;
	int64_t index = 0;

	bool overwrite = false;

	if(effect == MM_COMMON_SOUNDEFFECT_NONE) return -1;

	index = PLEX_LIMIT_SOUNDCHANNELS - 1;

	while((PLEX_isSoundPlaying(index) && !overwrite) || MM_COMMON_THEME_usingMusicLoop(index))
	{
		--index;

		if(index <= bottom)
		{
			if(overwrite) return -1;

			index = PLEX_LIMIT_SOUNDCHANNELS - 1;
			overwrite = true;
		}
	}

	buffer = bufferBottom + (index - bottom);

	PLEX_clearSoundBuffer(buffer);

	switch(effect)
	{
		case MM_COMMON_SOUNDEFFECT_KNOCKING:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_KNOCKING, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SHOCK:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SHOCKCUE, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SURREALHONKHONK:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SURREALHONKHONK, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_PAMENGINEREV:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_PAMENGINEREV, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_PAMENGINESTRUGGLE:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_PAMENGINESTRUGGLE, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_PAMENGINERUN:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_PAMENGINERUN, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_CRASH:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_CRASH, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SURREALGLASSCRACK:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SURREALGLASSCRACK, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_ZOOMBY:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_ZOOMBY, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_TABLESCREECH:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_TABLESCREECH, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_CLUB:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_CLUB, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_GROAN:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_GROAN, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_QUICKGROAN:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_QUICKGROAN, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SHOT:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SHOT, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_EMPTYCHAMBER, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_RELOAD:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_RELOAD, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_GULP:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_GULP, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SMALLSHOT:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SMALLSHOT, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_RAPIDSHOT:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_RAPIDSHOT, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SHOTMISS:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SHOTMISS, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_COWBOYBIRTH:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_COWBOYBIRTH, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SHOTGUNSHOT:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SHOTGUNSHOT, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_SLASH:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_SLASH, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_RAYGUN:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_RAYGUN, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_EXPLOSION:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_EXPLOSION, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_CHAINSAWCUT:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_CHAINSAWCUT, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_ARROW:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_ARROW, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_EXPLOSIONLOOP:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_EXPLOSIONLOOP, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_DOORSLAM:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_DOORSLAM, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_CRUELTWIST:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_CRUELTWIST, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_ELECTRICSHOCK:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_ELECTRICSHOCK, buffer);
		break;

		case MM_COMMON_SOUNDEFFECT_PHONE:
			PLEX_preloadSoundFileToSpecificBuffer(MM_COMMON_SOUNDPATH_PHONE, buffer);
		break;

		default: break;
	};

	if(PLEX_isSoundPlaying(index)) PLEX_soundChannelOff(index);

	if(buffer != -1 && PLEX_assignSoundBuffer(buffer, index)) PLEX_soundChannelOn(loop, index);

	PLEX_setVolume(volume, index);

	p_soundEffect[index] = true;

	return index;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

int64_t MM_COMMON_playSoundEffect(const MM_COMMON_SOUNDEFFECT effect)
{
	return p_playSoundEffectBase(effect, false, 1);
}

int64_t MM_COMMON_playSoundEffectVolume(const double volume, const MM_COMMON_SOUNDEFFECT effect)
{
	return p_playSoundEffectBase(effect, false, volume);
}

int64_t MM_COMMON_loopSoundEffect(const MM_COMMON_SOUNDEFFECT effect)
{
	return p_playSoundEffectBase(effect, true, 1);
}

int64_t MM_COMMON_loopSoundEffectVolume(const double volume, const MM_COMMON_SOUNDEFFECT effect)
{
	return p_playSoundEffectBase(effect, true, volume);
}

void MM_COMMON_stopSoundEffect(const int64_t index)
{
	if(index < 0 || index >= PLEX_LIMIT_SOUNDCHANNELS || !p_soundEffect[index]) return;

	p_soundEffect[index] = false;
	PLEX_soundChannelOff(index);
}

// setters ------------------------------------------------------------------------------------------------------------------

void MM_COMMON_setSoundEffectVolume(const double volume, const int64_t index)
{
	if(index < 0 || index > PLEX_LIMIT_SOUNDCHANNELS - 1 || !p_soundEffect[index]) return;

	PLEX_setVolume(volume, index);
}

void MM_COMMON_THEME_useSoundEffect(const size_t index)
{
	p_soundEffect[index % PLEX_LIMIT_SOUNDCHANNELS] = true;
}

void MM_COMMON_THEME_unuseSoundEffect(const size_t index)
{
	p_soundEffect[index % PLEX_LIMIT_SOUNDCHANNELS] = false;
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_SEName(const MM_COMMON_SOUNDEFFECT effect)
{
	switch(effect)
	{
		case MM_COMMON_SOUNDEFFECT_NONE: return PLEX_createString50("None");
		case MM_COMMON_SOUNDEFFECT_KNOCKING: return PLEX_createString50("Knocking");
		case MM_COMMON_SOUNDEFFECT_SHOCK: return PLEX_createString50("Shock");
		case MM_COMMON_SOUNDEFFECT_SURREALHONKHONK: return PLEX_createString50("Surreal Honk");
		case MM_COMMON_SOUNDEFFECT_PAMENGINEREV: return PLEX_createString50("Engine Rev");
		case MM_COMMON_SOUNDEFFECT_PAMENGINERUN: return PLEX_createString50("Engine Run");
		case MM_COMMON_SOUNDEFFECT_PAMENGINESTRUGGLE: return PLEX_createString50("Engine Struggle");
		case MM_COMMON_SOUNDEFFECT_CRASH: return PLEX_createString50("Crash");
		case MM_COMMON_SOUNDEFFECT_SURREALGLASSCRACK: return PLEX_createString50("Surreal Glass Crack");
		case MM_COMMON_SOUNDEFFECT_ZOOMBY: return PLEX_createString50("ZoomBy");
		case MM_COMMON_SOUNDEFFECT_TABLESCREECH: return PLEX_createString50("Table Screech");
		case MM_COMMON_SOUNDEFFECT_CLUB: return PLEX_createString50("Club");
		case MM_COMMON_SOUNDEFFECT_GROAN: return PLEX_createString50("Groan");
		case MM_COMMON_SOUNDEFFECT_QUICKGROAN: return PLEX_createString50("Quick Groan");
		case MM_COMMON_SOUNDEFFECT_SHOT: return PLEX_createString50("Shot");
		case MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER: return PLEX_createString50("Empty Chamber");
		case MM_COMMON_SOUNDEFFECT_RELOAD: return PLEX_createString50("Reload");
		case MM_COMMON_SOUNDEFFECT_GULP: return PLEX_createString50("Gulp");
		case MM_COMMON_SOUNDEFFECT_SMALLSHOT: return PLEX_createString50("Small Shot");
		case MM_COMMON_SOUNDEFFECT_RAPIDSHOT: return PLEX_createString50("Rapid Shot");
		case MM_COMMON_SOUNDEFFECT_SHOTMISS: return PLEX_createString50("Shot Miss");
		case MM_COMMON_SOUNDEFFECT_COWBOYBIRTH: return PLEX_createString50("Cowboy Birth");
		case MM_COMMON_SOUNDEFFECT_SHOTGUNSHOT: return PLEX_createString50("Shotgun");
		case MM_COMMON_SOUNDEFFECT_SLASH: return PLEX_createString50("Slash");
		case MM_COMMON_SOUNDEFFECT_RAYGUN: return PLEX_createString50("Raygun");
		case MM_COMMON_SOUNDEFFECT_EXPLOSION: return PLEX_createString50("Explosion");
		case MM_COMMON_SOUNDEFFECT_CHAINSAWCUT: return PLEX_createString50("Chainsaw");
		case MM_COMMON_SOUNDEFFECT_ARROW: return PLEX_createString50("Arrow");
		case MM_COMMON_SOUNDEFFECT_EXPLOSIONLOOP: return PLEX_createString50("Explosion Loop");
		case MM_COMMON_SOUNDEFFECT_DOORSLAM: return PLEX_createString50("Doorslam");
		case MM_COMMON_SOUNDEFFECT_CRUELTWIST: return PLEX_createString50("Cruel Twist");
		case MM_COMMON_SOUNDEFFECT_ELECTRICSHOCK: return PLEX_createString50("Electric Shock");
		case MM_COMMON_SOUNDEFFECT_PHONE: return PLEX_createString50("Phone");
		case MM_COMMON_SOUNDEFFECT_LAST: return PLEX_createString50("Last");
	};

	return PLEX_blankString50();
}

bool MM_COMMON_THEME_usingSoundEffect(const size_t index)
{
	return p_soundEffect[index % PLEX_LIMIT_SOUNDCHANNELS];
}
