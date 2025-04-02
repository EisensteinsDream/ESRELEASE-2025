#ifndef PLEX_ERROR_H
#define PLEX_ERROR_H

#include "terminate.h"

// this is the error subsystem. PLEX errors are very verbose and very specific. They allow you to know exactly what is going on and where. Errors are called in PLEX and can be custom made for any project using PLEX. An error consists of 4 parts: Category (reference to the unit calling them), Type (indicates the variety of error), Severity (signals the severity of the error and determines whether an error should be shown in a pop-up, printed, or terminate execution), and messages which you can have up to two of and specify important information. When and how errors are presented can also be modified in the config file.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity, const size_t lineNumber, const char* const fileloc)

#define PLEX_errorInt0A(category, type, severity, errorline, errorfile) PLEX_errorInt(category, type, severity, "", "", errorline, errorfile)

// ARGUMENTS: (const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity, const char* const message, const size_t lineNumber, const char* const fileloc)

#define PLEX_errorInt1A(category, type, severity, message, errorline, errorfile) PLEX_errorInt(category, type, severity, message, "", errorline, errorfile)

// ARGUMENTS: (const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity, const char* const message)

#define PLEX_error(category, type, severity, message) PLEX_errorInt(category, type, severity, message, "", __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity, const char* const message, const char* const message2)

#define PLEX_error2(category, type, severity, message, message2) PLEX_errorInt(category, type, severity, message, message2, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity)

#define PLEX_errorNoDesc(category, type, severity) PLEX_errorInt(category, type, severity, "", "", __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ERROR_SEVERITY severity) - returns bool

#define PLEX_errorSDL(severity) PLEX_errorSDLInt(severity, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ERROR_SEVERITY severity) - returns bool

#define PLEX_errorSDLImage(severity) PLEX_errorSDLImageInt(severity, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ERROR_SEVERITY severity, const PaError error) - returns bool

#define PLEX_errorPortAudio(severity, error) PLEX_errorPortAudioInt(severity, error, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef enum
{
	PLEX_ERROR_CATEGORY_NONE = 0, // < unassignable to error
	PLEX_ERROR_CATEGORY_START = 1,
	PLEX_ERROR_CATEGORY_UPDATE = 2,
	PLEX_ERROR_CATEGORY_SDL = 3,
	PLEX_ERROR_CATEGORY_PORTAUDIO = 4,
	PLEX_ERROR_CATEGORY_MATH = 5,
	PLEX_ERROR_CATEGORY_DATETIME = 6,
	PLEX_ERROR_CATEGORY_FAKESTRING = 7,
	PLEX_ERROR_CATEGORY_STRINGBANK = 8,
	PLEX_ERROR_CATEGORY_DEFAULT = 9,
	PLEX_ERROR_CATEGORY_MEM = 10,
	PLEX_ERROR_CATEGORY_ARRAY = 11,
	PLEX_ERROR_CATEGORY_SOUND = 12,
	PLEX_ERROR_CATEGORY_TEXTURE = 13,
	PLEX_ERROR_CATEGORY_WINDOW = 14,
	PLEX_ERROR_CATEGORY_PROMINENCEMACHINE = 15,
	PLEX_ERROR_CATEGORY_SCREENEFFECTS = 16,
	PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_GL = 17, // < not yet implemented
	PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL = 18,
	PLEX_ERROR_CATEGORY_FILEPARSE = 19,
	PLEX_ERROR_CATEGORY_INPUT = 20,
	PLEX_ERROR_CATEGORY_GENERATOR = 21,
	PLEX_ERROR_CATEGORY_SPRITETHEATER = 22,
	PLEX_ERROR_CATEGORY_TIMING = 23,
	PLEX_ERROR_CATEGORY_GLOBALTIME = 24,
	PLEX_ERROR_CATEGORY_GRAPHICS = 25,
	PLEX_ERROR_CATEGORY_ANIMATION = 26,
	PLEX_ERROR_CATEGORY_ANIMATION_PLATE = 27,
	PLEX_ERROR_CATEGORY_SPRITE = 28,
	PLEX_ERROR_CATEGORY_DIRECTORY = 29,
	PLEX_ERROR_CATEGORY_SCROLLER = 30,
	PLEX_ERROR_CATEGORY_SYSTEMREAD = 31,
	PLEX_ERROR_CATEGORY_INPROJECT = 32 // < for errors in plex projects rather than plex itself
} PLEX_ERROR_CATEGORY;

