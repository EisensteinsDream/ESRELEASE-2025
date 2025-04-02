#include "minigame/minigame2/minigame2.h"

static size_t p_clubIcon = 0;
static size_t p_clubCursor = 0;
static size_t p_clubCursorShoot = 0;
static size_t p_clubAnimation = 0;

static size_t p_revolverIcon = 0;
static size_t p_revolverCursor = 0;
static size_t p_revolverCursorShoot = 0;
static size_t p_revolverAnimation = 0;
static size_t p_revolverClipIcon = 0;

static size_t p_uziIcon = 0;
static size_t p_uziCursor = 0;
static size_t p_uziCursorShoot = 0;
static size_t p_uziAnimation = 0;
static size_t p_uziClipIcon = 0;

static size_t p_shotgunIcon = 0;
static size_t p_shotgunCursor = 0;
static size_t p_shotgunCursorShoot = 0;
static size_t p_shotgunAnimation = 0;
static size_t p_shotgunClipIcon = 0;

static size_t p_grenadeIcon = 0;
static size_t p_grenadeCursor = 0;
static size_t p_grenadeCursorShoot = 0;
static size_t p_grenadeAnimation = 0;
static size_t p_grenadeClipIcon = 0;

static size_t p_flamethrowerIcon = 0;
static size_t p_flamethrowerCursor = 0;
static size_t p_flamethrowerCursorShoot = 0;
static size_t p_flamethrowerAnimation = 0;
static size_t p_flamethrowerClipIcon = 0;

static size_t p_knifeIcon = 0;
static size_t p_knifeCursor = 0;
static size_t p_knifeCursorShoot = 0;
static size_t p_knifeAnimation = 0;

static size_t p_molotovIcon = 0;
static size_t p_molotovCursor = 0;
static size_t p_molotovCursorShoot = 0;
static size_t p_molotovAnimation = 0;
static size_t p_molotovClipIcon = 0;

static size_t p_dynamiteIcon = 0;
static size_t p_dynamiteCursor = 0;
static size_t p_dynamiteCursorShoot = 0;
static size_t p_dynamiteAnimation = 0;
static size_t p_dynamiteClipIcon = 0;

static size_t p_tomahawkIcon = 0;
static size_t p_tomahawkCursor = 0;
static size_t p_tomahawkCursorShoot = 0;
static size_t p_tomahawkAnimation = 0;
static size_t p_tomahawkClipIcon = 0;

static size_t p_bowAndArrowIcon = 0;
static size_t p_bowAndArrowCursor = 0;
static size_t p_bowAndArrowCursorShoot = 0;
static size_t p_bowAndArrowAnimation = 0;
static size_t p_bowAndArrowClipIcon = 0;

static size_t p_chainsawIcon = 0;
static size_t p_chainsawCursor = 0;
static size_t p_chainsawCursorShoot = 0;
static size_t p_chainsawAnimation = 0;
static size_t p_chainsawClipIcon = 0;

static size_t p_raygunIcon = 0;
static size_t p_raygunCursor = 0;
static size_t p_raygunCursorShoot = 0;
static size_t p_raygunAnimation = 0;
static size_t p_raygunClipIcon = 0;

static uint32_t p_points = 0;
static double p_cash = 0;
static double p_health = 1;

static int64_t p_shotTime = -1;
static uint64_t p_shotDuration = 0;

static MMS_MINIGAME2GUN p_guns[MMS2_GUNCOUNT];
static bool p_hasGun[MMS2_GUNCOUNT];

static MMS_MINIGAME2DODGEPHASE p_dodgePhase = MMS_MINIGAME2DODGEPHASE_STAND;
static uint64_t p_playerShotTime = 0;

static double p_leanX = 0;
static double p_leanY = 0;

static int64_t p_emptyChamberSE = 0;

// clears all sprites of all guns

static void p_clearGunSprites()
{
	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		MMS_MINIGAME2GUN* gun = p_guns + ze;

		if(gun->shotAnimation != NULL) PLEX_destroySprite(&gun->shotAnimation);
	}
}

// sets the aspects of a gun based on passed values (does not select the gun)

static void p_setGun(const size_t index, const char* const name, const size_t icon, const size_t cursor, const size_t shotCursor, const size_t clipIcon, const MM_COMMON_SOUNDEFFECT soundEffect, const MM_COMMON_SOUNDEFFECT outOfAmmoSoundEffect, const int64_t ammoMaximum, const int64_t ammoClipMaximum, const uint64_t shootTime, const uint64_t reloadDuration, const double innerDamage, const double outerDamage, const size_t cost, const PLEX_ANIMATION_PLATE shotPlate)
{
	MMS_MINIGAME2GUN* gun = NULL;

	if(index >= MMS2_GUNCOUNT) return;

	gun = p_guns + index;

	gun->name = PLEX_createString25(name);
	gun->icon = icon;
	gun->cursor = cursor;
	gun->shotCursor = shotCursor;
	gun->soundEffect = soundEffect;
	gun->outOfAmmoSoundEffect = outOfAmmoSoundEffect;
	gun->ammoAmount = ammoMaximum;
	gun->ammoMaximum = ammoMaximum;
	gun->ammoClip = ammoClipMaximum;
	gun->ammoClipMaximum = ammoClipMaximum;
	gun->clipIcon = clipIcon;
	gun->shootTime = shootTime;
	gun->reloadDuration = reloadDuration;
	gun->innerDamage = innerDamage;
	gun->outerDamage = outerDamage;
	gun->cost = cost;

	gun->reloadTime = -1;

	gun->shotAnimation = PLEX_genSprite(&shotPlate);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemPlayer(const uint64_t time)
{
	MMS2_createGuns(time);

	MMS2_initPointsCashHealth();

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		MMS_MINIGAME2GUN* gun = MMS2_gun(ze);

		gun->ammoAmount = gun->ammoMaximum;
		gun->ammoClip = gun->ammoClipMaximum;

		MMS2_takeGun(ze);
	}

	MMS2_addGun(0); // < player starts with club
	MMS2_addGun(1); // < player starts with revolver

	p_shotTime = -1;

	p_emptyChamberSE = -1;
}

