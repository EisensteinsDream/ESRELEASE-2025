#ifndef PLEX_ERRORMESS_EN_H
#define PLEX_ERRORMESS_EN_H

// This is a header which contains all of the error macro strings for the English version of PLEX. This is basically the error message equivalent of "meta/language/language_en.h". More information can be found there or in "meta/language.h".

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// ERROR CONSTRUCTION STRINGS

#define PLEX_ERRORMESS_ERROR_FILENAMEMID " for file "
#define PLEX_ERRORMESS_ERROR_CATEGORY "\" in category \""
#define PLEX_ERRORMESS_ERROR_FILE " in file \""
#define PLEX_ERRORMESS_ERROR_FOOTER ") "
#define PLEX_ERRORMESS_ERROR_HEADER "PLEX Error! "
#define PLEX_ERRORMESS_ERROR_LINE "@ line "
#define PLEX_ERRORMESS_ERROR_MESSAGEEND "\")"
#define PLEX_ERRORMESS_ERROR_MESSAGESPLIT ": \""
#define PLEX_ERRORMESS_ERROR_MESSAGESPLIT2 "\" | \""
#define PLEX_ERRORMESS_ERROR_MESSAGESTART "\" ("
#define PLEX_ERRORMESS_ERROR_PRINTTHRESHOLDCHANGED "Error printing threshold has been changed to \""
#define PLEX_ERRORMESS_ERROR_PRINTTHRESHOLDCHANGED2 "\". No error with a severity below this will be printed."

#define PLEX_ERRROMESS_ERROR_DUMPFAIL_FILE "Failed to open a file to dump errors. If you want dump errors on, make sure to have a folder called 'error' in your main directory. If you want dumping off, set dump errors to false in the config."
#define PLEX_ERRORMESS_ERROR_DUMPFAIL_FILELOC "Failed to create dumpfile file loc, therefore dumpfile for errors has not been created."
#define PLEX_ERRROMESS_ERROR_SUPPRESSFAIL_FILE "Failed to open a file to dump suppressed errors. If you want dump errors on, make sure to have a folder called 'error' in your main directory. If you want dumping off, set dump errors to false in the config."
#define PLEX_ERRROMESS_ERROR_SUPPRESSFAIL_FILELOC "Failed to create suppress file loc, therefore suppressfile for errors has not been created"
#define PLEX_ERRORMESS_ERROR_LINENUMBEREXCEED "The line number exceeded the number of digits for the print buffer so error not printed. Something is probably really wrong if this is printing unless you have an unusually large source file. The macro 'PLEX_LIMIT_ERROR_LINENUMMAX' in hardlimits.h decides this. It should default to 10."

#define PLEX_ERRORMESS_ERROR_SEVERITY ". Error Severity: "
#define PLEX_ERRORMESS_ERROR_SEVERITY_LONG " ("
#define PLEX_ERRORMESS_ERROR_SHOWNTHRESHOLDCHANGED "Error showing threshold has been changed to \""
#define PLEX_ERRORMESS_ERROR_SHOWNTHRESHOLDCHANGED2 "\". No error with a severity below this will be shown in a popup."
#define PLEX_ERRORMESS_ERROR_SHOWOVERFLOW "Pop-up errors have reached their printable limit. This is probably something very bad. The program will terminate. Recompiling code from source is reccomended. If that doesn't work, please report bug."
#define PLEX_ERRORMESS_ERROR_SYSTEMFAIL_NOOS "No operating system detected! This means that PLEX somehow compiled incorrectly."
#define PLEX_ERRORMESS_ERROR_SYSTEMFAIL_INIT "The error system has failed on initialization!"
#define PLEX_ERRORMESS_ERROR_TERMINATE "TERMINATED!"
#define PLEX_ERRORMESS_ERROR_TERMINATEDTHRESHOLDCHANGED "Fatal error threshold has been changed to \""
#define PLEX_ERRORMESS_ERROR_TERMINATEDTHRESHOLDCHANGED2 "\". Any error with an equal or above severity will terminate the program."
#define PLEX_ERRORMESS_ERROR_MESSDIVIDE " | "
#define PLEX_ERRORMESS_ERROR_EXCLAMATION "! "
#define PLEX_ERRORMESS_ERROR_POPUPTITLE " Error! "
#define PLEX_ERRORMESS_ERROR_FATALERROR "Terminal Error! Program will be terminated!"
#define PLEX_ERRORMESS_ERROR_ATTEMPTIMPOSSIBLEERROR "You cannot set the error termination threshold above 'fatal'. Which means it's impossible to set it to 'impossible' or 'none'. This cannot happen. It will be set to 'fatal'."
#define PLEX_ERRORMESS_ERROR_NOCATEGORY "You cannot create an error with category of 'none'"
#define PLEX_ERRORMESS_ERROR_NOTYPE "You cannot create an error with type of 'none'"
#define PLEX_ERRORMESS_ERROR_NOSEVERITY "You cannot create an error with severity of 'none'"

// CATEGORY STRINGS

#define PLEX_ERRORMESS_CATEGORY_NONE "None (This should be impossible)"
#define PLEX_ERRORMESS_CATEGORY_START "Start"
#define PLEX_ERRORMESS_CATEGORY_UPDATE "Update"
#define PLEX_ERRORMESS_CATEGORY_SDL "SDL"
#define PLEX_ERRORMESS_CATEGORY_PORTAUDIO "PortAudio"
#define PLEX_ERRORMESS_CATEGORY_MATH "Math"
#define PLEX_ERRORMESS_CATEGORY_DATETIME "Datetime"
#define PLEX_ERRORMESS_CATEGORY_FAKESTRING "Fakestrings"
#define PLEX_ERRORMESS_CATEGORY_STRINGBANK "Stringbank"
#define PLEX_ERRORMESS_CATEGORY_DEFAULT "Default"
#define PLEX_ERRORMESS_CATEGORY_MEM "Memory"
#define PLEX_ERRORMESS_CATEGORY_ARRAY "Array"
#define PLEX_ERRORMESS_CATEGORY_SOUND "Sound"
#define PLEX_ERRORMESS_CATEGORY_TEXTURE "Texture"
#define PLEX_ERRORMESS_CATEGORY_WINDOW "Window"
#define PLEX_ERRORMESS_CATEGORY_PROMINENCEMACHINE "Prominence Machine"
#define PLEX_ERRORMESS_CATEGORY_SCREENEFFECTS "Screen Effects"
#define PLEX_ERRORMESS_CATEGORY_LOWLEVELGRAPHICS_GL "Low Level Graphics - GL"
#define PLEX_ERRORMESS_CATEGORY_LOWLEVELGRAPHICS_SDL "Low Level Graphics - SDL"
#define PLEX_ERRORMESS_CATEGORY_FILEPARSE "File Parser"
#define PLEX_ERRORMESS_CATEGORY_INPUT "Input"
#define PLEX_ERRORMESS_CATEGORY_GENEARTOR "Generator"
#define PLEX_ERRORMESS_CATEGORY_SPRITETHEATER "Sprite Theater"
#define PLEX_ERRORMESS_CATEGORY_TIMING "Timing System"
#define PLEX_ERRORMESS_CATEGORY_GRAPHICS "Graphics"
#define PLEX_ERRORMESS_CATEGORY_ANIMATION "Animation"
#define PLEX_ERRORMESS_CATEGORY_DIRECTORY "Directory"
#define PLEX_ERRORMESS_CATEGORY_SCROLLER "Scroller"
// #define PLEX_ERRORMESS_CATEGORY_SYSTEMREAD "System Read" // PLEX_V2
#define PLEX_ERRORMESS_CATEGORY_INPROJECT "In Project Error"

// SEVERITY STRINGS

#define PLEX_ERRORMESS_SEVERITY_NONE "None"
#define PLEX_ERRORMESS_SEVERITY_IMPOSSIBLE "Severity"
#define PLEX_ERRORMESS_SEVERITY_IMPOSSIBLE_LONG "Impossible errors are the most serious errors. They only happen if something was corrupted by a bad modification of code. Every impossible error is fatal"
#define PLEX_ERRORMESS_SEVERITY_FATAL "Fatal"
#define PLEX_ERRORMESS_SEVERITY_FATAL_LONG "Fatal error indicates the program cannot safely continue after error is posted. This should always terminate the program"
#define PLEX_ERRORMESS_SEVERITY_MAJOR "Major"
#define PLEX_ERRORMESS_SEVERITY_MAJOR_LONG "A major error isn't quite as serious as a fatal error but it's something to be concerned about. It may terminate the program based on plex settings. There's a config file entry if you only want 'fatal' and 'impossible' errors to execute"
#define PLEX_ERRORMESS_SEVERITY_MINOR "Minor"
#define PLEX_ERRORMESS_SEVERITY_MINOR_LONG "Minor errors may be a problem but rarely ever are on their own. It's good for optimization and final unit checks to make this terminate. Otherwise, it really shouldn't. If this error causes to terminate otherwise, change the severity level in the config file"
#define PLEX_ERRORMESS_SEVERITY_BADSTYLE "Bad Style"
#define PLEX_ERRORMESS_SEVERITY_BADSTYLE_LONG "An error which is pretty much harmless but might be an indication of some sloppy code. Typically you don't even want this error to print let alone terminate unless you are developing something yourself. The print, show, and terminate levels are in the config file"

// TYPE STRINGS