typedef enum
{
	PLEX_ERROR_NONE = 0, // < unassignable to error
	PLEX_ERROR_START = 1, // subsystem failed to start
	PLEX_ERROR_LOADEXTERNALMODULE = 2, // external module failed to load
	PLEX_ERROR_EXTERNALMODULE = 3, // an error related to the external module
	PLEX_ERROR_CREATE = 4, // failed to create something needed
	PLEX_ERROR_UPDATE = 5, // system failed to update
	PLEX_ERROR_MINMAXREVERSE = 6, // the minimum and maximum are reversed
	PLEX_ERROR_DEFAULTPOP = 7, // default failed to populate for whatever reason
	PLEX_ERROR_FILELOAD = 8, // filed to load a crucial file
	PLEX_ERROR_FILESAVE = 9, // filed to save to a crucial file
	PLEX_ERROR_DOUBLESTART = 10, // for whatever reason a system was started multiple times without ending
	PLEX_ERROR_ENDBEFORESTART = 11, // for whatever reason a system was started before it ended
	PLEX_ERROR_ACTIONBEFORESTART = 12, // some function inside a system was attempted but stopped because the system has not been started
	PLEX_ERROR_FREENULL = 13, // attempted to deallocate a null pointer
	PLEX_ERROR_FREENULLPTR = 14, // attempted to deallocate a pointer to a null pointer
	PLEX_ERROR_ALLOCFAIL = 15, // failed to allocate something
	PLEX_ERROR_CONTENTCORRUPTION = 16, // any error happened because the contents of something are corrupted
	PLEX_ERROR_EXPANDNULL = 17, // something tried to expand from a null array
	PLEX_ERROR_EXPAND = 18, // something failed to expand somewhere
	PLEX_ERROR_INCREMENTNULL = 19, // something tried to increment from a NULL array
	PLEX_ERROR_INCREMENT = 20, // something failed to be incremented
	PLEX_ERROR_DECREMENT = 21, // something failed to be decremented
	PLEX_ERROR_CLEAR = 22, // something failed to be cleared
	PLEX_ERROR_SWAP = 23, // something failed to be swapped
	PLEX_ERROR_CUT = 24, // something failed to be cut
	PLEX_ERROR_REARRANGE = 25, // something failed to be cut
	PLEX_ERROR_BADBUFFERSOUNDHOOK = 26, // for whatever reason the buffer in the soundhook is bad
	PLEX_ERROR_OVERLIMIT = 27, // tried to create something over the designated limit allowed
	PLEX_ERROR_ISNULL = 28, // something is NULL but probably shouldn't be
	PLEX_ERROR_SAMEVALUE = 29, // two values that should be different are the same
	PLEX_ERROR_UNDERLIMIT = 30, // the number is under the limit somewhere
	PLEX_ERROR_ZEROVALUE = 31, // a value is zero somewhere where it shouldn't be
	PLEX_ERROR_DISABLED = 32, // attempted to use a disabled feature
	PLEX_ERROR_BADOPERATION = 33, // an operation has been blocked for whatever reason
	PLEX_ERROR_HOOKCORRUPTION = 34, // the corruption of a hook that should not be accessed externally
	PLEX_ERROR_NOSTRINGLEN = 35, // something has no length value
	PLEX_ERROR_UPDATEBEFORESTART = 36, // tried to update before starting
	PLEX_ERROR_SUCCESSCHECKFAIL = 37, // a success check has failed
	PLEX_ERROR_ISNULLTEXTURE = 38, // an operation requiring a texture has been passed a NULL texture
	PLEX_ERROR_SOUNDHOOKINUSE = 39, // a process was halted because a sound hook is being used
	PLEX_ERROR_SOUNDCHANNELSTATE = 40, // a process was halted because either the sound channel is already on or off
	PLEX_ERROR_ACQUIRE = 41, // failed to acquire something for whatever reason
	PLEX_ERROR_ACQUIRELAST = 42, // failed to acquire the last of something for whatever reason
	PLEX_ERROR_STREAMSTATE = 43, // a process was halted because the sound stream was either inactive when it should have been active or vice versa
	PLEX_ERROR_FILETYPE = 44, // is the wrong filetype for a particular operation
	PLEX_ERROR_DOUBLEDEALLOC = 45, // attempting to deallocating already deallocated memory
	PLEX_ERROR_DIRECTORYOPENSTATE = 46 // the wrong directory open state
} PLEX_ERROR_TYPE;

