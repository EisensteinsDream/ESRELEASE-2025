#include "sound/sound.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PaStream* stream;
	size_t needle, length, id, iterations, type, channelCount;
	int64_t buffer;
	bool on, loop;
	double volume, sampleRate;
	bool complexPattern[8];
	size_t complexPatternCount;
	void* playBuffer;
	size_t errorline;
	const char* errorfile;
} PLEX_SOUNDCHANNEL;

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_SOUNDCHANNEL p_soundChannel[PLEX_LIMIT_SOUNDCHANNELS];

static PLEX_EXPANDARRAY* p_preloadBuffers[PLEX_LIMIT_PREBUFFERCOUNT];
static size_t p_preloadBufferFrameCount[PLEX_LIMIT_PREBUFFERCOUNT], p_preloadBufferSize[PLEX_LIMIT_PREBUFFERCOUNT], p_preloadBufferType[PLEX_LIMIT_PREBUFFERCOUNT], p_preloadBufferChannelCount[PLEX_LIMIT_PREBUFFERCOUNT];
static double p_preloadBufferSampleRate[PLEX_LIMIT_PREBUFFERCOUNT];

static size_t p_preloadBufferCount = 0;

static size_t p_universalThemeCueID = 0;
static size_t p_universalSoundEffect = 0;
static bool p_universalThemeStopSignal = false;

static bool p_running = false;

static bool p_disabled = false;

// static functions ---------------------------------------------------------------------------------------------------------

// checks to see if an error is a port audio error or not. It signals a plex error if it is.

static bool p_checkError(const PLEX_ERROR_SEVERITY severity, const PaError error, const size_t errorline, const char* const errorfile)
{
	if(error != paNoError)
	{
		PLEX_errorPortAudioInt(severity, error, errorline, errorfile);
		return false;
	}

	return true;
}

// restarts a sound channel's contained data

static void p_restartChannelInfo(PLEX_SOUNDCHANNEL* channel)
{
	channel->needle = 0;
	channel->loop = false;
	channel->iterations = 0;

	// do not reset volume here

	channel->complexPatternCount = 0;

	channel->on = false;
}

// kills a sound stream

static void p_killChannelStream(PLEX_SOUNDCHANNEL* channel, const size_t errorline, const char* const errorfile)
{
	if(channel->stream != NULL)
	{
		#if(PLEX_CORE_OS == PLEX_CORE_WINDOWS)
			Pa_AbortStream(channel->stream);
		#else
			Pa_CloseStream(channel->stream);
			Pa_AbortStream(channel->stream);
		#endif

		channel->stream = NULL;
	}
}

// returns the size of a filetype (all non-wav's are 4 because they're converted to floats)

static size_t p_fileTypeSize(const size_t type) // < keep above hook
{
	switch(type)
	{
		case SF_FORMAT_PCM_S8: return 1;
		case SF_FORMAT_PCM_16: return 2;
		case SF_FORMAT_PCM_24: return 3;
		case SF_FORMAT_PCM_32: return 4;
		case SF_FORMAT_PCM_U8: return 1;

		case SF_FORMAT_FLOAT: return 4;
		case SF_FORMAT_DOUBLE: return 8;

		default: return 0;
	};

	return 0;
}

// the sound hook function that port audio streams take

