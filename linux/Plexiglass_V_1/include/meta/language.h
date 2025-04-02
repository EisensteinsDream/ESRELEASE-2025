#ifndef PLEX_LANGUAGE_H
#define PLEX_LANGUAGE_H

// This header is a branching header for different language compiles of PLEX. Currently the only supported language is English. I'm hoping that won't remain that way forever. To see the string macros contained within just go to the "meta/language/language_en.h" header. There are also similar language files for error messages and default names (ie. variable names for the '.pcfg' file)

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// language codes for plex

#define PLEX_LANGUAGE_ENGLISH 0

// if no language is defined in compilation defaults to English

#ifndef PLEX_LANGUAGE
	#define PLEX_LANGUAGE PLEX_LANGUAGE_ENGLISH
#endif

// branches to relevant language header

#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
	#include "language/language_en.h"
#endif

#endif
