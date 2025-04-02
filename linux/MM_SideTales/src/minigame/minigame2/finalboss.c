#include "minigame/minigame2/minigame2.h"

static PLEX_SPRITE* p_finalBossSprite = NULL;
static PLEX_SPRITE* p_finalBossDropBoxSprite = NULL;
static PLEX_SPRITE* p_finalBossExplosionSprite = NULL;

static bool p_activateFinalBoss = false;
static bool p_levineFight = false;
static bool p_beginFinalBossIntroCut = false;
static bool p_beginFinalBossOutroCut = false;

static uint64_t p_beginFinalBossIntroTime = 0;
static uint64_t p_beginFinalBossOutroTime = 0;

static PLEX_RECT p_finalBossRect;

static bool p_finalBossDamaged = false;

static size_t p_finalBossSpriteTex = 0;
static size_t p_finalBossDropBoxSpriteTex = 0;
static size_t p_finalBossExplosionSpriteTex = 0;

static int8_t p_finalBossPlace = 0;
static int8_t p_finalBossMove = 2;

static uint64_t p_finalBossLastMove = 0;
static uint64_t p_finalBossDamageTime = 0;

static double p_finalBossHealth = MMS2_FINALBOSSMAXHEALTH;

static bool p_finalBossShootMode = false;
static uint64_t p_finalBossShootTime = 0;
static uint64_t p_finalBossShootHitTime = 0;
static uint64_t p_finalBossDropBoxTime = 0;

static MMS_MINIGAME2FINALBOSSDROPBOX p_finalBossDropBoxes[MMS2_FINALBOSSDROPBOXCOUNT];
static size_t p_finalBossDropBoxCount = 0;

static int64_t p_finalBossExplosionLoopSE = -1;

// plays the theme for the ascension of levine's helicopter

static void p_playFinalBossIntroTheme()
{
	int64_t harpBuffer = -1;
	int64_t harmonicaBuffer = -1;
	int64_t geetarBuffer = -1;
	int64_t organBuffer = -1;
	int64_t pianoBuffer = -1;

	PLEX_clearSoundPreloads();

	harpBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSINTRO_HARPBUFFER);
	harmonicaBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSINTRO_HARMONICABUFFER);
	geetarBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSINTRO_GEETARBUFFER);
	organBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSINTRO_ORGANBUFFER);
	pianoBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSINTRO_PIANOBUFFER);

	if(harpBuffer != -1 && PLEX_assignSoundBuffer(harpBuffer, 0)) PLEX_soundChannelOn(false, 0);
	if(harmonicaBuffer != -1 && PLEX_assignSoundBuffer(harmonicaBuffer, 1)) PLEX_soundChannelOn(false, 1);
	if(geetarBuffer != -1 && PLEX_assignSoundBuffer(geetarBuffer, 2)) PLEX_soundChannelOn(false, 2);
	if(organBuffer != -1 && PLEX_assignSoundBuffer(organBuffer, 3)) PLEX_soundChannelOn(false, 3);
	if(pianoBuffer != -1 && PLEX_assignSoundBuffer(pianoBuffer, 4)) PLEX_soundChannelOn(false, 4);
}

// updates all the 'drop boxes' by the final boss that either turn into an enemy or treasure. Turning into enemies in higher frequency as the final boss's hp dwindles.

