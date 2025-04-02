#ifndef PLEX_INPUT_H
#define PLEX_INPUT_H

#include "windowing/texture.h"

#include "utility/math.h"
#include "utility/globaltime.h"

#include "terminate.h"

// Here is the unit that controls all input. Almost all of it is polled in the update function and returned otherwise. It also manages stuff like the custom cursors.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// NO ARGUMENTS - returns bool

#define PLEX_startInput() PLEX_startInputInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_updateInput() PLEX_updateInputInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endInput() PLEX_endInputInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd)

#define PLEX_setCustomCursor(tex, w, h, fx, fy, fw, fh, fxc, fyc, fwc, fhc, fxd, fyd, fwd, fhd) PLEX_setCustomCursorInt(tex, w, h, fx, fy, fw, fh, fxc, fyc, fwc, fhc, fxd, fyd, fwd, fhd, __LINE__, __FILE__)

// ARGUMENTS: (const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd, const uint8_t r, const uint8_t g, const uint8_t b)

#define PLEX_setCustomCursorTinted(tex, w, h, fx, fy, fw, fh, fxc, fyc, fwc, fhc, fxd, fyd, fwd, fhd, r, g, b) PLEX_setCustomCursorTintedInt(tex, w, h, fx, fy, fw, fh, fxc, fyc, fwc, fhc, fxd, fyd, fwd, fhd, r, g, b, __LINE__, __FILE__)

// ARGUMENTS: (const size_t tex)

#define PLEX_setCustomCursorClick(tex, fx, fy, fw, fh) PLEX_setCustomCursorClickInt(tex, fx, fy, fw, fh, __LINE__, __FILE__)

// ARGUMENTS: (const size_t tex)

#define PLEX_setCustomCursorDown(tex, fx, fy, fw, fh) PLEX_setCustomCursorDownInt(tex, fx, fy, fw, fh, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h)

#define PLEX_cursorWH(w, h) PLEX_cursorWHInt(w, h, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h)

#define PLEX_cursorFCoor(w, h) PLEX_cursorFCoorInt(w, h, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h)

#define PLEX_cursorFCoorClick(w, h) PLEX_cursorFCoorClickInt(w, h, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h)

#define PLEX_cursorFCoorDown(w, h) PLEX_cursorFCoorDownInt(w, h, __LINE__, __FILE__)

// ARGUMENTS: (uint32_t* w, uint32_t* h, uint32_t* fx, uint32_t* fy, uint32_t* fw, uint32_t* fh)

#define PLEX_cursorDimens(w, h, fx, fy, fw, fh) PLEX_cursorDimensInt(w, h, fx, fy, fw, fh, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller, const uint8_t button) - returns bool

#define PLEX_CONTROLLER_down(controller, button) PLEX_CONTROLLER_downInt(controller, button, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller, const uint8_t button) - returns bool

#define PLEX_CONTROLLER_press(controller, button) PLEX_CONTROLLER_pressInt(controller, button, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller, const size_t axisNum, const double sensitivity) - returns bool

#define PLEX_CONTROLLER_axis(controller, axisNum, sensitivity) PLEX_CONTROLLER_axisInt(controller, axisNum, sensitivity, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisUp(controller) PLEX_CONTROLLER_axisUpInt(controller, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisRight(controller) PLEX_CONTROLLER_axisRightInt(controller, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisDown(controller) PLEX_CONTROLLER_axisDownInt(controller, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisLeft(controller) PLEX_CONTROLLER_axisLeftInt(controller, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisUp2(controller, sensitivity) PLEX_CONTROLLER_axisUp2Int(controller, sensitivity, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisRight2(controller, sensitivity) PLEX_CONTROLLER_axisRight2Int(controller, sensitivity, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisDown2(controller, sensitivity) PLEX_CONTROLLER_axisDown2Int(controller, sensitivity, __LINE__, __FILE__)

// ARGUMENTS: (const size_t controller) - returns bool

#define PLEX_CONTROLLER_axisLeft2(controller, sensitivity) PLEX_CONTROLLER_axisLeft2Int(controller, sensitivity, __LINE__, __FILE__)

// NO ARGUMENTS - returns size_t

