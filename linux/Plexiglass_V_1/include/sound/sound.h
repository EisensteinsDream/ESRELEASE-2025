#ifndef PLEX_SOUND_H
#define PLEX_SOUND_H

#include "utility/defaults.h"
#include "utility/error.h"
#include "utility/math.h"
#include "utility/fakestrings.h"

#include "mem/expandarray.h"

// this unit manages PLEX's sound. PLEX's sound engine is very low-level and very powerful. It allows for fully programmable algorithmic sound based on portaudio. Currently supports the types of wav, ogg, and FLAC. I do not link this with LAME and haven't been able to successfully load MP3s for that reason. MP3s have strict copyright nonsense that makes that process more difficult. Which is why oggs exist. I haven't had the means or inclination to test any other format, albeit some may theoretically work if they're supported by libsndfile.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const char* const fileloc, const size_t buffer) - returns bool

#define PLEX_preloadSoundFileToSpecificBuffer(fileloc, buffer) PLEX_preloadSoundFileToSpecificBufferInt(fileloc, buffer, __LINE__, __FILE__)

// ARGUMENTS: (const char* const fileloc) - returns int64_t

#define PLEX_preloadSoundFile(fileloc) PLEX_preloadSoundFileInt(fileloc, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer, const size_t index) - returns bool

#define PLEX_assignSoundBuffer(buffer, index) PLEX_assignSoundBufferInt(buffer, index, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer)

#define PLEX_clearSoundBuffer(buffer) PLEX_clearSoundBufferInt(buffer, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_clearSoundBufferByChannel(index) PLEX_clearSoundBufferByChannelInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const char* const fileloc, const size_t index) - returns bool

#define PLEX_loadSoundFileIntoBuffer(fileloc, index) PLEX_loadSoundFileIntoBufferInt(fileloc, index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t length, const size_t index) - returns bool

#define PLEX_setSoundBufferLen(length, index) PLEX_setSoundBufferLenInt(length, index, __LINE__, __FILE__)

// ARGUMENTS: (const bool seq0, const bool seq1, const bool seq2, const bool seq3, const bool seq4, const bool seq5, const bool seq6, const bool seq7, const size_t count, const size_t index)

#define PLEX_setComplexSoundSequence(seq0, seq1, seq2, seq3, seq4, seq5, seq6, seq7, count, index) PLEX_setComplexSoundSequenceInt(seq0, seq1, seq2, seq3, seq4, seq5, seq6, seq7, count, index, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer1, const int64_t buffer2, const double perc, const double perc2, const double lenPerc)

#define PLEX_soundBufferRandomSwap(buffer1, buffer2, perc, perc2, lenPerc) PLEX_soundBufferRandomSwapInt(buffer1, buffer2, perc, perc2, lenPerc, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer, const double perc, const double perc2, const double lenPerc)

#define PLEX_soundBufferRearrange(buffer, perc, perc2, lenPerc) PLEX_soundBufferRearrangeInt(buffer, perc, perc2, lenPerc, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer, const double perc, const double lenPerc)

#define PLEX_soundBufferCut(buffer, perc, lenPerc) PLEX_soundBufferCutInt(buffer, perc, lenPerc, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t buffer, const double perc, const double lenPerc)

#define PLEX_soundReverse(buffer, perc, lenPerc) PLEX_soundReverseInt(buffer, perc, lenPerc, __LINE__, __FILE__)

// ARGUMENTS: (const double volume, const size_t index)

#define PLEX_setVolume(volume, index) PLEX_setVolumeInt(volume, index, __LINE__, __FILE__);

// ARGUMENTS: (const bool loop, const size_t index)

#define PLEX_soundChannelOn(loop, index) PLEX_soundChannelOnInt(loop, index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_soundChannelOff(index) PLEX_soundChannelOffInt(index, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_clearSoundPreloads() PLEX_clearSoundPreloadsInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns uint64_t

#define PLEX_channelDuration(index) PLEX_channelDurationInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns size_t

#define PLEX_channelIteration(index) PLEX_channelIterationInt(index, __LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_startSound() PLEX_startSoundInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_updateSound() PLEX_updateSoundInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endSound() PLEX_endSoundInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns int64_t

#define PLEX_getBuffer(index) PLEX_getBufferInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns bool

