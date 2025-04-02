#ifndef PLEX_OSADAPT_H
#define PLEX_OSADAPT_H

// This header contains all the macro branches to indicate different operating systems and environments. This header is included at the top of cinclude.h, and should always be included before all other PLEX headers. Useful for cutting off sections of code which are only relevant to a particular environment. This is a foundational part of the entire PLEX library.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// Number codes which indicate the bitrate of the environment. If undetectable XX_BIT is assigned. XX_BIT is assigned on default. I know the likelihood of this being compiled on a 16 bit environment is very low. I figure better safe than sorry, I guess.

#define PLEX_CORE_XXBIT 0
#define PLEX_CORE_16BIT 1
#define PLEX_CORE_32BIT 2
#define PLEX_CORE_64BIT 3

// Number codes which indicate the base OS. NOOS mode means the current OS is unavailable or unread. PLEX will not run in NOOS mode. It's only Windows and Linux for the moment as mentioned above.

#define PLEX_CORE_NOOS 0
#define PLEX_CORE_LINUX 1
#define PLEX_CORE_WINDOWS 2

// sets default values.

#define PLEX_CORE_OS PLEX_CORE_NOOS
#define PLEX_CORE_IS_UNIX false
#define PLEX_CORE_IS_APPLE false
#define PLEX_CORE_BITCOMPILE PLEX_CORE_XXBIT

// all the definitions for windows system. PLEX_NL means Plex New Line. Which indicates the fashion of new line for printing.

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
	#undef PLEX_CORE_OS
	#define PLEX_CORE_OS PLEX_CORE_WINDOWS

	#define PLEX_NL "\r\n"

	#ifdef _WIN16
		#undef PLEX_CORE_BITCOMPILE
		#define PLEX_CORE_BITCOMPILE PLEX_CORE_16BIT
	#endif

	#ifdef _WIN32
		#ifdef _WIN64
			#undef PLEX_CORE_BITCOMPILE
			#define PLEX_CORE_BITCOMPILE PLEX_CORE_64BIT
		#else
			#undef PLEX_CORE_BITCOMPILE
			#define PLEX_CORE_BITCOMPILE PLEX_CORE_32BIT
		#endif
	#endif
#endif

// checking if the system is linux

#if defined(__linux__) || defined(linux) || defined(__linux)
	#undef PLEX_CORE_OS
	#define PLEX_CORE_OS PLEX_CORE_LINUX

	#define PLEX_NL "\n"

	#if defined(__x86_64__) || defined(__amd64__) || defined(__amd64)
		#undef PLEX_CORE_BITCOMPILE
		#define PLEX_CORE_BITCOMPILE PLEX_CORE_64BIT
	#elif defined(i386) || defined(__i386) || defined(__i386__)
		#undef PLEX_CORE_BITCOMPILE
		#define PLEX_CORE_BITCOMPILE PLEX_CORE_32BIT
	#endif
#endif

// checking if the system is apple (not yet implemented or tested. PLEX will not run if this is true)

#if defined(__APPLE__)
	#undef PLEX_CORE_IS_APPLE
	#define PLEX_CORE_IS_APPLE true

	#define PLEX_NL "\r"
#endif

// checking if the OS is linux

#if defined(__unix__) || defined(__unix) || defined(_POSIX_VERSION)
	#undef PLEX_CORE_IS_UNIX
	#define PLEX_CORE_IS_UNIX true

	// some features may not work without this. I haven't been able to test on an environment where this isn't the case.
	#if defined(__GNUG__)
		#define _GNU_SOURCE
	#endif

	// this is needed for directory crawling. It may disqualify some versions of linux without it (very very old versions, highly unlikely for somebody to be using). Updated branches of Linux should theoretically use updated versions of POSIX and this shouldn't be an issue.
	#define _XOPEN_SOURCE 700
#endif

#endif