#define PLEX_CONTROLLER_count() PLEX_CONTROLLER_countInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// clears the mouse click buffer so anything between this function and the next PLEX_update call will not read mouse down or click as true

	extern void PLEX_clearMouseClicks();

	// clears the key input buffer so that no keys will be read as pressed or down between the calling of this function and next evocation of PLEX_update

	extern void PLEX_clearKeyInput();

	// checks if the mouse cursor is within x, y, w, and h. Optionally allowing the offset to be enabled.

	extern bool PLEX_mouseInside(const int64_t x, const int64_t y, const uint32_t w, const uint32_t h, const bool offset);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the input system returning false on failure (typically terminating the program). This is usually called by PLEX_start and rarely ever has to be called manually.

	extern bool PLEX_startInputInt(const size_t errorline, const char* const errorfile);

	// updates the input system returning false on failure (typically terminating the program). This is usually called by PLEX_update and rarely has to ever be called manually.

	extern bool PLEX_updateInputInt(const size_t errorline, const char* const errorfile);

	// ends the input system. This is usually called by PLEX_update and rarely has to ever be called manually.

	extern void PLEX_endInputInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets a custom cursor of wh from texture coordinates (fx, fy, fw, fh) and texture tex. Also includes texture coordinates for clicked (fxc, fyc, fwc, fhc) and for down (fxd, fyd, fwd, fhd).

	extern void PLEX_setCustomCursorInt(const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd, const size_t errorline, const char* const errorfile);

	// sets a custom cursor of wh from texture coordinates (fx, fy, fw, fh) and texture tex but tinted r, g, b (all forms including the click and down will be tinted this way). Also includes texture coordinates for clicked (fxc, fyc, fwc, fhc) and for down (fxd, fyd, fwd, fhd).

	extern void PLEX_setCustomCursorTintedInt(const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile);

	// sets the custom cursor texture for clicking

	extern void PLEX_setCustomCursorClickInt(const size_t tex, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const size_t errorline, const char* const errorfile);

	// sets the custom cursor texture for down

	extern void PLEX_setCustomCursorDownInt(const size_t tex, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const size_t errorline, const char* const errorfile);

	// unsets the custom cursor reverting back to the regular cursor

	extern void PLEX_unsetCustomCursor();

	// loads the cursor width and height. You do not need to call this manually.

	extern void PLEX_cursorWHInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// loads the cursor from coordinates. You do not need to call this manually.

	extern void PLEX_cursorFCoorInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// loads the click cursor from coordinates. You do not need to call this manually.

	extern void PLEX_cursorFCoorClickInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// loads the down cursor from coordinates. You do not need to call this manually.

	extern void PLEX_cursorFCoorDownInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// disables pausing

	extern void PLEX_disablePause();

	// enables pausing

	extern void PLEX_enablePause();

	// hides the cursor

	extern void PLEX_hideCursor();

	// shows the cursor

	extern void PLEX_unhideCursor();

	// shows the cursor if it's hidden and hides it if it's not

	extern void PLEX_toggleHideCursor();

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the w, h dimensions and the fx, fy, fw, fh texture cropping dimensions

	extern void PLEX_cursorDimensInt(uint32_t* w, uint32_t* h, uint32_t* fx, uint32_t* fy, uint32_t* fw, uint32_t* fh, const size_t errorline, const char* const errorfile);

	// returns the cursor's red tint

	extern uint8_t PLEX_cursorR();

	// return the cursor's green tint

	extern uint8_t PLEX_cursorG();

	// return the cursor's blue tint

	extern uint8_t PLEX_cursorB();

	// return the custom cursor's red tint

	extern uint8_t PLEX_customCursorR();

	// return the custom cursor's green tint

	extern uint8_t PLEX_customCursorG();

	// return the custom cursor's blue tint

	extern uint8_t PLEX_customCursorB();

	// return whether or not the cursor is hidden

	extern bool PLEX_cursorIsHidden();

	// returns whether or not the custom cursor is enabled

	extern bool PLEX_usingCustomCursor();

	// returns the texture of the custom cursor

	extern size_t PLEX_customCursor();

	// returns the texture of the regular cursor

	extern size_t PLEX_regularCursor();

	// returns the texture of the regular cursor clicking

	extern size_t PLEX_regularCursorClick();

	// returns the texture of the regular cursor down

	extern size_t PLEX_regularCursorDown();

	// returns true if the pause has been disabled

	extern bool PLEX_pauseDisabled();

	// returns true if right shift is down

	extern bool PLEX_KEY_rshift();

	// returns true if left shift is down

	extern bool PLEX_KEY_lshift();

	// returns true if any shift is down

	extern bool PLEX_KEY_shift();

	//  returns true if right control key is down

	extern bool PLEX_KEY_rctrl();

	// returns true if left control key is down

	extern bool PLEX_KEY_lctrl();

	// returns true if any control key is down

	extern bool PLEX_KEY_ctrl();

	// returns true if key passed is down. pass 'a' for the a key and '\n' for the new line or ' ' for space or '\t' for tab, etc.

	extern bool PLEX_KEY_down(const uint8_t key);

	// returns true if key passed is pressed. pass 'a' for the a key and '\n' for the new line or ' ' for space or '\t' for tab, etc.

	extern bool PLEX_KEY_press(const uint8_t key);

	// returns whether function key of 'number' is down. These are equivalent so F1 key is 1, F2 key is 2, etc.

	extern bool PLEX_KEY_fdown(const size_t number);

	// returns whether function key of 'number' is pressed. These are equivalent so F1 key is 1, F2 key is 2, etc.

	extern bool PLEX_KEY_fpress(const size_t number);

	// returns if backspace is down

	extern bool PLEX_backspace();

	// returns if backspace is pressed

	extern bool PLEX_backspacePress();

	// return if up key is down

	extern bool PLEX_upKey();

	// return if left key is down

	extern bool PLEX_leftKey();

	// return if down key is down

	extern bool PLEX_downKey();

	// return if right key is down

	extern bool PLEX_rightKey();

	// return if up key is pressed

	extern bool PLEX_upKeyPress();

	// return if left key is pressed

	extern bool PLEX_leftKeyPress();

	// return if down key is pressed

	extern bool PLEX_downKeyPress();

	// return if right key is pressed

	extern bool PLEX_rightKeyPress();

	// return if any key is down

	extern bool PLEX_KEY_anyKey();

	// return if any key is pressed

	extern bool PLEX_KEY_anyPress();

	// return the x of the mouse (not adjusted to offset)

	extern int64_t PLEX_MX();

	// return the y of the mouse (not adjusted to offset)

	extern int64_t PLEX_MY();

	// return if the left mouse key is down

	extern bool PLEX_left();

	// return if the left mouse key is clicked

	extern bool PLEX_leftClick();

	// return if the right mouse key is down

	extern bool PLEX_right();

	// return if the right mouse key is clicked

	extern bool PLEX_rightClick();

	// return if the middle button is pressed

	extern bool PLEX_midButton(); // < experimental/untested

	// return if the middle button is clicked

	extern bool PLEX_midButtonClick(); // < experimental/untested

	// return if the mouse x, y have changed since last PLEX_update

	extern bool PLEX_mouseMoved();

	// return the amount the mouse button has been scrolled

	extern double PLEX_mouseScroll(); // < experimental/untested

	// returns whether controller button 'button' is down or not. Button is decided by SDL macro. 'controller' is the controller ID, typically this should be 0 for the first controller.

	extern bool PLEX_CONTROLLER_downInt(const size_t controller, const uint8_t button, const size_t errorline, const char* const errorfile);

	// returns whether controller button 'button' is pressed or not. Button is decided by SDL macro. 'controller' is the controller ID, typically this should be 0 for the first controller.

	extern bool PLEX_CONTROLLER_pressInt(const size_t controller, const uint8_t button, const size_t errorline, const char* const errorfile);

	// returns whether the axis at 'axisNum' is in a direction with the sensitivity margin of 'sensitivity' (in order to weed out very slight or accidental tilts). This is how you determine analog controller direction. 'controller' is the controller ID, typically this should be 0 for the first controller.

	extern bool PLEX_CONTROLLER_axisInt(const size_t controller, const size_t axisNum, const double sensitivity, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is up. Has the sensitivity decided by default.

	extern bool PLEX_CONTROLLER_axisUpInt(const size_t controller, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is right. Has the sensitivity decided by default.

	extern bool PLEX_CONTROLLER_axisRightInt(const size_t controller, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is down. Has the sensitivity decided by default.

	extern bool PLEX_CONTROLLER_axisDownInt(const size_t controller, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is left. Has the sensitivity decided by default.

	extern bool PLEX_CONTROLLER_axisLeftInt(const size_t controller, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is up.

	extern bool PLEX_CONTROLLER_axisUp2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is right.

	extern bool PLEX_CONTROLLER_axisRight2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is down.

	extern bool PLEX_CONTROLLER_axisDown2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile);

	// a quicker way to read that the axis is left.

	extern bool PLEX_CONTROLLER_axisLeft2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile);

	// returns the number of controllers

	extern size_t PLEX_CONTROLLER_countInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
