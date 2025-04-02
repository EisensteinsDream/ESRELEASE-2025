#ifndef PLEX_SPRITETHEATER_H
#define PLEX_SPRITETHEATER_H

#include "windowing/sprite.h"

#include "utility/globaltime.h"

#include "sound/sound.h"

// This unit contains 'sprite theater' which is like a simple setup for a diorama-like presentation for simple sprite-based cutscenes that you can run through frame-by-frame like slideshows.

// NOTE: Even though sprite theater has a beginning, middle, and end; this is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const char* const stageName) - returns PLEX_SPRITETHEATER_SCENE*

#define PLEX_genScene(stagename) PLEX_genSceneInt(stagename, __LINE__, __FILE__)

// ARGUMENTS: (const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_addSlideToScene(r, g, b, message, actor, waitTime, pauseForWait, scene) PLEX_addSlideToSceneInt(r, g, b, message, actor, waitTime, pauseForWait, scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite, const size_t aniIndex, const PLEX_RECT space, const bool hidden, PLEX_SPRITETHEATER_SCENE* scene) - returns int64_t

#define PLEX_addActorToScene(sprite, aniIndex, space, hidden, stopped, scene) PLEX_addActorToSceneInt(sprite, aniIndex, space, hidden, stopped, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_hideActorInScene(actor, scene) PLEX_hideActorInSceneInt(actor, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_unhideActorInScene(actor, scene) PLEX_unhideActorInSceneInt(actor, scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_hideAllActorsInScene(scene) PLEX_hideAllActorsInSceneInt(scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const bool start, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_startStopActorSpriteInScene(actor, start, scene) PLEX_startStopActorSpriteInSceneInt(actor, start, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const PLEX_SPRITE* sprite, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_changeActorSpriteInScene(actor, sprite, scene) PLEX_changeActorSpriteInSceneInt(actor, sprite, scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_darkenScene(scene) PLEX_darkenSceneInt(scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const size_t index, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_changeActorAnimationInScene(actor, index, scene) PLEX_changeActorAnimationInSceneInt(actor, index, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const double x, const double y, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_moveActorInScene(actor, x, y, scene) PLEX_moveActorInSceneInt(actor, x, y, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const double w, const double h, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_resizeActorInScene(actor, w, h, scene) PLEX_resizeActorInSceneInt(actor, w, h, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t backdrop, const char* const name, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_changeBackdropInScene(backdrop, name, scene) PLEX_changeBackdropInSceneInt(backdrop, name, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t id, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_playSoundEffectInScene(id, scene) PLEX_playSoundEffectInSceneInt(id, scene, __LINE__, __FILE__)

// ARGUMENTS: (const size_t id, PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_changeMusicInScene(id, scene) PLEX_changeMusicInSceneInt(id, scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_stopMusicInScene(scene) PLEX_stopMusicInSceneInt(scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITETHEATER_SCENE* scene)

#define PLEX_loadSpriteTheaterScene(scene, time) PLEX_loadSpriteTheaterSceneInt(scene, time, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITETHEATER_SCENE** scene)

#define PLEX_destroyScene(scene) PLEX_destroySceneInt(scene, __LINE__, __FILE__)

// ARGUMENTS: (const char* const string, const PLEX_SPRITETHEATER_SCENE* const scene) - return bool

#define PLEX_checkSceneString(string, scene) PLEX_checkSceneStringInt(string, scene, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite, const size_t aniIndex,  const PLEX_RECT space, const bool hidden) - returns int64_t

#define PLEX_createActor(sprite, aniIndex, space, hidden) PLEX_createActorInt(sprite, aniIndex, space, hidden, __LINE__, __FILE__)

// ARGUMENTS: (const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait)

#define PLEX_addSpriteTheaterSlide(r, g, b, message, actor, waitTime, pauseForWait) PLEX_addSpriteTheaterSlideInt(r, g, b, message, actor, waitTime, pauseForWait, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_nextSlide() PLEX_nextSlideInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t actor)

#define PLEX_hideActor(actor) PLEX_hideActorInt(actor, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor)

#define PLEX_unhideActor(actor) PLEX_unhideActorInt(actor, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const size_t index)

#define PLEX_changeActor(actor, index) PLEX_changeActorInt(actor, index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const double x, const double y)

#define PLEX_moveActor(actor, x, y) PLEX_moveActorInt(actor, x, y, __LINE__, __FILE__)

// ARGUMENTS: (const size_t actor, const double w, const double h)