void MMS2_initSystemPlayer()
{
	if(!p_clubIcon) p_clubIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CLUBICON, MMS2_FILEPATH_HEADERLESS_CLUBICON);
	if(!p_clubCursor) p_clubCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CLUBCURSOR, MMS2_FILEPATH_HEADERLESS_CLUBCURSOR);
	if(!p_clubCursorShoot) p_clubCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CLUBCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_CLUBCURSORSHOOT);
	if(!p_clubAnimation) p_clubAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CLUBANIMATION, MMS2_FILEPATH_HEADERLESS_CLUBANIMATION);

	if(!p_revolverIcon) p_revolverIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_REVOLVERICON, MMS2_FILEPATH_HEADERLESS_REVOLVERICON);
	if(!p_revolverCursor) p_revolverCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_REVOLVERCURSOR, MMS2_FILEPATH_HEADERLESS_REVOLVERCURSOR);
	if(!p_revolverCursorShoot) p_revolverCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_REVOLVERCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_REVOLVERCURSORSHOOT);
	if(!p_revolverAnimation) p_revolverAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_REVOLVERANIMATION, MMS2_FILEPATH_HEADERLESS_REVOLVERANIMATION);
	if(!p_revolverClipIcon) p_revolverClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_REVOLVERCLIPICON, MMS2_FILEPATH_HEADERLESS_REVOLVERCLIPICON);

	if(!p_uziIcon) p_uziIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_UZIICON, MMS2_FILEPATH_HEADERLESS_UZIICON);
	if(!p_uziCursor) p_uziCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_UZICURSOR, MMS2_FILEPATH_HEADERLESS_UZICURSOR);
	if(!p_uziCursorShoot) p_uziCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_UZICURSORSHOOT, MMS2_FILEPATH_HEADERLESS_UZICURSORSHOOT);
	if(!p_uziAnimation) p_uziAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_UZIANIMATION, MMS2_FILEPATH_HEADERLESS_UZIANIMATION);
	if(!p_uziClipIcon) p_uziClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_UZICLIPICON, MMS2_FILEPATH_HEADERLESS_UZICLIPICON);

	if(!p_shotgunIcon) p_shotgunIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SHOTGUNICON, MMS2_FILEPATH_HEADERLESS_SHOTGUNICON);
	if(!p_shotgunCursor) p_shotgunCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SHOTGUNCURSOR, MMS2_FILEPATH_HEADERLESS_SHOTGUNCURSOR);
	if(!p_shotgunCursorShoot) p_shotgunCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SHOTGUNCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_SHOTGUNCURSORSHOOT);
	if(!p_shotgunAnimation) p_shotgunAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SHOTGUNANIMATION, MMS2_FILEPATH_HEADERLESS_SHOTGUNANIMATION);
	if(!p_shotgunClipIcon) p_shotgunClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SHOTGUNCLIPICON, MMS2_FILEPATH_HEADERLESS_SHOTGUNCLIPICON);

	if(!p_grenadeIcon) p_grenadeIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GRENADEICON, MMS2_FILEPATH_HEADERLESS_GRENADEICON);
	if(!p_grenadeCursor) p_grenadeCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GRENADECURSOR, MMS2_FILEPATH_HEADERLESS_GRENADECURSOR);
	if(!p_grenadeCursorShoot) p_grenadeCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GRENADECURSORSHOOT, MMS2_FILEPATH_HEADERLESS_GRENADECURSORSHOOT);
	if(!p_grenadeAnimation) p_grenadeAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GRENADEANIMATION, MMS2_FILEPATH_HEADERLESS_GRENADEANIMATION);
	if(!p_grenadeClipIcon) p_grenadeClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GRENADECLIPICON, MMS2_FILEPATH_HEADERLESS_GRENADECLIPICON);

	if(!p_flamethrowerIcon) p_flamethrowerIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FLAMETHROWERICON, MMS2_FILEPATH_HEADERLESS_FLAMETHROWERICON);
	if(!p_flamethrowerCursor) p_flamethrowerCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FLAMETHROWERCURSOR, MMS2_FILEPATH_HEADERLESS_FLAMETHROWERCURSOR);
	if(!p_flamethrowerCursorShoot) p_flamethrowerCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FLAMETHROWERCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_FLAMETHROWERCURSORSHOOT);
	if(!p_flamethrowerAnimation) p_flamethrowerAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FLAMETHROWERANIMATION, MMS2_FILEPATH_HEADERLESS_FLAMETHROWERANIMATION);
	if(!p_flamethrowerClipIcon) p_flamethrowerClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FLAMETHROWERCLIPICON, MMS2_FILEPATH_HEADERLESS_FLAMETHROWERCLIPICON);

	if(!p_knifeIcon) p_knifeIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_KNIFEICON, MMS2_FILEPATH_HEADERLESS_KNIFEICON);
	if(!p_knifeCursor) p_knifeCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_KNIFECURSOR, MMS2_FILEPATH_HEADERLESS_KNIFECURSOR);
	if(!p_knifeCursorShoot) p_knifeCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_KNIFECURSORSHOOT, MMS2_FILEPATH_HEADERLESS_KNIFECURSORSHOOT);
	if(!p_knifeAnimation) p_knifeAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_KNIFEANIMATION, MMS2_FILEPATH_HEADERLESS_KNIFEANIMATION);

	if(!p_molotovIcon) p_molotovIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MOLOTOVICON, MMS2_FILEPATH_HEADERLESS_MOLOTOVICON);
	if(!p_molotovCursor) p_molotovCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MOLOTOVCURSOR, MMS2_FILEPATH_HEADERLESS_MOLOTOVCURSOR);
	if(!p_molotovCursorShoot) p_molotovCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MOLOTOVCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_MOLOTOVCURSORSHOOT);
	if(!p_molotovAnimation) p_molotovAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MOLOTOVANIMATION, MMS2_FILEPATH_HEADERLESS_MOLOTOVANIMATION);
	if(!p_molotovClipIcon) p_molotovClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MOLOTOVCLIPICON, MMS2_FILEPATH_HEADERLESS_MOLOTOVCLIPICON);

	if(!p_dynamiteIcon) p_dynamiteIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DYNAMITEICON, MMS2_FILEPATH_HEADERLESS_DYNAMITEICON);
	if(!p_dynamiteCursor) p_dynamiteCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DYNAMITECURSOR, MMS2_FILEPATH_HEADERLESS_DYNAMITECURSOR);
	if(!p_dynamiteCursorShoot) p_dynamiteCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DYNAMITECURSORSHOOT, MMS2_FILEPATH_HEADERLESS_DYNAMITECURSORSHOOT);
	if(!p_dynamiteAnimation) p_dynamiteAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DYNAMITEANIMATION, MMS2_FILEPATH_HEADERLESS_DYNAMITEANIMATION);
	if(!p_dynamiteClipIcon) p_dynamiteClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DYNAMITECLIPICON, MMS2_FILEPATH_HEADERLESS_DYNAMITECLIPICON);

	if(!p_tomahawkIcon) p_tomahawkIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOMAHAWKICON, MMS2_FILEPATH_HEADERLESS_TOMAHAWKICON);
	if(!p_tomahawkCursor) p_tomahawkCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOMAHAWKCURSOR, MMS2_FILEPATH_HEADERLESS_TOMAHAWKCURSOR);
	if(!p_tomahawkCursorShoot) p_tomahawkCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOMAHAWKCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_TOMAHAWKCURSORSHOOT);
	if(!p_tomahawkAnimation) p_tomahawkAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOMAHAWKANIMATION, MMS2_FILEPATH_HEADERLESS_TOMAHAWKANIMATION);
	if(!p_tomahawkClipIcon) p_tomahawkClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOMAHAWKCLIPICON, MMS2_FILEPATH_HEADERLESS_TOMAHAWKCLIPICON);

	if(!p_bowAndArrowIcon) p_bowAndArrowIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BOWANDARROWICON, MMS2_FILEPATH_HEADERLESS_BOWANDARROWICON);
	if(!p_bowAndArrowCursor) p_bowAndArrowCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BOWANDARROWCURSOR, MMS2_FILEPATH_HEADERLESS_BOWANDARROWCURSOR);
	if(!p_bowAndArrowCursorShoot) p_bowAndArrowCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BOWANDARROWCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_BOWANDARROWCURSORSHOOT);
	if(!p_bowAndArrowAnimation) p_bowAndArrowAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BOWANDARROWANIMATION, MMS2_FILEPATH_HEADERLESS_BOWANDARROWANIMATION);
	if(!p_bowAndArrowClipIcon) p_bowAndArrowClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BOWANDARROWCLIPICON, MMS2_FILEPATH_HEADERLESS_BOWANDARROWCLIPICON);

	if(!p_chainsawIcon) p_chainsawIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAINSAWICON, MMS2_FILEPATH_HEADERLESS_CHAINSAWICON);
	if(!p_chainsawCursor) p_chainsawCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAINSAWCURSOR, MMS2_FILEPATH_HEADERLESS_CHAINSAWCURSOR);
	if(!p_chainsawCursorShoot) p_chainsawCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAINSAWCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_CHAINSAWCURSORSHOOT);
	if(!p_chainsawAnimation) p_chainsawAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAINSAWANIMATION, MMS2_FILEPATH_HEADERLESS_CHAINSAWANIMATION);
	if(!p_chainsawClipIcon) p_chainsawClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CHAINSAWCLIPICON, MMS2_FILEPATH_HEADERLESS_CHAINSAWCLIPICON);

	if(!p_raygunIcon) p_raygunIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RAYGUNICON, MMS2_FILEPATH_HEADERLESS_RAYGUNICON);
	if(!p_raygunCursor) p_raygunCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RAYGUNCURSOR, MMS2_FILEPATH_HEADERLESS_RAYGUNCURSOR);
	if(!p_raygunCursorShoot) p_raygunCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RAYGUNCURSORSHOOT, MMS2_FILEPATH_HEADERLESS_RAYGUNCURSORSHOOT);
	if(!p_raygunAnimation) p_raygunAnimation = PLEX_loadTextureFromFileOrHeaderless(1280, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RAYGUNANIMATION, MMS2_FILEPATH_HEADERLESS_RAYGUNANIMATION);
	if(!p_raygunClipIcon) p_raygunClipIcon = PLEX_loadTextureFromFileOrHeaderless(32, 32, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RAYGUNCLIPICON, MMS2_FILEPATH_HEADERLESS_RAYGUNCLIPICON);
}

