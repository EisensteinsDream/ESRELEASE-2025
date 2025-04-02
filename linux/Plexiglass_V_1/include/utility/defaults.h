#ifndef PLEX_DEFAULT_H
#define PLEX_DEFAULT_H

// This is the unit that manages the 'defaults'. Basically any value managed externally by the config_xx.pcfg file. This is a file that every PLEX based program should have. It will even autogenerate every single time a PLEX based program is closed properly and one is not there. It's also always loaded at the beginning of execution. Also, this library also allows for new defaults to be added specific to the particular plex based program.

// NOTE: This is a unit with a state machine affiliated therefore has a start and end function. Some functions will not work if the 'start' function is not called successfully. Default's state machine does not have an 'update' function.

#include "meta/cinclude.h"
#include "meta/defaultnames.h"

#include "mem/expandarray.h"

#include "mem/mem.h"

#include "utility/error.h"

#include "utility/stringbank.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const char* fileloc) - returns bool

#define PLEX_loadConfig(fileloc) PLEX_loadConfigInt(fileloc, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_assignDefaultUInt8(name, min, max, def, comment) PLEX_assignDefaultUInt8Int(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_assignDefaultUInt32(name, min, max, def, comment) PLEX_assignDefaultUInt32Int(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_assignDefaultBool(name, def, comment) PLEX_assignDefaultBoolInt(name, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_assignDefaultDouble(name, min, max, def, comment) PLEX_assignDefaultDoubleInt(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_assignDefaultString(name, value, comment) PLEX_assignDefaultStringInt(name, value, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_addCustomDefaultUInt8(name, min, max, def, comment) PLEX_addCustomDefaultUInt8Int(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_addCustomDefaultUInt32(name, min, max, def, comment) PLEX_addCustomDefaultUInt32Int(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_addCustomDefaultBool(name, def, comment) PLEX_addCustomDefaultBoolInt(name, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment) - returns int64_t

#define PLEX_addCustomDefaultDouble(name, min, max, def, comment) PLEX_addCustomDefaultDoubleInt(name, min, max, def, comment, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment)

#define PLEX_addCustomDefaultString(name, value, comment) PLEX_addCustomDefaultStringInt(name, value, comment, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_width() PLEX_DEF_widthInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_height() PLEX_DEF_heightInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_killOnEscape() PLEX_DEF_killOnEscapeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_killOnClose() PLEX_DEF_killOnCloseInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_allowResize() PLEX_DEF_allowResizeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_allowMaximize() PLEX_DEF_allowMaximizeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_startMaximized() PLEX_DEF_startMaximizedInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_disableAudio() PLEX_DEF_disableAudioInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_cursorR() PLEX_DEF_cursorRInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_cursorG() PLEX_DEF_cursorGInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_cursorB() PLEX_DEF_cursorBInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_cursorW() PLEX_DEF_cursorWInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_cursorH() PLEX_DEF_cursorHInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_controllerPause() PLEX_DEF_controllerPauseInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_disableController() PLEX_DEF_disableControllerInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_disableJoystick() PLEX_DEF_disableJoystickInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_disableKeyboard() PLEX_DEF_disableKeyboardInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_disableMouse() PLEX_DEF_disableMouseInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_24HourTime() PLEX_DEF_24HourTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_textureDimensLimit() PLEX_DEF_textureDimensLimitInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_printErrors() PLEX_DEF_printErrorsInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_showErrors() PLEX_DEF_showErrorsInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_dumpErrors() PLEX_DEF_dumpErrorsInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_printErrorThreshold() PLEX_DEF_printErrorThresholdInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_showErrorThreshold() PLEX_DEF_showErrorThresholdInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_fatalErrorThreshold() PLEX_DEF_fatalErrorThresholdInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_headerlessCopy() PLEX_DEF_headerlessCopyInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_memProfile() PLEX_DEF_memProfileInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_memoryReport() PLEX_DEF_memoryReportInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_DEF_memoryReportToFile() PLEX_DEF_memoryReportToFileInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_startDefaults() PLEX_startDefaultsInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endDefaults() PLEX_endDefaultsInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_FAKESTRING_100