#define PLEX_actorResizeActionChange(actor, w, h) PLEX_actorResizeActionChangeInt(actor, w, h, __LINE__, __FILE__)

// ARGUMENTS: (const size_t backdrop, const char* const name)

#define PLEX_changeSpriteTheaterBackground(backdrop, name) PLEX_changeSpriteTheaterBackgroundInt(backdrop, name, __LINE__, __FILE__)

// ARGUMENTS: (const size_t ID)

#define PLEX_changeSpriteTheaterMusic(ID) PLEX_changeSpriteTheaterMusicInt(ID, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_stopSpriteTheaterMusic() PLEX_stopSpriteTheaterMusicInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t ID)

#define PLEX_playSpriteTheaterSoundEffect(ID) PLEX_playSpriteTheaterSoundEffectInt(ID, __LINE__, __FILE__)

// ARGUMENTS: (const char* const stageName, const size_t backdrop, const uint32_t labelPlateX, const uint32_t labelPlateY, const uint32_t labelPlateW, const uint32_t labelPlateH, const uint8_t labelR, const uint8_t labelG, const uint8_t labelB, const size_t font, const size_t labelPlate, const size_t bubble, const size_t arrow, const uint64_t time)

#define PLEX_startSpriteTheater(stageName, backdrop, labelPlateX, labelPlateY, labelPlateW, labelPlateH, labelR, labelG, labelB,  font, labelPlate, bubble, arrow, time) PLEX_startSpriteTheaterInt(stageName, backdrop, labelPlateX, labelPlateY, labelPlateW, labelPlateH, labelR, labelG, labelB,  font, labelPlate, bubble, arrow, time, __LINE__, __FILE__);

// ARGUMENTS: (const uint64_t time) - returns bool

#define PLEX_updateSpriteTheater(time) PLEX_updateSpriteTheaterInt(time, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endSpriteTheater() PLEX_endSpriteTheaterInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_SPRITE*