static void p_updateFinalBossDropBoxes(const double secondsPass, const uint64_t time)
{
	for(size_t ze = 0; ze < p_finalBossDropBoxCount; ++ze)
	{
		MMS_MINIGAME2FINALBOSSDROPBOX* box = p_finalBossDropBoxes + ze;

		double arcUp = -0.5;
		double arcRight = 0.5;
		double speed = 0;

		if(!box->active) continue;

		if(box->maxDistance/8 < box->distance) arcUp = 0.5;
		if(box->endPoint.x < box->point.x) arcRight = -0.5;

		if(box->point.x < 0) box->point.x = 0;
		if(box->point.x >= PLEX_WIDTHUNITMAX()) box->point.x = PLEX_WIDTHUNITMAX();

		speed = 20 * secondsPass;

		box->distance += speed;

		box->point.x += arcRight * speed;
		box->point.y += arcUp * speed;

		if(box->point.y > box->endPoint.y)
		{
			size_t place = 0;

			if(box->isCover)
			{
				place = MMS2_coverCount();

				for(size_t ze = 0; ze < MMS2_coverCount(); ++ze)
				{
					MMS_MINIGAME2COVER* cover = MMS2_cover(ze);

					if(cover->health <= 0)
					{
						place = ze;
						break;
					}
				}

				if(place < MMS2_COVERCOUNT)
				{
					MMS_MINIGAME2COVER* newCover = MMS2_coverGen(box->index);
					MMS_MINIGAME2COVER* cover = MMS2_cover(place);

					if(newCover != NULL)
					{
						if(cover->gravesite && cover->sprite != NULL) PLEX_destroySprite(&cover->sprite);

						memcpy(cover, newCover, sizeof(MMS_MINIGAME2COVER));

						cover->space.origin = box->point;
						if(place == MMS2_coverCount()) MMS2_incrementCoverCount();
					}else{
						PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONFINALBOSSDROPCOVER, MMS2_ERRORMESS_GENCOVER);
					}
				}
			}else{
				place = MMS2_enemyCount();

				for(size_t ze = 0; ze < MMS2_enemyCount(); ++ze)
				{
					MMS_MINIGAME2ENEMY* enemy2 = MMS2_enemy(ze);

					if(enemy2->health <= 0)
					{
						place = ze;
						break;
					}
				}

				if(place < MMS2_ENEMYCOUNT)
				{
					const size_t aiIndex = PLEX_randomNumber(0, 6);

					MMS_MINIGAME2ENEMY* enemy = MMS2_enemy(place);
					MMS_MINIGAME2ENEMY* enemyGen = MMS2_enemyGen(box->index);

					if(enemyGen != NULL)
					{
						memcpy(enemy, enemyGen, sizeof(MMS_MINIGAME2ENEMY));

						enemy->space.origin = box->point;
						MMS2_setEnemySprite(enemy->startImage, enemy, time);

						switch(aiIndex)
						{
							case 0: enemy->aiPattern = MMS2_ai_dodger; break;
							case 1: enemy->aiPattern = MMS2_ai_coward; break;
							case 2: enemy->aiPattern = MMS2_ai_sneak; break;
							case 3: enemy->aiPattern = MMS2_ai_runner; break;
							case 4: enemy->aiPattern = MMS2_ai_diver; break;
							default: enemy->aiPattern = MMS2_ai_sharpshooter;
						};

						MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_COWBOYBIRTH);

						if(place == MMS2_enemyCount()) MMS2_incrementEnemyCount();
						MMS2_incrementTotalEnemyCount();
					}else{
						PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONFINALBOSSDROPENEMY, MMS2_ERRORMESS_GENENEMY);
					}
				}
			}

			box->active = false;
		}

		PLEX_drawSprite(MMS2_DRAWLAYER_FINALBOSSDROP, 0, PLEX_UNIT(box->point.x - 0.5), PLEX_UNIT(box->point.y - 0.5), PLEX_UNIT(1), PLEX_UNIT(1), p_finalBossDropBoxSprite, true, time);
	}
}