#define PLEX_getDefaultName(index) PLEX_getDefaultNameInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_DEF_ENTRYTYPE

#define PLEX_getDefaultType(index) PLEX_getDefaultTypeInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_FAKESTRING_500

#define PLEX_getDefaultComment(index) PLEX_getDefaultCommentInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns double

#define PLEX_getDefaultMinimum(index) PLEX_getDefaultMinimumInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns double

#define PLEX_getDefaultMaximum(index) PLEX_getDefaultMaximumInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns uint8_t

#define PLEX_getDefaultUint8(index) PLEX_getDefaultUint8Int(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns uint32_t

#define PLEX_getDefaultUint32(index) PLEX_getDefaultUint32Int(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns bool

#define PLEX_getDefaultBool(index) PLEX_getDefaultBoolInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns double

#define PLEX_getDefaultDouble(index) PLEX_getDefaultDoubleInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_FAKESTRING_100

#define PLEX_getDefaultString(index) PLEX_getDefaultStringInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name) - returns uint8_t

#define PLEX_getDefaultUint8ByName(name) PLEX_getDefaultUint8ByNameInt(name, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name) - returns uint32_t

#define PLEX_getDefaultUint32ByName(name) PLEX_getDefaultUint32ByNameInt(name, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name) - returns bool

#define PLEX_getDefaultBoolByName(name) PLEX_getDefaultBoolByNameInt(name, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name) - returns double

#define PLEX_getDefaultDoubleByName(name) PLEX_getDefaultDoubleByNameInt(name, __LINE__, __FILE__)

// ARGUMENTS: (const char* const name) - returns PLEX_FAKESTRING_100

#define PLEX_getDefaultStringByName(name) PLEX_getDefaultStringByNameInt(name, __LINE__, __FILE__)

// NO ARGUMENTS - returns size_t

