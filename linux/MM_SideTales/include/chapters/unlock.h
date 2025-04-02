#ifndef MMS_UNLOCK_H
#define MMS_UNLOCK_H

#include "plex.h"

#include "meta/mms_language.h"

#ifdef __cplusplus
extern "C"
{
#endif
	extern uint64_t MMS_MMS0MinigameKeyword();
	extern uint64_t MMS_MMS1Keyword();

	extern uint64_t MMS_MMS1MinigameKeyword();
	extern uint64_t MMS_MMS2Keyword();

	extern uint64_t MMS_MMS2MinigameKeyword();
	extern uint64_t MMS_MMS3Keyword();

	extern bool MMS_MMS0MinigameUnlocked();
	extern bool MMS_MMS1Unlocked();
	extern bool MMS_MMS1MinigameUnlocked();
	extern bool MMS_MMS2Unlocked();
	extern bool MMS_MMS2MinigameUnlocked();
	extern bool MMS_MMS3Unlocked();

	extern void MMS_MMS0MarkMinigame();
	extern void MMS_MMS0MarkEnd();
	extern void MMS_MMS1MarkMinigame();
	extern void MMS_MMS1MarkEnd();
	extern void MMS_MMS2MarkMinigame();
	extern void MMS_MMS2MarkEnd();
#ifdef __cplusplus
}
#endif

#endif