#define PLEX_ERRORMESS_TYPE_NONETYPE "No Type - This shouldn't happen"
#define PLEX_ERRORMESS_TYPE_START "Start Failure"
#define PLEX_ERRORMESS_TYPE_LOADEXTERNALMODULE "Load External Module Failure"
#define PLEX_ERRORMESS_TYPE_EXTERNALMODULE "External Module Error"
#define PLEX_ERRORMESS_TYPE_CREATE "Creation Failure"
#define PLEX_ERRORMESS_TYPE_UPDATE "Update Failure"
#define PLEX_ERRORMESS_TYPE_MINMAXREVERSE "Min/Max Reverse"
#define PLEX_ERRORMESS_TYPE_DEFAULTPOP "Default Populate Fail"
#define PLEX_ERRORMESS_TYPE_FILELOAD "File Load Fail"
#define PLEX_ERRORMESS_TYPE_FILESAVE "File Save Fail"
#define PLEX_ERRORMESS_TYPE_DOUBLESTART "Double Start"
#define PLEX_ERRORMESS_TYPE_ENDBEFORESTART "End Before Start"
#define PLEX_ERRORMESS_TYPE_ACTIONBEFORESTART "Action Execute Before Start"
#define PLEX_ERRORMESS_TYPE_FREENULL "Free Null Attempt"
#define PLEX_ERRORMESS_TYPE_FREENULLPTR "Free Null Pointer Attempt"
#define PLEX_ERRORMESS_TYPE_ALLOCFAIL "Allocation Failure"
#define PLEX_ERRORMESS_TYPE_CONTENTCORRUPTION "Content Corruption"
#define PLEX_ERRORMESS_TYPE_EXPANDNULL "Expand NULL Failure"
#define PLEX_ERRORMESS_TYPE_EXPAND "Expand Failure"
#define PLEX_ERRORMESS_TYPE_INCREMENTNULL "Increment NULL Attempt"
#define PLEX_ERRORMESS_TYPE_INCREMENT "Increment Failure"
#define PLEX_ERRORMESS_TYPE_DECREMENT "Decrement Failure"
#define PLEX_ERRORMESS_TYPE_CLEAR "Clear Failure"
#define PLEX_ERRORMESS_TYPE_SWAP "Swap Failure"
#define PLEX_ERRORMESS_TYPE_CUT "Cut Failure"
#define PLEX_ERRORMESS_TYPE_REARRANGE "Rearrange Failure"
#define PLEX_ERRORMESS_TYPE_BADBUFFERSOUNDHOOK "Bad Buffer in Sound Hook"
#define PLEX_ERRORMESS_TYPE_OVERLIMIT "Out of Range"
#define PLEX_ERRORMESS_TYPE_ISNULL "Is Null"
#define PLEX_ERRORMESS_TYPE_SAMEVALUE "Same Value"
#define PLEX_ERRORMESS_TYPE_UNDERLIMIT "Under Limit"
#define PLEX_ERRORMESS_TYPE_ZEROVALUE "Zero Value"
#define PLEX_ERRORMESS_TYPE_DISABLED "Disabled Feature"
#define PLEX_ERRORMESS_TYPE_BADOPERATION "Bad Operation"
#define PLEX_ERRORMESS_TYPE_HOOKCORRUPTION "Hook Corruption"
#define PLEX_ERRORMESS_TYPE_NOSTRINGLEN "No String Length"
#define PLEX_ERRORMESS_TYPE_UPDATEBEFORESTART "Update Before Start"
#define PLEX_ERRORMESS_TYPE_SUCCESSCHECKFAIL "Success Check Failed"
#define PLEX_ERRORMESS_TYPE_ISNULLTEXTURE "NULL Texture"
#define PLEX_ERRORMESS_TYPE_SOUNDHOOKINUSE "Sound Hook In Use"
#define PLEX_ERRORMESS_TYPE_SOUNDCHANNELSTATE "Sound Channel State"
#define PLEX_ERRORMESS_TYPE_ACQUIRE "Acquire"
#define PLEX_ERRORMESS_TYPE_ACQUIRELAST "Acquire Last"
#define PLEX_ERRORMESS_TYPE_STREAMSTATE "Sound Stream State"
#define PLEX_ERRORMESS_TYPE_FILETYPE "File type"
#define PLEX_ERRORMESS_TYPE_DOUBLEDEALLOC "Double Dealloc"
#define PLEX_ERRORMESS_TYPE_DIRECTORYOPENSTATE "Directory State"

// LONG TYPE STRINGS

#define PLEX_ERRORMESS_TYPE_NONETYPE_LONG "No Type Description - this shouldn't happen"
#define PLEX_ERRORMESS_TYPE_START_LONG "Subsystem failed to start"
#define PLEX_ERRORMESS_TYPE_LOADEXTERNALMODULE_LONG "External module failed to load"
#define PLEX_ERRORMESS_TYPE_EXTERNALMODULE_LONG "Error related to external module function"
#define PLEX_ERRORMESS_TYPE_CREATE_LONG "failed to create something"
#define PLEX_ERRORMESS_TYPE_UPDATE_LONG "failed to update something"
#define PLEX_ERRORMESS_TYPE_MINMAXREVERSE_LONG "the minimum and maximum are reversed"
#define PLEX_ERRORMESS_TYPE_DEFAULTPOP_LONG "a default value failed to populate"
#define PLEX_ERRORMESS_TYPE_FILELOAD_LONG "failed to load a file"
#define PLEX_ERRORMESS_TYPE_FILESAVE_LONG "failed to save a file"
#define PLEX_ERRORMESS_TYPE_DOUBLESTART_LONG "attempted to double start a system"
#define PLEX_ERRORMESS_TYPE_ENDBEFORESTART_LONG "attempted to end a system before starting it"
#define PLEX_ERRORMESS_TYPE_ACTIONBEFORESTART_LONG "attempted an action before a system set up"
#define PLEX_ERRORMESS_TYPE_FREENULL_LONG "attempted to free a NULL"
#define PLEX_ERRORMESS_TYPE_FREENULLPTR_LONG "attempted to free but the double pointer to the data was pointing to NULL."
#define PLEX_ERRORMESS_TYPE_ALLOCFAIL_LONG "failed to allocate a piece of memory"
#define PLEX_ERRORMESS_TYPE_CONTENTCORRUPTION_LONG "contents of something have been corrupted"
#define PLEX_ERRORMESS_TYPE_EXPANDNULL_LONG "attempted to expand an array from NULL pointer or NULL contents"
#define PLEX_ERRORMESS_TYPE_EXPAND_LONG "failed to expand array contents"
#define PLEX_ERRORMESS_TYPE_INCREMENTNULL_LONG "attempted to increment an array from NULL pointer or NULL contents"
#define PLEX_ERRORMESS_TYPE_DECREMENT_LONG "failed to decrement array contents"
#define PLEX_ERRORMESS_TYPE_CLEAR_LONG "failed to clear an array"
#define PLEX_ERRORMESS_TYPE_SWAP_LONG "failed to swap array"
#define PLEX_ERRORMESS_TYPE_CUT_LONG "failed to cut array"
#define PLEX_ERRORMESS_TYPE_REARRANGE_LONG "failed to rearrange array"
#define PLEX_ERRORMESS_TYPE_BADBUFFERSOUNDHOOK_LONG "the buffer in the sound hook is bad for whatever reason"
#define PLEX_ERRORMESS_TYPE_OVERLIMIT_LONG "went out of bounds when accessing a value"
#define PLEX_ERRORMESS_TYPE_ISNULL_LONG "something is NULL that really shouldn't be"
#define PLEX_ERRORMESS_TYPE_SAMEVALUE_LONG "Two values that shouldn't be the same are the same"
#define PLEX_ERRORMESS_TYPE_UNDERLIMIT_LONG "Value is under the limit"
#define PLEX_ERRORMESS_TYPE_ZEROVALUE_LONG "Value is zero where it cannot be"
#define PLEX_ERRORMESS_TYPE_DISABLED_LONG "Tried to access a disabled feature. Usually, this is completely harmless. If not intended, then check the config file to see what's disabled."
#define PLEX_ERRORMESS_TYPE_BADOPERATION_LONG "This operation has been blocked for whatever reason."
#define PLEX_ERRORMESS_TYPE_HOOKCORRUPTION_LONG "A hook function has been corrupted somewhere. This is serious and likely demands the source to be recompiled."
#define PLEX_ERRORMESS_TYPE_NOSTRINGLEN_LONG "A string that should have contents is 0 in length"
#define PLEX_ERRORMESS_TYPE_UPDATEBEFORESTART_LONG "Attempted to update a subsystem before starting it. This kind of shouldn't happen but it's not severe enough for an impossible error. However, typically, the update PLEX function should update all subsystems so you don't have to worry about it."
#define PLEX_ERRORMESS_TYPE_SUCCESSCHECKFAIL_LONG "A success check for a function has failed."
#define PLEX_ERRORMESS_TYPE_ISNULLTEXTURE_LONG "an operation requiring a texture has been passed a NULL texture"
#define PLEX_ERRORMESS_TYPE_SOUNDHOOKINUSE_LONG "A process was halted because the sound hook is already in use"
#define PLEX_ERRORMESS_TYPE_SOUNDCHANNELSTATE_LONG "A process was halted because the sound channel was either on/off and it couldn't have happened in that state."
#define PLEX_ERRORMESS_TYPE_ACQUIRE_LONG "An attempt to acquire something has failed"
#define PLEX_ERRORMESS_TYPE_ACQUIRELAST_LONG "An attempt to acquire the last value of something has failed"
#define PLEX_ERRORMESS_TYPE_STREAMSTATE_LONG "Attempted a function that required the stream state to either be active or deactivated but was not in the right state."
#define PLEX_ERRORMESS_TYPE_FILETYPE_LONG "Attempted a function accessing the wrong filetype for it's operation."
#define PLEX_ERRORMESS_TYPE_DOUBLEDEALLOC_LONG "Attempted to deallocate something that's already deallocated"
#define PLEX_ERRORMESS_TYPE_DIRECTORYOPENSTATE_LONG "Directory open state wrong for function"