static void p_checkLoadFinalBossSprite(const uint64_t time)
{
	if(p_finalBossSprite == NULL)
	{
		PLEX_ANIMATION* normal = NULL;
		PLEX_ANIMATION* tiltLeft = NULL;
		PLEX_ANIMATION* tiltRight = NULL;
		PLEX_ANIMATION* normalShooting = NULL;
		PLEX_ANIMATION* tiltLeftShooting = NULL;
		PLEX_ANIMATION* tiltRightShooting = NULL;
		PLEX_ANIMATION* flames = NULL;

		PLEX_ANIMATION_PLATE animationPlate;

		p_finalBossSpriteTex = PLEX_loadTextureFromFileOrHeaderless(1512, 255, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_LEVINECOPTER, MMS2_FILEPATH_HEADERLESS_LEVINECOPTER);

		animationPlate = PLEX_createAnimationPlate(0.125, 0.5, p_finalBossSpriteTex);

		p_finalBossSprite = PLEX_genSprite(&animationPlate);

		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 200, time);
		PLEX_addAnimation(p_finalBossSprite, 250, time);

		normal = PLEX_getAnimation(0, p_finalBossSprite);

		PLEX_addAnimationFrame(0, normal);
		PLEX_addAnimationFrame(1, normal);

		tiltLeft = PLEX_getAnimation(1, p_finalBossSprite);

		PLEX_addAnimationFrame(2, tiltLeft);
		PLEX_addAnimationFrame(3, tiltLeft);

		tiltRight = PLEX_getAnimation(2, p_finalBossSprite);

		PLEX_addAnimationFrame(4, tiltRight);
		PLEX_addAnimationFrame(5, tiltRight);

		normalShooting = PLEX_getAnimation(3, p_finalBossSprite);

		PLEX_addAnimationFrame(8, normalShooting);
		PLEX_addAnimationFrame(9, normalShooting);

		tiltLeftShooting = PLEX_getAnimation(4, p_finalBossSprite);

		PLEX_addAnimationFrame(10, tiltLeftShooting);
		PLEX_addAnimationFrame(11, tiltLeftShooting);

		tiltRightShooting = PLEX_getAnimation(5, p_finalBossSprite);

		PLEX_addAnimationFrame(12, tiltRightShooting);
		PLEX_addAnimationFrame(13, tiltRightShooting);

		flames = PLEX_getAnimation(6, p_finalBossSprite);

		PLEX_addAnimationFrame(6, flames);
		PLEX_addAnimationFrame(7, flames);
		PLEX_addAnimationFrame(14, flames);
		PLEX_addAnimationFrame(15, flames);
	}
}

static void p_checkLoadDropBoxSprite(const uint64_t time)
{
	if(p_finalBossDropBoxSprite == NULL)
	{
		PLEX_ANIMATION* boxAnim = NULL;

		PLEX_ANIMATION_PLATE dropBoxAnimationPlate;

		p_finalBossDropBoxSpriteTex = PLEX_loadTextureFromFileOrHeaderless(64, 48, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FINALBOSSBOXDROP, MMS2_FILEPATH_HEADERLESS_FINALBOSSBOXDROP);

		dropBoxAnimationPlate = PLEX_createAnimationPlate(0.5, 1, p_finalBossDropBoxSpriteTex);

		p_finalBossDropBoxSprite = PLEX_genSprite(&dropBoxAnimationPlate);

		PLEX_addAnimation(p_finalBossDropBoxSprite, 1000, time);

		boxAnim = PLEX_getAnimation(0, p_finalBossDropBoxSprite);

		PLEX_addAnimationFrame(0, boxAnim);
		PLEX_addAnimationFrame(1, boxAnim);
	}
}

