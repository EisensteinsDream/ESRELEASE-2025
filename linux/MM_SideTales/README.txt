------------------------------------------------------------
MMS V.2:
------------------------------------------------------------

This is version 2 of 'MM Side Tales'. It is a companion piece to a much bigger project simply called 'MM'. Which will be released in the distantish future. MMS is not one game, but three minigames with three different styles of gameplay. They are also intertwined in a series of story events presented as a "digital puppet show".

Some of these minigames are a bit tricky. I've included a 'Tips' file, in case some of them get a bit frustrating. The Tips file won't tell you exactly how need to beat any of them, but it'll help you get there.

------------------------------------------------------------
Installation:
------------------------------------------------------------

NOTE: Currently MMS will only run in Windows and Linux (unless compiled from a modified 'PLEX' and 'MM Common'). For the moment only a 32 bit version of windows is available.

Linux:

	NOTE: MMS requires an OS with a posix standard of at least 7. It's very very rare that you'll be running a version of Linux where this isn't the case. It should be fine unless you're running a really dated distribution. It also compiles to C18 which should not be an issue if you have gcc updated.

	> Make sure to install the following libraries on your system: shell, make, gcc, portaudio, sdl2, sdl2_image, and libsndfile. These should all be readily available through most package managers. The vast majority of linux systems come with the first three already installed.

	> simply go into the linux subdirectory and open a terminal. Type 'sh install.sh' into that terminal. If you have all the dependencies it should install. If not, it's likely a system or dependency issues. Read error messages carefully in that case.

	> with your terminal still open type 'sh run.sh'. If it works, everything went well.

Windows:

	> There's a precompiled executable in 'windows\Win32'. Any error or memory logs are stored in 'windows\mms_error_32'. I compiled this with mingw and I don't have a windows computer to test this on. I would like to supply a 64-bit version but for complicated reasons I can't until I have a windows computer to build on again.

------------------------------------------------------------
Config file:
------------------------------------------------------------

When you run MMS for the first time it should produce a file called 'config_en.pcfg'. This is a basic configuration file. Most the values either take a boolean ('false' is assumed if it's anything but 'true'), a number, or a string. Neither MMS nor PLEX at the moment use string entries. But PLEX allows custom entries that can be strings. A lot of these you'll never really need to change. Some of them are just there for fun (changing the r, g, b values of the standard cursor value 0-255). Others are there for preference (disable sound is the one I've had to use through testing most extensively).

Performance configurations:

	> There are a few performance options if MMS is being sluggish. The first is the 'texture dimension limit'. This should default to 10000. MMS loads very large textures which give it longish loading times at points. On some systems with lower VRAM this can cause textures to disappear entirely. If you lower this number, textures width or height cannot be larger than whatever number you put into it. If you see what appears to be images not rendering this is an option.

	> Another is 'memory profile' which can be raised to precache more data in memory or lowered for less. The number goes from 0-4. The higher the number is, the more ram it takes but the lower CPU overhead. On most modern systems, any of these numbers should be fine. But on low performance machines '4' may be a good option. Even the lowest end PCs available now should have enough RAM to handle MMS easily.

	> The final is "copy headerless textures". If this value is 'true' on the load of most textures there will be an alternate 'headerless texture' created in the 'headerlesstex' folder. These are much larger than the compressed '.png' files they're loaded from. However, because they are uncompressed they load much more quickly than a regular image file. It's recommended to only set this false if you are working with extremely limited drive space.

Debugging configurations:

	> You can use some debug values if you're interested in modifying the source. This is NOT recommended if you're not familiar with C programming. However, if you're comfortable with that, there's a few debug features that are quite useful. Like a very readable error system and memory diagnostics.

	> "print memory report" and "print memory report to file". The first indicates to print a memory report in the terminal at end of programming execution. This should tell you if anything in smart memory is allocated but not deallocated. Smart memory, of course, does deallocate everything at the end of execution. However, not using the dealloc feature makes memory hangs possible. This also will tell you the line and file where this happens. Of course "print memory report to file" prints a copy into the ./error folder.

	> There's also values that can control which errors print, show, or terminate. These are determined by numbers from 1-4. With 1 being 'impossible errors', 2 being 'fatal errors', 3 being 'major errors', 4 being 'minor errors', and 5 being 'badstyle' errors. Impossible and fatal errors will terminate the program no matter what. You can't change that.

	The values you set with these numbers are 'print error threshold', 'show error threshold', and 'fatal error threshold'. Also, if you chose any error setting then it will also apply to all errors of a higher number. So if you decide to print 'major errors' it will also print 'minor' and 'badstyle' errors but not 'fatal' or 'impossible' errors.

	> There's also boolean "print errors", "show errors", and "dump errors". Print means print to terminal. Show means show in pop up menu. Dump means dump to error log file. The first two usually you don't really need to make false unless they're annoying. These will overwrite the number thresholds.

------------------------------------------------------------
Improvements (From V.1):
------------------------------------------------------------

	* changed the word 'rookie' to 'struggling' in the intro to make more chonological sense.
	* the skip button was moved from MMS into MM_Common
	* finished PLEX V_1, deleted PLEX_MMS, and calibrated MMS for PLEX V_1
	* fixed and rearranged the 'day-to-day' theme.
	* fixed a lot of underlying issues with the plex sound library and with the songs themselves in mm_common
	* fixed a bug that made the menu highlight the wrong gun
	* fixed a bug where the 'skip' button would get stuck in the pre-boss cutscene of minigame 2 'reboot'
	* got rid of the 'get null' and 'set null' error types in PLEX so they're also gone in MMS
	* fixed issues with the 'panic' theme
	* fixed sprite plate 2 in mms2 which I accidentally had a large portions of the sprites translucent
	* fixed the random algorithm in PLEX so things aren't generated bunched together
	* added a lizard animal cover in the final trail of MMS2
	* added a storm cloud cover in the final trail of MMS2
	* changed a red cross pattern on an NPC's crotch which was there for no reason I can surmise and I must've been crazy from exhaustion when I made that choice.
	* added a mechanical horse cover in the final trail of MMS2
	* MM common has been improved in some ways (every theme has been separated to a different file)
	* Set up the usage of an MM themed custom cursor
	* Cleaned up the internal code a little bit. Particularly correcting stuff that should have been in gui.c that was in player.c and vice versa.
	* Gotten rid of the incredibly poorly written 'documentation' at the bottom of this document. Hoping at some point to be able to write something more comprehensible.
	* rebalanced the trumbone in 'newsroom' theme so it didn't clip as ridiculously as it was
	* fixed a MAJOR crash that sometimes randomly caused the program to terminate execution during sprite theater
	* replaced the line 'I married him when I was around 3275.' with 'I was well over 6275 when the divorce happened.' to make more logical sense.
