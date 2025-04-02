#include "chapters/mms0.h"

void MMS_startOutroB(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_NEWSROOM);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE1);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE2);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE3);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE4);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE5);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE6);

	MMS_pamTalkWait(MMS_LANGUAGE_OUTROB_LINE7, 3000, true);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE8);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE9);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE10);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE11);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE12);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE13);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE14);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE15);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE16);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE17);

	MMS_extrapTalk(MMS_LANGUAGE_OUTROB_LINE18);

	MMS_pamTalk(MMS_LANGUAGE_OUTROB_LINE19);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS_LANGUAGE_OUTROB_LINE20);
}