static void p_checkLoadExplosionSprite(const uint64_t time)
{
	if(p_finalBossExplosionSprite == NULL)
	{
		PLEX_ANIMATION* finalExplosionAnim = NULL;

		PLEX_ANIMATION_PLATE finalBossExplosionPlate;

		p_finalBossExplosionSpriteTex = PLEX_loadTextureFromFileOrHeaderless(1024, 512, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_FINALBOSSEXPLOSION, MMS2_FILEPATH_HEADERLESS_FINALBOSSEXPLOSION);

		finalBossExplosionPlate = PLEX_createAnimationPlate(0.5, 1, p_finalBossExplosionSpriteTex);

		p_finalBossExplosionSprite = PLEX_genSprite(&finalBossExplosionPlate);

		PLEX_addAnimation(p_finalBossExplosionSprite, 50, time);

		finalExplosionAnim = PLEX_getAnimation(0, p_finalBossExplosionSprite);

		PLEX_addAnimationFrame(0, finalExplosionAnim);
		PLEX_addAnimationFrame(1, finalExplosionAnim);
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemFinalBoss()
{
	p_activateFinalBoss = false;
	p_levineFight = false;
	p_beginFinalBossIntroCut = false;
	p_beginFinalBossOutroCut = false;

	p_finalBossDamageTime = 0;
}

void MMS2_initSystemFinalBoss()
{

}

bool MMS2_checkRunSystemFinalBoss(bool* success, const uint64_t time)
{
	if(MMS2_levineFight())
	{
		MMS2_setCurrentRoom(MMS2_LANGUAGE_FINAL_TITLE, MMS2_backgroundGraphic(4), MMS2_skyGraphic(4), false);

		MMS2_unmarkLevineFight();

		MMS2_startFinalBoss(time);

		return true;
	}

	if(MMS2_beginFinalBossIntro()) MMS2_finalBossIntroCut(time);

	if(MMS2_beginFinalBossOutro())
	{
		if(!MMS2_finalBossOutroCut(time))
		{
			MMS_MMS2MarkEnd();
			*success = true;
			return true;
		}
	}

	if(MMS2_activateFinalBoss())
	{
		if(MMS2_updateFinalBoss(time))
		{
			MMS2_markFinalBossOutroCut();
			p_beginFinalBossOutroTime = time;
			MMS2_playFinalBossOutroTheme();

			return true;
		}
	}

	return false;
}

void MMS2_endSystemFinalBoss()
{
	MMS2_clearFinalBossSprites();
	MMS2_clearCoverSprites();
}

void MMS2_clearFinalBossSprites()
{
	PLEX_destroySprite(&p_finalBossSprite);
	PLEX_destroySprite(&p_finalBossDropBoxSprite);
	PLEX_destroySprite(&p_finalBossExplosionSprite);

	if(!p_finalBossSpriteTex) PLEX_destroyTexture(p_finalBossSpriteTex);
	if(!p_finalBossDropBoxSpriteTex) PLEX_destroyTexture(p_finalBossDropBoxSpriteTex);
	if(!p_finalBossExplosionSpriteTex) PLEX_destroyTexture(p_finalBossExplosionSpriteTex);

	p_finalBossSpriteTex = 0;
	p_finalBossDropBoxSpriteTex = 0;
	p_finalBossExplosionSpriteTex = 0;
}

void MMS2_clearFinalBoss()
{
	p_activateFinalBoss = false;
	p_levineFight = false;
	p_beginFinalBossIntroCut = false;
	p_beginFinalBossOutroCut = false;
}

void MMS2_readyLevineFight(){ p_levineFight = true; }
void MMS2_unmarkLevineFight(){ p_levineFight = false; }

void MMS2_markFinalBossIntroCut(){ p_beginFinalBossIntroCut = true; }
void MMS2_unmarkFinalBossIntroCut(){ p_beginFinalBossIntroCut = false; }

void MMS2_finalBossIntroCut(const uint64_t time)
{
	const double baseDuration = PLEX_DEF_disableAudio() ? MMS2_FINALBOSSINTROCUTDURATIONNOSOUND : MMS2_FINALBOSSINTROCUTDURATION;
	const double duration = time - p_beginFinalBossIntroTime;
	const double perc = 1 - duration/baseDuration;

	const double flyY = p_finalBossRect.origin.y + (PLEX_HEIGHTUNITMAX(true) - p_finalBossRect.dimens.h - p_finalBossRect.origin.y) * perc;

	const PLEX_RECT levineFly = PLEX_convRect(PLEX_convPoint(p_finalBossRect.origin.x, flyY), p_finalBossRect.dimens);

	if(perc <= 0)
	{
		MMS2_markFinalBossActive();
		p_beginFinalBossOutroTime = time;

		MMS2_unmarkFinalBossIntroCut();
		return;
	}

	PLEX_drawSprite(MMS2_DRAWLAYER_FINALBOSSLEVINEFLY, 0, PLEX_UNIT(levineFly.origin.x + MMS2_leanX()), PLEX_UNIT(levineFly.origin.y + MMS2_leanY()), PLEX_UNIT(levineFly.dimens.w), PLEX_UNIT(levineFly.dimens.h), p_finalBossSprite, true, time);

	MMS2_dumpSnapshot();
}

void MMS2_startFinalBoss(const uint64_t time)
{
	const PLEX_DIMENS dimens = PLEX_convDimens(8, 4.5);

	if(MMS2_activateFinalBoss() || MMS2_beginFinalBossIntro()) return;

	p_checkLoadFinalBossSprite(time);
	p_checkLoadDropBoxSprite(time);
	p_checkLoadExplosionSprite(time);

	p_finalBossRect = PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX(true)/2 - dimens.w/2, 6), dimens);

	PLEX_startSprite(time, p_finalBossSprite);
	PLEX_startSprite(time, p_finalBossDropBoxSprite);
	PLEX_startSprite(time, p_finalBossExplosionSprite);

	p_finalBossPlace = 0;

	p_finalBossLastMove = time;
	p_finalBossDropBoxTime = time;

	p_finalBossShootMode = false;

	p_finalBossHealth = MMS2_FINALBOSSMAXHEALTH;
	p_finalBossShootTime = time;
	p_finalBossShootHitTime = time;
	p_finalBossDropBoxCount = 0;
	p_finalBossDamaged = false;

	MMS2_markFinalBossIntroCut();

	p_beginFinalBossIntroTime = time;

	MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);
	p_playFinalBossIntroTheme();
}

