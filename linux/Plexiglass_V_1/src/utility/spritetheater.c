#include "utility/spritetheater.h"

// NOTE: global function descriptions in header.

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	char* message;

	uint8_t r, g, b;
	int64_t actor;
	uint64_t startGlobalTime, waitTime;
	bool pauseForWait, darken;
} P_SPRITETHEATER_SLIDE;

typedef struct
{
	PLEX_SPRITE* sprite;
	PLEX_RECT space;
	bool hidden, stopped;
	size_t aniIndex;
} P_SPRITETHEATER_ACTOR;

typedef enum
{
	P_SPRITETHEATER_ACTIONCHANGE_HIDE = 0,
	P_SPRITETHEATER_ACTIONCHANGE_UNHIDE = 1,
	P_SPRITETHEATER_ACTIONCHANGE_CHANGEANIMATION = 2,
	P_SPRITETHEATER_ACTIONCHANGE_MOVE = 3,
	P_SPRITETHEATER_ACTIONCHANGE_RESIZE = 4,
	P_SPRITETHEATER_ACTIONCHANGE_BACKGROUND = 5,
	P_SPRITETHEATER_ACTIONCHANGE_STARTSTOPSPRITE = 6,
	P_SPRITETHEATER_ACTIONCHANGE_CHANGESPRITE = 7,
	P_SPRITETHEATER_ACTIONCHANGE_DARKEN = 8
} P_SPRITETHEATER_ACTIONCHANGEEVENT;

typedef struct
{
	int64_t actor;
	size_t slide, backdrop;
	P_SPRITETHEATER_ACTIONCHANGEEVENT event;
	double amount, amount2;
	bool used;
	PLEX_FAKESTRING_100 stageName;
	PLEX_SPRITE* sprite;
} P_SPRITETHEATER_ACTIONCHANGE;

typedef enum
{
	P_SPRITETHEATER_MUSICSTOP = 0,
	P_SPRITETHEATER_MUSICPLAY = 1,
	P_SPRITETHEATER_SOUNDEFFECT = 2
} P_SPRITETHEATER_MUSICCHANGEEVENT;

typedef struct
{
	size_t slide, id;
	P_SPRITETHEATER_MUSICCHANGEEVENT event;
	bool used;
} P_SPRITETHEATER_MUSICCHANGE;

// static values ------------------------------------------------------------------------------------------------------------

static bool p_running = false;
static bool p_dispPause = false;

static size_t p_backdrop = 0;
static size_t p_font = 0;
static size_t p_labelPlate = 0;
static size_t p_bubble = 0;
static size_t p_arrow = 0;

static uint32_t p_labelPlateX = 0;
static uint32_t p_labelPlateY = 0;
static uint32_t p_labelPlateW = 0;
static uint32_t p_labelPlateH = 0;

static uint32_t p_bubbleW = 0;
static uint32_t p_bubbleH = 0;

static uint32_t p_arrowW = 0;
static uint32_t p_arrowH = 0;

static uint8_t p_labelR = 0;
static uint8_t p_labelG = 0;
static uint8_t p_labelB = 0;

static uint8_t p_messageR = 0;
static uint8_t p_messageG = 0;
static uint8_t p_messageB = 0;

static uint64_t p_theaterStart = 0;

static PLEX_FAKESTRING_100 p_stageName;

static char* p_message = NULL;

static PLEX_EXPANDARRAY* p_slides = NULL;
static PLEX_EXPANDARRAY* p_actors = NULL;

static PLEX_EXPANDARRAY* p_changes = NULL;

static PLEX_EXPANDARRAY* p_musicChanges = NULL;

static size_t p_slideIndex = 0;

static int64_t p_actorIndex = -1;

static size_t p_currentSong = 0;

static bool p_waitStopMusic = false;
static bool p_darken = false;

// static functions ---------------------------------------------------------------------------------------------------------

static void p_destroyActorStack(PLEX_EXPANDARRAY** actors, const size_t errorline, const char* const errorfile)
{
	PLEX_EXPANDARRAY* const actorPtr = *actors;

	const size_t count = PLEX_expandArrayCountInt(actorPtr, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		P_SPRITETHEATER_ACTOR* actor = PLEX_getExpandArrayEntryInt(ze, actorPtr, errorline, errorfile);

		PLEX_destroySpriteInt(&actor->sprite, errorline, errorfile);
	}

	PLEX_destroyExpandArrayInt(actors, errorline, errorfile);
}

static bool p_setMessageBase(const char* const message, char** message2, const size_t errorline, const char* const errorfile)
{
	size_t mlen = 0;

	// does not expect message2 to be NULL, so does not errorcheck for it.
	char* message2Ptr = *message2;

	if(message2Ptr != NULL) PLEX_deallocInt((void**)message2, errorline, errorfile);

	if(message == NULL)
	{
		*message2 = NULL;
		return false;
	}

	mlen = strlen(message);

	*message2 = PLEX_alloc(mlen + 1);
	message2Ptr = *message2;

	memcpy(message2Ptr, message, mlen);

	message2Ptr[mlen] = '\0';

	return true;
}

static void p_setMessageSlide(const char* const message, P_SPRITETHEATER_SLIDE* slide, const size_t errorline, const char* const errorfile)
{
	if(!p_setMessageBase(message, &slide->message, errorline, errorfile)) slide->message = NULL;
}

static void p_setMessage(const char* const message, const size_t errorline, const char* const errorfile)
{
	if(!p_setMessageBase(message, &p_message, errorline, errorfile)) p_message = NULL;
}