static int p_hook(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
	PLEX_SOUNDCHANNEL* const me = (PLEX_SOUNDCHANNEL*)userData;

	size_t typeSize = p_fileTypeSize(me->type);

	int8_t* iOut = (int8_t*)output;

	for(size_t ze = 0; ze < frameCount; ++ze)
	{
		const size_t index = ze * typeSize * me->channelCount;
		const size_t nindex = me->needle * typeSize * me->channelCount;

		#if(PLEX_CORE_OS == PLEX_CORE_WINDOWS)
			if(!me->on)
			{
				me->iterations = 0;
				memset(iOut + index, 0, typeSize);
				continue;
			}
		#endif

		if(me->buffer < 0)
		{
			PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADBUFFERSOUNDHOOK, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_GENERIC_UNDERLIMIT, me->errorline, me->errorfile);
			continue;
		}

		if(me->buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
		{
			PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADBUFFERSOUNDHOOK, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_GENERIC_OVERLIMIT, me->errorline, me->errorfile);
			continue;
		}

		if(me->needle >= me->length || !me->length)
		{
			if(me->length) ++me->iterations; // make sure this happens before it tries to continue

			if(me->loop){ me->needle = 0; }
			else
			{
				memset(iOut + index, 0, typeSize);
				me->on = false;
				continue;
			}
		}

		if((me->complexPatternCount && !me->complexPattern[me->iterations % me->complexPatternCount]))
		{
			memset(iOut + index, 0, typeSize);
			++me->needle;
			continue;
		}

		if(me->needle < me->length)
		{
			if(me->playBuffer == NULL)
			{
				PLEX_error2(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONHOOK, PLEX_ERRORMESS_SOUND_BUFFER);
				break;
			}

			for(size_t uh = 0; uh < me->channelCount; ++uh)
			{
				const size_t frameAdjust = uh * typeSize; // < do not multiply by channel count

				int8_t* frame = 0;

				int8_t mod8 = 0;
				int16_t mod16 = 0;
				int32_t mod24 = 0;
				int32_t mod32 = 0;
				uint8_t modu8 = 0;
				float modf = 0;
				double mod = 0;

				frame = (int8_t*)me->playBuffer + nindex + frameAdjust;

				switch(me->type)
				{
					case SF_FORMAT_PCM_S8: mod = *frame; break;
					case SF_FORMAT_PCM_16: mod = *(int16_t*)frame; break;
					case SF_FORMAT_PCM_24: memcpy(&mod24, frame, 3); mod = mod24; break;
					case SF_FORMAT_PCM_32: mod = *(int32_t*)frame; break;
					case SF_FORMAT_PCM_U8: mod = *frame; break;

					case SF_FORMAT_FLOAT: mod = *(float*)frame; break;
					case SF_FORMAT_DOUBLE: mod = *(double*)frame; break;
				};

				if(me->volume < 1) mod *= me->volume;

				// apply effects here (future vesion)

				// absolutely DO NOT use me->needle here
				switch(me->type)
				{
					case SF_FORMAT_PCM_S8: mod8 = mod; memcpy(iOut + index + frameAdjust, (char*)&mod8, sizeof(mod8)); break;
					case SF_FORMAT_PCM_16: mod16 = mod; memcpy(iOut + index + frameAdjust, (char*)&mod16, sizeof(mod16)); break;
					case SF_FORMAT_PCM_24: mod24 = mod; memcpy(iOut + index + frameAdjust, (char*)&mod24, 3); break;
					case SF_FORMAT_PCM_32: mod32 = mod; memcpy(iOut + index + frameAdjust, (char*)&mod32, sizeof(mod32)); break;
					case SF_FORMAT_PCM_U8: modu8 = mod; memcpy(iOut + index + frameAdjust, (char*)&modu8, sizeof(modu8)); break;

					case SF_FORMAT_FLOAT: modf = mod; memcpy(iOut + index + frameAdjust, (char*)&modf, sizeof(modf)); break;
					case SF_FORMAT_DOUBLE: memcpy(iOut + index + frameAdjust, (char*)&mod, sizeof(mod)); break;
				};
			}

			++me->needle;
		}
	}

	return 0;
}

// gets a libsnd sound file

static SNDFILE* p_getFile(const char* const fileloc, SF_INFO* info)
{
	return sf_open(fileloc, SFM_READ, info);
}

// gets the length of a buffer from it's bytesize, frames, and the number of channels in it's info

static size_t p_adjustedBufferLen(const SF_INFO info, const size_t frames, const size_t byteSize)
{
	return frames * byteSize * info.channels;
}

// gets a buffer length from just an info and byteSize using the frames value of info

static size_t p_fileBufferLen(const SF_INFO info, const size_t byteSize)
{
	return p_adjustedBufferLen(info, info.frames, byteSize);
}

// figures out the format of 'format'

