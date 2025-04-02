#ifndef PLEX_ERRORMESS_H
#define PLEX_ERRORMESS_H

// A branching header that uses language macros to decide the proper error message string macros. More information can be found in language.h.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

#include "meta/language.h"

// here's where they branch:

#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
	#include "errormess/errormess_en.h"
#endif

#endif
