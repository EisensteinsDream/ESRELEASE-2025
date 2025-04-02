#ifndef PLEX_DEFAULTNAMES_H
#define PLEX_DEFAULTNAMES_H

// A branching header that uses language macros to decide the macro strings for default names (ie. names of config variables). More information can be found in language.h.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

#include "meta/language.h"

// here's where they branch:

#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
	#include "defaultnames/defaultnames_en.h"
#endif

#endif
