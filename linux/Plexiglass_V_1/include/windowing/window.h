#ifndef PLEX_WINDOW_H
#define PLEX_WINDOW_H

#include "windowing/graphics_low.h"

#include "utility/error.h"

// This unit contains all functions related to manipulating the window. PLEX's windowing system automatically generates a borderspace which can be changed in terms of ratio (defaults to 4:3. Which means you can draw outside that centered ratio, but you can also optionally keep in it by making offset booleans 'true'. You can also change the size of the ratio). It also manages plex units which are a screen size that's normally 25x25 on a 800x600 screen resolution but adjust to the window size without losing their proportion. This allows the window to be freely resized. This does not handle any input or direct drawing though. Those are handled by the input and graphics units.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// these are simply for the math needed to change the ratio. It's based off of 800x600 but that is irrelevant to the actual screen size. THEY SHOULD NEVER BE CHANGED. Use PLEX_changeScreenRatio if you want to change the offset area.

#define PLEX_HEIGHTUNITMAXBASE 24
#define PLEX_SCREENUNITBASE 25
#define PLEX_SCREENRATIOBASE 600.0

// NO ARGUMENTS

#define PLEX_updateWindowResize() PLEX_updateWindowResizeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_restoreWindow() PLEX_restoreWindowInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_markSizing() PLEX_markSizingInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_unmarkSizing() PLEX_unmarkSizingInt(__LINE__, __FILE__)

// ARGUMENTS: (const double ratio)

#define PLEX_changeScreenRatio(ratio) PLEX_changeScreenRatioInt(ratio, __LINE__, __FILE__)

// ARGUMENTS: (const char* const title, const uint32_t width, const uint32_t height, const double ratio) - returns bool

#define PLEX_startWindow(title, width, height, ratio) PLEX_startWindowInt(title, width, height, ratio, __LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_updateWindow() PLEX_updateWindowInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endWindow() PLEX_endWindowInt(__LINE__, __FILE__)

// ARGUMENTS: (const char* const title) - returns const char*

#define PLEX_setWindowTitle(title) PLEX_setWindowTitleInt(title, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_getWindowTitle() PLEX_getWindowTitleInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// unmaximizes the window. Probably won't be calling this manually.

	extern void PLEX_restoreWindowInt(const size_t errorline, const char* const errorfile);

	// updates the window has been resized. Does not need to be called manually.

	extern void PLEX_updateWindowResizeInt(const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the window subsystem and creates the base window. Returns bool on failure. If this returns bool in PLEX_start the program will terminate. Does not need to be manually called as it's called in PLEX_start.

	extern bool PLEX_startWindowInt(const char* const title, const uint32_t width, const uint32_t height, const double ratio, const size_t errorline, const char* const errorfile);

	// updates the window subsystem and creates the base window. Returns bool on failure. If this returns bool in PLEX_update the program will terminate. Does not need to be manually called as it's called in PLEX_update.

	extern bool PLEX_updateWindowInt(const size_t errorline, const char* const errorfile);

	// ends the window subsystem. Does not need to be manually called as it's called in PLEX_end.

	extern void PLEX_endWindowInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// marks that the window is resizing. Does not need to be manually called.

	extern void PLEX_markSizingInt(const size_t errorline, const char* const errorfile);

	// unmarks that the window is resizing. Does not need to be manually called

	extern void PLEX_unmarkSizingInt(const size_t errorline, const char* const errorfile);

	// changes the centralized inner space which the 'offset' bool is proportion to. The ratio double is a factor you multiply the height to get the width. ie. if you're doing a 4:3 screen ratio the double would be 1.333333 because 4/3 is one and one third.

	extern void PLEX_changeScreenRatioInt(const double ratio, const size_t errorline, const char* const errorfile);

	// changes the title of the main window

	extern void PLEX_setWindowTitleInt(const char* const title, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns a plex unit. This is a unit of measurement that changes with the size of the window. On an 800x600 resolution it's 25.

	extern double PLEX_ONEUNIT();

	// returns a plex pixel. This is the smallest unit of pixel avail. At 800x600 this is one.

	extern double PLEX_UNITPIXEL();

	// returns a number of plex units of count. Count can be a decimal number.

	extern double PLEX_UNIT(const double count);

	// translates a percentage of the width within the offset area

	extern uint32_t PLEX_TRANS_W(const double perc);

	// translates a percentage of the height within the offset area

	extern uint32_t PLEX_TRANS_H(const double perc);

	// returns the width of the screen. If offset is true it only factors the offset area within the centered screen ratio.

	extern uint32_t PLEX_WW(const bool offset);

	// returns the height of the screen. If offset is true it only factors the offset area within the centered screen ratio.

	extern uint32_t PLEX_WH(const bool offset);

	// returns the width offset area or the width in pixels of everything left of the offset area.

	extern uint32_t PLEX_WOFFSET();

	// returns the height offset area or the height in pixels of everything above the offset area.

	extern uint32_t PLEX_HOFFSET();

	// returns the percentage of the screen that's the width offset

	extern double PLEX_WOFFSETPERC();

	// returns the percentage of the screen that's the height offset

	extern double PLEX_HOFFSETPERC();

	// returns the percentage of the width that the offset space covers

	extern double PLEX_WCROPPERC();

	// returns the percentage of the height that the offset space covers

	extern double PLEX_HCROPPERC();

	// returns the maximum amount of plex units in the ratio area's width

	extern uint32_t PLEX_WIDTHUNITMAX();

	// returns the maximum amount of plex units in the ratio area's height

	extern uint32_t PLEX_HEIGHTUNITMAX();

	// returns true if the window is resizing

	extern bool PLEX_isSizing();

	// returns a pointer to the main window

	extern SDL_Window* PLEX_getWindowContents();

	// returns the window's title as a c-string

	extern const char* PLEX_getWindowTitleInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