static void p_destroySlides(PLEX_EXPANDARRAY** slides, const size_t errorline, const char* const errorfile)
{
	// this assumes this is being passed an expand array of slides, so it will not check otherwise. Same with not expecting slides to be NULL.

	PLEX_EXPANDARRAY* slidesPtr = *slides;

	size_t count = PLEX_expandArrayCountInt(slidesPtr, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		P_SPRITETHEATER_SLIDE* slide = PLEX_getExpandArrayEntryInt(ze, slidesPtr, errorline, errorfile);

		if(slide->message != NULL) PLEX_deallocInt((void**)&slide->message, errorline, errorfile);
	}

	PLEX_destroyExpandArrayInt(slides, errorline, errorfile);
}

static void p_addActionChangeToScene(const int64_t actor, const size_t slide, const size_t backdrop, const P_SPRITETHEATER_ACTIONCHANGEEVENT event, const double amount, const double amount2, const char* const stageName, const PLEX_SPRITE* const sprite, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE* change = NULL;

	if(!PLEX_incrementExpandArrayInt(scene->actionChanges, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTIONCHANGETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	change = PLEX_getExpandArrayLastInt(scene->actionChanges, errorline, errorfile);

	if(change == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTIONCHANGETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	change->actor = actor;
	change->slide = slide;
	change->backdrop = backdrop;
	change->event = event;
	change->amount = amount;
	change->amount2 = amount2;

	if(stageName != NULL) change->stageName = PLEX_createString100Int(stageName, errorline, errorfile);
	else change->stageName = PLEX_blankString100();

	if(sprite != NULL) change->sprite = PLEX_copySpriteInt(sprite, errorline, errorfile);

	change->used = false;
}

static void p_changeMusicInScene(const size_t slide, const size_t id, const P_SPRITETHEATER_MUSICCHANGEEVENT event, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_MUSICCHANGE* change = NULL;

	if(!PLEX_incrementExpandArrayInt(scene->musicChanges, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDMUSICCHANGETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	change = PLEX_getExpandArrayLastInt(scene->musicChanges, errorline, errorfile);

	if(change == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDMUSICCHANGETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	change->slide = slide;
	change->id = id;
	change->event = event;

	change->used = false;
}

// check all internal expand arrays, generates them if they are not already generated

static bool p_checkExpandArrays(const size_t errorline, const char* const errorfile)
{
	if(p_slides == NULL)
	{
		p_slides = PLEX_genExpandArrayInt(PLEX_getMemProfileSpriteTheaterSlide(), sizeof(P_SPRITETHEATER_SLIDE), errorline, errorfile);

		if(p_slides == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKEXPANDARRAYS, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
			return false;
		}
	}

	if(p_actors == NULL)
	{
		p_actors = PLEX_genExpandArrayInt(PLEX_getMemProfileActor(), sizeof(P_SPRITETHEATER_ACTOR), errorline, errorfile);

		if(p_actors == NULL)
		{
			PLEX_destroyExpandArrayInt(&p_slides, errorline, errorfile);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKEXPANDARRAYS, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
			return false;
		}
	}

	if(p_changes == NULL)
	{
		p_changes = PLEX_genExpandArrayInt(PLEX_getMemProfileActionChange(), sizeof(P_SPRITETHEATER_ACTIONCHANGE), errorline, errorfile);

		if(p_changes == NULL)
		{
			PLEX_destroyExpandArrayInt(&p_slides, errorline, errorfile);
			p_destroyActorStack(&p_actors, errorline, errorfile);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKEXPANDARRAYS, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
			return false;
		}
	}

	if(p_musicChanges == NULL)
	{
		p_musicChanges = PLEX_genExpandArrayInt(PLEX_getMemProfileMusicChange(), sizeof(P_SPRITETHEATER_MUSICCHANGE), errorline, errorfile);

		if(p_musicChanges == NULL)
		{
			PLEX_destroyExpandArrayInt(&p_slides, errorline, errorfile);
			p_destroyActorStack(&p_actors, errorline, errorfile);
			PLEX_destroyExpandArrayInt(&p_changes, errorline, errorfile);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKEXPANDARRAYS, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
			return false;
		}
	}

	return true;
}

// sets a change for actors

static void p_setChange(const P_SPRITETHEATER_ACTIONCHANGE change, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE* toChange = NULL;

	if(!p_checkExpandArrays(errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_EXPAND, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSETACTIONCHANGE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(p_changes, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONSETACTIONCHANGE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	toChange = PLEX_getExpandArrayLastInt(p_changes, errorline, errorfile);

	if(toChange == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONSETACTIONCHANGE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	*toChange = change;
}

// set a change for music

static void p_setChangeMusic(const P_SPRITETHEATER_MUSICCHANGE change, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_MUSICCHANGE* toChange = NULL;

	if(!p_checkExpandArrays(errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_EXPAND, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSETMUSICCHANGE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(p_musicChanges, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONSETMUSICCHANGE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	toChange = PLEX_getExpandArrayLastInt(p_musicChanges, errorline, errorfile);

	if(toChange == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONSETMUSICCHANGE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	*toChange = change;
}

static void p_copyActorSprite(P_SPRITETHEATER_ACTOR* actor, PLEX_SPRITE* sprite, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL) actor->sprite = sprite;
	else
	{
		actor->sprite = PLEX_copySpriteInt(sprite, errorline, errorfile);

		PLEX_startSpriteInt(time, actor->sprite, errorline, errorfile);
		if(actor->stopped) PLEX_stopSpriteInt(actor->sprite, errorline, errorfile);
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_SPRITETHEATER_SCENE* PLEX_genSceneInt(const char* const stageName, const size_t errorline, const char* const errorfile)
{
	PLEX_SPRITETHEATER_SCENE* ret = PLEX_allocInt(sizeof(PLEX_SPRITETHEATER_SCENE), errorline, errorfile);

	ret->stageName = PLEX_createString100Int(stageName, errorline, errorfile);

	ret->slides = PLEX_genExpandArrayInt(PLEX_getMemProfileSpriteTheaterSlide(), sizeof(P_SPRITETHEATER_SLIDE), errorline, errorfile);

	if(ret->slides == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONGENERATESCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);
		return NULL;
	}

	ret->actors = PLEX_genExpandArrayInt(PLEX_getMemProfileActor(), sizeof(P_SPRITETHEATER_ACTOR), errorline, errorfile);

	if(ret->actors == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONGENERATESCENE, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		PLEX_destroyExpandArrayInt(&ret->slides, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);
		return NULL;
	}

	ret->actionChanges = PLEX_genExpandArrayInt(PLEX_getMemProfileActionChange(), sizeof(P_SPRITETHEATER_ACTIONCHANGE), errorline, errorfile);

	if(ret->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONGENERATESCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		PLEX_destroyExpandArrayInt(&ret->slides, errorline, errorfile);
		p_destroyActorStack(&ret->actors, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);
		return NULL;
	}

	ret->musicChanges = PLEX_genExpandArrayInt(PLEX_getMemProfileMusicChange(), sizeof(P_SPRITETHEATER_MUSICCHANGE), errorline, errorfile);

	if(ret->musicChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONGENERATESCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		PLEX_destroyExpandArrayInt(&ret->actionChanges, errorline, errorfile);
		PLEX_destroyExpandArrayInt(&ret->slides, errorline, errorfile);
		p_destroyActorStack(&ret->actors, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);
		return NULL;
	}

	return ret;
}

void PLEX_addSlideToSceneInt(const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_SLIDE* slide = NULL;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(scene->slides, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = PLEX_getExpandArrayLastInt(scene->slides, errorline, errorfile);

	if(slide == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDETOSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide->r = r;
	slide->g = g;
	slide->b = b;

	p_setMessageSlide(message, slide, errorline, errorfile);

	slide->actor = actor;
	slide->waitTime = waitTime;
	slide->pauseForWait = false;
}

int64_t PLEX_addActorToSceneInt(PLEX_SPRITE* sprite, const size_t aniIndex, const PLEX_RECT space, const bool hidden, const bool stopped, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTOR* actor = NULL;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTORTOSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return -1;
	}

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTORTOSCENE, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return -1;
	}

	if(!PLEX_incrementExpandArrayInt(scene->actors, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTORTOSCENE, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return -1;
	}

	actor = PLEX_getExpandArrayLastInt(scene->actors, errorline, errorfile);

	if(actor == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDACTORTOSCENE, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return -1;
	}

	p_copyActorSprite(actor, sprite, 0, errorline, errorfile);

	actor->space = space;
	actor->hidden = hidden;
	actor->aniIndex = aniIndex;
	actor->stopped = stopped;

	return PLEX_expandArrayCountInt(scene->actors, errorline, errorfile) - 1;
}

void PLEX_hideActorInSceneInt(const size_t actor, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_HIDE, 0, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_unhideActorInSceneInt(const size_t actor, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t slide = 0;

	size_t count = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONUNHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONUNHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONUNHIDEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_UNHIDE, 0, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_hideAllActorsInSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t slide = 0;

	size_t count = 0;

	size_t actorCount = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEALLACTORSINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEALLACTORSINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONHIDEALLACTORSINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	actorCount = PLEX_expandArrayCountInt(scene->actors, errorline, errorfile);

	for(size_t ze = 0; ze < actorCount; ++ze) p_addActionChangeToScene(ze, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_HIDE, 0, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_startStopActorSpriteInSceneInt(const size_t actor, const bool start, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		// PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPSPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		// PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPSPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		// PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPSPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_STARTSTOPSPRITE, start, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_changeActorSpriteInSceneInt(const size_t actor, const PLEX_SPRITE* sprite, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGESPRITEINSCENE, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGESPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGESPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGESPRITEINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_CHANGESPRITE, 0, 0, NULL, sprite, scene, errorline, errorfile);
}

void PLEX_darkenSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONDARKENSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONDARKENSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONDARKENSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(0, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_DARKEN, 0, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_changeActorAnimationInSceneInt(const size_t actor, const size_t index, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEANIMATIONINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEANIMATIONINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEANIMATIONINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_CHANGEANIMATION, index, 0, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_moveActorInSceneInt(const size_t actor, const double x, const double y, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONMOVEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONMOVEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONMOVEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_MOVE, x, y, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_resizeActorInSceneInt(const size_t actor, const double w, const double h, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONRESIZEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONRESIZEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONRESIZEACTORINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(actor, slide, 0, P_SPRITETHEATER_ACTIONCHANGE_RESIZE, w, h, NULL, NULL, scene, errorline, errorfile);
}

void PLEX_changeBackdropInSceneInt(const size_t backdrop, const char* const name, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}


	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_addActionChangeToScene(0, slide, backdrop, P_SPRITETHEATER_ACTIONCHANGE_BACKGROUND, 0, 0, name, NULL, scene, errorline, errorfile);
}

void PLEX_playSoundEffectInSceneInt(const size_t id, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->musicChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEBACKDROPINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_changeMusicInScene(slide, id, P_SPRITETHEATER_SOUNDEFFECT, scene, errorline, errorfile);
}

void PLEX_changeMusicInSceneInt(const size_t id, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->musicChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		p_currentSong = id;

		//PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCHANGEMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_changeMusicInScene(slide, id, P_SPRITETHEATER_MUSICPLAY, scene, errorline, errorfile);
}

void PLEX_stopMusicInSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	size_t slide = 0;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->musicChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONSTOPMUSICINSCENE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = count - 1;

	p_changeMusicInScene(slide, 0, P_SPRITETHEATER_MUSICSTOP, scene, errorline, errorfile);
}

void PLEX_loadSpriteTheaterSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	size_t slideCount = 0;
	size_t actorCount = 0;
	size_t actionChangeCount = 0;
	size_t musicChangeCount = 0;

	if(p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, errorline, errorfile);
		return;
	}

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	if(scene->slides == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	if(scene->actors == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return;
	}

	if(scene->actionChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
		return;
	}

	if(scene->musicChanges == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
		return;
	}

	if(p_slides != NULL) p_destroySlides(&p_slides, errorline, errorfile);
	if(p_actors != NULL) p_destroyActorStack(&p_actors, errorline, errorfile);
	if(p_changes != NULL) PLEX_destroyExpandArrayInt(&p_changes, errorline, errorfile);
	if(p_musicChanges != NULL) PLEX_destroyExpandArrayInt(&p_musicChanges, errorline, errorfile);

	p_stageName = scene->stageName;

	p_slides = PLEX_genExpandArrayInt(PLEX_getMemProfileSpriteTheaterSlide(), sizeof(P_SPRITETHEATER_SLIDE), errorline, errorfile);
	p_actors = PLEX_genExpandArrayInt(PLEX_getMemProfileActor(), sizeof(P_SPRITETHEATER_ACTOR), errorline, errorfile);
	p_changes = PLEX_genExpandArrayInt(PLEX_getMemProfileActionChange(), sizeof(P_SPRITETHEATER_ACTIONCHANGE), errorline, errorfile);
	p_musicChanges = PLEX_genExpandArrayInt(PLEX_getMemProfileMusicChange(), sizeof(P_SPRITETHEATER_MUSICCHANGE), errorline, errorfile);

	slideCount = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);
	actorCount = PLEX_expandArrayCountInt(scene->actors, errorline, errorfile);
	actionChangeCount = PLEX_expandArrayCountInt(scene->actionChanges, errorline, errorfile);
	musicChangeCount = PLEX_expandArrayCountInt(scene->musicChanges, errorline, errorfile);;

	for(size_t ze = 0; ze < slideCount; ++ze)
	{
		P_SPRITETHEATER_SLIDE* from = PLEX_getExpandArrayEntryInt(ze, scene->slides, errorline, errorfile);
		P_SPRITETHEATER_SLIDE* to = NULL;

		if(from == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
			return;
		}

		if(!PLEX_incrementExpandArrayInt(p_slides, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
			return;
		}

		to = PLEX_getExpandArrayLastInt(p_slides, errorline, errorfile);

		if(to == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_SLIDES2, errorline, errorfile);
			return;
		}

		memcpy(to, from, sizeof(P_SPRITETHEATER_SLIDE));

		to->message = NULL; // < crucial, do not remove

		p_setMessageSlide(from->message, to, errorline, errorfile);

		if(!p_slideIndex)
		{
			p_messageR = to->r;
			p_messageG = to->g;
			p_messageB = to->b;
			p_actorIndex = to->actor;

			p_setMessage(to->message, errorline, errorfile);

			++p_slideIndex;
		}
	}

	for(size_t ze = 0; ze < actorCount; ++ze)
	{
		P_SPRITETHEATER_ACTOR* from = PLEX_getExpandArrayEntryInt(ze, scene->actors, errorline, errorfile);
		P_SPRITETHEATER_ACTOR* to = NULL;

		if(from == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
			return;
		}

		if(!PLEX_incrementExpandArrayInt(p_actors, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
			return;
		}

		to = PLEX_getExpandArrayLastInt(p_actors, errorline, errorfile);

		if(to == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_ACTORS2, errorline, errorfile);
			return;
		}

		p_copyActorSprite(to, from->sprite, time, errorline, errorfile);

		to->space = from->space;
		to->hidden = from->hidden;
		to->stopped = from->stopped;
		to->aniIndex = from->aniIndex;
	}

	for(size_t ze = 0; ze < actionChangeCount; ++ze)
	{
		P_SPRITETHEATER_ACTIONCHANGE* from = PLEX_getExpandArrayEntryInt(ze, scene->actionChanges, errorline, errorfile);
		P_SPRITETHEATER_ACTIONCHANGE* to = NULL;

		if(from == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
			return;
		}

		if(!PLEX_incrementExpandArrayInt(p_changes, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_CHANGES, errorline, errorfile);
			return;
		}

		to = PLEX_getExpandArrayLastInt(p_changes, errorline, errorfile);

		if(to == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_CHANGES2, errorline, errorfile);
			return;
		}

		memcpy(to, from, sizeof(P_SPRITETHEATER_ACTIONCHANGE));
	}

	for(size_t ze = 0; ze < musicChangeCount; ++ze)
	{
		P_SPRITETHEATER_MUSICCHANGE* from = PLEX_getExpandArrayEntryInt(ze, scene->musicChanges, errorline, errorfile);
		P_SPRITETHEATER_MUSICCHANGE* to = NULL;

		if(from == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
			return;
		}

		if(!PLEX_incrementExpandArrayInt(p_musicChanges, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES, errorline, errorfile);
			return;
		}

		to = PLEX_getExpandArrayLastInt(p_musicChanges, errorline, errorfile);

		if(to == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONLOADSCENEINSPRITETHEATER, PLEX_ERRORMESS_SPRITETHEATER_MUSICCHANGES2, errorline, errorfile);
			return;
		}

		memcpy(to, from, sizeof(P_SPRITETHEATER_MUSICCHANGE));
	}
}

void PLEX_destroySceneInt(PLEX_SPRITETHEATER_SCENE** scene, const size_t errorline, const char* const errorfile)
{
	PLEX_SPRITETHEATER_SCENE* scenePtr = NULL;

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONDESTROYSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	scenePtr = *scene;

	if(scenePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONDESTROYSCENE, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return;
	}

	PLEX_destroyExpandArrayInt(&scenePtr->musicChanges, errorline, errorfile);
	PLEX_destroyExpandArrayInt(&scenePtr->actionChanges, errorline, errorfile);

	if(scenePtr->slides != NULL) p_destroySlides(&scenePtr->slides, errorline, errorfile);

	p_destroyActorStack(&scenePtr->actors, errorline, errorfile);

	PLEX_deallocInt((void**)scene, errorline, errorfile);
}

bool PLEX_checkSceneStringInt(const char* const string, const PLEX_SPRITETHEATER_SCENE* const scene, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;
	size_t count500 = 0;
	size_t slen = 0;

	PLEX_FAKESTRING_100 a100;

	if(string == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKSCENESTRING, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return false;
	}

	if(scene == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKSCENESTRING, PLEX_ERRORMESS_SPRITETHEATER_SCENE, errorline, errorfile);
		return false;
	}

	a100 = PLEX_createString100Int(string, errorline, errorfile);

	if(PLEX_insideString100Int(scene->stageName, a100, true, errorline, errorfile)) return true;

	count = PLEX_expandArrayCountInt(scene->slides, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		P_SPRITETHEATER_SLIDE* slide = PLEX_getExpandArrayEntryInt(ze, scene->slides, errorline, errorfile);

		if(slide == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCHECKSCENESTRING, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
			return false;
		}

		if(slide->message == NULL) continue; // < NO ERROR. SOME SLIDES JUST DON'T HAVE MESSAGES

		slen = strlen(slide->message);

		count500 = (slen/500) + 1;

		for(size_t uh = 0; uh < count500; ++uh)
		{
			const size_t adjust = uh * 500;

			const PLEX_FAKESTRING_500 a500 = PLEX_createString500Int(string, errorline, errorfile);
			const PLEX_FAKESTRING_500 comp = PLEX_createString500Int(slide->message + adjust, errorline, errorfile);

			if(PLEX_insideString500Int(comp, a500, true, errorline, errorfile)) return true;
		}
	}

	return false;
}

int64_t PLEX_createActorInt(PLEX_SPRITE* sprite, const size_t aniIndex, const PLEX_RECT space, const bool hidden, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTOR* actor = NULL;

	// DO NOT CHECK P_RUNNNING HERE //

	if(!p_checkExpandArrays(errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_EXPAND, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONCREATEACTOR, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return -1;
	}

	if(!PLEX_incrementExpandArrayInt(p_actors, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCREATEACTOR, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return -1;
	}

	actor = PLEX_getExpandArrayLastInt(p_actors, errorline, errorfile);

	if(actor == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONCREATEACTOR, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return -1;
	}

	if(sprite != NULL)
	{
		actor->sprite = PLEX_copySpriteInt(sprite, errorline, errorfile);
	}

	actor->space = space;
	actor->hidden = hidden;
	actor->aniIndex = aniIndex;

	return PLEX_expandArrayCountInt(p_actors, errorline, errorfile) - 1;
}

void PLEX_addSpriteTheaterSlideInt(const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait, const size_t errorline, const char* const errorfile)
{
	// do not null check 'message'

	P_SPRITETHEATER_SLIDE* slide = NULL;

	// DO NOT CHECK P_RUNNNING HERE //

	if(!p_checkExpandArrays(errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_EXPAND, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(p_slides, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONADDSLIDE, PLEX_ERRORMESS_SPRITETHEATER_SLIDES, errorline, errorfile);
		return;
	}

	slide = PLEX_getExpandArrayLastInt(p_slides, errorline, errorfile);

	slide->r = r;
	slide->g = g;
	slide->b = b;

	p_setMessageSlide(message, slide, errorline, errorfile);

	slide->actor = actor;
	slide->waitTime = waitTime;
	slide->pauseForWait = pauseForWait;

	if(!p_slideIndex)
	{
		p_messageR = r;
		p_messageB = b;
		p_messageG = g;

		p_setMessage(message, errorline, errorfile);

		p_actorIndex = actor;

		++p_slideIndex;
	}
}

void PLEX_nextSlideInt(const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_SLIDE* slide = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONNEXTSLIDE, errorline, errorfile);
		return;
	}

	if(p_slideIndex < PLEX_expandArrayCount(p_slides))
	{
		slide = PLEX_getExpandArrayEntryInt(p_slideIndex, p_slides, errorline, errorfile);

		p_messageR = slide->r;
		p_messageG = slide->g;
		p_messageB = slide->b;

		p_setMessage(slide->message, errorline, errorfile);

		p_actorIndex = slide->actor;
	}

	++p_slideIndex;
}

void PLEX_hideActorInt(const size_t actor, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_HIDE;
	change.actor = actor;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_unhideActorInt(const size_t actor, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_UNHIDE;
	change.actor = actor;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_changeActorInt(const size_t actor, const size_t index, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_CHANGEANIMATION;
	change.actor = actor;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.amount = index;
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_moveActorInt(const size_t actor, const double x, const double y, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_MOVE;
	change.actor = actor;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.amount = x;
	change.amount2 = y;
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_actorResizeActionChangeInt(const size_t actor, const double w, const double h, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_RESIZE;
	change.actor = actor;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.amount = w;
	change.amount2 = h;
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_changeSpriteTheaterBackgroundInt(const size_t backdrop, const char* const name, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTIONCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_ACTIONCHANGE_BACKGROUND;
	change.backdrop = backdrop;

	if(name != NULL) change.stageName = PLEX_createString100Int(name, errorline, errorfile);
	else change.stageName = PLEX_blankString100Int(errorline, errorfile);

	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChange(change, errorline, errorfile);
}

void PLEX_changeSpriteTheaterMusicInt(const size_t ID, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_MUSICCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_MUSICPLAY;
	change.id = ID;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChangeMusic(change, errorline, errorfile);
}

void PLEX_stopSpriteTheaterMusicInt(const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_MUSICCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_MUSICSTOP;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChangeMusic(change, errorline, errorfile);
}

void PLEX_playSpriteTheaterSoundEffectInt(const size_t ID, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_MUSICCHANGE change;

	// DO NOT CHECK P_RUNNNING HERE //

	change.event = P_SPRITETHEATER_SOUNDEFFECT;
	change.id = ID;
	change.slide = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);
	change.used = false;

	p_setChangeMusic(change, errorline, errorfile);
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startSpriteTheaterInt(const char* const stageName, const size_t backdrop, const uint32_t labelPlateX, const uint32_t labelPlateY, const uint32_t labelPlateW, const uint32_t labelPlateH, const uint8_t labelR, const uint8_t labelG, const uint8_t labelB, const size_t font, const size_t labelPlate, const size_t bubble, const size_t arrow, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	p_theaterStart = time;

	if(backdrop) p_backdrop = backdrop;
	// do not change backdrop if p_backdrop is 0

	if(stageName != NULL) p_stageName = PLEX_createString100(stageName);
	// do not change the stage name if it's NULL

	p_labelPlateX = labelPlateX;
	p_labelPlateY = labelPlateY;
	p_labelPlateW = labelPlateW;
	p_labelPlateH = labelPlateH;

	p_labelR = labelR;
	p_labelG = labelG;
	p_labelB = labelB;

	p_font = font;

	p_labelPlate = labelPlate;

	p_bubble = bubble;
	p_arrow = arrow;

	if(bubble) PLEX_textureWHInt(bubble, &p_bubbleW, &p_bubbleH, errorline, errorfile);
	if(arrow) PLEX_textureWHInt(arrow, &p_arrowW, &p_arrowH, errorline, errorfile);

	p_running = true;
	p_dispPause = false;

	if(!PLEX_pauseDisabled())
	{
		PLEX_disablePause();
		p_dispPause = true;
	}

	return true;
}

bool PLEX_updateSpriteTheaterInt(const uint64_t time, const size_t errorline, const char* const errorfile)
{
	bool slideWait = false;

	size_t slideCount = 0;

	uint32_t bh = 0;

	P_SPRITETHEATER_SLIDE* slide = NULL;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	bh = PLEX_UNIT(4);

	PLEX_disablePause();

	slideCount = PLEX_expandArrayCountInt(p_slides, errorline, errorfile);

	if(p_slideIndex < slideCount && p_slideIndex > 0)
	{
		slide = PLEX_getExpandArrayEntryInt(p_slideIndex - 1, p_slides, errorline, errorfile);

		if(!slide->startGlobalTime) slide->startGlobalTime = time;

		slideWait = time - slide->startGlobalTime < slide->waitTime;

		if(slideWait && slide->pauseForWait)
		{
			PLEX_signalUniversalThemeStop();
			p_waitStopMusic = true;
		}else{
			if(p_waitStopMusic)
			{
				if(p_currentSong) PLEX_setUniversalThemeID(p_currentSong);
				p_waitStopMusic = false;
			}
		}
	}

	if(p_slideIndex >= slideCount) slide = PLEX_getExpandArrayLastInt(p_slides, errorline, errorfile);

	if(p_backdrop) PLEX_drawPanoramaInt(PLEX_SPRITETHEATER_BACKDROPLAYER, p_backdrop, errorline, errorfile);

	if(p_darken) PLEX_fillRect(PLEX_SPRITETHEATER_LABELLAYER, 0, 0, PLEX_WW(false), PLEX_WH(false), 0, 0, 0, 200, false);

	if(p_stageName.len && p_font && p_labelPlate) PLEX_drawLabelInt(PLEX_SPRITETHEATER_LABELLAYER, PLEX_fts(p_stageName), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, p_labelR, p_labelG, p_labelB, 255, PLEX_UNIT(0.25), PLEX_UNIT(0.25), PLEX_UNIT(12), PLEX_UNIT(1.5), 0.05, 0.1, 0.9, 0.9, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, p_font, p_labelPlate, p_labelPlateX, p_labelPlateY, p_labelPlateW, p_labelPlateH, true, errorline, errorfile);

	if(!slideWait)
	{
		if(p_font && p_message != NULL)
		{
			const uint32_t ox = PLEX_UNIT(2);
			const uint32_t oy = PLEX_UNIT(2.75);

			const uint32_t fw = PLEX_UNIT(0.5);
			const uint32_t fh = PLEX_UNIT(1);

			const uint32_t ex = PLEX_WW(true) - ox;

			size_t index = 0;
			char next = p_message[index];

			uint32_t x = ox;
			uint32_t y = oy;

			char wbuffer[1024];
			size_t wit = 0;

			wbuffer[0] = '\0';

			while(next != '\0')
			{
				if(next == '\t' || next == ' ')
				{
					const uint32_t wordWidth = fw * wit;

					if(next == '\t') x += fw * 5;
					else x += fw;

					if(x + wordWidth >= ex)
					{
						x = ox;
						y += fh;
					}

					if(wit) PLEX_printFontStringTinted(PLEX_SPRITETHEATER_FONTLAYER, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, x, y, fw, fh, p_messageR, p_messageG, p_messageB, (char*)wbuffer, PLEX_LANGUAGE_ALPHASTRING, p_font, true);

					x += wordWidth;
					wit = 0;
					wbuffer[0] = '\0';
				}else{
					if(next == '\n' || next == '\r')
					{
						x = ox;
						y += fh;
					}else{
						wbuffer[wit] = next;
						wbuffer[wit + 1] = '\0';
						++wit;
					}
				}

				++index;
				next = p_message[index];
			}

			if(x + fw * wit >= ex)
			{
				x = ox;
				y += fh;
			}

			x += fw;

			if(wit) PLEX_printFontStringTinted(PLEX_SPRITETHEATER_FONTLAYER, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, x, y, fw, fh, p_messageR, p_messageG, p_messageB, (char*)wbuffer, PLEX_LANGUAGE_ALPHASTRING, p_font, true);

			if(y >= PLEX_UNIT(0.25) + bh) bh = PLEX_UNIT(0.25) + y;
		}

		if(!slideWait && p_bubble && p_message != NULL && p_message[0] != '\0') PLEX_printTexture(PLEX_SPRITETHEATER_BUBBLELAYER, p_bubble, 0, 0, p_bubbleW, p_bubbleH, PLEX_UNIT(0.25), PLEX_UNIT(2.5), PLEX_WW(true) - PLEX_UNIT(0.5), bh, true);

		if(p_arrow && p_actorIndex >= 0)
		{
			const P_SPRITETHEATER_ACTOR* actor = PLEX_getExpandArrayEntryInt(p_actorIndex, p_actors, errorline, errorfile);

			double ax = 0;
			double ay = 0;
			double aw = 0;

			double w = aw * 3;

			if(actor != NULL)
			{
				ax = PLEX_UNIT(actor->space.origin.x);
				ay = PLEX_UNIT(actor->space.origin.y);
				aw = PLEX_UNIT(actor->space.dimens.w);

				w = aw * 3;

				PLEX_printTexture(PLEX_SPRITETHEATER_ARROWLAYER, p_arrow, 0, 0, p_arrowW, p_arrowH, (ax + aw/2) - w/2, bh, w, (ay - bh) * 0.75, true);
			}else{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONUPDATE, PLEX_ERRORMESS_SPRITETHEATER_ACTOR, errorline, errorfile);
			}
		}

		for(size_t ze = 0; ze < PLEX_expandArrayCount(p_changes); ++ze)
		{
			P_SPRITETHEATER_ACTIONCHANGE* change = PLEX_getExpandArrayEntryInt(ze, p_changes, errorline, errorfile);

			if(change->slide < p_slideIndex)
			{
				if(!change->used)
				{
					P_SPRITETHEATER_ACTOR* actor = NULL;

					if(change->actor < PLEX_expandArrayCountInt(p_actors, errorline, errorfile) && change->actor >= 0) actor = PLEX_getExpandArrayEntryInt(change->actor, p_actors, errorline, errorfile);

					switch(change->event)
					{
						case P_SPRITETHEATER_ACTIONCHANGE_HIDE: if(actor != NULL) actor->hidden = true; break;
						case P_SPRITETHEATER_ACTIONCHANGE_UNHIDE: if(actor != NULL) actor->hidden = false; break;

						case P_SPRITETHEATER_ACTIONCHANGE_CHANGEANIMATION: if(actor != NULL) actor->aniIndex = change->amount; break;

						case P_SPRITETHEATER_ACTIONCHANGE_MOVE: if(actor != NULL) actor->space.origin = PLEX_convPoint(change->amount, change->amount2); break;

						case P_SPRITETHEATER_ACTIONCHANGE_RESIZE: if(actor != NULL) actor->space.dimens = PLEX_convDimens(change->amount, change->amount2); break;

						case P_SPRITETHEATER_ACTIONCHANGE_BACKGROUND:
							if(change->backdrop) p_backdrop = change->backdrop;
							if(change->stageName.len) p_stageName = change->stageName;
						break;

						case P_SPRITETHEATER_ACTIONCHANGE_STARTSTOPSPRITE:
							if(actor->sprite != NULL)
							{
								if(change->amount) PLEX_startSpriteInt(time, actor->sprite, errorline, errorfile);
								else PLEX_stopSpriteInt(actor->sprite, errorline, errorfile);
							}

							actor->stopped = !change->amount;
						break;

						case P_SPRITETHEATER_ACTIONCHANGE_CHANGESPRITE:
							if(change->sprite != NULL)
							{
								if(actor != NULL)
								{
									if(actor->sprite != NULL) PLEX_destroySpriteInt(&actor->sprite, errorline, errorfile);
									p_copyActorSprite(actor, change->sprite, time, errorline, errorfile);
								}else{
									PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONUPDATE, PLEX_ERRORMESS_SPRITETHEATER_SPRITECHANGEACTOR, errorline, errorfile);
								}
							}else{
								PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONUPDATE, PLEX_ERRORMESS_SPRITETHEATER_SPRITECHANGESPRITE, errorline, errorfile);
							}
						break;

						case P_SPRITETHEATER_ACTIONCHANGE_DARKEN:
							p_darken = true;
							slide->darken = true;
						break;
					};

					change->used = true;
				}
			}
		}

		if(slide != NULL && !slide->darken) p_darken = false;
		if(slide == NULL) p_darken = false;

		for(size_t ze = 0; ze < PLEX_expandArrayCount(p_musicChanges); ++ze)
		{
			P_SPRITETHEATER_MUSICCHANGE* change = PLEX_getExpandArrayEntryInt(ze, p_musicChanges, errorline, errorfile);

			if(change->slide < p_slideIndex && !change->used)
			{
				switch(change->event)
				{
					case P_SPRITETHEATER_MUSICPLAY: p_currentSong = change->id; break;
					case P_SPRITETHEATER_MUSICSTOP: PLEX_signalUniversalThemeStop(); p_currentSong = 0; break;
					case P_SPRITETHEATER_SOUNDEFFECT: PLEX_setUniversalSoundEffect(change->id); break;
				};

				change->used = true;
			}
		}
	}

	for(size_t ze = 0; ze < PLEX_expandArrayCount(p_actors); ++ze)
	{
		P_SPRITETHEATER_ACTOR* actor = PLEX_getExpandArrayEntryInt(ze, p_actors, errorline, errorfile);

		double x = PLEX_UNIT(actor->space.origin.x);
		double y = PLEX_UNIT(actor->space.origin.y);
		double w = PLEX_UNIT(actor->space.dimens.w);
		double h = PLEX_UNIT(actor->space.dimens.h);

		if(actor->hidden || actor->sprite == NULL) continue;

		if(actor->stopped && !PLEX_isSpriteStopped(actor->sprite)) PLEX_stopSpriteInt(actor->sprite, errorline, errorfile);
		if(!actor->stopped && PLEX_isSpriteStopped(actor->sprite)) PLEX_startSpriteInt(time, actor->sprite, errorline, errorfile);

		PLEX_drawSpriteInt(PLEX_SPRITETHEATER_ACTORLAYER, actor->aniIndex, x, y, w, h, actor->sprite, true, time, errorline, errorfile);
	}

	if(p_currentSong != PLEX_getUniversalThemeCueID()) PLEX_setUniversalThemeID(p_currentSong);

	if(!slideWait && (PLEX_leftClick() || PLEX_KEY_press('\n') || PLEX_CONTROLLER_press(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))) PLEX_nextSlideInt(errorline, errorfile);

	return true;
}

void PLEX_endSpriteTheaterInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	if(p_dispPause) PLEX_enablePause();

	PLEX_signalUniversalThemeStop();

	if(p_slides != NULL) p_destroySlides(&p_slides, errorline, errorfile);
	if(p_actors != NULL) p_destroyActorStack(&p_actors, errorline, errorfile);
	if(p_changes != NULL) PLEX_destroyExpandArrayInt(&p_changes, errorline, errorfile);
	if(p_musicChanges != NULL) PLEX_destroyExpandArrayInt(&p_musicChanges, errorline, errorfile);

	PLEX_deallocInt((void**)&p_message, errorline, errorfile);
	p_message = NULL;

	p_stageName = PLEX_blankString100();
	p_backdrop = 0;

	p_slideIndex = 0; // < keep in end
	p_actorIndex = -1; // < keep in end

	p_dispPause = false;
	p_running = false;
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_SPRITE* PLEX_theaterActorSpriteInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	P_SPRITETHEATER_ACTOR* actor = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONGETACTORSPRITE, errorline, errorfile);
		return NULL;
	}

	if(p_actors == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONGETACTORSPRITE, PLEX_ERRORMESS_SPRITETHEATER_ACTORS, errorline, errorfile);
		return NULL;
	}

	if(index >= PLEX_expandArrayCountInt(p_actors, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITETHEATER_ONGETACTORSPRITE, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return NULL;
	}

	actor = PLEX_getExpandArrayEntryInt(index, p_actors, errorline, errorfile);

	if(actor == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITETHEATER, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITETHEATER_ONGETACTORSPRITE, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return NULL;
	}

	return actor->sprite;
}

bool PLEX_inSpriteTheater(){ return p_running; }

bool PLEX_isSpriteTheaterOver()
{
	if(!p_running) return true; // < not running == over, no need for error checks.

	return p_slideIndex > PLEX_expandArrayCount(p_slides);
}