// SUBSYSTEM STRINGS

#define PLEX_ERRORMESS_SUBSYSTEM_ERROR "Error Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_MEMORY "Memory Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_DEFAULT "Default Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_TIME "Time Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_WINDOW "Window Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_TEXTURE "Texture Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_SCREENEFFECTS "Screen Effects Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_GRAPHICS "Graphics Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_INPUT "Input Subsystem"
#define PLEX_ERRORMESS_SUBSYSTEM_SOUND "Sound Subsystem"

// BAD OPERATION STRINGS

#define PLEX_ERRORMESS_OP_DOUBLESAMPLERATE "Attempted to open a stream with a double (ie. 64-bit float) sample rate. Port Audio does not support this."
#define PLEX_ERRORMESS_OP_CTIME "Failed to acquire the time struct from C standard library function. This is likely a platform issue and not a problem with the execution with PLEX. Try recompiling source before moving forward."
#define PLEX_ERRORMESS_OP_CLOCALTIME "Failed to acquire the local time from the C standard library function. This is most likely a platform issue and not a problem with PLEX. Try recompiling source before moving forward."
#define PLEX_ERRORMESS_OP_CUTSOUNDBUFFER "Cutting sound buffer"
#define PLEX_ERRORMESS_OP_REVERSESOUNDBUFFER "Reversing sound buffer"
#define PLEX_ERRORMESS_OP_CLEARCLEAREDTEXTURE "Attempted to clear an already cleared texture"
#define PLEX_ERRORMESS_OP_PLAYSOUNDCHANNEL "Attempted to play sound channel"
#define PLEX_ERRORMESS_OP_DECIDESOUNDTYPE "Failed to establish loaded sound file's type."
#define PLEX_ERRORMESS_OP_CLOSEDIRECTORY "OS specific directory close operation"
#define PLEX_ERRORMESS_OP_OPENSOUNDSTREAM "Failed to open sound stream"
#define PLEX_ERRORMESS_OP_CLEARCLEAREDPROTOTOEXPANDMEM "Tried clearing internal memory for protoexpandarrays but it's already been cleared."
#define PLEX_ERRORMESS_OP_HIDEHIDDENSCREENEFFECT "Tried to hide an already hidden screeneffect"
#define PLEX_ERRORMESS_OP_UNHIDESHOWINGSCREENEFFECT "Tried to unhide an already showing screeneffect"

// EXTERNAL MODUlES

#define PLEX_ERRORMESS_SDLMODULE_CONTROLLER "SDL Gamepad Module"
#define PLEX_ERRORMESS_SDLMODULE_IMAGE "SDL Image Module"
#define PLEX_ERRORMESS_SDLMODULE_INPUT "SDL Input Module"
#define PLEX_ERRORMESS_SDLMODULE_VIDEO "SDL Video Module"

// ------------------------------------------------------------------------------

// GENERIC ACTION TARGETS  ------------------------------------------------------

#define PLEX_ERRORMESS_GENERIC_INDEX "Index"
#define PLEX_ERRORMESS_GENERIC_INDEX2 "Index 2"
#define PLEX_ERRORMESS_GENERIC_COUNT "Count"
#define PLEX_ERRORMESS_GENERIC_LENGTH "Length"
#define PLEX_ERRORMESS_GENERIC_ENTRY "Entry"

#define PLEX_ERRORMESS_GENERIC_DIMENX "X Coordinate"
#define PLEX_ERRORMESS_GENERIC_DIMENY "Y Coordinate"
#define PLEX_ERRORMESS_GENERIC_DIMENW "Width"
#define PLEX_ERRORMESS_GENERIC_DIMENH "Height"

#define PLEX_ERRORMESS_GENERIC_RED "Red"
#define PLEX_ERRORMESS_GENERIC_GREEN "Green"
#define PLEX_ERRORMESS_GENERIC_BLUE "Blue"
#define PLEX_ERRORMESS_GENERIC_ALPHA "Alpha"

#define PLEX_ERRORMESS_GENERIC_ALPHASTRING "Alphastring"
#define PLEX_ERRORMESS_GENERIC_MESSAGE "Message"
#define PLEX_ERRORMESS_GENERIC_STRING "String"
#define PLEX_ERRORMESS_GENERIC_NAME "Name"
#define PLEX_ERRORMESS_GENERIC_VALUE "Value"
#define PLEX_ERRORMESS_GENERIC_NUMBER "Number"

#define PLEX_ERRORMESS_GENERIC_FILE "File"
#define PLEX_ERRORMESS_GENERIC_FILEPTR "Pointer to File"
#define PLEX_ERRORMESS_GENERIC_FILEPATH "Filepath"
#define PLEX_ERRORMESS_GENERIC_FILEPATH2 "The Second Filepath"

#define PLEX_ERRORMESS_GENERIC_LINE "Line"
#define PLEX_ERRORMESS_GENERIC_LINES "The Lines"
#define PLEX_ERRORMESS_GENERIC_LINECOUNT "Line Count"
#define PLEX_ERRORMESS_GENERIC_NEXTLINE "The Next Line"

#define PLEX_ERRORMESS_GENERIC_TOKEN "Token"
#define PLEX_ERRORMESS_GENERIC_TOKEN2 "The Second Token"
#define PLEX_ERRORMESS_GENERIC_TOKENS "The Tokens"

#define PLEX_ERRORMESS_GENERIC_BUFFER "Buffer"

#define PLEX_ERRORMESS_GENERIC_WIDTH "Width"
#define PLEX_ERRORMESS_GENERIC_HEIGHT "Height"

#define PLEX_ERRORMESS_GENERIC_WPERC "Width Percentage"
#define PLEX_ERRORMESS_GENERIC_HPERC "Height Percentage"

#define PLEX_ERRORMESS_GENERIC_OPENED "Opened"
#define PLEX_ERRORMESS_GENERIC_CLOSED "Closed"

#define PLEX_ERRORMESS_GENERIC_UNDERLIMIT "Underlimit"
#define PLEX_ERRORMESS_GENERIC_OVERLIMIT "Overlimit"

// ANIMATION PLATE --------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE "While creating an animation plate"
#define PLEX_ERRORMESS_ANIMATIONPLATE_ONCLEARING "While clearing an animation plate"
#define PLEX_ERRORMESS_ANIMATIONPLATE_ONUNCLEARING "While unclearing an animation"
#define PLEX_ERRORMESS_ANIMATIONPLATE_ONDESTROY "While destroying an animation"

// ACTION TARGETS

#define PLEX_ERRORMESS_ANIMATIONPLATE_PLATE "Animation Plate"
#define PLEX_ERRORMESS_ANIMATIONPLATE_PLATEPTR "Pointer to Animation Plate"

// ANIMATION --------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_ANIMATION_ONADDFRAME "While adding animation frame"
#define PLEX_ERRORMESS_ANIMATION_ONSTART "While starting an animation"
#define PLEX_ERRORMESS_ANIMATION_ONCYCLESPEEDCHANGE "While changing the cycle speed of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONGETFRAME "While trying to get the frame of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONGET "While getting an animation"
#define PLEX_ERRORMESS_ANIMATION_ONSTOP "While stopping an animation"
#define PLEX_ERRORMESS_ANIMATION_ONDRAWFRAME "While drawing a frame of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMETINTED "While drawing a tinted frame of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMEROTATED "While drawing a rotated frame of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMEROTATEDTINTED "While drawing a tinted and rotated frame of an animation"
#define PLEX_ERRORMESS_ANIMATION_ONISSTOPPED "While checking whether or not an animation is stopped"
#define PLEX_ERRORMESS_ANIMATION_ONGETCYCLE "While acquiring the animation cycle length"
#define PLEX_ERRORMESS_ANIMATION_ONGETSTART "While acquiring the animation start"

// ACTION TARGETS

#define PLEX_ERRORMESS_ANIMATION_ANIMATION "Animation"
#define PLEX_ERRORMESS_ANIMATION_ANIMATION2 "The Second Animation"
#define PLEX_ERRORMESS_ANIMATION_ANIMATIONS "Animations"
#define PLEX_ERRORMESS_ANIMATION_FRAMES "Frames"

// SPRITE ------------------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_SPRITE_ONADDANIMATION "While adding an animation to a sprite"