bool MMS2_checkRunSystemPlayer(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t fontPlate, bool* success, const uint64_t time)
{
	if(p_emptyChamberSE != -1 && !PLEX_isSoundPlaying(p_emptyChamberSE)) p_emptyChamberSE = -1;

	if(MMS2_health() <= 0)
	{
		if(!MMS2_setGame(chapter2SpriteTex, chapter2SpriteTex2, time))
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONDYING, MMS2_ERRORMESS_OP_SETGAME);
			return false;
		}

		MMS2_gameOverScene(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, label, bubble, arrow, fontPlate, time);

		*success = false;
		return false;
	}

	if(MMS2_isNotMoving())
	{
		if(!MMS2_currentRoomCalm())
		{
			MMS2_setLeanX(0);
			MMS2_setLeanY(0);

			MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_STAND);

			if(PLEX_KEY_down('s'))
			{
				if(PLEX_KEY_down('a')) MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT);
				else if(PLEX_KEY_down('d')) MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT);
				else MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCH);
			}else{
				if(PLEX_KEY_down('a')) MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT);
				else if(PLEX_KEY_down('d')) MMS2_setDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT);
			}

			if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT)) MMS2_setLeanX(-4);
			if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT)) MMS2_setLeanX(4);
			if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCH) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT)) MMS2_setLeanY(4);
		}
	}

	if(MMS2_playerIsShooting(time))
	{
		if(time - MMS2_shotTime() > MMS2_shotDuration()) MMS2_setShotTime(-1);
	}else{
		if(time - MMS2_getPlayerShotTime() > MMS2_SHOTDURATION * 2) MMS2_setPlayerShotTime(0);

		if(!MMS2_currentRoomCalm() && MMS2_isNotMoving())
		{
			if(PLEX_KEY_press('j')) MMS2_selectLastGun(time);
			else if(PLEX_KEY_press('l')) MMS2_selectNextGun(time);

			for(char key = '1'; key <= '9'; ++key)
			{
				const size_t it = key - (size_t)'1';

				if(PLEX_KEY_press(key)) MMS2_selectGunSlotAt(it, time);
			}
		}
	}

	return true;
}