#define PLEX_theaterActorSprite(index) PLEX_theaterActorSpriteInt(index, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	PLEX_FAKESTRING_100 stageName;

	PLEX_EXPANDARRAY* slides;
	PLEX_EXPANDARRAY* actors;
	PLEX_EXPANDARRAY* actionChanges;
	PLEX_EXPANDARRAY* musicChanges;
} PLEX_SPRITETHEATER_SCENE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// generates a new scene (a scene is a way to create a sprite theater 'scene' but not start it immediately)

	extern PLEX_SPRITETHEATER_SCENE* PLEX_genSceneInt(const char* const stageName, const size_t errorline, const char* const errorfile);

	// adds a slide to a generated scene

	extern void PLEX_addSlideToSceneInt(const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds an actor to a generated scene

	extern int64_t PLEX_addActorToSceneInt(PLEX_SPRITE* sprite, const size_t aniIndex, const PLEX_RECT space, const bool hidden, const bool stopped, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds hide actor action change to a generated scene

	extern void PLEX_hideActorInSceneInt(const size_t actor, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds unhide actor action change to a generated scene

	extern void PLEX_unhideActorInSceneInt(const size_t actor, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds hide actor action change to all actors in a generated scene

	extern void PLEX_hideAllActorsInSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// stop sprite actor action change to a generated scene

	extern void PLEX_startStopActorSpriteInSceneInt(const size_t actor, const bool start, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds sprite actor action change to a generated scene

	extern void PLEX_changeActorSpriteInSceneInt(const size_t actor, const PLEX_SPRITE* sprite, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds a darken actor action change to a generated scene

	extern void PLEX_darkenSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds animation actor action change to a generated scene

	extern void PLEX_changeActorAnimationInSceneInt(const size_t actor, const size_t index, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds move actor action change to a generated scene

	extern void PLEX_moveActorInSceneInt(const size_t actor, const double x, const double y, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds actor resize action change to a generated scene

	extern void PLEX_resizeActorInSceneInt(const size_t actor, const double w, const double h, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds background action change to a generated scene

	extern void PLEX_changeBackdropInSceneInt(const size_t backdrop, const char* const name, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds a sound effect music change to a generated scene

	extern void PLEX_playSoundEffectInSceneInt(const size_t id, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds a music change music change to a generated scene

	extern void PLEX_changeMusicInSceneInt(const size_t id, PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// adds a music stop music change to a generated event

	extern void PLEX_stopMusicInSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const size_t errorline, const char* const errorfile);

	// loads a scene into sprite theater

	extern void PLEX_loadSpriteTheaterSceneInt(PLEX_SPRITETHEATER_SCENE* scene, const uint64_t time, const size_t errorline, const char* const errorfile);

	// destroys a generated scene clearing it's contents from memory

	extern void PLEX_destroySceneInt(PLEX_SPRITETHEATER_SCENE** scene, const size_t errorline, const char* const errorfile);

	// checks if a string appears in scene's dialog

	extern bool PLEX_checkSceneStringInt(const char* const string, const PLEX_SPRITETHEATER_SCENE* const scene, const size_t errorline, const char* const errorfile);

	// creates an 'actor' for sprite theater based on sprite and space

	extern int64_t PLEX_createActorInt(PLEX_SPRITE* sprite, const size_t aniIndex, const PLEX_RECT space, const bool hidden, const size_t errorline, const char* const errorfile);

	// adds a slide to the current sprite theater

	extern void PLEX_addSpriteTheaterSlideInt(const uint8_t r, const uint8_t g, const uint8_t b, const char* const message, const int64_t actor, const uint64_t waitTime, const bool pauseForWait, const size_t errorline, const char* const errorfile);

	// sets sprite theater to the next slide. Typically you never have to do this manually.

	extern void PLEX_nextSlideInt(const size_t errorline, const char* const errorfile);

	// adds a hide actor action change directly in the sprite theater

	extern void PLEX_hideActorInt(const size_t actor, const size_t errorline, const char* const errorfile);

	// adds an unhide actor action change directly in the sprite theater

	extern void PLEX_unhideActorInt(const size_t actor, const size_t errorline, const char* const errorfile);

	// changes the animation of an actor directly to the sprite theater

	extern void PLEX_changeActorInt(const size_t actor, const size_t index, const size_t errorline, const char* const errorfile);

	// moves an actor directly in the sprite theater

	extern void PLEX_moveActorInt(const size_t actor, const double x, const double y, const size_t errorline, const char* const errorfile);

	// change the size of an actor directly in the sprite theater

	extern void PLEX_actorResizeActionChangeInt(const size_t actor, const double w, const double h, const size_t errorline, const char* const errorfile);

	// changes the background directly in the sprite theater

	extern void PLEX_changeSpriteTheaterBackgroundInt(const size_t backdrop, const char* const name, const size_t errorline, const char* const errorfile);

	// changes the universal signal in sound.h directly on the sprite theater slide. More information on sound signals in sound.h

	extern void PLEX_changeSpriteTheaterMusicInt(const size_t ID, const size_t errorline, const char* const errorfile);

	// stops the universal signal in sound.h directly on the sprite theater slide. More information on sound signals in sound.h

	extern void PLEX_stopSpriteTheaterMusicInt(const size_t errorline, const char* const errorfile);

	// changes the universal signal in sound.h for a sound effect directly on the sprite theater slide. More information on sound signals in sound.h

	extern void PLEX_playSpriteTheaterSoundEffectInt(const size_t ID, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the sprite theater and returns false on failure. Sprite theater is NOT part of a PLEX_start, update, end state machine so you call this when you want the sprite theater to start and PLEX does not terminate on failure. Can return a stageName as NULL not to change the stage name (useful if you loaded the stage with a scene)

	extern bool PLEX_startSpriteTheaterInt(const char* const stageName, const size_t backdrop, const uint32_t labelPlateX, const uint32_t labelPlateY, const uint32_t labelPlateW, const uint32_t labelPlateH, const uint8_t labelR, const uint8_t labelG, const uint8_t labelB, const size_t font, const size_t labelPlate, const size_t bubble, const size_t arrow, const uint64_t time, const size_t errorline, const char* const errorfile);

	// updates the sprite theater returning false on failure or end.

	extern bool PLEX_updateSpriteTheaterInt(const uint64_t time, const size_t errorline, const char* const errorfile);

	// ends the sprite theater freeing all resources

	extern void PLEX_endSpriteTheaterInt(const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the sprite of actor inside running sprite theater at 'index'

	extern PLEX_SPRITE* PLEX_theaterActorSpriteInt(const size_t index, const size_t errorline, const char* const errorfile);

	// returns whether or not it's in sprite theater (and true if over as well)

	extern bool PLEX_inSpriteTheater();

	// returns whether or not a sprite theater is over

	extern bool PLEX_isSpriteTheaterOver();
#ifdef __cplusplus
}
#endif

#endif