#define PLEX_ERRORMESS_SPRITE_ONCLEAR "While clearing sprite"
#define PLEX_ERRORMESS_SPRITE_ONSYNCANIMATIONS "While syncing two animations"
#define PLEX_ERRORMESS_SPRITE_ONDRAW "While drawing a sprite"
#define PLEX_ERRORMESS_SPRITE_ONDRAWTINTED "While drawing a tinted sprite"
#define PLEX_ERRORMESS_SPRITE_ONDRAWROTATED "While drawing a rotated sprite"
#define PLEX_ERRORMESS_SPRITE_ONDRAWROTATEDTINTED "While drawing a rotated and tinted sprite"
#define PLEX_ERRORMESS_SPRITE_ONGEN "While generating a sprite"
#define PLEX_ERRORMESS_SPRITE_ONCYCLESPEEDCHANGE "While changing sprite cycle speed"
#define PLEX_ERRORMESS_SPRITE_ONSTART "While starting sprite"
#define PLEX_ERRORMESS_SPRITE_ONSTOP "While stopping sprite"
#define PLEX_ERRORMESS_SPRITE_ONSYNCING "While syncing two sprites"
#define PLEX_ERRORMESS_SPRITE_ONUNCLEAR "While unclearing sprite"
#define PLEX_ERRORMESS_SPRITE_ONDESTROY "While destroying a sprite"
#define PLEX_ERRORMESS_SPRITE_ONCOPY "While attempting to copy a sprite"
#define PLEX_ERRORMESS_SPRITE_ONGETTOPPED "While getting whether or not a sprite is stopped"
#define PLEX_ERRORMESS_SPRITE_ONGETCYCLELEN "While getting the cycle length from a sprite"
#define PLEX_ERRORMESS_SPRITE_ONGETTEX "While getting the sprite's texture"
#define PLEX_ERRORMESS_SPRITE_ONGETWPERC "While getting the sprite width percentage"
#define PLEX_ERRORMESS_SPRITE_ONGETHPERC "While getting the sprite height percentage"
#define PLEX_ERRORMESS_SPRITE_ONGETCOUNT "While getting the animation count of a sprite"

// ACTION TARGETS

#define PLEX_ERRORMESS_SPRITE_ANIINDEX "Animation Index"
#define PLEX_ERRORMESS_SPRITE_SPRITE "Sprite"
#define PLEX_ERRORMESS_SPRITE_SPRITEPTR "Pointer to Sprite"

// PROMINENCE MACHINE ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONADD "While adding a prominence to a prominence machine"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONGET "While getting a prominence from a prominece machine"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONREMOVAL "While removing a prominence from a prominence machine"

#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONGENERATE "While generating a prominence machine"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONDESTROY "While destroying a prominence machine"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_ONGETCOUNT "While acquiring the count from prominence machine"

// ACTION TARGETS

#define PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCE "Prominence"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE "Prominence Machine"
#define PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCES "The Prominences stored on the Prominence Machine"

// GRAPHICS ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURE_DRAWSTACK "While printing texture (drawstack phase)"
#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATED_DRAWSTACK "While printing a rotated texture (drawstack phase)"

#define PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREEN "While clearing the screen (excluding offsets)"
#define PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENALPHA "While clearing the screen (excluding offsets) inc. alpha"
#define PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENOFFSET "While clearing the screen's offset"
#define PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENOFFSETALPHA "While clearing the screen's offset inc. alpha"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE1 "While drawing line (Operation 1)"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE2 "While drawing line (Operation 2)"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE3 "While drawing line (Operation 3)"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWRECT "While drawing a rectangle"
#define PLEX_ERRORMESS_GRAPHICS_ONFILLRECT "While drawing a filled rectangle"
#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURE "While printing texture"
#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURETINTED "While printing tinted texture"
#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATED "While printing rotated texture"
#define PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATEDTINTED "While printing texutre rotated and tinted"
#define PLEX_ERRORMESS_GRAPHICS_ONADDINGTODRAWLIST "While adding to drawlist"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWDRAWLIST "While drawing the drawlist"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWICON "While drawing an icon"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWICONTINTED "While drawing an icon tinted"
#define PLEX_ERRORMESS_GRAPHICS_ONARROWDRAWING "While drawing an arrow"
#define PLEX_ERRORMESS_GRAPHICS_ONDRAWINGICONBUTTON "While drawing an icon button"
#define PLEX_ERRORMESS_GRAPHICS_ONCHARGEBARDRAWING "While drawing chargebar"
#define PLEX_ERRORMESS_GRAPHICS_ONTAKINGSCREENCAP "While taking a screencap"
#define PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING "While drawing a button"
#define PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING "While drawing a label"
#define PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING "While printing a letter"
#define PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTINGTINTED "While printing a tinted letter"
#define PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSSTART "While starting the graphics"
#define PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSUPDATE "While updating the graphics"
#define PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSEND "While ending the graphics"
#define PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING "While printing a strings"
#define PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED "While printing a tinted string"
#define PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING "While drawing a text box"
#define PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING "While drawing a tinted text box"
#define PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING "While checking to draw a tooltip"
#define PLEX_ERRORMESS_GRAPHICS_ONTWOIMAGEBUTTONDDRAWING "While drawing a two image button"
#define PLEX_ERRORMESS_GRAPHICS_ONPANORAMADRAWING "While drawing a panorama backdrop"
#define PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING "While drawing scrolling text box"
#define PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING "While drawing scrolling tinted text box"
#define PLEX_ERRORMESS_GRAPHICS_ONSETTEXTURETARGET "While setting a texture's target"
#define PLEX_ERRORMESS_GRAPHICS_ONUNSETTEXTURETARGET "While unsetting a texture's target"
#define PLEX_ERRORMESS_GRAPHICS_ONSETREFRESHRGB "While setting the refresh color"
#define PLEX_ERRORMESS_GRAPHICS_ONSETBLENDRGB "While setting the blend color"
#define PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSOR "While setting a custom cursor"
#define PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORTINTED "While setting a tinted custom cursor"
#define PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORCLICK "While setting custom cursor click graphic"
#define PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORDOWN "While setting custom cursor down graphic"
#define PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORWH "While loading the width and height of the cursor"
#define PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORFCOORDINATES "While loading the from coordinates of the cursor image"
#define PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORCLICKFCOORDINATES "While loading the from coordinates of the cursor image during click"
#define PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORDOWNFCOORDINATES "While loading the from coordinates of the cursor image while down"
#define PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS "While getting the cursor dimensions"

// ACTION TARGETS

#define PLEX_ERRORMESS_GRAPHICS_DRAWLIST "Drawlist"
#define PLEX_ERRORMESS_GRAPHICS_HEADERLESSTEX "Headerless Texture"

#define PLEX_ERRORMESS_GRAPHICS_FROMX "From X"
#define PLEX_ERRORMESS_GRAPHICS_FROMY "From Y"
#define PLEX_ERRORMESS_GRAPHICS_FROMW "From W"
#define PLEX_ERRORMESS_GRAPHICS_FROMH "From H"

// LOW LEVEL GRAPHICS ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_LOWGRAPHICS_ONGETBLENDMODE "While getting the blend mode"
#define PLEX_ERRORMESS_LOWGRAPHICS_ONGETRENDERER "While getting renderer"

// ACTION TARGETS

#define PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER "SDL Renderer"
#define PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACE "SDL Surface"
#define PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACELOADED "SDL Surface loaded from file"

// HIGH LEVEL TEXTURE ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_TEXTURE_ONDESTROY "While destroying a texture"
#define PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE "While loading a texture from a file"
#define PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE "While converting a headerless image"
#define PLEX_ERRORMESS_TEXTURE_LOADFROMHEADERLESS "While loading texture from headerless image"
#define PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS "While loading texture from headerless image OR file location"
#define PLEX_ERRORMESS_TEXTURE_ONCOPY "While copying texture"
#define PLEX_ERRORMESS_TEXTURE_ONCREATE "While creating a new texture"
#define PLEX_ERRORMESS_TEXTURE_ONGENHIGHLEVEL "While generating a texture (high level)"
#define PLEX_ERRORMESS_TEXTURE_ONSTART "While starting the texture system"
#define PLEX_ERRORMESS_TEXTURE_ONSETALPHA "While setting a texture's alpha"
#define PLEX_ERRORMESS_TEXTURE_ONTINTING "While tinting a texture"
#define PLEX_ERRORMESS_TEXTURE_ONUNCLEAR "While unclearing a texture"
#define PLEX_ERRORMESS_TEXTURE_ONUPDATE "While updating texture."
#define PLEX_ERRORMESS_TEXTURE_ONEND "While ending the texture system."
#define PLEX_ERRORMESS_TEXTURE_ONNULLCHECK "While NULL checking texture."
#define PLEX_ERRORMESS_TEXTURE_ONGETWIDTHHEIGHT "While acquiring a textures width and height."
#define PLEX_ERRORMESS_TEXTURE_ONGETINNER "While getting inner texture."
#define PLEX_ERRORMESS_TEXTURE_ONGETCLEAR "While checking if texture cleared."
#define PLEX_ERRORMESS_TEXTURE_ONCLEAR "While clearing a texture"

// ACTION TARGETS

#define PLEX_ERRORMESS_TEXTURE_TEXTURE "Texture"
#define PLEX_ERRORMESS_TEXTURE_TEXTURE2 "The Second Texture"
#define PLEX_ERRORMESS_TEXTURE_TEXTUREBANK "Texture Bank"
#define PLEX_ERRORMESS_TEXTURE_TEXTURECOPY "Texture Copy"
#define PLEX_ERRORMESS_TEXTURE_FROMTEXTURE "From Texture"

