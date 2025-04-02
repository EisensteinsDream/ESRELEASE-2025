#include "utility/prominencemachine.h"

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_PROMINENCEMACHINE* PLEX_genProminenceMachineInt(const size_t errorline, const char* const errorfile)
{
	PLEX_PROMINENCEMACHINE* ret = PLEX_allocInt(sizeof(PLEX_PROMINENCEMACHINE), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGENERATE, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return NULL;
	}

	ret->prominenceCap = 0;
	ret->prominences = PLEX_genExpandArrayInt(PLEX_getMemProfilePromPreload(), sizeof(uint32_t), errorline, errorfile);

	if(ret->prominences == NULL)
	{
		PLEX_deallocInt((void**)&ret, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGENERATE, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCES, errorline, errorfile);
		return NULL;
	}

	return ret;
}

void PLEX_destroyProminenceMachineInt(PLEX_PROMINENCEMACHINE** toDestroy, const size_t errorline, const char* const errorfile)
{
	PLEX_PROMINENCEMACHINE* toDestroyPtr = NULL;

	if(toDestroy == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONDESTROY, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return;
	}

	toDestroyPtr = *toDestroy;

	if(toDestroyPtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONDESTROY, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return;
	}

	PLEX_destroyExpandArrayInt(&toDestroyPtr->prominences, errorline, errorfile);

	PLEX_deallocInt((void**)toDestroy, errorline, errorfile);
}

int64_t PLEX_addProminenceInt(const uint32_t prominence, PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile)
{
	uint32_t* prominencePtr = NULL;

	if(machine == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONADD, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return -1;
	}

	if(machine->prominences == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_PROMINENCEMACHINE_ONADD, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCES, errorline, errorfile);
		return -1;
	}

	if(!PLEX_incrementExpandArrayInt(machine->prominences, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONADD, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCES, errorline, errorfile);
		return -1;
	}

	prominencePtr = (uint32_t*)PLEX_getExpandArrayLastInt(machine->prominences, errorline, errorfile);

	if(prominencePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONADD, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCE, errorline, errorfile);
		return -1;
	}

	*prominencePtr = prominence;

	machine->prominenceCap += prominence;

	return PLEX_expandArrayCountInt(machine->prominences, errorline, errorfile) - 1;
}

void PLEX_removeProminenceInt(const size_t index, PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	uint32_t* removeAmount = NULL;

	if(machine == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONREMOVAL, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return;
	}

	if(machine->prominences == NULL)
	{
		// not neccesarily content corruption
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_PROMINENCEMACHINE_ONREMOVAL, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(machine->prominences, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_PROMINENCEMACHINE_ONREMOVAL, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	removeAmount = (uint32_t*)PLEX_getExpandArrayEntryInt(index, machine->prominences, errorline, errorfile);

	if(removeAmount == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONREMOVAL, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCE, errorline, errorfile);
		return;
	}

	machine->prominenceCap -= *removeAmount;

	PLEX_removeExpandArrayInt(index, machine->prominences, errorline, errorfile);
}

// getters ------------------------------------------------------------------------------------------------------------------

int64_t PLEX_getProminenceInt(const PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile)
{
	uint64_t nextProminence = 0;
	uint64_t prominencePoint = 0;

	if(machine == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGET, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return -1;
	}

	prominencePoint = PLEX_randomNumber(0, machine->prominenceCap);

	for(size_t ze = 0; ze < PLEX_expandArrayCount(machine->prominences); ++ze)
	{
		uint32_t* prominencePtr = PLEX_getExpandArrayEntry(ze, machine->prominences);

		if(prominencePtr == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGET, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCE, errorline, errorfile);
		}

		nextProminence += *prominencePtr;

		if(prominencePoint < nextProminence) return ze;
	}

	return PLEX_expandArrayCountInt(machine->prominences, errorline, errorfile);
}

size_t PLEX_getProminenceCountInt(const PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile)
{
	if(machine == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGETCOUNT, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCEMACHINE, errorline, errorfile);
		return 0;
	}

	if(machine->prominences == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_PROMINENCEMACHINE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_PROMINENCEMACHINE_ONGETCOUNT, PLEX_ERRORMESS_PROMINENCEMACHINE_PROMINENCES, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(machine->prominences, errorline, errorfile);
}
