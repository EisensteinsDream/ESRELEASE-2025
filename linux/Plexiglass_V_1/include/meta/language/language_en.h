#ifndef PLEX_LANGUAGE_EN_H
#define PLEX_LANGUAGE_EN_H

// this header contains macro strings which are relevant to the English Language output of PLEX. More information on how that works check out the "meta/language.h" header.

// NOTE: As with all headers in the meta folder, there is no correlating source file.

// these two strings are basically strings which determine the order of letters in which bitmap fonts read. Entirely optional but saves some time. The first is for most messages, the second is only for strings that show a timer.

#define PLEX_LANGUAGE_ALPHASTRING "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!*.,;:?\"%'-() /$#"
#define PLEX_LANGUAGE_TIMESTRING "0123456789: "

// The default title. It's commonly overwritten by whatever project is dependant on the library

#define PLEX_LANGUAGE_TITLE "Yet Another"

// MEM REPORT

#define PLEX_MEMREPORT_HEADING "PLEX memory usage report (not to be confused with total memory usage as some memory is not handled through PLEX smart memory. ie. memory managed by PLEX's dependencies, low level system tasks, and memory used to run the smart memory containers themselves. If properly done, however, most heap memory should theoretically be smart memory)"

#define PLEX_MEMREPORT_PEAKMEMORY "Peak memory use (most allocated at one time)"

#define PLEX_MEMREPORT_MEMALLOCTOTAL "Total Memory Allocated with PLEX_alloc"
#define PLEX_MEMREPORT_MEMDEALLOCTOTAL "Total Memory Deallocated with PLEX_alloc"

#define PLEX_MEMREPORT_ALLOCDIFF "The difference between memory allocated by PLEX_alloc and PLEX_delloc is:"
#define PLEX_MEMREPORT_ALLOCDIFF2 "The larger this number is; the worse it is. Make sure that's PLEX_alloc'd is also PLEX_dealloc'd."
#define PLEX_MEMREPORT_ALLOCSAME "Good news! The amount of memory allocated with PLEX_alloc and PLEX_dealloc are the same!"
#define PLEX_MEMREPORT_FOOTER "All allocated memory will be cleared from the system. Since this smart memory management is neither a garbage collector nor a reference counter, forgetting to deallocate memory could result in memory hangs which risk overrun."

#define PLEX_MEMREPORT_EXPANDARRAY "Expand array @ line"
#define PLEX_MEMREPORT_EXPANDARRAY2 "in file"
#define PLEX_MEMREPORT_EXPANDARRAY3 "was never free'd in the program. This has been free'd at the end of the program but it's reccomended you free it before then to prevent memory hangs."

#define PLEX_MEMREPORT_HEADING_TOP "Spots where PLEX_alloc allocates memory but PLEX_dealloc is not applied:"

#define PLEX_MEMREPORT_UNFREE1 "Error # : "
#define PLEX_MEMREPORT_UNFREE2 " | Allocated at line : "
#define PLEX_MEMREPORT_UNFREE3 " | In File : \""
#define PLEX_MEMREPORT_UNFREE4 "\" | The Amount of Memory Allocated Was : "

#endif