typedef enum
{
	PLEX_ERROR_SEVERITY_NONE = 0, // < unassignable to error
	PLEX_ERROR_SEVERITY_IMPOSSIBLE = 1,
	PLEX_ERROR_SEVERITY_FATAL = 2,
	PLEX_ERROR_SEVERITY_MAJOR = 3,
	PLEX_ERROR_SEVERITY_MINOR = 4,
	PLEX_ERROR_SEVERITY_BADSTYLE = 5
} PLEX_ERROR_SEVERITY;

typedef struct
{
	PLEX_ERROR_CATEGORY category;
	PLEX_ERROR_TYPE type;
	PLEX_ERROR_SEVERITY severity;
	uint32_t lineNumber;
	const char* message, *message2, *fileloc;
} PLEX_ERROR;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// PLEX_fileLoadErrorPath is defined in fakestrings.h

	// shows an error pop up with title and message

	extern void PLEX_showErrorPopup(const char* const title, const char* const message); // < defined in window.c

	// the base function to call a new error

	extern void PLEX_errorInt(const PLEX_ERROR_CATEGORY category, const PLEX_ERROR_TYPE type, const PLEX_ERROR_SEVERITY severity, const char* const message, const char* const message2, const size_t lineNumber, const char* const fileloc);

	// function to manually print an error to terminal

	extern bool PLEX_printError(const PLEX_ERROR toPrint, const bool ignoreThreshold);

	// function to manually show an error pop up.

	extern bool PLEX_showError(const PLEX_ERROR toShow, const bool ignoreThreshold);

	// function to manually dump an error to file

	extern bool PLEX_dumpError(const PLEX_ERROR toDump, FILE* file);

	// checks for an SDL error and calls it if there is one present

	extern bool PLEX_errorSDLInt(const PLEX_ERROR_SEVERITY severity, const size_t line, const char* const file);

	// checks for an SDL image error and calls it if there is one present

	extern bool PLEX_errorSDLImageInt(const PLEX_ERROR_SEVERITY severity, const size_t line, const char* const file);

	// checks for a port audio error and calls it if there is one present

	extern bool PLEX_errorPortAudioInt(const PLEX_ERROR_SEVERITY severity, const PaError error, const size_t line, const char* const file);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// start error system state machine

	extern bool PLEX_startErrorSystem();

	// update error system state machine

	extern bool PLEX_updateErrorSystem();

	// end error system state machine

	extern void PLEX_endErrorSystem();

// setters ------------------------------------------------------------------------------------------------------------------

	// sets the error log date tot he current date. You don't really need to manually call this.

	extern void PLEX_setErrorLogDate();

	// sets the error date from the year, month, day, etc. values. This is also something you should never manually call.

	extern void PLEX_setErrorLogDateInt(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t minute, const uint8_t second);

	// sets the threshold to print errors to terminal by severity

	extern void PLEX_setErrorPrintingThreshold(const PLEX_ERROR_SEVERITY threshold);

	// sets the threshold to print errors to show error pop-ups by severity

	extern void PLEX_setErrorShowingThreshold(const PLEX_ERROR_SEVERITY threshold);

	// sets the threshold to print errors to terminate execution by severity

	extern void PLEX_setErrorFatalThreshold(const PLEX_ERROR_SEVERITY threshold);

	// sets whether to print errors at all

	extern void PLEX_printErrors(const bool set);

	// sets whether to show error pop-ups at all

	extern void PLEX_showErrors(const bool set);

	// set whether to dump errors to file at all

	extern void PLEX_dumpErrors(const bool set);

	// flags that errors that needs SDL to be running can be run. You never need to call this.

	extern void PLEX_flagSDLError();

	// unflags that errors that needs SDL to be running can be run. You never need to call this.

	extern void PLEX_unflagSDLError();

// getters ------------------------------------------------------------------------------------------------------------------

	// gets the error log's date. You probably never need to call this but it's available.

	extern void PLEX_getErrorLogDateInt(uint16_t* year, uint8_t* month, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second);

	// gets the readable string description of the error category

	extern const char* PLEX_getCategoryString(const PLEX_ERROR_CATEGORY category);

	// gets the readable string description of the error type

	extern const char* PLEX_getTypeString(const PLEX_ERROR_TYPE type);

	// gets the readable string description of the error severity

	extern const char* PLEX_getSeverityString(const PLEX_ERROR_SEVERITY severity);

	// gets the long readable description of the severity

	extern const char* PLEX_getSeverityStringLong(const PLEX_ERROR_SEVERITY severity);

	// gets the long readable description of the type

	extern const char* PLEX_getTypeStringLong(const PLEX_ERROR_TYPE type);

#ifdef __cplusplus
}
#endif

#endif