void MMS2_endSystemPlayer()
{
	MMS2_clearPlayerSprites();
}

void MMS2_clearPlayerSprites()
{
	p_clearGunSprites();

	PLEX_destroyTexture(p_clubIcon);
	PLEX_destroyTexture(p_clubCursor);
	PLEX_destroyTexture(p_clubCursorShoot);
	PLEX_destroyTexture(p_clubAnimation);

	PLEX_destroyTexture(p_revolverIcon);
	PLEX_destroyTexture(p_revolverCursor);
	PLEX_destroyTexture(p_revolverCursorShoot);
	PLEX_destroyTexture(p_revolverAnimation);
	PLEX_destroyTexture(p_revolverClipIcon);

	PLEX_destroyTexture(p_uziIcon);
	PLEX_destroyTexture(p_uziCursor);
	PLEX_destroyTexture(p_uziCursorShoot);
	PLEX_destroyTexture(p_uziAnimation);
	PLEX_destroyTexture(p_uziClipIcon);

	PLEX_destroyTexture(p_shotgunIcon);
	PLEX_destroyTexture(p_shotgunCursor);
	PLEX_destroyTexture(p_shotgunCursorShoot);
	PLEX_destroyTexture(p_shotgunAnimation);
	PLEX_destroyTexture(p_shotgunClipIcon);

	PLEX_destroyTexture(p_grenadeIcon);
	PLEX_destroyTexture(p_grenadeCursor);
	PLEX_destroyTexture(p_grenadeCursorShoot);
	PLEX_destroyTexture(p_grenadeAnimation);
	PLEX_destroyTexture(p_grenadeClipIcon);

	PLEX_destroyTexture(p_flamethrowerIcon);
	PLEX_destroyTexture(p_flamethrowerCursor);
	PLEX_destroyTexture(p_flamethrowerCursorShoot);
	PLEX_destroyTexture(p_flamethrowerAnimation);
	PLEX_destroyTexture(p_flamethrowerClipIcon);

	PLEX_destroyTexture(p_knifeIcon);
	PLEX_destroyTexture(p_knifeCursor);
	PLEX_destroyTexture(p_knifeCursorShoot);
	PLEX_destroyTexture(p_knifeAnimation);

	PLEX_destroyTexture(p_molotovIcon);
	PLEX_destroyTexture(p_molotovCursor);
	PLEX_destroyTexture(p_molotovCursorShoot);
	PLEX_destroyTexture(p_molotovAnimation);
	PLEX_destroyTexture(p_molotovClipIcon);

	PLEX_destroyTexture(p_dynamiteIcon);
	PLEX_destroyTexture(p_dynamiteCursor);
	PLEX_destroyTexture(p_dynamiteCursorShoot);
	PLEX_destroyTexture(p_dynamiteAnimation);
	PLEX_destroyTexture(p_dynamiteClipIcon);

	PLEX_destroyTexture(p_tomahawkIcon);
	PLEX_destroyTexture(p_tomahawkCursor);
	PLEX_destroyTexture(p_tomahawkCursorShoot);
	PLEX_destroyTexture(p_tomahawkAnimation);
	PLEX_destroyTexture(p_tomahawkClipIcon);

	PLEX_destroyTexture(p_bowAndArrowIcon);
	PLEX_destroyTexture(p_bowAndArrowCursor);
	PLEX_destroyTexture(p_bowAndArrowCursorShoot);
	PLEX_destroyTexture(p_bowAndArrowAnimation);
	PLEX_destroyTexture(p_bowAndArrowClipIcon);

	PLEX_destroyTexture(p_chainsawIcon);
	PLEX_destroyTexture(p_chainsawCursor);
	PLEX_destroyTexture(p_chainsawCursorShoot);
	PLEX_destroyTexture(p_chainsawAnimation);
	PLEX_destroyTexture(p_chainsawClipIcon);

	PLEX_destroyTexture(p_raygunIcon);
	PLEX_destroyTexture(p_raygunCursor);
	PLEX_destroyTexture(p_raygunCursorShoot);
	PLEX_destroyTexture(p_raygunAnimation);
	PLEX_destroyTexture(p_raygunClipIcon);

	p_clubIcon = 0;
	p_clubCursor = 0;
	p_clubCursorShoot = 0;
	p_clubAnimation = 0;

	p_revolverIcon = 0;
	p_revolverCursor = 0;
	p_revolverCursorShoot = 0;
	p_revolverAnimation = 0;
	p_revolverClipIcon = 0;

	p_uziIcon = 0;
	p_uziCursor = 0;
	p_uziCursorShoot = 0;
	p_uziAnimation = 0;
	p_uziClipIcon = 0;

	p_shotgunIcon = 0;
	p_shotgunCursor = 0;
	p_shotgunCursorShoot = 0;
	p_shotgunAnimation = 0;
	p_shotgunClipIcon = 0;

	p_grenadeIcon = 0;
	p_grenadeCursor = 0;
	p_grenadeCursorShoot = 0;
	p_grenadeAnimation = 0;
	p_grenadeClipIcon = 0;

	p_flamethrowerIcon = 0;
	p_flamethrowerCursor = 0;
	p_flamethrowerCursorShoot = 0;
	p_flamethrowerAnimation = 0;
	p_flamethrowerClipIcon = 0;

	p_knifeIcon = 0;
	p_knifeCursor = 0;
	p_knifeCursorShoot = 0;
	p_knifeAnimation = 0;
}