static size_t p_fileTypeFormat(const size_t format)
{
	if((format & SF_FORMAT_FLAC) == SF_FORMAT_FLAC) return SF_FORMAT_FLAC;
	if((format & SF_FORMAT_OGG) == SF_FORMAT_OGG) return SF_FORMAT_OGG;

	// UNTESTED FORMATS //

	if((format & SF_FORMAT_AIFF) == SF_FORMAT_AIFF) return SF_FORMAT_AIFF;
	if((format & SF_FORMAT_AU) == SF_FORMAT_AU) return SF_FORMAT_AU;
	if((format & SF_FORMAT_RAW) == SF_FORMAT_RAW) return SF_FORMAT_RAW;
	if((format & SF_FORMAT_PAF) == SF_FORMAT_PAF) return SF_FORMAT_PAF;
	if((format & SF_FORMAT_SVX) == SF_FORMAT_SVX) return SF_FORMAT_SVX;
	if((format & SF_FORMAT_NIST) == SF_FORMAT_NIST) return SF_FORMAT_NIST;
	if((format & SF_FORMAT_VOC) == SF_FORMAT_VOC) return SF_FORMAT_VOC;
	if((format & SF_FORMAT_IRCAM) == SF_FORMAT_IRCAM) return SF_FORMAT_IRCAM;
	if((format & SF_FORMAT_W64) == SF_FORMAT_W64) return SF_FORMAT_W64;
	if((format & SF_FORMAT_MAT4) == SF_FORMAT_MAT4) return SF_FORMAT_MAT4;
	if((format & SF_FORMAT_MAT5) == SF_FORMAT_MAT5) return SF_FORMAT_MAT5;
	if((format & SF_FORMAT_PVF) == SF_FORMAT_PVF) return SF_FORMAT_PVF;
	if((format & SF_FORMAT_XI) == SF_FORMAT_XI) return SF_FORMAT_XI;
	if((format & SF_FORMAT_HTK) == SF_FORMAT_HTK) return SF_FORMAT_HTK;
	if((format & SF_FORMAT_SDS) == SF_FORMAT_SDS) return SF_FORMAT_SDS;
	if((format & SF_FORMAT_AVR) == SF_FORMAT_AVR) return SF_FORMAT_AVR;
	if((format & SF_FORMAT_WAVEX) == SF_FORMAT_WAVEX) return SF_FORMAT_WAVEX;
	if((format & SF_FORMAT_SD2) == SF_FORMAT_SD2) return SF_FORMAT_SD2;
	if((format & SF_FORMAT_CAF) == SF_FORMAT_CAF) return SF_FORMAT_CAF;
	if((format & SF_FORMAT_WVE) == SF_FORMAT_WVE) return SF_FORMAT_WVE;
	if((format & SF_FORMAT_MPC2K) == SF_FORMAT_MPC2K) return SF_FORMAT_MPC2K;
	if((format & SF_FORMAT_RF64) == SF_FORMAT_RF64) return SF_FORMAT_RF64;

	// keep wav's last otherwise libsnd file confuses some formats for wav's

	if((format & SF_FORMAT_WAV) == SF_FORMAT_WAV) return SF_FORMAT_WAV;

	return 0;
}

// returns the format type of a libnsd info file (audio file header). If this is not a wav it assumes it as a float because all non-wav files are converted

static size_t p_fileType(const SF_INFO info)
{
	const size_t format = info.format;

	const size_t typeFormat = p_fileTypeFormat(info.format);

	if(typeFormat == SF_FORMAT_WAV)
	{
		if((SF_FORMAT_PCM_S8 & format) == SF_FORMAT_PCM_S8) return SF_FORMAT_PCM_S8;
		if((SF_FORMAT_PCM_16 & format) == SF_FORMAT_PCM_16) return SF_FORMAT_PCM_16;
		if((SF_FORMAT_PCM_24 & format) == SF_FORMAT_PCM_24) return SF_FORMAT_PCM_24;
		if((SF_FORMAT_PCM_32 & format) == SF_FORMAT_PCM_32) return SF_FORMAT_PCM_32;

		if((SF_FORMAT_PCM_U8 & format) == SF_FORMAT_PCM_U8) return SF_FORMAT_PCM_U8;

		if((SF_FORMAT_FLOAT & format) == SF_FORMAT_FLOAT) return SF_FORMAT_FLOAT;
		if((SF_FORMAT_DOUBLE & format) == SF_FORMAT_DOUBLE) return SF_FORMAT_DOUBLE;
	}

	return SF_FORMAT_FLOAT;
}

// loads sound info from a libsnd file source and into a buffer also supplying a new framecount if needed

static void p_fileBufferLoad(SNDFILE* source, void* buffer, size_t* length, const size_t readLen, const SF_INFO info)
{
	const size_t typeFormat = p_fileTypeFormat(info.format);

	memset(buffer, 0, readLen);

	if(typeFormat == SF_FORMAT_WAV)
	{
		sf_read_raw(source, buffer, readLen);
		*length = info.frames;
	}else *length = sf_read_float(source, buffer, readLen)/info.channels;
}

// opens a new portaudio stream for the channel

