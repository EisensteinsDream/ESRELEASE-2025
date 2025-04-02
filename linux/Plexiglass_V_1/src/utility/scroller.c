#include "utility/scroller.h"

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_SCROLLER PLEX_createScroller(const size_t count)
{
	PLEX_SCROLLER scroll;

	memset(&scroll, 0, sizeof(scroll));

	scroll.count = count;

	return scroll;
}

void PLEX_resetScrollingInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONRESET, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	scroller->counted = 0;
	scroller->skip = 0;
}

bool PLEX_incrementInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONINCREMENT, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return false;
	}

	if(scroller->counted >= scroller->count) return false;

	++scroller->counted;

	return true;
}

void PLEX_setPagelenInt(const double entryH, const double h, PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONSETSCROLLERPAGELEN, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	scroller->pageLen = h/entryH;
}

bool PLEX_checkSkipInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONCHECKINGSKIPSCROLLER, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return false;
	}

	if(scroller->skip < scroller->start)
	{
		++scroller->skip;
		return true;
	}

	return false;
}

void PLEX_scrollUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONSCROLLUP, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	if(scroller->start < scroller->counted) ++scroller->start;
}

void PLEX_scrollDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONSCROLLDOWN, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	if(scroller->start) --scroller->start;
}

void PLEX_pageUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONPAGEUP, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	if(scroller->start > scroller->pageLen) scroller->start -= scroller->pageLen;
	else scroller->start = 0;
}

void PLEX_pageDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONPAGEDOWN, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return;
	}

	scroller->start += scroller->pageLen;
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_scrollCountInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONCANSCROLLCOUNT, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return 0;
	}

	return scroller->count;
}

bool PLEX_canScrollUpInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONCANSCROLLUP, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return false;
	}

	return scroller->start;
}

bool PLEX_canScrollDownInt(PLEX_SCROLLER* scroller, const size_t errorline, const char* const errorfile)
{
	if(scroller == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCROLLER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCROLLER_ONCANSCROLLDOWN, PLEX_ERRORMESS_SCROLLER_SCROLLER, errorline, errorfile);
		return false;
	}

	return scroller->pageLen < scroller->counted;
}