bool MMS2_updateFinalBoss(const uint64_t time)
{
	static uint64_t lastTime = 0;

	static const uint64_t moveTimeRange = MMS2_FINALBOSSMOVETIMEMAX - MMS2_FINALBOSSMOVETIMEMIN;

	static const double velocityRange = MMS2_FINALBOSSMOVEVELOCITYMAX - MMS2_FINALBOSSMOVEVELOCITYMIN;

	static const double shootCoolRange = MMS2_FINALBOSSSHOOTCOOLMAX - MMS2_FINALBOSSSHOOTCOOLMIN;

	static const double dropBoxRange = MMS2_FINALBOSSDROPBOXDURATIONMAX - MMS2_FINALBOSSDROPBOXDURATIONMIN;

	static const size_t coverBoxRange = MMS2_FINALBOSSDROPBOXCOVERMAX - MMS2_FINALBOSSDROPBOXCOVERMIN;

	const double healthPerc = p_finalBossHealth/(double)MMS2_FINALBOSSMAXHEALTH;

	const uint64_t thinkTime = MMS2_FINALBOSSMOVETIMEMIN + (moveTimeRange * healthPerc);

	const double velocity = MMS2_FINALBOSSMOVEVELOCITYMIN + (velocityRange * (1 - healthPerc));

	const uint64_t shootCool = MMS2_FINALBOSSSHOOTCOOLMIN + (shootCoolRange * healthPerc);

	const uint64_t dropBoxDuration = MMS2_FINALBOSSDROPBOXDURATIONMIN + (dropBoxRange * healthPerc);

	const size_t coverBoxDensity = MMS2_FINALBOSSDROPBOXCOVERMIN + (coverBoxRange * healthPerc);

	double secondsPass = 0;

	PLEX_RECT dr;

	int8_t direction = 0;

	uint8_t g = 255;
	uint8_t b = 255;

	bool endMove = false;

	bool shooting = false;

	if(!lastTime) lastTime = time;

	secondsPass = (time - lastTime)/1000.0;

	MM_COMMON_playTheme(MM_COMMON_THEMEID_AGGRESSION);

	p_updateFinalBossDropBoxes(secondsPass, time);

	dr.origin.x = PLEX_UNIT(p_finalBossRect.origin.x + MMS2_leanX());
	dr.origin.y = PLEX_UNIT(p_finalBossRect.origin.y + MMS2_leanY());
	dr.dimens.w = PLEX_UNIT(p_finalBossRect.dimens.w);
	dr.dimens.h = PLEX_UNIT(p_finalBossRect.dimens.h);

	if(p_finalBossDamageTime)
	{
		if(time - p_finalBossDamageTime < MMS2_FINALBOSSDAMAGEDURATION)
		{
			g = 0;
			b = 0;
			p_finalBossDamaged = true;
		}else{
			if(PLEX_rectCollisionNoMove(MMS2_shotArea(), dr))
			{
				if(MMS2_shotArea().origin.x < PLEX_WW(true)/2) p_finalBossRect.origin.x += p_finalBossRect.dimens.w;
				else p_finalBossRect.origin.x -= p_finalBossRect.dimens.w;
			}
		}
	}

	if(MMS2_playerIsNotShooting(time)) p_finalBossDamaged = false;

	if(!p_finalBossDamaged && time - p_finalBossShootTime > shootCool)
	{
		p_finalBossShootMode = !p_finalBossShootMode;
		p_finalBossShootTime = time;
		p_finalBossShootHitTime = time;
	}

	shooting = !p_finalBossDamaged && p_finalBossShootMode;

	if(shooting)
	{
		if(time - p_finalBossShootHitTime > MMS2_FINALBOSSMINSHOTDURATION)
		{
			const double hit = PLEX_randomPercentage();

			if(hit < 0.75)
			{
				const double damage = PLEX_randomNumber(0.001, 0.0025);

				PLEX_doScreenEffect(PLEX_SCREENEFFECT_TINTFADE, 255, 0, 0, 200, false, false, MMS2_SHOTDURATION, 0.5, time);

				MMS2_decrementHealth(damage);

				MMS2_setPlayerShotTime(time);
			}

			p_finalBossShootHitTime = time;
		}
	}

	if(p_finalBossMove != 2 && !direction)
	{
		if(p_finalBossMove < p_finalBossPlace) direction = 1;
		if(p_finalBossMove > p_finalBossPlace) direction = 2;
	}

	PLEX_drawSpriteTinted(MMS2_DRAWLAYER_FINALBOSS, direction + (3 * shooting), dr.origin.x, dr.origin.y, dr.dimens.w, dr.dimens.h, 255, g, b, p_finalBossSprite, true, time);

	if(p_finalBossRect.origin.x + p_finalBossRect.dimens.w > PLEX_WIDTHUNITMAX(true))
	{
		p_finalBossRect.origin.x = PLEX_WIDTHUNITMAX(true) - p_finalBossRect.dimens.w;
		p_finalBossPlace = 1;
		endMove = true;
	}

	if(p_finalBossRect.origin.x < 0)
	{
		p_finalBossRect.origin.x = 0;
		p_finalBossPlace = -1;
		endMove = true;
	}

	if(p_finalBossDamaged) return false;

	if(MMS2_playerIsShooting(time) && PLEX_rectCollisionNoMove(MMS2_shotArea(), dr))
	{
		MMS_MINIGAME2GUN* gun = MMS2_selectedGun();

		double damage = gun->outerDamage;

		if(PLEX_rectCollisionNoMove(MMS2_innerShotArea(), dr)) damage += gun->innerDamage;

		if(p_finalBossHealth > damage)
		{
			p_finalBossHealth -= damage;
		}else{
			p_finalBossHealth = 0;
			p_finalBossExplosionLoopSE = -1;
			MMS2_markFinalBossDead();
			return true;
		}

		p_finalBossDamageTime = time;
		return false;
	}

	p_finalBossDamageTime = 0;

	switch(p_finalBossMove)
	{
		case -1:
			endMove = p_finalBossRect.origin.x < p_finalBossRect.dimens.w * 0.25;
		break;

		case 0:
			endMove = (p_finalBossRect.origin.x < PLEX_WIDTHUNITMAX(true)/2 - p_finalBossRect.dimens.w/2 && p_finalBossPlace == 1) || (p_finalBossRect.origin.x + p_finalBossRect.dimens.w > PLEX_WIDTHUNITMAX(true)/2 + p_finalBossRect.dimens.w/2 && p_finalBossPlace == -1);
		break;

		case 1:
			endMove = p_finalBossRect.origin.x + p_finalBossRect.dimens.w * 2 > PLEX_WIDTHUNITMAX(true);
		break;
	};

	if(endMove)
	{
		switch(p_finalBossMove)
		{
			case -1:
				p_finalBossRect.origin.x = 0;
			break;

			case 0:
				p_finalBossRect.origin.x = PLEX_WIDTHUNITMAX(true)/2 - p_finalBossRect.dimens.w/2;
			break;

			case 1:
				p_finalBossRect.origin.x = PLEX_WIDTHUNITMAX(true) - p_finalBossRect.dimens.w;
			break;
		};

		p_finalBossPlace = p_finalBossMove;
		p_finalBossLastMove = time;
		p_finalBossMove = 2;
	}

	switch(direction)
	{
		case 1:
			p_finalBossRect.origin.x -= velocity * secondsPass;
		break;

		case 2:
			p_finalBossRect.origin.x += velocity * secondsPass;
		break;
	};

	if((p_finalBossLastMove && time - p_finalBossLastMove > thinkTime))
	{
		switch(p_finalBossPlace)
		{
			case 0:
				if(PLEX_randomNumber(0, 10) <= 5) p_finalBossMove = -1;
				else p_finalBossMove = 1;
			break;

			default:
				p_finalBossMove = 0;
			break;
		};

		p_finalBossLastMove = 0;
	}

	if(time - p_finalBossDropBoxTime > dropBoxDuration)
	{
		int64_t create = -1;

		MMS_MINIGAME2FINALBOSSDROPBOX* newBox = NULL;

		for(size_t ze = 0; ze < p_finalBossDropBoxCount; ++ze)
		{
			MMS_MINIGAME2FINALBOSSDROPBOX* box = p_finalBossDropBoxes + ze;

			if(!box->active)
			{
				create = ze;
				break;
			}
		}

		if(p_finalBossDropBoxCount < MMS2_FINALBOSSDROPBOXCOUNT)
		{
			create = p_finalBossDropBoxCount;
			++p_finalBossDropBoxCount;
		}

		if(create >= 0)
		{
			newBox = p_finalBossDropBoxes + create;

			memset(newBox, 0, sizeof(MMS_MINIGAME2FINALBOSSDROPBOX));

			newBox->active = true;
			newBox->point = p_finalBossRect.origin;

			newBox->endPoint = PLEX_convPoint(PLEX_randomNumber(2, PLEX_WIDTHUNITMAX(true) - 2), PLEX_randomNumber(8, 15));

			newBox->maxDistance = newBox->endPoint.x < p_finalBossRect.origin.x ? p_finalBossRect.origin.x - newBox->endPoint.x : newBox->endPoint.x -  p_finalBossRect.origin.x;

			newBox->isCover = PLEX_randomNumber(0, 10) < coverBoxDensity;

			if(newBox->isCover) newBox->index = PLEX_randomNumber(0, 14);
			else newBox->index = PLEX_randomNumber(0, 5);
		}

		p_finalBossDropBoxTime = time;
	}

	lastTime = time;

	return false;
}