static bool p_openChannelStream(PLEX_SOUNDCHANNEL* channel, const size_t index, const size_t errorline, const char* const errorfile)
{
	const size_t type = channel->type;

	size_t paType = 0;

	switch(type)
	{
		case SF_FORMAT_PCM_S8: paType = paInt8; break;
		case SF_FORMAT_PCM_16: paType = paInt16; break;
		case SF_FORMAT_PCM_24: paType = paInt24; break;
		case SF_FORMAT_PCM_32: paType = paInt32; break;

		case SF_FORMAT_PCM_U8: paType = paUInt8; break;

		case SF_FORMAT_FLOAT: paType = paFloat32; break;

		case SF_FORMAT_DOUBLE:
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONOPENSTREAM, PLEX_ERRORMESS_OP_DOUBLESAMPLERATE, errorline, errorfile);
		return false;

		default: paType = paFloat32;
	}

	if(!p_checkError(PLEX_ERROR_SEVERITY_MAJOR, Pa_OpenDefaultStream(&channel->stream, 0, channel->channelCount, paType, channel->sampleRate, 256, p_hook, p_soundChannel + index), errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PORTAUDIO, PLEX_ERROR_EXTERNALMODULE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_SOUND_ONOPENSTREAM, PLEX_ERRORMESS_SOUND_FAILEDTOOPENSTREAM, errorline, errorfile);
		return false;
	}

	return true;
}

// plays a port audio steam stored in a channel

static bool p_playChannelStream(PLEX_SOUNDCHANNEL* channel, const size_t errorline, const char* const errorfile)
{
	if(channel->playBuffer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONPLAY, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	if(Pa_IsStreamActive(channel->stream) && !Pa_IsStreamStopped(channel->stream)) return true;

	return p_checkError(PLEX_ERROR_SEVERITY_MAJOR, Pa_StartStream(channel->stream), errorline, errorfile);
}

// stops a port audio stream stored in a channel

static void p_stopChannelStream(PLEX_SOUNDCHANNEL* channel, const size_t errorline, const char* const errorfile)
{
	if(!Pa_IsStreamActive(channel->stream))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_STREAMSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONSTOPSTREAM, PLEX_ERRORMESS_SOUND_STREAMISINACTIVE, errorline, errorfile);
		return;
	}

	if(Pa_IsStreamStopped(channel->stream)) return;

	// the windows build is unusually slow with stopping streams
	#if (PLEX_CORE_OS != PLEX_CORE_WINDOWS)
		p_checkError(PLEX_ERROR_SEVERITY_MAJOR, Pa_StopStream(channel->stream), errorline, errorfile);
	#endif

	channel->needle = 0;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

bool PLEX_preloadSoundFileToSpecificBufferInt(const char* const fileloc, const size_t buffer, const size_t errorline, const char* const errorfile)
{
	SF_INFO info;

	size_t bufferLen = 0;
	size_t frameLen = 0;
	size_t byteSize = 0;

	size_t type = 0;

	SNDFILE* file = NULL;

	if(PLEX_DEF_disableAudio()) return true;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER, errorline, errorfile);
		return false;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	file = p_getFile(fileloc, &info);

	if(file == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_SOUND_BUFFERFILE);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	type = p_fileType(info);

	if(!type)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_OP_DECIDESOUNDTYPE, errorline, errorfile);
		sf_close(file);
		return false;
	}

	p_preloadBufferType[buffer] = type;
	byteSize = p_fileTypeSize(p_preloadBufferType[buffer]);
	bufferLen = p_fileBufferLen(info, byteSize);
	frameLen = info.frames * info.channels;

	if(p_preloadBuffers[buffer] == NULL || PLEX_expandArrayCount(p_preloadBuffers[buffer]) <= frameLen || byteSize != p_preloadBufferSize[buffer])
	{
		if(p_preloadBuffers[buffer] != NULL) PLEX_destroyExpandArrayInt(p_preloadBuffers + buffer, errorline, errorfile);
		p_preloadBuffers[buffer] = PLEX_genExpandArrayInt(frameLen, byteSize, errorline, errorfile);
	}

	if(p_preloadBuffers[buffer] == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER, errorline, errorfile);
		sf_close(file);
		return false;
	}

	p_preloadBufferSampleRate[buffer] = info.samplerate;
	p_preloadBufferChannelCount[buffer] = info.channels;

	p_fileBufferLoad(file, PLEX_expandArrayContentsInt(p_preloadBuffers[buffer], errorline, errorfile), p_preloadBufferFrameCount + buffer, bufferLen, info);

	if(p_preloadBufferFrameCount[buffer] != info.frames)
	{
		bufferLen = p_adjustedBufferLen(info, p_preloadBufferFrameCount[buffer], byteSize);
		frameLen = p_preloadBufferFrameCount[buffer] * info.channels;
	}

	p_preloadBufferSize[buffer] = bufferLen;

	if(!PLEX_multiIncrementExpandArrayInt(frameLen, p_preloadBuffers[buffer], errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	sf_close(file);

	return true;
}

int64_t PLEX_preloadSoundFileInt(const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	size_t index = p_preloadBufferCount;

	if(PLEX_DEF_disableAudio()) return 0; // 0 instead of -1 to not indicate something is wrong

	if(p_preloadBufferCount >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
	}

	if(!PLEX_preloadSoundFileToSpecificBufferInt(fileloc, index, errorline, errorfile))
	{
		PLEX_FAKESTRING_25 errMess2 = PLEX_createString25Int(PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		PLEX_FAKESTRING_25 errMess2IndexNum = PLEX_createStringFromNumber25(index);
		PLEX_FAKESTRING_25 errMess2Filepath = PLEX_createString25Int(PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		PLEX_FAKESTRING_25 errMess2Filename = PLEX_createString25Int(fileloc, errorline, errorfile);

		errMess2 = PLEX_concatString25(errMess2, ':', 1);
		errMess2 = PLEX_concatString25(errMess2, ' ', 1);
		errMess2 = PLEX_mergeString25(errMess2, errMess2IndexNum);
		errMess2 = PLEX_concatString25(errMess2, ' ', 1);
		errMess2 = PLEX_mergeString25(errMess2, errMess2Filepath);
		errMess2 = PLEX_concatString25(errMess2, ':', 1);
		errMess2 = PLEX_concatString25(errMess2, ' ', 1);
		errMess2 = PLEX_mergeString25(errMess2, errMess2Filename);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONPRELOADINTOBUFFER, PLEX_fts(errMess2), errorline, errorfile);
		return -1;
	}

	if(index == p_preloadBufferCount) ++p_preloadBufferCount;

	return index;
}

bool PLEX_assignSoundBufferInt(const int64_t buffer, const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return true;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER, errorline, errorfile);
		return false;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return false;
	}

	if(buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	if(PLEX_isSoundPlaying(index))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_SOUNDCHANNELSTATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER, PLEX_ERRORMESS_SOUND_CHANNELON, errorline, errorfile);
		return false;
	}

	channel = p_soundChannel + index;

	p_restartChannelInfo(channel);

	channel->buffer = buffer;
	channel->iterations = 0;
	channel->needle = 0;

	p_killChannelStream(channel, errorline, errorfile);

	if(channel->playBuffer != NULL) PLEX_deallocInt(&channel->playBuffer, errorline, errorfile);

	return true;
}