#define PLEX_isSoundPlaying(index) PLEX_isSoundPlayingInt(index, __LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// preloads sound file into index'd buffer. returns false if anything goes wrong.

	extern bool PLEX_preloadSoundFileToSpecificBufferInt(const char* const fileloc, const size_t buffer, const size_t errorline, const char* const errorfile);

	// preloads sound file into the last unused buffer and returns the index

	extern int64_t PLEX_preloadSoundFileInt(const char* const fileloc, const size_t errorline, const char* const errorfile);

	// assigns buffer 'buffer' into channel 'index'. Returns false if anything goes wrong.

	extern bool PLEX_assignSoundBufferInt(const int64_t buffer, const size_t index, const size_t errorline, const char* const errorfile);

	// clears out a particular buffer by index

	extern void PLEX_clearSoundBufferInt(const int64_t buffer, const size_t errorline, const char* const errorfile);

	// clears out a particular channel's buffer (index indicating the channel not the buffer)

	extern void PLEX_clearSoundBufferByChannelInt(const size_t index, const size_t errorline, const char* const errorfile);

	// loads buffer of fileloc directly into channel @ index

	extern bool PLEX_loadSoundFileIntoBufferInt(const char* const fileloc, const size_t index, const size_t errorline, const char* const errorfile);

	// sets the sound buffer at index's length. This is poorly tested and, therefore, experimental.

	extern bool PLEX_setSoundBufferLenInt(const size_t length, const size_t index, const size_t errorline, const char* const errorfile);

	// sets a sound channels play/not play patterns. Holds up to 8. Essentially how this works, is that it creates a pattern the length of 'count' up to 8. The sequence repeats at the end of count. So every repetition of the sound it basically plays on 'true's and does not play on 'false''s. This is also an experimental poorly tested feature that has shown problems. It will be further tested and fixed in the future but possibly removed entirely.

	extern void PLEX_setComplexSoundSequenceInt(const bool seq0, const bool seq1, const bool seq2, const bool seq3, const bool seq4, const bool seq5, const bool seq6, const bool seq7, const size_t count, const size_t index, const size_t errorline, const char* const errorfile);

	// swaps a piece of one sound buffer to another by percentage length of said buffer. Is safe because the buffer playing is copied from the buffer this is editing rather than directly streamed. However, it also means that this doesn't effect the currently playing buffer.

	extern void PLEX_soundBufferRandomSwapInt(const int64_t buffer1, const int64_t buffer2, const double perc, const double perc2, const double lenPerc, const size_t errorline, const char* const errorfile);

	// takes one piece of a buffer and moves it to another piece by the percentage. Is safe because the buffer playing is copied from the buffer this is editing rather than directly streamed. However, it also means that this doesn't effect the currently playing buffer.

	extern void PLEX_soundBufferRearrangeInt(const int64_t buffer, const double perc, const double perc2, const double lenPerc, const size_t errorline, const char* const errorfile);

	// cuts out a piece of the buffer by percentage, shortening the length. Is safe because the buffer playing is copied from the buffer this is editing rather than directly streamed. However, it also means that this doesn't effect the currently playing buffer.

	extern void PLEX_soundBufferCutInt(const int64_t buffer, const double perc, const double lenPerc, const size_t errorline, const char* const errorfile);

	// reverses (backmasks) a piece of the buffer by percentage. Is safe because the buffer playing is copied from the buffer this is editing rather than directly streamed. However, it also means that this doesn't effect the currently playing buffer.

	extern void PLEX_soundReverseInt(const int64_t buffer, const double perc, const double lenPerc, const size_t errorline, const char* const errorfile);

	// sets the volume of a current index for playback by percentage.
	extern void PLEX_setVolumeInt(const double volume, const size_t index, const size_t errorline, const char* const errorfile);

	// turns the channel on (copying and playing buffer linked to channel) or off (stops playing). If the 'loop' bool is true the channel will not stop playing until it's told to.

	extern void PLEX_soundChannelOnInt(const bool loop, const size_t index, const size_t errorline, const char* const errorfile);

	// turns off the sound channel at index

	extern void PLEX_soundChannelOffInt(const size_t index, const size_t errorline, const char* const errorfile);

	// clears out all preloaded buffer and stops all channels (If all buffers are cleared than technically all channels must be stopped)

	extern void PLEX_clearSoundPreloadsInt(const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the sound state machine. Returning false on failure. This is automatically called by PLEX_start so it does not need to be manually called. Terminates program on failure.

	extern bool PLEX_startSoundInt(const size_t errorline, const char* const errorfile);

	// updates the sound state machine. Returning false on failure. This is automatically called by PLEX_update so it does not need to be manually called. Terminates program on failure.

	extern bool PLEX_updateSoundInt(const size_t errorline, const char* const errorfile);

	// updates the end state machine. This is automatically called by PLEX_end so it does not need to be manually called.

	extern void PLEX_endSoundInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets a universal sound effect index. Now, this doesn't do anything but send the index. However, you can use it as a signaler if you want to build a sound/music system that interprets said index in different ways. These can also be signaled through events in the Sprite Theater connecting it to a custom sound effect and music cue system.

	extern void PLEX_setUniversalSoundEffect(const size_t id);

	// same thing except it does so with a theme ID. Same system as the universal sound effect index.

	extern void PLEX_setUniversalThemeID(const size_t id);

	// sets out a universal boolean to signify the theme is stopped. Like the index, this doesn't do anything on it's own but can be used for a sound signaling system.

	extern void PLEX_signalUniversalThemeStop();

// getters ------------------------------------------------------------------------------------------------------------------

	// reads the universal sound effect ID set by the PLEX_setUniversalSoundEffect function.

	extern size_t PLEX_getUniversalSoundEffect();

	// reads the sound effect ID set by the PLEX_setUniversalThemeID function

	extern size_t PLEX_getUniversalThemeCueID();

	// reads whether or not the boolean thrown out by PLEX_signalUniversalThemeStop()

	extern bool PLEX_getUniversalThemeStopSignal();

	// returns the buffer index assigned to channel index

	extern int64_t PLEX_getBufferInt(const size_t index, const size_t errorline, const char* const errorfile);

	// returns the duration of the buffer at channel index in microseconds

	extern uint64_t PLEX_channelDurationInt(const size_t index, const size_t errorline, const char* const errorfile);

	// returns the amount of times that a channel at index has looped over.

	extern size_t PLEX_channelIterationInt(const size_t index, const size_t errorline, const char* const errorfile);

	// returns whether or not sound is playing at channel index

	extern bool PLEX_isSoundPlayingInt(const size_t index, const size_t errorline, const char* const errorfile);

#ifdef __cplusplus
}
#endif

#endif