// LOW LEVEL TEXTURE ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_LOWTEXTURE_ONLOWLEVELGRAPHICSUPDATE "While low level graphics update"
#define PLEX_ERRORMESS_LOWTEXTURE_ONGETTINT "While getting the tint of a texture (low level)"
#define PLEX_ERRORMESS_LOWTEXTURE_ONGETBLENDMODE "While getting the blendmode of a texture (low level)"
#define PLEX_ERRORMESS_LOWTEXTURE_ONPROCESSGEN "While processing generated texture (low level)"
#define PLEX_ERRORMESS_LOWTEXTURE_ONGETFROMSURFACE "While getting a texture from a surface"

#define PLEX_ERRORMESS_LOWTEXTURE_ONGETWIDTHHEIGHT "While acquiring a textures width and height. (low level)"

#define PLEX_ERRORMESS_LOWTEXTURE_ONDESTROY "While destroying a texture (low level)"

// ACTION TARGETS

#define PLEX_ERRORMESS_LOWTEXTURE_INNERTEXTURE "Inner Texture"

// WINDOW ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_WINDOW_ONCREATELOWLEVEL "While creating a window (low level)"
#define PLEX_ERRORMESS_WINDOW_ONGETTITLE "While getting window title"
#define PLEX_ERRORMESS_WINDOW_ONDESTROYLOWLEVEL "While destroying a window (low level)"
#define PLEX_ERRORMESS_WINDOW_ONENDING "While ending window"
#define PLEX_ERRORMESS_WINDOW_ONSETTITLE "While setting window title"
#define PLEX_ERRORMESS_WINDOW_ONREADJUST "While readjusting window"
#define PLEX_ERRORMESS_WINDOW_ONSTART "While starting window"
#define PLEX_ERRORMESS_WINDOW_ONCHANGESCREENRATIO "While changing screen ratio"
#define PLEX_ERRORMESS_WINDOW_ONMARKSIZING "While marking the window to resize"
#define PLEX_ERRORMESS_WINDOW_ONUNMARKSIZING "While marking the window to resize"
#define PLEX_ERRORMESS_WINDOW_ONRESTORE "While restoring window"
#define PLEX_ERRORMESS_WINDOW_ONUPDATERESIZE "While checking to update the resize"

// ACTION TARGETS

#define PLEX_ERRORMESS_WINDOW_WINDOW "Window"
#define PLEX_ERRORMESS_WINDOW_WINDOWRATIO "Window Size Ratio"
#define PLEX_ERRORMESS_WINDOW_CURSORGRAPHIC "Cursor Graphic"
#define PLEX_ERRORMESS_WINDOW_CURSORGRAPHICCLICK "Cursor Click Graphic"
#define PLEX_ERRORMESS_WINDOW_CURSORGRAPHICDOWN "Cursor Down Graphic"

// FILE PARSER ------------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_FILEPARSE_ONADDLINE "While adding a new line"
#define PLEX_ERRORMESS_FILEPARSE_ONADDTOKEN "While adding a new token"
#define PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINE "While getting parse line"
#define PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINECOUNT "While getting the amount of parse lines"
#define PLEX_ERRORMESS_FILEPARSE_ONGETTOKEN "While the destruction of a parse file"
#define PLEX_ERRORMESS_FILEPARSE_ONGETTOKENCOUNT "While getting the amount of tokens"
#define PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE "While parsing a file"
#define PLEX_ERRORMESS_FILEPARSE_ONPARSEFILEDESTROY "While the destruction of a parse file"
#define PLEX_ERRORMESS_FILEPARSE_ONEXPORTPARSEFILE "While exporting a parsefile"

// ACTION TARGETS

#define PLEX_ERRORMESS_FILEPARSE_NEXTLINESTOKEN "The token of the next line"
#define PLEX_ERRORMESS_FILEPARSE_PARSEFILE "The parsefile struct"
#define PLEX_ERRORMESS_FILEPARSE_FILEPARSER "File Parser"

// SPRITE THEATER ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDE "While executing a slide change event for Sprite theater"
#define PLEX_ERRORMESS_SPRITETHEATER_ONNEXTSLIDE "While receiving the next slide from sprite theater"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCREATEACTOR "While executing an actor creation event for Sprite theater"
#define PLEX_ERRORMESS_SPRITETHEATER_ONADDACTIONCHANGETOSCENE "While adding an action change to a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONADDMUSICCHANGETOSCENE "While adding a music change to a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDETOSCENE "While adding a sprite theater slide to a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONADDACTORTOSCENE "While adding an actor to a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONHIDEACTORINSCENE "While hiding an actor in scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONUNHIDEACTORINSCENE "While unhiding an actor in scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONHIDEALLACTORSINSCENE "While hiding all actors in scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHANGESPRITEINSCENE "While changing actor's sprite in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONDARKENSCENE "While making a slide dark in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEANIMATIONINSCENE "While changing the actor's animation in scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONMOVEACTORINSCENE "While moving an actor in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONRESIZEACTORINSCENE "While resizing an actor in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE "While changing the backdrop in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEMUSICINSCENE "While changing the music in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONSTOPMUSICINSCENE "While stopping the music in a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER "While loading the scene into sprite theater"
#define PLEX_ERRORMESS_SPRITETHEATER_ONDESTROYSCENE "While destroying a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHECKSCENESTRING "While checking if a string is within a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONCHECKEXPANDARRAYS "While sprite theater is expanding internal arrays"
#define PLEX_ERRORMESS_SPRITETHEATER_ONSETACTIONCHANGE "While setitng an actor change"
#define PLEX_ERRORMESS_SPRITETHEATER_ONSETMUSICCHANGE "While setting a music change"
#define PLEX_ERRORMESS_SPRITETHEATER_ONGENERATESCENE "While generating a scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ONUPDATE "While updating sprite theater"
#define PLEX_ERRORMESS_SPRITETHEATER_ONGETACTORSPRITE "While getting the sprite of an actor"

// ACTION TARGETS

#define PLEX_ERRORMESS_SPRITETHEATER_SCENE "The Scene"
#define PLEX_ERRORMESS_SPRITETHEATER_ACTOR "Actor"
#define PLEX_ERRORMESS_SPRITETHEATER_ACTORS "Actors"
#define PLEX_ERRORMESS_SPRITETHEATER_ACTORS2 "Actors 2"
#define PLEX_ERRORMESS_SPRITETHEATER_SLIDES "Slides"
#define PLEX_ERRORMESS_SPRITETHEATER_SLIDES2 "Slides 2"
#define PLEX_ERRORMESS_SPRITETHEATER_CHANGES "Changes"
#define PLEX_ERRORMESS_SPRITETHEATER_CHANGES2 "Changes 2"
#define PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES "Music Changes"
#define PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES2 "Music Changes 2"
#define PLEX_ERRORMESS_SPRITETHEATER_SPRITECHANGEACTOR "Actor intended for a sprite change"
#define PLEX_ERRORMESS_SPRITETHEATER_SPRITECHANGESPRITE "Sprite intended for a sprite change"

// STRINGBANK -------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_STRINGBANK_ONGENERATE "While generating a new stringbank"
#define PLEX_ERRORMESS_STRINGBANK_ONDESTROY "While destroying a stringbank"
#define PLEX_ERRORMESS_STRINGBANK_ONADD "While adding a new string to a stringbank"
#define PLEX_ERRORMESS_STRINGBANK_ONREMOVE "While removing a string from a stringbank"
#define PLEX_ERRORMESS_STRINGBANK_ONLOAD "While loading stringbank from file"
#define PLEX_ERRORMESS_STRINGBANK_ONGETENTRY "While getting string from stringbank"
#define PLEX_ERRORMESS_STRINGBANK_ONCOUNT "While returning count of stringbank"

// ACTION TARGETS

#define PLEX_ERRORMESS_STRINGBANK_STRINGBANK "The Stringbank"
#define PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS "Contents of Stringbank"

// DEFAULTS ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_DEFAULTS_ONGETSTRING "While getting string from default"
#define PLEX_ERRORMESS_DEFAULTS_ONSTART "While starting default system"
#define PLEX_ERRORMESS_DEFAULTS_ONEND "While starting default system"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGN "While assigning a default value"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGNBOOL "While assigning a default of bool value"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGNDOUBLE "While assigning a default of double value"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGNSTRING "While assigning a default of string value"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT32 "While assigning a default of uint32 value"
#define PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT8 "While assigning a default of uint8 value"
#define PLEX_ERRORMESS_DEFAULTS_ONADDTOSTRINGBANK "While adding value to stringbank"
#define PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG "While loading a config file"

#define PLEX_ERRORMESS_DEFAULTS_ONSAVE "While saving default"
#define PLEX_ERRORMESS_DEFAULTS_ONGETVALUE "While getting a default's value"
#define PLEX_ERRORMESS_DEFAULTS_ONGETENTRY "While getting a default's entry"
#define PLEX_ERRORMESS_DEFAULTS_ONCHECKENTRY "While checking a default's entry to add a custom default"

#define PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT8 "While adding a custom Uint8"
#define PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT32 "While adding a custom Uint32"
#define PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMBOOL "While adding a custom boolean"
#define PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMDOUBLE "While adding a custom double"
#define PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING "While adding a custom string"