void PLEX_clearSoundBufferInt(const int64_t buffer, const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONCLEARBUFFER, errorline, errorfile);
		return;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONCLEARBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer < 0)
	{
		// sometimes buffers of channels are automatically cleared without being set, so this should remain a bad style as to not flood the output with pointless error messages.
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONCLEARBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	p_preloadBufferFrameCount[buffer] = 0;
	p_preloadBufferSize[buffer] = 0;
	PLEX_destroyExpandArrayInt(p_preloadBuffers + buffer, errorline, errorfile);

	if(buffer == p_preloadBufferCount - 1)
	{
		--p_preloadBufferCount;
		return;
	}
}

void PLEX_clearSoundBufferByChannelInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONCLEARBUFFERBYCHANNEL, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	channel = p_soundChannel + index;

	PLEX_clearSoundBuffer(channel->buffer);

	p_killChannelStream(channel, errorline, errorfile);

	channel->buffer = -1;
}

bool PLEX_loadSoundFileIntoBufferInt(const char* const fileloc, const size_t index, const size_t errorline, const char* const errorfile)
{
	int64_t buffer = -1;

	if(PLEX_DEF_disableAudio()) return true;

	buffer = PLEX_preloadSoundFileInt(fileloc, errorline, errorfile);

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONLOADFILEINTOBUFFER, errorline, errorfile);
		return false;
	}

	if(buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONLOADFILEINTOBUFFER, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return false;
	}

	PLEX_assignSoundBufferInt(buffer, index, errorline, errorfile);

	return true;
}

bool PLEX_setSoundBufferLenInt(const size_t length, const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return true;

	size_t byteSize = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETBUFFERLEN, errorline, errorfile);
		return false;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETBUFFERLEN, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return false;
	}

	channel = p_soundChannel + index;

	p_restartChannelInfo(channel);

	byteSize = p_fileTypeSize(channel->type);

	channel->length = byteSize ? length/byteSize : 0;

	return true;
}

