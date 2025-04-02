#include "(system directory)/(system).h" // < preferably all lower case

// NOTE: global function descriptions in header.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

// structs, unions, and enums go here if they are needed.

// static values ------------------------------------------------------------------------------------------------------------

static bool p_active = false;
static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

// static functions that are needed go here.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void (PROJ)_activate(System Name)()
{
	if(!p_running)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_ACTIVATE, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	p_active = true;
}

void (PROJ)_deactivate(System Name)()
{
	if(!p_running)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_DEACTIVATE, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	p_active = false;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool (PROJ)_start(System Name)()
{
	if(p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return true;
	}

	p_active = false;
	p_running = true;

	return true;
}

bool (PROJ)_update(System Name)(const uint64_t time)
{
	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return false;
	}

	if(!p_active)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_UPDATE, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return false;
	}

	return true;
}

void (PROJ)_end(System Name)()
{
	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_SYSTEMERROR0 "(System Name)" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

// any functions that set internal values go here.

// getters ------------------------------------------------------------------------------------------------------------------

bool (PROJ)_is(System Name)Running(){ return p_running; }
bool (PROJ)_is(System Name)Active(){ return p_active; }