#define PLEX_defaultCount() PLEX_defaultCountInt(__LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef enum
{
	PLEX_DEF_UINT8,
	PLEX_DEF_UINT32,
	PLEX_DEF_BOOL,
	PLEX_DEF_DOUBLE,
	PLEX_DEF_STRING,
	PLEX_DEF_NONE
} PLEX_DEF_ENTRYTYPE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// loads the config file

	extern bool PLEX_loadConfigInt(const char* fileloc, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the default state machine (this is automatically started at the start of PLEX)

	extern bool PLEX_startDefaultsInt(const size_t errorline, const char* const errorfile);

	//  ends the default state machine (this is automatically ended at the end of PLEX)

	extern void PLEX_endDefaultsInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// assigns a default of 'name' with a value of uint8_t 'def' which is ranged by a min and max value. Returns the index of the default assigned or -1 on failure.

	extern int64_t PLEX_assignDefaultUInt8Int(const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment, const size_t errorline, const char* const errorfile);

	// assigns a default of 'name' with a value of uint32_t 'def' which is ranged by a min and max value. Returns the index of the default assigned or -1 on failure.

	extern int64_t PLEX_assignDefaultUInt32Int(const char* const name, const uint32_t min, const uint32_t max, const uint32_t def, const char* const comment, const size_t errorline, const char* const errorfile);

	// assigns a default of 'name' with a value of boolean 'def'. Returns the index of the default assigned or -1 on failure.

	extern int64_t PLEX_assignDefaultBoolInt(const char* const name, const bool def, const char* const comment, const size_t errorline, const char* const errorfile);

	// assigns a default of 'name' with a value of double 'def' which is ranged by a min and max value. Returns the index of the default assigned or -1 on failure.

	extern int64_t PLEX_assignDefaultDoubleInt(const char* const name, const double min, const double max, const double def, const char* const comment, const size_t errorline, const char* const errorfile);

	// assigns a default of 'name' with a value of string 'def'. The string value is automatically created and managed in an internal string bank. Returns the index of the default assigned or -1 on failure.

	extern int64_t PLEX_assignDefaultStringInt(const char* const name, const char* const value, const char* const comment, const size_t errorline, const char* const errorfile);

	// adds a custom value of uint8_t def. This is like assign value but is intended to be used externally by a program that links to PLEX in order to create custom defaults for that program.

	extern int64_t PLEX_addCustomDefaultUInt8Int(const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment, const size_t errorline, const char* const errorfile);

	// adds a custom value of uint32_t def. This is like assign value but is intended to be used externally by a program that links to PLEX in order to create custom defaults for that program.

	extern int64_t PLEX_addCustomDefaultUInt32Int(const char* const name, const uint32_t min, const uint32_t max, const uint32_t def, const char* const comment, const size_t errorline, const char* const errorfile);

	// adds a custom value of bool def. This is like assign value but is intended to be used externally by a program that links to PLEX in order to create custom defaults for that program.

	extern int64_t PLEX_addCustomDefaultBoolInt(const char* const name, const bool def, const char* const comment, const size_t errorline, const char* const errorfile);

	// adds a custom value of double def. This is like assign value but is intended to be used externally by a program that links to PLEX in order to create custom defaults for that program.

	extern int64_t PLEX_addCustomDefaultDoubleInt(const char* const name, const double min, const double max, const double def, const char* const comment, const size_t errorline, const char* const errorfile);

	// adds a custom value of string def. This is like assign value but is intended to be used externally by a program that links to PLEX in order to create custom defaults for that program.

	extern int64_t PLEX_addCustomDefaultStringInt(const char* const name, const char* const value, const char* const comment, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns default screen width

	extern uint32_t PLEX_DEF_widthInt(const size_t errorline, const char* const errorfile);

	// returns default screen height

	extern uint32_t PLEX_DEF_heightInt(const size_t errorline, const char* const errorfile);

	// returns whether or not program kills on escape

	extern bool PLEX_DEF_killOnEscapeInt(const size_t errorline, const char* const errorfile);

	// returns whether or not program kills on pressing the close button

	extern bool PLEX_DEF_killOnCloseInt(const size_t errorline, const char* const errorfile);

	// returns whether resize is allowed

	extern bool PLEX_DEF_allowResizeInt(const size_t errorline, const char* const errorfile);

	// returns whether maximize is allowed

	extern bool PLEX_DEF_allowMaximizeInt(const size_t errorline, const char* const errorfile);

	// returns if the program is set to maximize

	extern bool PLEX_DEF_startMaximizedInt(const size_t errorline, const char* const errorfile);

	// returns if the audio is disabled

	extern bool PLEX_DEF_disableAudioInt(const size_t errorline, const char* const errorfile);

	// returns red of custom cursors

	extern uint8_t PLEX_DEF_cursorRInt(const size_t errorline, const char* const errorfile);

	// returns green of custom cursors

	extern uint8_t PLEX_DEF_cursorGInt(const size_t errorline, const char* const errorfile);

	// return blue of custom cursors

	extern uint8_t PLEX_DEF_cursorBInt(const size_t errorline, const char* const errorfile);

	//  return width of custom cursors

	extern double PLEX_DEF_cursorWInt(const size_t errorline, const char* const errorfile);

	//  return height of custom cursors

	extern double PLEX_DEF_cursorHInt(const size_t errorline, const char* const errorfile);

	// returns if the controller can pause the program or not

	extern bool PLEX_DEF_controllerPauseInt(const size_t errorline, const char* const errorfile);

	// returns if controller input is disabled

	extern bool PLEX_DEF_disableControllerInt(const size_t errorline, const char* const errorfile);

	extern bool PLEX_DEF_disableJoystickInt(const size_t errorline, const char* const errorfile);

	// returns if keyboard input is disabled

	extern bool PLEX_DEF_disableKeyboardInt(const size_t errorline, const char* const errorfile);

	// returns if mouse input is disabled

	extern bool PLEX_DEF_disableMouseInt(const size_t errorline, const char* const errorfile);

	// returns if time is defaulted to 24 hours

	extern bool PLEX_DEF_24HourTimeInt(const size_t errorline, const char* const errorfile);

	// returns the default maximum texture width or height

	extern uint32_t PLEX_DEF_textureDimensLimitInt(const size_t errorline, const char* const errorfile);

	// returns that the error system will print errors

	extern bool PLEX_DEF_printErrorsInt(const size_t errorline, const char* const errorfile);

	// returns that the error system will show pop-ups

	extern bool PLEX_DEF_showErrorsInt(const size_t errorline, const char* const errorfile);

	// returns that the error system will dump errors into a file

	extern bool PLEX_DEF_dumpErrorsInt(const size_t errorline, const char* const errorfile);

	// returns the threshold for error printing

	extern uint8_t PLEX_DEF_printErrorThresholdInt(const size_t errorline, const char* const errorfile);

	// returns the threshold for showing error pop-ups

	extern uint8_t PLEX_DEF_showErrorThresholdInt(const size_t errorline, const char* const errorfile);

	// returns the threshold for errors killing the program

	extern uint8_t PLEX_DEF_fatalErrorThresholdInt(const size_t errorline, const char* const errorfile);

	// returns whether or not headerless copies will be made of images

	extern bool PLEX_DEF_headerlessCopyInt(const size_t errorline, const char* const errorfile);

	// returns the memory profile by number 0-3

	extern uint8_t PLEX_DEF_memProfileInt(const size_t errorline, const char* const errorfile);

	// returns whether or not a memory report will be printed out

	extern bool PLEX_DEF_memoryReportInt(const size_t errorline, const char* const errorfile);

	// returns whether or not a memory report will be dumped to a file

	extern bool PLEX_DEF_memoryReportToFileInt(const size_t errorline, const char* const errorfile);

	// returns the smallest the window minimum width can be brought to

	extern uint32_t PLEX_DEF_minWindowW();

	// returns the smallest the window minimum height can be brought to

	extern uint32_t PLEX_DEF_minWindowH();

	// returns the largest the window maximum width can be brought to

	extern uint32_t PLEX_DEF_maxWindowW();

	// returns the largest the window maximum height can be brought to

	extern uint32_t PLEX_DEF_maxWindowH();

	// this will return the name of a default from it's index

	extern PLEX_FAKESTRING_100 PLEX_getDefaultNameInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the type of a default from it's index

	extern PLEX_DEF_ENTRYTYPE PLEX_getDefaultTypeInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the minimum of a default from it's index

	extern double PLEX_getDefaultMinimumInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the maximum of a default from it's index

	extern double PLEX_getDefaultMaximumInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the comment of a default from it's index

	extern PLEX_FAKESTRING_500 PLEX_getDefaultCommentInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's index as uint8_t

	extern uint8_t PLEX_getDefaultUint8Int(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's index as uint32_t

	extern uint32_t PLEX_getDefaultUint32Int(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's index as bool

	extern bool PLEX_getDefaultBoolInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's index as double

	extern double PLEX_getDefaultDoubleInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's index as string

	extern PLEX_FAKESTRING_100 PLEX_getDefaultStringInt(const size_t index, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's name as uint8_t

	extern uint8_t PLEX_getDefaultUint8ByNameInt(const char* const name, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's name as uint32_t

	extern uint32_t PLEX_getDefaultUint32ByNameInt(const char* const name, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's name as a boolean

	extern bool PLEX_getDefaultBoolByNameInt(const char* const name, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's name as a double

	extern double PLEX_getDefaultDoubleByNameInt(const char* const name, const size_t errorline, const char* const errorfile);

	// this will return the value of a default from it's name as a string

	extern PLEX_FAKESTRING_100 PLEX_getDefaultStringByNameInt(const char* const name, const size_t errorline, const char* const errorfile);

	// this will return the number of entries

	extern size_t PLEX_defaultCountInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
