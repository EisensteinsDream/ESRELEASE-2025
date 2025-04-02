The directory containing this file (0Template) is a template for PLEX-based projects. 'PLEX' refers to the 'Plexiglass Utility Layer'. The source for PLEX should have been distributed alongside this template. More information on that will be in the directory 'Plexiglass'.

First thing you need to do is copy/paste '0Template' to a new directory. This new directory should have the same parent directory as 'Plexiglass'. Rename it something relevant to your project. After doing that, close this version of 'README_FIRST.txt', and open the 'README_FIRST.txt' in the newly pasted directory.

NOTE: All replace operations should be case sensitive. So if it's 'PROJ' it'd be all caps, 'proj' it'd be all lower, and 'Proj' would be capitalized. This is very very important.

NOTE: PLEX is a C library not a C++ library. So the term 'namespace' simply means a series of characters that you put at the front of function names and typenames.

NOTE: I'm using UNIX style filepaths in these examples. I am Linux user; it's a force of habit. It's pretty much the same as windows except it uses the opposite slashes. Most modern windows compilers don't care about this. Possibly all of them don't. It might be jarring to a windows user. There are no drive letters like 'C:' in UNIX filepaths, either. However, drive letters are not that important to this tutorial. Every directory path is relative to the directory THIS file is in.

--------------------------
DEPENDENCIES: gcc, clang (optional), sdl2, sdl2_image, portaudio, libsndfile (Pre-compiled windows versions of PLEX should already have these. No need to compile them)
--------------------------

1. Find and replace all instances of (PROJ) in all files in this folder with your own namespace (exclude parentheses). This should be a unique-ish set of letters typically 3-5 long. Obviously should not be using 'PLEX' or 'SDL' or anything of that nature. (ie. for my project MMS, that would be 'MMS').
2. You can skip this step if you're not compiling on Linux. Replace (DIRECTORYNAME) in 'updateplex.sh' (exclude parentheses). It will be the same name as the folder this is in.
3. Replace every instance of 'proj_' in all headers with your new namespace then an underscore. (ie. for MMS that you would make '#include language/proj_language_en.h' into "#include language/mms_language_en.h")
4. Change the filenames of "include/meta/proj_language.h" and "include/meta/language/proj_language_en.h" in the same way. Same with "include/meta/language/proj_filepaths.h" (ie. MMS would be "include/meta/mms_language.h", "include/meta/language/mms_language_en.h" and "include/meta/language/mms_filepaths.h")

(Steps 5-5c are Linux only unless you are planning to compile this with GNU Make on windows)

5. In file 'makefile'. replace the following lines accordingly:

	A. "HRLANGUAGE=$(INC)/meta/proj_language.h $(INC)/meta/language/proj_language_en.h" replacing the 'proj' in the same way as above. (ie. MMS would be "HRLANGUAGE=$(INC)/meta/mms_language.h $(INC)/meta/language/mms_language_en.h").

	B. "HRFILENAME=$(INC)/meta/proj_filepaths.h" same story (ie. MMS would be "HRFILENAME=$(INC)/meta/mms_filepaths.h")

5b. If you want to use clang instead of gcc to compile it's pretty simple just replace these lines:

		CC=gcc -O3 -fsanitize=address,undefined
		CCD=gcc -g3

	With these ones:

		CC=clang -O3 -fsanitize=address,undefined
		CCD=clang -g3

5c. If you want to compile to C++ rather than C you must replace the lines again.

	For gcc take those same lines and make them:

		CC=g++ -O3 -fsanitize=address,undefined
		CCD=g++ -g3

	With clang the lines would be:

		CC=clang++ -O3 -fsanitize=address,undefined
		CCD=clang++ -g3

	You also have the replace the line:

		FLAGS=-Wall -Wextra -Wno-sign-compare -Werror -Wno-strict-prototypes -pedantic -std=c18 -march=native -I$(INC) -I$(HINC) -Wno-unused-parameter

	with the line:

		FLAGS=-Wall -Wextra -Wno-sign-compare -Werror -Wno-strict-prototypes -pedantic -std=c++17 -march=native -I$(INC) -I$(HINC) -Wno-unused-parameter

	I am guessing that you can also compile to C++20 if you wish. Probably, C++17 or any modern C++ versions. I have no idea whether this will compile in C++98 or not. I'm not sure how C versions and C++ versions align that way.

6. In the file formerly "include/meta/language/proj_language_en.h" replace (PROJECT TITLE) with whatever you want your project title to be. It will show up in the window bar when you run the program.

