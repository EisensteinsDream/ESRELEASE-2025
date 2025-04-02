#ifndef PLEX_PROMINENCEMACHINE_H
#define PLEX_PROMINENCEMACHINE_H

#include "utility/math.h"

#include "mem/expandarray.h"

// this unit allows the creation of 'prominence machines' which essentially work as weighted randomizer. You create a new entry by passing a 'prominence' which offers a sort of weight to the next entry. It returns a index to that prominence. You then can 'get prominence' at any point in time. It returns a randomized index to which more likely will hit the entries with a higher prominence than ones with a lower prominence.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// NO ARGUMENTS - returns PLEX_PROMINENCEMACHINE*

#define PLEX_genProminenceMachine() PLEX_genProminenceMachineInt(__LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROMINENCEMACHINE** toDestroy)

#define PLEX_destroyProminenceMachine(toDestroy) PLEX_destroyProminenceMachineInt(toDestroy, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t prominence, PLEX_PROMINENCEMACHINE* machine) - returns int64_t

#define PLEX_addProminence(prominence, machine) PLEX_addProminenceInt(prominence, machine, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_PROMINENCEMACHINE* machine)

#define PLEX_removeProminence(index, machine) PLEX_removeProminenceInt(index, machine, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROMINENCEMACHINE* machine) - returns int64_t

#define PLEX_getProminence(machine) PLEX_getProminenceInt(machine, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROMINENCEMACHINE* machine) - returns size_t

#define PLEX_getProminenceCount(machine) PLEX_getProminenceCountInt(machine, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

// struct that contains the information for a prominence machine.
typedef struct
{
	PLEX_EXPANDARRAY* prominences;
	uint64_t prominenceCap;
} PLEX_PROMINENCEMACHINE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// creates a new prominence machine. Prominence machines do not need any information passed for their creation.

	extern PLEX_PROMINENCEMACHINE* PLEX_genProminenceMachineInt(const size_t errorline, const char* const errorfile);

	// destroys a prominence machine and sets the pointer to it as NULL.

	extern void PLEX_destroyProminenceMachineInt(PLEX_PROMINENCEMACHINE** toDestroy, const size_t errorline, const char* const errorfile);

	// adds a 'prominence' to the machine. A higher 'prominence' number gives it a higher chance of being chosen at getProminence. Returns index, if anything goes wrong it returns -1

	extern int64_t PLEX_addProminenceInt(const uint32_t prominence, PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile);

	// removes the prominence entry at 'index'

	extern void PLEX_removeProminenceInt(const size_t index, PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns generated prominence index from the passed in prominence machine. Returns -1 if something goes wrong.

	extern int64_t PLEX_getProminenceInt(const PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile);

	// returns the number of prominences in the prominence machine.

	extern size_t PLEX_getProminenceCountInt(const PLEX_PROMINENCEMACHINE* machine, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