void MMS2_markFinalBossActive(){ p_activateFinalBoss = true; }
void MMS2_markFinalBossDead(){ p_activateFinalBoss = false; }

void MMS2_markFinalBossOutroCut(){ p_beginFinalBossOutroCut = true; }
void MMS2_unmarkFinalBossOutroCut(){ p_beginFinalBossOutroCut = false; }

void MMS2_setBossOutroTimeMarker(const uint64_t time){ p_beginFinalBossOutroTime = time; }

void MMS2_playFinalBossOutroTheme()
{
	int64_t harpBuffer = -1;
	int64_t harmonicaBuffer = -1;
	int64_t geetarBuffer = -1;
	int64_t organBuffer = -1;
	int64_t pianoBuffer = -1;

	PLEX_clearSoundPreloads();

	harpBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSOUTRO_HARPBUFFER);
	harmonicaBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSOUTRO_HARMONICABUFFER);
	geetarBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSOUTRO_GEETARBUFFER);
	organBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSOUTRO_ORGANBUFFER);
	pianoBuffer = PLEX_preloadSoundFile(MMS2_FILEPATH_FINALBOSSOUTRO_PIANOBUFFER);

	if(harpBuffer != -1 && PLEX_assignSoundBuffer(harpBuffer, 0)) PLEX_soundChannelOn(false, 0);
	if(harmonicaBuffer != -1 && PLEX_assignSoundBuffer(harmonicaBuffer, 1)) PLEX_soundChannelOn(false, 1);
	if(geetarBuffer != -1 && PLEX_assignSoundBuffer(geetarBuffer, 2)) PLEX_soundChannelOn(false, 2);
	if(organBuffer != -1 && PLEX_assignSoundBuffer(organBuffer, 3)) PLEX_soundChannelOn(false, 3);
	if(pianoBuffer != -1 && PLEX_assignSoundBuffer(pianoBuffer, 4)) PLEX_soundChannelOn(false, 4);
}