void MMS2_initPointsCashHealth()
{
	p_points = 0;
	p_cash = 10;
	p_health = 1;
}

void MMS2_cure(const double amount)
{
	p_health += amount;

	if(p_health < 0) p_health = 0;
	if(p_health > 1) p_health = 1;
}

void MMS2_fillHealth(){ p_health = 1; }

void MMS2_setHealth(const double health) { p_health = health; }

void MMS2_decrementHealth(const double health)
{
	if(health >= p_health) p_health = 0;
	else p_health -= health;
}

void MMS2_setPoints(const uint32_t points){ p_points = points; }

void MMS2_incrementPoints(const uint32_t points){ p_points += points; }

void MMS2_decrementPoints(const uint32_t points)
{
	if(points >= p_points) p_points = 0;
	else p_points -= points;
}

void MMS2_clearPoints(){ p_points = 0; }

bool MMS2_costCash(const double cost)
{
	if(cost <= p_cash)
	{
		p_cash -= cost;
		return true;
	}

	return false;
}

void MMS2_emptyCash()
{
	p_cash = 0;
}

void MMS2_setCash(const double cash) { p_cash = cash; }

void MMS2_incrementCash(const double cash){ p_cash += cash; }

void MMS2_clearCash(){ p_cash = 0; }

void MMS2_createGuns(const uint64_t time)
{
	// 0 - club

	PLEX_ANIMATION_PLATE clubPlate = PLEX_createAnimationPlate(0.25, 1, p_clubAnimation);

	PLEX_ANIMATION* clubShootAnimation = NULL;

	// 1 - revolver

	PLEX_ANIMATION_PLATE revolverPlate = PLEX_createAnimationPlate(0.25, 1, p_revolverAnimation);

	PLEX_ANIMATION* revolverShootAnimation = NULL;

	// 2 - uzi

	PLEX_ANIMATION_PLATE uziPlate = PLEX_createAnimationPlate(0.25, 1, p_uziAnimation);

	PLEX_ANIMATION* uziShootAnimation = NULL;

	// 3 - shotgun

	PLEX_ANIMATION_PLATE shotgunPlate = PLEX_createAnimationPlate(0.25, 1, p_shotgunAnimation);

	PLEX_ANIMATION* shotgunShootAnimation = NULL;

	// 4 - grenade

	PLEX_ANIMATION_PLATE grenadePlate = PLEX_createAnimationPlate(0.25, 1, p_grenadeAnimation);

	PLEX_ANIMATION* grenadeShootAnimation = NULL;

	// 5 - flame thrower

	PLEX_ANIMATION_PLATE flamethrowerPlate = PLEX_createAnimationPlate(0.25, 1, p_flamethrowerAnimation);

	PLEX_ANIMATION* flamethrowerShootAnimation = NULL;

	// 6 - knife

	PLEX_ANIMATION_PLATE knifePlate = PLEX_createAnimationPlate(0.25, 1, p_knifeAnimation);

	PLEX_ANIMATION* knifeShootAnimation = NULL;

	// 7 - molotov

	PLEX_ANIMATION_PLATE molotovPlate = PLEX_createAnimationPlate(0.25, 1, p_molotovAnimation);

	PLEX_ANIMATION* molotovShootAnimation = NULL;

	// 8 - dynamite

	PLEX_ANIMATION_PLATE dynamitePlate = PLEX_createAnimationPlate(0.25, 1, p_dynamiteAnimation);

	PLEX_ANIMATION* dynamiteShootAnimation = NULL;

	// 9 - tomahawk

	PLEX_ANIMATION_PLATE tomahawkPlate = PLEX_createAnimationPlate(0.25, 1, p_tomahawkAnimation);

	PLEX_ANIMATION* tomahawkShootAnimation = NULL;

	// 10 - bowAndArrow

	PLEX_ANIMATION_PLATE bowAndArrowPlate = PLEX_createAnimationPlate(0.25, 1, p_bowAndArrowAnimation);

	PLEX_ANIMATION* bowAndArrowShootAnimation = NULL;

	// 11 - chainsaw

	PLEX_ANIMATION_PLATE chainsawPlate = PLEX_createAnimationPlate(0.25, 1, p_chainsawAnimation);

	PLEX_ANIMATION* chainsawShootAnimation = NULL;

	// 12 - raygun

	PLEX_ANIMATION_PLATE raygunPlate = PLEX_createAnimationPlate(0.25, 1, p_raygunAnimation);

	PLEX_ANIMATION* raygunShootAnimation = NULL;

	// clear guns

	p_clearGunSprites();

	memset(p_guns, 0, sizeof(MMS_MINIGAME2GUN) * MMS2_GUNCOUNT);
	memset(p_hasGun, false, sizeof(bool) * MMS2_GUNCOUNT);

	// 0 - club

	p_setGun(0, MMS2_LANGUAGE_WEAPONNAME_CLUB, p_clubIcon, p_clubCursor, p_clubCursorShoot, 0, MM_COMMON_SOUNDEFFECT_CLUB, MM_COMMON_SOUNDEFFECT_NONE, -1, -1, 500, 0, 0.1, 0.1, 0, clubPlate);

	PLEX_addAnimation(p_guns[0].shotAnimation, p_guns[0].shootTime, time);

	clubShootAnimation = PLEX_getAnimation(0, p_guns[0].shotAnimation);

	PLEX_addAnimationFrame(0, clubShootAnimation);
	PLEX_addAnimationFrame(1, clubShootAnimation);
	PLEX_addAnimationFrame(2, clubShootAnimation);
	PLEX_addAnimationFrame(3, clubShootAnimation);

	// 1 - revolver

	p_setGun(1, MMS2_LANGUAGE_WEAPONNAME_REVOLVER, p_revolverIcon, p_revolverCursor, p_revolverCursorShoot, p_revolverClipIcon, MM_COMMON_SOUNDEFFECT_SHOT, MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER, 6, 5, 200, 1000, 0.35, 0.15, 0, revolverPlate);

	PLEX_addAnimation(p_guns[1].shotAnimation, p_guns[1].shootTime, time);


	revolverShootAnimation = PLEX_getAnimation(0, p_guns[1].shotAnimation);

	PLEX_addAnimationFrame(0, revolverShootAnimation);
	PLEX_addAnimationFrame(1, revolverShootAnimation);
	PLEX_addAnimationFrame(2, revolverShootAnimation);
	PLEX_addAnimationFrame(3, revolverShootAnimation);

	// 2 - uzianimation

	p_setGun(2, MMS2_LANGUAGE_WEAPONNAME_UZI, p_uziIcon, p_uziCursor, p_uziCursorShoot, p_uziClipIcon, MM_COMMON_SOUNDEFFECT_RAPIDSHOT, MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER, 300, 3, 50, 5000, 0.08, 0.02, 200, uziPlate);

	PLEX_addAnimation(p_guns[2].shotAnimation, p_guns[2].shootTime, time);

	uziShootAnimation = PLEX_getAnimation(0, p_guns[2].shotAnimation);

	PLEX_addAnimationFrame(0, uziShootAnimation);
	PLEX_addAnimationFrame(1, uziShootAnimation);
	PLEX_addAnimationFrame(2, uziShootAnimation);
	PLEX_addAnimationFrame(3, uziShootAnimation);

	// 3 - shotgun

	p_setGun(3, MMS2_LANGUAGE_WEAPONNAME_SHOTGUN, p_shotgunIcon, p_shotgunCursor, p_shotgunCursorShoot, p_shotgunClipIcon, MM_COMMON_SOUNDEFFECT_SHOTGUNSHOT, MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER, 2, 5, 300, 3000, 0.7, 0.3, 10, shotgunPlate);

	PLEX_addAnimation(p_guns[3].shotAnimation, p_guns[3].shootTime, time);

	shotgunShootAnimation = PLEX_getAnimation(0, p_guns[3].shotAnimation);

	PLEX_addAnimationFrame(0, shotgunShootAnimation);
	PLEX_addAnimationFrame(1, shotgunShootAnimation);
	PLEX_addAnimationFrame(2, shotgunShootAnimation);
	PLEX_addAnimationFrame(3, shotgunShootAnimation);

	// 4 - grenade

	p_setGun(4, MMS2_LANGUAGE_WEAPONNAME_GRENADE, p_grenadeIcon, p_grenadeCursor, p_grenadeCursorShoot, p_grenadeClipIcon, MM_COMMON_SOUNDEFFECT_EXPLOSION, MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER, 1, 3, 1000, 1000, 5, 5, 200, grenadePlate);

	PLEX_addAnimation(p_guns[4].shotAnimation, p_guns[4].shootTime, time);

	grenadeShootAnimation = PLEX_getAnimation(0, p_guns[4].shotAnimation);

	PLEX_addAnimationFrame(0, grenadeShootAnimation);
	PLEX_addAnimationFrame(1, grenadeShootAnimation);
	PLEX_addAnimationFrame(2, grenadeShootAnimation);
	PLEX_addAnimationFrame(3, grenadeShootAnimation);

	// 5 - flame thrower

	p_setGun(5, MMS2_LANGUAGE_WEAPONNAME_FLAMETHROWER, p_flamethrowerIcon, p_flamethrowerCursor, p_flamethrowerCursorShoot, p_flamethrowerClipIcon, MM_COMMON_SOUNDEFFECT_SHOT, MM_COMMON_SOUNDEFFECT_EMPTYCHAMBER, 1000, 10, 50, 1000, 0.04, 0.04, 500, flamethrowerPlate);

	PLEX_addAnimation(p_guns[5].shotAnimation, p_guns[5].shootTime, time);

	flamethrowerShootAnimation = PLEX_getAnimation(0, p_guns[5].shotAnimation);

	PLEX_addAnimationFrame(0, flamethrowerShootAnimation);
	PLEX_addAnimationFrame(1, flamethrowerShootAnimation);
	PLEX_addAnimationFrame(2, flamethrowerShootAnimation);
	PLEX_addAnimationFrame(3, flamethrowerShootAnimation);

	// 6 - knife

	p_setGun(6, MMS2_LANGUAGE_WEAPONNAME_KNIFE, p_knifeIcon, p_knifeCursor, p_knifeCursorShoot, 0, MM_COMMON_SOUNDEFFECT_SLASH, MM_COMMON_SOUNDEFFECT_NONE, -1, -1, 100, 0, 0.05, 0.02, 10, knifePlate);

	PLEX_addAnimation(p_guns[6].shotAnimation, p_guns[6].shootTime, time);

	knifeShootAnimation = PLEX_getAnimation(0, p_guns[6].shotAnimation);

	PLEX_addAnimationFrame(0, knifeShootAnimation);
	PLEX_addAnimationFrame(1, knifeShootAnimation);
	PLEX_addAnimationFrame(2, knifeShootAnimation);
	PLEX_addAnimationFrame(3, knifeShootAnimation);

	// 7 - molotov

	p_setGun(7, MMS2_LANGUAGE_WEAPONNAME_MOLOTOVCOCKTAIL, p_molotovIcon, p_molotovCursor, p_molotovCursorShoot, p_molotovClipIcon, MM_COMMON_SOUNDEFFECT_EXPLOSION, MM_COMMON_SOUNDEFFECT_NONE, 5, 1, 750, 250, 0.8, 0.2, 50,  molotovPlate);

	PLEX_addAnimation(p_guns[7].shotAnimation, p_guns[7].shootTime, time);

	molotovShootAnimation = PLEX_getAnimation(0, p_guns[7].shotAnimation);

	PLEX_addAnimationFrame(0, molotovShootAnimation);
	PLEX_addAnimationFrame(1, molotovShootAnimation);
	PLEX_addAnimationFrame(2, molotovShootAnimation);
	PLEX_addAnimationFrame(3, molotovShootAnimation);

	// 8 - dynamite

	p_setGun(8, MMS2_LANGUAGE_WEAPONNAME_DYNAMITE, p_dynamiteIcon, p_dynamiteCursor, p_dynamiteCursorShoot, p_dynamiteClipIcon, MM_COMMON_SOUNDEFFECT_EXPLOSION, MM_COMMON_SOUNDEFFECT_NONE, 1, 0, 2000, 250, 10, 10, 400, dynamitePlate);

	PLEX_addAnimation(p_guns[8].shotAnimation, p_guns[8].shootTime, time);

	dynamiteShootAnimation = PLEX_getAnimation(0, p_guns[8].shotAnimation);

	PLEX_addAnimationFrame(0, dynamiteShootAnimation);
	PLEX_addAnimationFrame(1, dynamiteShootAnimation);
	PLEX_addAnimationFrame(2, dynamiteShootAnimation);
	PLEX_addAnimationFrame(3, dynamiteShootAnimation);

	// 9 - tomahawk

	p_setGun(9, MMS2_LANGUAGE_WEAPONNAME_TOMAHAWK, p_tomahawkIcon, p_tomahawkCursor, p_tomahawkCursorShoot, p_tomahawkClipIcon, MM_COMMON_SOUNDEFFECT_CLUB, MM_COMMON_SOUNDEFFECT_NONE, 10, 10, 100, 500, 0.15, 0.09, 50, tomahawkPlate);

	PLEX_addAnimation(p_guns[9].shotAnimation, p_guns[9].shootTime, time);

	tomahawkShootAnimation = PLEX_getAnimation(0, p_guns[9].shotAnimation);

	PLEX_addAnimationFrame(0, tomahawkShootAnimation);
	PLEX_addAnimationFrame(1, tomahawkShootAnimation);
	PLEX_addAnimationFrame(2, tomahawkShootAnimation);
	PLEX_addAnimationFrame(3, tomahawkShootAnimation);

	// 10 - bowAndArrow

	p_setGun(10, MMS2_LANGUAGE_WEAPONNAME_BOWANDARROW, p_bowAndArrowIcon, p_bowAndArrowCursor, p_bowAndArrowCursorShoot, p_bowAndArrowClipIcon, MM_COMMON_SOUNDEFFECT_ARROW, MM_COMMON_SOUNDEFFECT_NONE, 20, 5, 100, 5000, 0.25, 0, 25, bowAndArrowPlate);

	PLEX_addAnimation(p_guns[10].shotAnimation, p_guns[10].shootTime, time);

	bowAndArrowShootAnimation = PLEX_getAnimation(0, p_guns[10].shotAnimation);

	PLEX_addAnimationFrame(0, bowAndArrowShootAnimation);
	PLEX_addAnimationFrame(1, bowAndArrowShootAnimation);
	PLEX_addAnimationFrame(2, bowAndArrowShootAnimation);
	PLEX_addAnimationFrame(3, bowAndArrowShootAnimation);

	// 11 - chainsaw

	p_setGun(11, MMS2_LANGUAGE_WEAPONNAME_CHAINSAW, p_chainsawIcon, p_chainsawCursor, p_chainsawCursorShoot, p_chainsawClipIcon, MM_COMMON_SOUNDEFFECT_CHAINSAWCUT, MM_COMMON_SOUNDEFFECT_NONE, 500, 3, 50, 2000, 0.1, 0, 2000, chainsawPlate);

	PLEX_addAnimation(p_guns[11].shotAnimation, p_guns[11].shootTime, time);

	chainsawShootAnimation = PLEX_getAnimation(0, p_guns[11].shotAnimation);

	PLEX_addAnimationFrame(0, chainsawShootAnimation);
	PLEX_addAnimationFrame(1, chainsawShootAnimation);
	PLEX_addAnimationFrame(2, chainsawShootAnimation);
	PLEX_addAnimationFrame(3, chainsawShootAnimation);

	// 12 - raygun

	p_setGun(12, MMS2_LANGUAGE_WEAPONNAME_RAYGUN, p_raygunIcon, p_raygunCursor, p_raygunCursorShoot, p_raygunClipIcon, MM_COMMON_SOUNDEFFECT_RAYGUN, MM_COMMON_SOUNDEFFECT_NONE, 5, 3, 500, 2500, 10, 6, 10000, raygunPlate);

	PLEX_addAnimation(p_guns[12].shotAnimation, p_guns[12].shootTime, time);

	raygunShootAnimation = PLEX_getAnimation(0, p_guns[12].shotAnimation);

	PLEX_addAnimationFrame(0, raygunShootAnimation);
	PLEX_addAnimationFrame(1, raygunShootAnimation);
	PLEX_addAnimationFrame(2, raygunShootAnimation);
	PLEX_addAnimationFrame(3, raygunShootAnimation);
}