(Step 7 is only relevant if you're using make to build your templated program)

7. type 'make rebuild' in a shell in the project directory.

8. delete every file named 'deleteme'. This is not strictly required but makes things much cleaner.

(Step 9 is only relevant if you're using make to build your templated program)

9. try running 'sh run.sh'. If it works feel free to delete this file.

NOTE: If you're using an IDE you're going to have to figure it out yourself. I can't provide a tutorial for every popular IDE. Obviously, you want to link all of the dependecies listed above. Include all the source in '/src' and include all the headers in '/include'

( --- STOP HERE IF THIS IS AN EXECUTABLE NOT A LIBRARY (NOT FOR BEGINNERS) --- )

10. Delete src/main.c
11. Rename "include/game.h" and "src/game.c" to something more relevant to the library (ie. MM_common = "include/mmcommon.h and src/mmcommon.c")
12. Likewise in both these files simply delete the word 'Game' in all function names leaving their names in tact. (ie. MM_COMMON = 'extern bool MM_COMMON_startGame();' would become 'extern bool MM_COMMON_start();')
13. In 'src/game.c' replace the line "#include "game.h" to whatever you renamed "game.h" something of the like (ie. MM_COMMON = "#include "mmcommon.h"")
14. in the SAME file replace "return !PLEX_isTerminated();" with "return true;"

(Steps 15-17 are only relevant if you are compiling in Linux or with GNU MAKE on another system)

The following steps should all be done in the makefile:

14. replace every instance of 'game' with the name you game.c to. (i.e. MM_common = game.o should be made into 'mmcommon.o' )
15. do the same with every uppercase incident of 'GAME'. (ie. MM_common = "HRGAME" should become "HRMMCOMMON")
16. Also in the makefile, delete EVERYTHING below, and including, the line "# BINARY COMPILES #"
17. This is a messy complicated step but it is needed. You no longer need a 'bin' directory anymore. You need to pull out every single reference to BIND. Read carefully.:

	A. Delete the lines "BIND=./bin", "RBIND=$(BIND)/release", "DBIND=$(BIND)/debug"

	B. in the line below the line that says "clean:" delete every single value between & signs that has the word BIND in it. Even if it's something like RBIND. It's important you don't screw around with the syntax here. When you're done the line should look like:

	"rm $(ROBJD)/*; rm $(RLIBD)/*; rm $(DOBJD)/*; rm $(DLIBD)/*;"

	You can simply copy/paste that line into there if you want (without quotations). As long as you keep the semicolon and single tab it, it should be ok.

	C. remove references to 'BIND' in all of the following lines. (this is IF you named your library MM_COMMON. Those parts of this should be whatever you named your library):

	"release: $(ROBJ) $(RLIBD)/libMM_COMMON.so $(RBIND)/main
	debug: $(DOBJ) $(DLIBD)/libMM_COMMON.so $(DBIND)/main"

	In the end it should look like this:

	"release: $(ROBJ) $(RLIBD)/libMM_COMMON.so
	debug: $(DOBJ) $(DLIBD)/libMM_COMMON.so"

	You can copy-paste this too (also without quotations). Just be careful you overwrite all the lines replaced and no more. Plus, make sure to replace the line MM_COMMON with your library name.

	D. Also remove all references of BIND in the following lines:

	"rclean:
		rm $(ROBJD)/*; rm $(RBIND)/*; rm $(RLIBD)/*;

	dclean:
		rm $(DOBJD)/*; rm $(DBIND)/*; rm $(DLIBD)/*;"

	To become:

	"rclean:
		rm $(ROBJD)/*; rm $(RLIBD)/*;

	dclean:
		rm $(DOBJD)/*; rm $(DLIBD)/*;"

Now we are done with makefiles:

18. delete the 'bin' directory (and all subdirectorys) in your main directory. These are irrelevant to a library anyway
19. WITH THE EXCEPTION OF "updateplex.sh", delete all shell scripts (any file ending with the extension .sh) in the directory. All of these are basically tuned specifically to run a project in Linux and make no sense without an executable to run.
20. (Linux only) run "sh updateplex.sh" in terminal. This may take awhile.
21. (Linux only) run make all.

NOTE: I'm also not going to include the process of compiling as library for IDEs. I mean, that's a complicated process that most IDEs do in their own specific way. Besides, I don't feel one should be compiling this as a library unless they know what they are doing to some extent.