#define PLEX_ERRORMESS_DEFAULTS_ONGETNAME "While getting a default's name"
#define PLEX_ERRORMESS_DEFAULTS_ONGETYPE "While getting a default's type"
#define PLEX_ERRORMESS_DEFAULTS_ONGETCOMMENT "While getting a default's comment"
#define PLEX_ERRORMESS_DEFAULTS_ONGETMINIMUM "While getting a default's minimum"
#define PLEX_ERRORMESS_DEFAULTS_ONGETMAXIMUM "While getting a default's maximum"

#define PLEX_ERRORMESS_DEFAULTS_ONGETCOUNT "While getting the default entry count"

#define PLEX_ERRORMESS_DEFAULTS_CONFIG "The default config file"

// ACTION TARGETS

#define PLEX_ERRORMESS_DEFAULT_ENTRIES "Default entries stack"
#define PLEX_ERRORMESS_DEFAULT_NONAME "No default name passed"
#define PLEX_ERRORMESS_DEFAULT_STRINGBANK "Default String Bank"

#define PLEX_ERRORMESS_DEFAULT_TYPE24HRTIME "Set time 24/7 Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEALLOWMAXIMIZE "Allow Maximize Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEALLOWRESIZE "Allow Resize Default"
#define PLEX_ERRORMESS_DEFAULT_TYPECONTROLLERPAUSE "Allow Controller Pause Default"
#define PLEX_ERRORMESS_DEFAULT_TYPECURSORR "Custom Cursor Red Default"
#define PLEX_ERRORMESS_DEFAULT_TYPECURSORG "Custom Cursor Green Default"
#define PLEX_ERRORMESS_DEFAULT_TYPECURSORB "Custom Cursor Blue Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEDISABLECONTROLLER "Disable Controller Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEDISABLEJOYSTICK "Disable Joystick Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEDISABLEKEYBOARD "Disable Keyboard Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEDISABLEMOUSE "Disble Mouse Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEDISABLESOUND "Disable Sound Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEHEIGHT "Screen Height Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEKILLONCLOSE "Kill on Close Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEKILLONESCAPE "Kill on Escape Default"
#define PLEX_ERRORMESS_DEFAULT_TYPESTARTMAXIMIZE "Start Maximized Default"
#define PLEX_ERRORMESS_DEFAULT_TYPEWIDTH "Screen Width Default"

#define PLEX_ERRORMESS_DEFAULT_TEXTUREDIMENSLIMIT "Texture Dimensions Limit Default"
#define PLEX_ERRORMESS_DEFAULT_PRINTERRORS "Print Errors Default"
#define PLEX_ERRORMESS_DEFAULT_SHOWERRORS "Show Errors Default"

#define PLEX_ERRORMESS_DEFAULT_PRINTERRORTHRESHOLD "Print Error Threshold Default"
#define PLEX_ERRORMESS_DEFAULT_SHOWERRORTHRESHOLD "Show Error Threshold Default"
#define PLEX_ERRORMESS_DEFAULT_FATALERRORTHRESHOLD "Print Error Threshold Default"

#define PLEX_ERRORMESS_DEFAULT_HEADERLESSCOPY "Headerless Copy Default"

#define PLEX_ERRORMESS_DEFAULT_MEMORYPROFILE "Memory Profile Default"

#define PLEX_ERRORMESS_DEFAULT_MEMORYREPORT "Memory Report Default"
#define PLEX_ERRORMESS_DEFAULT_MEMORYREPORTTOFILE "Memory Report To File Default"

// ARRAYS ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_ARRAY_ONMEMCLEARING "While clearing the internal memory for protoexpandarrays"
#define PLEX_ERRORMESS_ARRAY_ONMEMEXPANSION "While expanding internal memory for protoexpandarrays"
#define PLEX_ERRORMESS_ARRAY_ONMEMFREE "While trying to free an internally allocated protoexpandarray"
#define PLEX_ERRORMESS_ARRAY_ONCLEARING "While the clearing of an array."
#define PLEX_ERRORMESS_ARRAY_ONCREATE "While an array is being created"
#define PLEX_ERRORMESS_ARRAY_ONCUTTING "While the cutting of an array."
#define PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC "While the cutting of an array by percentage."
#define PLEX_ERRORMESS_ARRAY_ONDECREMENTATION "While the decrementation of an array."
#define PLEX_ERRORMESS_ARRAY_ONDESTROY "While the destruction of an array."
#define PLEX_ERRORMESS_ARRAY_ONEXPANSION "While the expansion of an array."
#define PLEX_ERRORMESS_ARRAY_ONGECONTENT "While the receiving of the contents of array."
#define PLEX_ERRORMESS_ARRAY_ONGETCAPACITY "While the receiving of the capacity from array."
#define PLEX_ERRORMESS_ARRAY_ONGETCAPACITYSIZE "While the receiving of the capacity size (ie. capacity times unit size) from array."
#define PLEX_ERRORMESS_ARRAY_ONGETCOUNT "While the receiving of the count from array."
#define PLEX_ERRORMESS_ARRAY_ONGETENTRY "While the receiving of entry from array."
#define PLEX_ERRORMESS_ARRAY_ONGETENTRYLAST "While the receiving of the last entry from array."
#define PLEX_ERRORMESS_ARRAY_ONGETSIZE "While the receiving of the size from array."
#define PLEX_ERRORMESS_ARRAY_ONGETUNITSIZE "While the receiving of the unit size from array."
#define PLEX_ERRORMESS_ARRAY_ONGETGROWTHUNIT "While the receiving of the growth size from array."
#define PLEX_ERRORMESS_ARRAY_ONINCREMENTATION "While the incrementation of an array."
#define PLEX_ERRORMESS_ARRAY_ONMULTIINCREMENTATION "While the multiple incrementation of an array."
#define PLEX_ERRORMESS_ARRAY_ONREARRANGING "While the rearranging of an array."
#define PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC "While the rearranging of an array by percentage."
#define PLEX_ERRORMESS_ARRAY_ONREVERSING "While the reversing of an array."
#define PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC "While the reversing of an array by percentage."
#define PLEX_ERRORMESS_ARRAY_ONSWAPPING "While the swapping of an array."
#define PLEX_ERRORMESS_ARRAY_ONSWAPPING2 "While the swapping of the second array."
#define PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC "While the swapping of an array by percentage."
#define PLEX_ERRORMESS_ARRAY_ONREMOVAL "While removing an element from an array"
#define PLEX_ERRORMESS_ARRAY_ONGROWTHUNITSET "While setting the growth unit of an array"

// ACTION TARGETS

#define PLEX_ERRORMESS_ARRAY_INTERNALMEMARRAY "The internal protoexpandarray memory storage array"
#define PLEX_ERRORMESS_ARRAY_INTERNALMEMPOINTER "Internal allocated protoexpandarray"
#define PLEX_ERRORMESS_ARRAY_INTERNALMEMEXPANDPOINTER "Newly allocated internal protoexpandarray"

#define PLEX_ERRORMESS_ARRAY_ARRAY "Array"
#define PLEX_ERRORMESS_ARRAY_ARRAY2 "Array 2"
#define PLEX_ERRORMESS_ARRAY_ARRAYBEG1 "Array beginning"
#define PLEX_ERRORMESS_ARRAY_ARRAYBEG2 "Second array beginning"
#define PLEX_ERRORMESS_ARRAY_ARRAYBUFFER "Array buffer"
#define PLEX_ERRORMESS_ARRAY_ARRAYBUFFER2 "Second array buffer"
#define PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS "Array Contents"
#define PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS2 "Array Contents 2"
#define PLEX_ERRORMESS_ARRAY_ARRAYFREEHOOK "Array's Free Hook"
#define PLEX_ERRORMESS_ARRAY_ARRAYGROWTHUNIT "Growth Unit"
#define PLEX_ERRORMESS_ARRAY_ARRAYMEMHOOK "Array's Mem Hook"
#define PLEX_ERRORMESS_ARRAY_ARRAYPTR "Pointer to Array"
#define PLEX_ERRORMESS_ARRAY_ARRAYUNITSIZE "Array Unit Size"
#define PLEX_ERRORMESS_ARRAY_ARRAYCOUNT "Array Count"
#define PLEX_ERRORMESS_ARRAY_NEWARRAYCONTENTS "New Array Contents"
#define PLEX_ERRORMESS_ARRAY_NEWBUFFER "New Buffer"
#define PLEX_ERRORMESS_ARRAY_PRELOADBUFFER "Preloaded Buffer"
#define PLEX_ERRORMESS_ARRAY_PRELOADBUFFER2 "The Second Preloaded Buffer"
#define PLEX_ERRORMESS_ARRAY_FREEHOOK "Free Hook"
#define PLEX_ERRORMESS_ARRAY_MEMHOOK "Memory Hook"

