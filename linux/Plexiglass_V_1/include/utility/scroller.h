#ifndef PLEX_SCROLLER_H
#define PLEX_SCROLLER_H

#include "utility/error.h"

// this unit manages generic scrolling agonistic of the items it is scrolling through

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

#define PLEX_resetScrolling(scroller) PLEX_resetScrollingInt(scroller, __LINE__, __FILE__)

#define PLEX_increment(scroller) PLEX_incrementInt(scroller, __LINE__, __FILE__)

#define PLEX_setPagelen(entryH, h, scroller) PLEX_setPagelenInt(entryH, h, scroller, __LINE__, __FILE__)

#define PLEX_checkSkip(scroller) PLEX_checkSkipInt(scroller, __LINE__, __FILE__)

#define PLEX_scrollUp(scroller) PLEX_scrollUpInt(scroller, __LINE__, __FILE__)

#define PLEX_scrollDown(scroller) PLEX_scrollDownInt(scroller, __LINE__, __FILE__)

#define PLEX_pageUp(scroller) PLEX_pageUpInt(scroller, __LINE__, __FILE__)

#define PLEX_pageDown(scroller) PLEX_pageDownInt(scroller, __LINE__, __FILE__)

#define PLEX_scrollCount(scroller) PLEX_scrollCountInt(scroller, __LINE__, __FILE__)

#define PLEX_canScrollUp(scroller) PLEX_canScrollUpInt(scroller, __LINE__, __FILE__)

#define PLEX_canScrollDown(scroller) PLEX_canScrollDownInt(scroller, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	size_t start, count, counted, pageLen, skip;
} PLEX_SCROLLER;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	extern PLEX_SCROLLER PLEX_createScroller(const size_t count);

	extern void PLEX_resetScrollingInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern bool PLEX_incrementInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern void PLEX_setPagelenInt(const double entryH, const double h, PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern bool PLEX_checkSkipInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern void PLEX_scrollUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern void PLEX_scrollDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern void PLEX_pageUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern void PLEX_pageDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	extern size_t PLEX_scrollCountInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern bool PLEX_canScrollUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

	extern bool PLEX_canScrollDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile);

#ifdef __cplusplus
}
#endif

#endif
