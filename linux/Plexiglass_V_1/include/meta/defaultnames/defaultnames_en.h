#ifndef PLEX_DEFAULTNAMES_EN_H
#define PLEX_DEFAULTNAMES_EN_H

// This is a header which contains all of the default name macro strings for the English version of PLEX. This is basically the default message equivalent of "meta/language/language_en.h". More information can be found there or in "meta/language.h".

// NOTE: As with all headers in the meta folder, there is no correlating source file.

#define PLEX_DEFAULT_TRUE "true"
#define PLEX_DEFAULT_FALSE "false"

// the name of the file itself

#define PLEX_DEFAULT_CONFIGPATH "config_en.pcfg"

// NAMES:

// termination

#define PLEX_DEFNAME_KILLONESCAPE "kill on escape"
#define PLEX_DEFNAME_KILLONCLOSE "kill on close"

// windowing

#define PLEX_DEFNAME_MAINWINWIDTH "main window width"
#define PLEX_DEFNAME_MAINWINHEIGHT "main window height"

#define PLEX_DEFNAME_ALLOWRESIZE "allow resize"
#define PLEX_DEFNAME_ALLOWMAXIMIZE "allow maximize"
#define PLEX_DEFNAME_STARTMAXIMIZED "start maximized"

// input

#define PLEX_DEFNAME_CURSOR_R "cursor red"
#define PLEX_DEFNAME_CURSOR_G "cursor green"
#define PLEX_DEFNAME_CURSOR_B "cursor blue"

#define PLEX_DEFNAME_CURSOR_W "cursor width"
#define PLEX_DEFNAME_CURSOR_H "cursor height"

#define PLEX_DEFNAME_CONTROLLERPAUSE "allow controller pause"

#define PLEX_DEFNAME_DISABLECONTROLLER "disable controller"
#define PLEX_DEFNAME_DISABLEJOYSTICK "disable joystick"
#define PLEX_DEFNAME_DISABLEKEYBOARD "disable keyboard"
#define PLEX_DEFNAME_DISABLEMOUSE "disable mouse"

// sound

#define PLEX_DEFNAME_DISABLESOUND "disable sound"

// date and time

#define PLEX_DEFNAME_24HOURTIME "24 hour time"

// resource limitations

#define PLEX_DEFNAME_TEXTUREDIMENSLIMIT "texture dimension limit"

// error printing

#define PLEX_DEFNAME_PRINTERRORS "print errors"
#define PLEX_DEFNAME_SHOWERRORS "show errors"
#define PLEX_DEFNAME_DUMPERRORS "dump errors"

#define PLEX_DEFNAME_PRINTTHRESHOLD "print error threshold"
#define PLEX_DEFNAME_SHOWTHRESHOLD "show error threshold"
#define PLEX_DEFNAME_FATALTHRESHOLD "fatal error threshold"

// texture

#define PLEX_DEFNAME_HEADERLESSCOPY "copy headerless textures"

// memory

#define PLEX_DEFNAME_MEMORYPROFILE "memory profile"

#define PLEX_DEFNAME_MEMORYREPORT "print memory report"
#define PLEX_DEFNAME_MEMORYREPORTTOFILE "print memory report to file"

// DESCRIPTIONS:

// termination

#define PLEX_DEFDESC_KILLONESCAPE "Controls if the ESC key kills the program. Either this or the kill on close need to be true."
#define PLEX_DEFDESC_KILLONCLOSE "Controls if closing the window kills the program. Either this or the kill on close need to be true."

// windowing

#define PLEX_DEFDESC_MAINWINWIDTH "Width of the window must be between 800 and 4096"
#define PLEX_DEFDESC_MAINWINHEIGHT "Height of the window must be between 600 and 2160"

#define PLEX_DEFDESC_ALLOWRESIZE "Controls whether or not you can resize the game window."
#define PLEX_DEFDESC_ALLOWMAXIMIZE "Controls whether or not you can maximize the window. Window resize must be enabled for this to work"
#define PLEX_DEFDESC_STARTMAXIMIZED "Starts window maximized (must have both allow maximize and allow resize enabled)"

// input

#define PLEX_DEFDESC_CURSOR_R "Sets cursor to red"
#define PLEX_DEFDESC_CURSOR_G "Sets cursor to green"
#define PLEX_DEFDESC_CURSOR_B "Sets cursor to blue"

#define PLEX_DEFDESC_CURSOR_W "Sets cursor width"
#define PLEX_DEFDESC_CURSOR_H "Sets cursor height"

#define PLEX_DEFDESC_CONTROLLERPAUSE "Decides whether or not the 'pause' button on a controller pauses the game"

#define PLEX_DEFDESC_DISABLECONTROLLER "Disable controller input"
#define PLEX_DEFDESC_DISABLEJOYSTICK "Disable joystick input (currently does nothing)"
#define PLEX_DEFDESC_DISABLEKEYBOARD "Disable keyboard input (does not work if both controller and mouse are disabled, does not interfere with close on escape)"
#define PLEX_DEFDESC_DISABLEMOUSE "disable mouse input"

// sound

#define PLEX_DEFDESC_DISABLESOUND "Disables all sound if true"

// time

#define PLEX_DEFDESC_24HOURTIME "Sets the default time to 24-hours. Some times may still be 12, but those not specified as 12 in code will not."

// resource limitations

#define PLEX_DEFDESC_TEXTUREDIMENSLIMIT "Sets the maximum dimensions (by pixel) that a texture can be loaded. If either the w or h is greater than this the loaded texture is scaled down (lower this number if your system is not loading textures)"

// error printing

#define PLEX_DEFDESC_PRINTERRORS "print errors to terminal. Overriden by threshold."
#define PLEX_DEFDESC_SHOWERRORS "show errors in pop-up. Overriden by threshold."
#define PLEX_DEFDESC_DUMPERRORS "dump errors in pop-up."


#define PLEX_DEFDESC_PRINTTHRESHOLD "the error severity to print to console: (1 - impossible, 2 - fatal, 3 - major, 4 - minor, 5 - badstyle)"
#define PLEX_DEFDESC_SHOWTHRESHOLD "the error severity to show to console: (1 - impossible, 2 - fatal, 3 - major, 4 - minor, 5 - badstyle)"
#define PLEX_DEFDESC_FATALTHRESHOLD "the error severity to kill program: (2 - fatal, 3 - major, 4 - minor, 5 - badstyle). Cannot be impossible or fatal errors will always terminate."

// texture

#define PLEX_DEFDESC_HEADERLESSCOPY "Allows the creation of headerless texture. Reccomended unless you're trying to conserve drive space."

// memory

#define PLEX_DEFDESC_MEMORYPROFILE "Sets a memory profile by number. The lower the memory profile the less memory is precached. 0 - low, 1 - medium, 2 - high, 3 - very high"

#define PLEX_DEFDESC_MEMORYREPORT "Prints the memory report for memory allocated by PLEX's smart memory. Useful for hunting down memory hangs, not useful for casual users."
#define PLEX_DEFDESC_MEMORYREPORTTOFILE "Makes sure to export memory report to file if it's printing it. If memory reporting is off, this does nothing."

#endif