// SOUND ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_SOUND_ONASSIGNBUFFER "While assinging sound to buffer"
#define PLEX_ERRORMESS_SOUND_ONCHECKPLAYING "While checking if a sound is playing"
#define PLEX_ERRORMESS_SOUND_ONGETCHANNELITERATION "While getting a channel's iteration"
#define PLEX_ERRORMESS_SOUND_ONGETSOUNDBUFFER "While getting a sound buffer"
#define PLEX_ERRORMESS_SOUND_ONGETDURATION "While getting a sound's duration"
#define PLEX_ERRORMESS_SOUND_ONOPENSTREAM "While opening a sound stream"
#define PLEX_ERRORMESS_SOUND_ONLOADFILEINTOBUFFER "While loading a sound file into a buffer"
#define PLEX_ERRORMESS_SOUND_ONPRELOADINTOSPECIFICBUFFER "While preloading a sound file into a specific buffer"
#define PLEX_ERRORMESS_SOUND_ONPRELOADINTOBUFFER "While preloading a sound file into a buffer"
#define PLEX_ERRORMESS_SOUND_ONSETCHANNELVOLUME "While setting a sound channel's volume"
#define PLEX_ERRORMESS_SOUND_ONSETBUFFERLEN "While setting the sound buffer's length"
#define PLEX_ERRORMESS_SOUND_ONSETCOMPLEXSEQUENCE "While setting a sound channel's complex sequence"
#define PLEX_ERRORMESS_SOUND_ONBUFFERCUT "While cutting a sound buffer"
#define PLEX_ERRORMESS_SOUND_ONBUFFERRANDOMSWAP "While randomly swapping a sound buffer"
#define PLEX_ERRORMESS_SOUND_ONBUFFERREARRANGE "While rearranging a sound buffer"
#define PLEX_ERRORMESS_SOUND_ONBUFFERREVERSE "While sound buffer reversing"
#define PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELOFF "While turning sound channel off"
#define PLEX_ERRORMESS_SOUND_ONTURNINGCHANNELON "While turning sound channel on"
#define PLEX_ERRORMESS_SOUND_ONCLEARBUFFER "While trying to clear the buffer"
#define PLEX_ERRORMESS_SOUND_ONCLEARBUFFERBYCHANNEL "While trying to clear the buffer by channel"
#define PLEX_ERRORMESS_SOUND_ONSTOPSTREAM "On attempting to stop sound stream"
#define PLEX_ERRORMESS_SOUND_ONHOOK "While the sound hook is executing"
#define PLEX_ERRORMESS_SOUND_ONPLAY "While trying to play a sound channel"

// ACTION TARGETS

#define PLEX_ERRORMESS_SOUND_BUFFER "Sound Buffer"
#define PLEX_ERRORMESS_SOUND_BUFFER2 "The Second Sound Buffer"
#define PLEX_ERRORMESS_SOUND_BUFFERFILE "Sound Buffer File"
#define PLEX_ERRORMESS_SOUND_CHANNEL "Sound Channel"
#define PLEX_ERRORMESS_SOUND_FAILEDTOOPENSTREAM "Failed to open sound stream"
#define PLEX_ERRORMESS_SOUND_STREAMISINACTIVE "Sound Stream Inactive"
#define PLEX_ERRORMESS_SOUND_CHANNELON "Sound Channel is On"
#define PLEX_ERRORMESS_SOUND_CHANNELOFF "Sound Channel is Off"

// DATETIME ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_DATETIME_ONGETDAY "While getting a datetime's day"
#define PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW "While getting the difference between two datetimes (from static base function)"
#define PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE "While getting the difference between two datetimes"
#define PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE12 "While getting the difference between two datetimes (12 hour time)"
#define PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE24 "While getting the difference between two datetimes (24 hour time)"
#define PLEX_ERRORMESS_DATETIME_ONGETHOUR "While getting a datetime's hour"
#define PLEX_ERRORMESS_DATETIME_ONGETMINUTE "While getting a datetime's minute"
#define PLEX_ERRORMESS_DATETIME_ONGETMONTH "While getting a datetime's month"
#define PLEX_ERRORMESS_DATETIME_ONGETMSH "While getting the minute, second, and hour of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETMYD "While getting the month, year, and day of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETPM "While getting the is PM from a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETSECOND "While getting a datetime's second"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALDAY "While getting the total days of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALHOUR "While getting the total hours of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALMINUTE "While getting the total minutes of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALMONTH "While getting the total months of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALSECOND "While getting the total seconds of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETTOTALYEAR "While getting the total years of a datetime"
#define PLEX_ERRORMESS_DATETIME_ONGETYEAR "While getting a datetime's year"
#define PLEX_ERRORMESS_DATETIME_ONGETCURRENTLOW "While getting the current datetime (from static base function)"
#define PLEX_ERRORMESS_DATETIME_ONSETCURRENT "While setting a date to current datetime"
#define PLEX_ERRORMESS_DATETIME_ONSETCURRENT12 "While setting a datetime to current datetime (12 hour time)"
#define PLEX_ERRORMESS_DATETIME_ONSETCURRENT24 "While setting a datetime to current datetime (24 hour time)"
#define PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE "While setting the datetime"
#define PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE12 "While setting the datetime (12 hour time)"
#define PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE24 "While setting the datetime (24 hour time)"

// ACTION TARGETS

#define PLEX_ERRORMESS_DATETIME_AMPM "AM/PM"
#define PLEX_ERRORMESS_DATETIME_TIMEDAY "Day"
#define PLEX_ERRORMESS_DATETIME_TIMEHOUR "Hour"
#define PLEX_ERRORMESS_DATETIME_TIMEMINUTE "Minute"
#define PLEX_ERRORMESS_DATETIME_TIMEMONTH "Month"
#define PLEX_ERRORMESS_DATETIME_TIMESECOND "Second"
#define PLEX_ERRORMESS_DATETIME_TIMETOTALDAYS "Total Day"
#define PLEX_ERRORMESS_DATETIME_TIMEYEAR "Year"
#define PLEX_ERRORMESS_DATETIME_DATETIME "Datetime"
#define PLEX_ERRORMESS_DATETIME_DATETIME2 "The Second Datetime"
#define PLEX_ERRORMESS_DATETIME_DATETIMESMALL "Date Time - hours, minutes, seconds"

// ERRNO

#define PLEX_ERRORMESS_DATETIME_ERRNO "(Localtime Error Number # "
#define PLEX_ERRORMESS_DATETIME_ERRNO2 ")"

// TIMER ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_TIME_ONMULTIPLIER "While setting a timer multiplier"
#define PLEX_ERRORMESS_TIME_ONRESET "While resetting of timer"
#define PLEX_ERRORMESS_TIME_ONREWIND "While rewinding of timer"
#define PLEX_ERRORMESS_TIME_ONRFASTFORWARD "While fast forwarding of timer"
#define PLEX_ERRORMESS_TIME_ONRPAUSE "While pausing of timer"
#define PLEX_ERRORMESS_TIME_ONRSTART "While start of timer"
#define PLEX_ERRORMESS_TIME_ONRUNPAUSE "While unpausing of timer"
#define PLEX_ERRORMESS_TIME_ONUPDATING "While updating timer"
#define PLEX_ERRORMESS_TIME_ONPAUSING "While pausing the timer"
#define PLEX_ERRORMESS_TIME_ONGETSECONDS "While getting seconds from a timer"

// ACTION TARGETS

#define PLEX_ERRORMESS_TIME_TIME "Time"
#define PLEX_ERRORMESS_TIME_TIMER "Timer"
#define PLEX_ERRORMESS_TIME_STRING "Time string"
#define PLEX_ERRORMESS_TIME_MULTIPLIER "Timer Multiplier"
#define PLEX_ERRORMESS_TIME_COUNTDOWN "countdown time"
#define PLEX_ERRORMESS_TIME_COUNTDOWNSTRING "Countdown time string"

// GLOBAL TIME ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_GLOBALTIME_ONGET "While getting game time"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETSTRING "While gettimg game time string"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETUNPAUSE "While getting game time paused"
#define PLEX_ERRORMESS_GLOBALTIME_ONPAUSE "While pausing game time"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETNOPAUSE "While getting the game timer that ignores pausetime"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETNOPAUSESTRING "While getting the game timer string that ignores pausetime"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETSECONDS "while getting the seconds passed on game timer"
#define PLEX_ERRORMESS_GLOBALTIME_ONGETSECONDSNOPAUSE "while getting the seconds passed on game timer that ignores pausetime"
#define PLEX_ERRORMESS_GLOBALTIME_ONUNPAUSE "While unpausing game time"

// ACTION TARGETS



// SCREEN EFFECTS ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_SCREENEFFECT_ONCEASING "While ceasing a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONHIDING "While hiding a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING "While unhiding a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONDOINGRANGED "While doing a ranged screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONDOING "While doing a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONUPDATE "While updating screen effects"
#define PLEX_ERRORMESS_SCREENEFFECT_ONPROJRAIN "While trying to execute the projectile rain screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONPAINTOVER "While trying to execute the paintover screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONSMOKE "While trying to execute the smoke screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONENDING "While ending screen effects"
#define PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE "While seeding a sprite for a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONREPOSITION "While repositioning a screen effect"
#define PLEX_ERRORMESS_SCREENEFFECT_ONSETDRAWLAYER "While changing draw layer"
#define PLEX_ERRORMESS_SCREENEFFECT_ONHIDDEN "While getting if a screen effect is hidden or not"
#define PLEX_ERRORMESS_SCREENEFFECT_ONOVER "While getting if a screen effect is over or not"

// ACTION TARGETS

#define PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT "Screen Effect"
#define PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECTSTACK "Screen Effect Stack"

// GENERATOR ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_GENERATOR_ONGEN "While generating a generator."
#define PLEX_ERRORMESS_GENERATOR_ONDESTROYING "While destroying a generator."