void MMS2_stopFinalBossOutroTheme()
{
	PLEX_soundChannelOff(0);
	PLEX_soundChannelOff(1);
	PLEX_soundChannelOff(2);
	PLEX_soundChannelOff(3);
}

bool MMS2_finalBossOutroCut(const uint64_t time)
{
	const double baseDuration = PLEX_DEF_disableAudio() ? MMS2_FINALBOSSOUTROCUTDURATIONNOSOUND : MMS2_FINALBOSSOUTROCUTDURATION;
	const double duration = time - p_beginFinalBossOutroTime;
	const double perc = duration/baseDuration;

	const double fallY = p_finalBossRect.origin.y + (PLEX_HEIGHTUNITMAX(true) - p_finalBossRect.dimens.h - p_finalBossRect.origin.y) * perc;

	const PLEX_RECT levineFall = PLEX_convRect(PLEX_convPoint(p_finalBossRect.origin.x, fallY), p_finalBossRect.dimens);

	const bool tiltRight = ((uint32_t)duration/500 % 2) == 1;

	MMS2_clearEnemyCount();
	MMS2_clearCoverCount();

	if(perc >= 1 && perc < 1.1)
	{
		PLEX_drawSprite(MMS2_DRAWLAYER_FINALBOSSEXPLOSION, 0, 0, 0, PLEX_WW(true), PLEX_WH(true), p_finalBossExplosionSprite, true, time);
		MMS2_stopFinalBossOutroTheme();
		if(p_finalBossExplosionLoopSE == -1) p_finalBossExplosionLoopSE = MM_COMMON_loopSoundEffect(MM_COMMON_SOUNDEFFECT_EXPLOSIONLOOP);
		return true;
	}

	if(perc >= 1.1)
	{
		MM_COMMON_stopSoundEffect(p_finalBossExplosionLoopSE);
		p_finalBossExplosionLoopSE = -1;
		MMS2_unmarkFinalBossOutroCut();
		return false;
	}

	PLEX_drawSprite(MMS2_DRAWLAYER_FINALBOSSLEVINEFALLRIGHT, 1 + tiltRight, PLEX_UNIT(levineFall.origin.x + MMS2_leanX()), PLEX_UNIT(levineFall.origin.y + MMS2_leanY()), PLEX_UNIT(levineFall.dimens.w), PLEX_UNIT(levineFall.dimens.h), p_finalBossSprite, true, time);

	PLEX_drawSprite(MMS2_DRAWLAYER_FINALBOSSLEVINEFALLLEFT, 6, PLEX_UNIT(levineFall.origin.x + MMS2_leanX()), PLEX_UNIT(levineFall.origin.y + MMS2_leanY()), PLEX_UNIT(levineFall.dimens.w), PLEX_UNIT(levineFall.dimens.h), p_finalBossSprite, true, time);

	return true;
}

bool MMS2_levineFight(){ return p_levineFight; }
bool MMS2_beginFinalBossIntro(){ return p_beginFinalBossIntroCut; }
bool MMS2_activateFinalBoss(){ return p_activateFinalBoss; }
bool MMS2_beginFinalBossOutro(){ return p_beginFinalBossOutroCut; }