void PLEX_setComplexSoundSequenceInt(const bool seq0, const bool seq1, const bool seq2, const bool seq3, const bool seq4, const bool seq5, const bool seq6, const bool seq7, const size_t count, const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCOMPLEXSEQUENCE, errorline, errorfile);
		return;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCOMPLEXSEQUENCE, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCOMPLEXSEQUENCE, PLEX_ERRORMESS_GENERIC_COUNT, errorline, errorfile);
		return;
	}

	if(count > 8)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCOMPLEXSEQUENCE, PLEX_ERRORMESS_GENERIC_COUNT, errorline, errorfile);
		return;
	}

	channel = p_soundChannel + index;

	channel->complexPattern[0] = seq0;
	if(count > 1) channel->complexPattern[1] = seq1; else channel->complexPattern[1] = false;
	if(count > 2) channel->complexPattern[2] = seq2; else channel->complexPattern[2] = false;
	if(count > 3) channel->complexPattern[3] = seq3; else channel->complexPattern[3] = false;
	if(count > 4) channel->complexPattern[4] = seq4; else channel->complexPattern[4] = false;
	if(count > 5) channel->complexPattern[5] = seq5; else channel->complexPattern[5] = false;
	if(count > 6) channel->complexPattern[6] = seq6; else channel->complexPattern[6] = false;
	if(count > 7) channel->complexPattern[7] = seq7; else channel->complexPattern[7] = false;

	channel->complexPatternCount = count;
}

void PLEX_soundBufferRandomSwapInt(const int64_t buffer1, const int64_t buffer2, const double perc, const double perc2, const double lenPerc, const size_t errorline, const char* const errorfile)
{
	PLEX_EXPANDARRAY* preBuff1 = NULL;
	PLEX_EXPANDARRAY* preBuff2 = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, errorline, errorfile);
		return;
	}

	if(buffer1 >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer2 >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_SOUND_BUFFER2, errorline, errorfile);
		return;
	}

	if(buffer1 < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer2 < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_SOUND_BUFFER2, errorline, errorfile);
		return;
	}

	preBuff1 = p_preloadBuffers[buffer1];

	if(preBuff1 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER, errorline, errorfile);
		return;
	}

	preBuff2 = p_preloadBuffers[buffer2];

	if(preBuff2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER2, errorline, errorfile);
		return;
	}

	PLEX_swapExpandArrayPercInt(perc, perc2, lenPerc, preBuff1, preBuff2, errorline, errorfile);
}

void PLEX_soundBufferRearrangeInt(const int64_t buffer, const double perc, const double perc2, const double lenPerc, const size_t errorline, const char* const errorfile)
{
	PLEX_EXPANDARRAY* preBuff = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREARRANGE, errorline, errorfile);
		return;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREARRANGE, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREARRANGE, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	preBuff = p_preloadBuffers[buffer];

	if(preBuff == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREARRANGE, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER, errorline, errorfile);
		return;
	}

	PLEX_rearrangeExpandArrayPercInt(perc, perc2, lenPerc, preBuff, errorline, errorfile);
}

void PLEX_soundBufferCutInt(const int64_t buffer, const double perc, const double lenPerc, const size_t errorline, const char* const errorfile)
{
	PLEX_EXPANDARRAY* preBuff = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERCUT, errorline, errorfile);
		return;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERCUT, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERCUT, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	preBuff = p_preloadBuffers[buffer];

	if(preBuff == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERCUT, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER, errorline, errorfile);
		return;
	}

	if(PLEX_cutExpandArrayPerc(perc, lenPerc, preBuff))
	{
		p_preloadBufferFrameCount[buffer] = PLEX_expandArrayCount(preBuff);
		p_preloadBufferSize[buffer] = PLEX_protoExpandArraySize(preBuff);
	}else{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERCUT, PLEX_ERRORMESS_OP_CUTSOUNDBUFFER, errorline, errorfile);
	}
}

void PLEX_soundReverseInt(const int64_t buffer, const double perc, const double lenPerc, const size_t errorline, const char* const errorfile)
{
	PLEX_EXPANDARRAY* preBuff = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, errorline, errorfile);
		return;
	}

	if(buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	if(buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, PLEX_ERRORMESS_SOUND_BUFFER, errorline, errorfile);
		return;
	}

	preBuff = p_preloadBuffers[buffer];

	if(preBuff == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, PLEX_ERRORMESS_ARRAY_PRELOADBUFFER, errorline, errorfile);
		return;
	}

	if(PLEX_reverseExpandArrayPercInt(perc, lenPerc, preBuff, errorline, errorfile))
	{
		p_preloadBufferFrameCount[buffer] = PLEX_expandArrayCount(preBuff);
		p_preloadBufferSize[buffer] = PLEX_protoExpandArraySize(preBuff);
	}else{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, PLEX_ERRORMESS_OP_REVERSESOUNDBUFFER, errorline, errorfile);
	}
}

void PLEX_setVolumeInt(const double volume, const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCHANNELVOLUME, errorline, errorfile);
		return;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCHANNELVOLUME, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	channel = p_soundChannel + index;

	if(channel == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONSETCHANNELVOLUME, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	channel->volume = volume;
}