#define PLEX_ERRORMESS_GENERATOR_ONCHANGEAREA "While changing the generator area"
#define PLEX_ERRORMESS_GENERATOR_ONEXTENDINGDURATION "While extending the generator's duration"
#define PLEX_ERRORMESS_GENERATOR_ONGETAREA "While getting the generator's area"
#define PLEX_ERRORMESS_GENERATOR_ONGETCOUNT "While getting the generator's count"
#define PLEX_ERRORMESS_GENERATOR_ONGETFINISHED "While getting if the generator is finished or not"
#define PLEX_ERRORMESS_GENERATOR_ONPULL "While pulling a generated value from generator"
#define PLEX_ERRORMESS_GENERATOR_ONSTART "While starting a generator"
#define PLEX_ERRORMESS_GENERATOR_ONUPDATE "While updating a generator"

// ACTION TARGETS

#define PLEX_ERRORMESS_GENERATOR_GENERATED "Generated Values of Generator"
#define PLEX_ERRORMESS_GENERATOR_GENERATOR "Generator"
#define PLEX_ERRORMESS_GENERATOR_MAXX "Generator Minimum X"
#define PLEX_ERRORMESS_GENERATOR_MAXXEND "Generator Minimum End X"
#define PLEX_ERRORMESS_GENERATOR_MAXY "Generator Minimum Y"
#define PLEX_ERRORMESS_GENERATOR_MAXYEND "Generator Minimum End Y"
#define PLEX_ERRORMESS_GENERATOR_MINX "Generator Minimum X"
#define PLEX_ERRORMESS_GENERATOR_MINXEND "Generator Minimum End X"
#define PLEX_ERRORMESS_GENERATOR_MINY "Generator Minimum Y"
#define PLEX_ERRORMESS_GENERATOR_MINYEND "Generator Minimum End Y"
#define PLEX_ERRORMESS_GENERATOR_XCOORDINATE "Generated X Coordinate"
#define PLEX_ERRORMESS_GENERATOR_YCOORDINATE "Generated Y Coordinate"

// INPUT ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_INPUT_ONSTART "While start of input system"
#define PLEX_ERRORMESS_INPUT_ONUPDATE "While update of input system"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERAXIS "While checking controller axis (ie. analog stick)"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISUP "While checking controller axis is up (ie. analog stick)"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISRIGHT "While checking controller axis is right (ie. analog stick)"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISDOWN "While checking controller axis is down (ie. analog stick)"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISLEFT "While checking controller axis is left (ie. analog stick)"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERCOUNT "While returning the controller count"
#define PLEX_ERRORMESS_INPUT_ONCONTROLLERPRESS "While checking pressing of controller button"

// ACTION TARGETS

#define PLEX_ERRORMESS_INPUT_AXISVALUE "Controller Axis Value"
#define PLEX_ERRORMESS_INPUT_CONTROLLER "Controller"
#define PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT "Controller Count"
#define PLEX_ERRORMESS_INPUT_CUSTOMCURSOR "Custom Cursor"
#define PLEX_ERRORMESS_INPUT_CURSORTEX "Cursor Texture"

#define PLEX_ERRORMESS_INPUT_CONTROLLERBUTTON "Controller Button"

// FAKESTRINGS ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_FAKESTRINGS_ONCREATE "While create string"

// ACTION TARGETS

#define PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING10 "Fakestring 10"
#define PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING25 "Fakestring 25"
#define PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING50 "Fakestring 50"
#define PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING100 "Fakestring 100"
#define PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING500 "Fakestring 500"

// MATH ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_MATH_ONGETRANDOMNUMBER "While getting a random number"
#define PLEX_ERRORMESS_MATH_ONPOINTTOPOLYGONCOLLISION "While calculating a point to polygon collision"
#define PLEX_ERRORMESS_MATH_ONPOLYGONTOPOLYGONCOLLISION "While calculating a collision of two polygons"

// ACTION TARGETS

#define PLEX_ERRORMESS_MATH_MINMAXRANDNUM "Random number generation"
#define PLEX_ERRORMESS_MATH_POLYGONPOINTS "Polygon points"
#define PLEX_ERRORMESS_MATH_POLYGONPOINTS2 "Polygon points on second polygon"

// MEMORY ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_MEM_ONSUBALLOC "While allocating memory on the suballoc level"
#define PLEX_ERRORMESS_MEM_ONSUBDEALLOC "While deallocating memory on the suballoc level"
#define PLEX_ERRORMESS_MEM_ONSTART "While starting the memory subsystem"
#define PLEX_ERRORMESS_MEM_ONEND "While ending the memory subsystem"
#define PLEX_ERRORMESS_MEM_ONALLOC "While allocating memory"
#define PLEX_ERRORMESS_MEM_ONINITREPORTFILE "While initializing the memory report file."
#define PLEX_ERRORMESS_MEM_ONDEALLOC "While deallocating memory"
#define PLEX_ERRORMESS_MEM_ONUPDATEPROFILE "While updating memory profile values"

#define PLEX_ERRORMESS_MEM_ONPRINTREPORTSTRING "While printing a memory report string"

#define PLEX_ERRORMESS_MEM_ONPRINTREPORTNUMSTRING "While printing a number to memory report string"

// ACTION TARGETS

#define PLEX_ERRORMESS_MEM_ALLOCED "Allocated memory"
#define PLEX_ERRORMESS_MEM_ALLOCEDPOINTER "Pointer to Pointer of Allocated Memory"
#define PLEX_ERRORMESS_MEM_REUSESTACK "Memory reuse stack"
#define PLEX_ERRORMESS_MEM_PREALLOCSSTACK "The preallocation stack"
#define PLEX_ERRORMESS_MEM_PREALLOCSSTACKCONTENTS "Contents of the preallocation stack"
#define PLEX_ERRORMESS_MEM_PREALLOCSSTACKENTRY "Preallocation stack entry #"
#define PLEX_ERRORMESS_MEM_PREALLOCSSTACKENTRYCONTENTS "Contents of preallocation stack entry #"
#define PLEX_ERRORMESS_MEM_REPORTSTACK "Stack carrying memory report info"
#define PLEX_ERRORMESS_MEM_REPORTFILENAME "Mem error report filename (the filename of the source an error is reported, not a filename it uses to save)"

// DIRECTORY ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLER "While getting a directory from a crawler"
#define PLEX_ERRORMESS_DIRECTORY_ONSTARTCRAWLER "While starting the directory crawler"
#define PLEX_ERRORMESS_DIRECTORY_ONCRAWL "While crawling directory"
#define PLEX_ERRORMESS_DIRECTORY_ONFREECRAWLER "While freeing direcctory crawler"
#define PLEX_ERRORMESS_DIRECTORY_ONGET "While getting directory from path"
#define PLEX_ERRORMESS_DIRECTORY_ONREOPEN "While trying to reopen a directory"
#define PLEX_ERRORMESS_DIRECTORY_ONCLOSE "While trying to close a directory"
#define PLEX_ERRORMESS_DIRECTORY_ONCOMPPATHS "While comparing directory paths"
#define PLEX_ERRORMESS_DIRECTORY_ONGETPATH "While getting the directory path"
#define PLEX_ERRORMESS_DIRECTORY_ONGETFULLPATH "While getting the directory full path"
#define PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLERPATH "While getting the directory crawler's path"
#define PLEX_ERRORMESS_DIRECTORY_ONGETFULLCRAWLERPATH "While getting the directory crawler's full path"
#define PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLERFILE "While getting the directory crawler's file from the directory crawler"
#define PLEX_ERRORMESS_DIRECTORY_ONCHECKINGCRAWLERISDIRECTORY "While checking if a directory crawler is a directory or not."

// ACTION TARGETS

#define PLEX_ERRORMESS_DIRECTORY_DIRECTORY "Directory"
#define PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS "Directory contents"
#define PLEX_ERRORMESS_DIRECTORY_CRAWLER "Directory crawler"
#define PLEX_ERRORMESS_DIRECTORY_CRAWLERSDIRECTORY "The directory inside a directory crawler"

// SCROLLER ---------------------------------------------------------------

// ACTIONS

#define PLEX_ERRORMESS_SCROLLER_ONRESET "While resetting a scroller"
#define PLEX_ERRORMESS_SCROLLER_ONINCREMENT "While incrementing the scroller"
#define PLEX_ERRORMESS_SCROLLER_ONSETSCROLLERPAGELEN "While setting the scroller's page length"
#define PLEX_ERRORMESS_SCROLLER_ONCHECKINGSKIPSCROLLER "While checking to skip the scroller"
#define PLEX_ERRORMESS_SCROLLER_ONSCROLLUP "While scrolling the scroller up"
#define PLEX_ERRORMESS_SCROLLER_ONSCROLLDOWN "While scrolling the scroller down"
#define PLEX_ERRORMESS_SCROLLER_ONPAGEUP "While paging scroller up"
#define PLEX_ERRORMESS_SCROLLER_ONPAGEDOWN "While paging scroller down"
#define PLEX_ERRORMESS_SCROLLER_ONCANSCROLLUP "While checking if scroller can scroll up"
#define PLEX_ERRORMESS_SCROLLER_ONCANSCROLLDOWN "While checking if scroller can scroll down"
#define PLEX_ERRORMESS_SCROLLER_ONCANSCROLLCOUNT "While getting scroller count"

// ACTION TARGETS

#define PLEX_ERRORMESS_SCROLLER_SCROLLER "Scroller"

#endif