bool MMS2_hasGun(const size_t index)
{
	if(index >= MMS2_GUNCOUNT) return false;

	return p_hasGun[index];
}

void MMS2_purchaseGun(const size_t index)
{
	MMS_MINIGAME2GUN* gun = NULL;

	if(index >= MMS2_GUNCOUNT || p_hasGun[index]) return;

	gun = p_guns + index;

	p_cash -= gun->cost;

	p_hasGun[index] = true;
}

void MMS2_refillGun(const size_t index)
{
	MMS_MINIGAME2GUN* gun = NULL;

	if(index >= MMS2_GUNCOUNT || !p_hasGun[index]) return;

	gun = p_guns + index;

	gun->ammoAmount = gun->ammoMaximum;
	gun->ammoClip = gun->ammoClipMaximum;
}

void MMS2_addGun(const size_t index){ p_hasGun[index] = true; }
void MMS2_takeGun(const size_t index){ p_hasGun[index] = false; }

void MMS2_setShotTime(const int64_t time){ p_shotTime = time; }
void MMS2_setShotDuration(const uint64_t duration){ p_shotDuration = duration; }

uint64_t MMS2_getPlayerShotTime(){ return p_playerShotTime; }

void MMS2_setPlayerShotTime(const uint64_t time){ p_playerShotTime = time; }