void PLEX_soundChannelOnInt(const bool loop, const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	size_t startLen = 0;
	size_t fullBufferLen = 0;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, errorline, errorfile);
		return;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	channel = p_soundChannel + index;

	if(channel->on)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_SOUNDCHANNELSTATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_ERRORMESS_SOUND_CHANNELON, errorline, errorfile);
		return;
	}

	if(channel->buffer < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_ERRORMESS_GENERIC_BUFFER, errorline, errorfile);
		return;
	}

	// DO NOT USE p_preloadBufferCount HERE!
	if(channel->buffer >= PLEX_LIMIT_PREBUFFERCOUNT)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_ERRORMESS_GENERIC_BUFFER, errorline, errorfile);
		return;
	}

	startLen = channel->length;

	channel->on = true;
	channel->loop = loop;
	channel->needle = 0;
	channel->iterations = 0;
	channel->length = 0;
	channel->errorline = errorline;
	channel->errorfile = errorfile;

	// keep before play buffer stuff
	if(channel->stream == NULL || channel->type != p_preloadBufferType[channel->buffer] || channel->sampleRate != p_preloadBufferSampleRate[channel->buffer] || channel->channelCount != p_preloadBufferChannelCount[channel->buffer])
	{
		channel->type = p_preloadBufferType[channel->buffer];
		channel->sampleRate = p_preloadBufferSampleRate[channel->buffer];
		channel->channelCount = p_preloadBufferChannelCount[channel->buffer];

		p_killChannelStream(channel, errorline, errorfile);

		if(!p_openChannelStream(channel, index, errorline, errorfile))
		{
			channel->on = false;

			PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_OP_OPENSOUNDSTREAM, errorline, errorfile);
			return;
		}
	}

	if(channel->buffer != -1 && p_preloadBuffers[channel->buffer] != NULL && PLEX_expandArrayContentsInt(p_preloadBuffers[channel->buffer], errorline, errorfile) != NULL)
	{
		const size_t frameCount = p_preloadBufferFrameCount[channel->buffer];

		const size_t byteSize = p_fileTypeSize(channel->type);

		if(channel->playBuffer == NULL || (channel->playBuffer != NULL && startLen >= frameCount))
		{
			fullBufferLen = frameCount * byteSize * channel->channelCount;

			if(channel->playBuffer != NULL) PLEX_deallocInt(&channel->playBuffer, errorline, errorfile);
			channel->playBuffer = PLEX_allocInt(fullBufferLen + (byteSize * channel->channelCount), errorline, errorfile);

			if(channel->playBuffer == NULL)
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_ERRORMESS_GENERIC_BUFFER, errorline, errorfile);
				return;
			}
		}

		channel->length = frameCount; // < do not move to assignBuffer

		memset(channel->playBuffer, 0, fullBufferLen + byteSize + 1);
		memcpy(channel->playBuffer, PLEX_expandArrayContentsInt(p_preloadBuffers[channel->buffer], errorline, errorfile), fullBufferLen);

		if(!p_playChannelStream(channel, errorline, errorfile))
		{
			PLEX_FAKESTRING_25 errMess2 = PLEX_createString25Int(PLEX_ERRORMESS_OP_PLAYSOUNDCHANNEL, errorline, errorfile);
			PLEX_FAKESTRING_25 errMess2ChannelIndex = PLEX_createStringFromNumber25(index);

			errMess2 = PLEX_concatString25(errMess2, ' ', 1);
			errMess2 = PLEX_mergeString25(errMess2, errMess2ChannelIndex);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON, PLEX_fts(errMess2), errorline, errorfile);
			return;
		}
	}
}

void PLEX_soundChannelOffInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELOFF, errorline, errorfile);
		return;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELOFF, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return;
	}

	// do not check for sound lock, the hook should stop when the stream stops

	channel = p_soundChannel + index;

	channel->iterations = 0;
	channel->volume = 1;

	if(!channel->on)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_SOUNDCHANNELSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELOFF, PLEX_ERRORMESS_SOUND_CHANNELOFF, errorline, errorfile);
		return;
	}

	channel->on = false;
}

void PLEX_clearSoundPreloadsInt(const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableAudio()) return;

	for(size_t ze = 0; ze < PLEX_LIMIT_SOUNDCHANNELS; ++ze)
	{
		if(PLEX_isSoundPlayingInt(ze, errorline, errorfile)) PLEX_soundChannelOffInt(ze, errorline, errorfile);
	}

	// DO NOT USE p_prelaodBufferCount HERE
	for(size_t ze = 0; ze < PLEX_LIMIT_PREBUFFERCOUNT; ++ze)
	{
		PLEX_clearSoundBufferInt(ze, errorline, errorfile);
	}

	p_preloadBufferCount = 0;
}

