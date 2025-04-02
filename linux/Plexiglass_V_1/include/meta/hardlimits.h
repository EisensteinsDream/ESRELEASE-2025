#ifndef PLEX_HARDLIMITS_H
#define PLEX_HARDLIMITS_H

// This header contains a series of macros which contain predetermined limitations for buffers and other things. Unlike values in memprofile these are constant throughout execution. Mostly for units that load before the memory system initiates like the error unit.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// ERROR

#define PLEX_LIMIT_ERROR_MESSLEN 1024
#define PLEX_LIMIT_ERROR_SHOWLEN 16
#define PLEX_LIMIT_ERROR_DUMPFILELEN 64
#define PLEX_LIMIT_ERROR_LINENUMMAX 10

// DEFAULTS

#define PLEX_LIMIT_DEFAULT_DEFAULTBUFFLEN 128

// MATH

#define PLEX_LIMIT_POLYSIDES 32

// MEM

#define PLEX_LIMIT_MEMREPORTFILENAME 1024

// INPUT

#define PLEX_LIMIT_CONTROLLERS 16

#define PLEX_LIMIT_KEYCAP 127 // this number should likely just remain 127 as that's the number of keys in ASCII and SDL keys can be remapped for unicode values.
#define PLEX_LIMIT_FKEYCAP 24 // this number is with the assumption that the version of SDL it is using has 24 fkeys. It should always be the number of function keys readable.

// SOUND

#define PLEX_LIMIT_SOUNDCHANNELS 16
#define PLEX_LIMIT_SOUNDEFFECTS 5
#define PLEX_LIMIT_PREBUFFERCOUNT 64

#endif