void MMS2_setEmptyChamberSE(const int64_t emptyChamberSE)
{
	if(p_emptyChamberSE != -1) return;

	p_emptyChamberSE = emptyChamberSE;

	MM_COMMON_playSoundEffect(p_emptyChamberSE);
}

void MMS2_setDodgePhase(const MMS_MINIGAME2DODGEPHASE phase){ p_dodgePhase = phase; }

void MMS2_setLeanX(const double leanX){ p_leanX = leanX; }
void MMS2_setLeanY(const double leanY){ p_leanY = leanY; }

double MMS2_leanX(){ return p_leanX; }
double MMS2_leanY(){ return p_leanY; }

double MMS2_health(){ return p_health; }
uint32_t MMS2_points(){ return p_points; }
double MMS2_cash(){ return p_cash; }

int64_t MMS2_shotTime(){ return p_shotTime; }
uint64_t MMS2_shotDuration(){ return p_shotDuration; }

bool MMS2_playerIsShooting(const uint64_t time)
{
	if(MMS2_isReloading(time)) return false;

	return p_shotTime != -1;
}

bool MMS2_playerIsNotShooting(const uint64_t time){ return !MMS2_playerIsShooting(time); }

bool MMS2_isReloading(const uint64_t time)
{
	MMS_MINIGAME2GUN* gun = MMS2_selectedGun();

	if(gun == NULL || gun->reloadTime == -1) return false;

	if(time - gun->reloadTime < gun->reloadDuration) return true;

	gun->reloadTime = -1;

	return false;
}

bool MMS2_isDodgePhase(const MMS_MINIGAME2DODGEPHASE phase){ return p_dodgePhase == phase; }

double MMS2_dodgePhaseAsNumber(){ return (double)p_dodgePhase; }

struct MMS_MINIGAME2GUN* MMS2_gun(const size_t index){ return p_guns + index; }