uint64_t PLEX_channelDurationInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETDURATION, errorline, errorfile);
		return false;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETDURATION, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return false;
	}

	channel = p_soundChannel + index;

	return channel->sampleRate ? channel->length/(channel->sampleRate/1000.0) : 0;
}

size_t PLEX_channelIterationInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETCHANNELITERATION, errorline, errorfile);
		return 0;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETCHANNELITERATION, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return 0;
	}

	channel = p_soundChannel + index;

	// if(!channel->on) return 0; << do not do

	return channel->iterations;
}

void PLEX_reloadSoundDefaults()
{
	if(PLEX_DEF_disableAudio() == p_disabled) return;

	PLEX_endSound();
	PLEX_startSound();
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startSoundInt(const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableAudio())
	{
		p_disabled = true;
		return true;
	}

	p_disabled = false;

	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(!p_checkError(PLEX_ERROR_SEVERITY_FATAL, Pa_Initialize(), errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_PORTAUDIO, PLEX_ERROR_LOADEXTERNALMODULE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE, errorline, errorfile);
		return false;
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_PREBUFFERCOUNT; ++ze) p_preloadBuffers[ze] = NULL;

	for(size_t ze = 0; ze < PLEX_LIMIT_SOUNDCHANNELS; ++ze)
	{
		PLEX_SOUNDCHANNEL* channel = p_soundChannel + ze;

		channel->on = false;
		channel->id = ze;
		channel->buffer = -1;
		channel->playBuffer = NULL;
		channel->stream = NULL;
		channel->volume = 1;

		p_restartChannelInfo(channel);
	}

	p_preloadBufferCount = 0;

	p_running = true;

	return true;
}

bool PLEX_updateSoundInt(const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableAudio()) return true;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_SOUNDCHANNELS; ++ze)
	{
		PLEX_SOUNDCHANNEL* channel = p_soundChannel + ze;

		if(!channel->on) p_stopChannelStream(channel, errorline, errorfile);
	}

	p_universalThemeCueID = 0;
	p_universalSoundEffect = 0;
	p_universalThemeStopSignal = false;

	Pa_Sleep(10);

	return true;
}

void PLEX_endSoundInt(const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableAudio()) return;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_SOUNDCHANNELS; ++ze)
	{
		PLEX_SOUNDCHANNEL* channel = p_soundChannel + ze;

		if(channel == NULL) continue;

		p_killChannelStream(channel, errorline, errorfile);

		if(channel->playBuffer != NULL) PLEX_deallocInt(&channel->playBuffer, errorline, errorfile);
	}

	Pa_Terminate();

	for(size_t ze = 0; ze < PLEX_LIMIT_PREBUFFERCOUNT; ++ze)
	{
		PLEX_EXPANDARRAY* expandArray = p_preloadBuffers[ze];

		if(expandArray != NULL) PLEX_destroyExpandArrayInt(&expandArray, errorline, errorfile);

		p_preloadBufferFrameCount[ze] = 0;
		p_preloadBufferSize[ze] = 0;
	}

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setUniversalSoundEffect(const size_t id)
{
	p_universalSoundEffect = id;
}

void PLEX_setUniversalThemeID(const size_t id)
{
	p_universalThemeCueID = id;
}

void PLEX_signalUniversalThemeStop()
{
	p_universalThemeStopSignal = true;
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_getUniversalSoundEffect(){ return p_universalSoundEffect; }
size_t PLEX_getUniversalThemeCueID(){ return p_universalThemeCueID; }
bool PLEX_getUniversalThemeStopSignal(){ return p_universalThemeStopSignal; }

int64_t PLEX_getBufferInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return 0; // 0 as to indicate nothing is wrong instead of -1

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETSOUNDBUFFER, errorline, errorfile);
		return -1;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONGETSOUNDBUFFER, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return -1;
	}

	channel = p_soundChannel + index;

	return channel->buffer;
}

bool PLEX_isSoundPlayingInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_SOUNDCHANNEL* channel = NULL;

	if(PLEX_DEF_disableAudio()) return true;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONCHECKPLAYING, errorline, errorfile);
		return false;
	}

	if(index >= PLEX_LIMIT_SOUNDCHANNELS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SOUND, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SOUND_ONCHECKPLAYING, PLEX_ERRORMESS_SOUND_CHANNEL, errorline, errorfile);
		return false;
	}

	channel = p_soundChannel + index;

	return channel->on;
}
