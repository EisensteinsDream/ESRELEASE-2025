#include "minigame/minigame0/minigame0.h"

static PLEX_SPRITE* p_enemySprite = NULL;

static bool p_anyEnemyDrinking = false;

static MMS0_ENEMY p_enemies[MMS0_ENEMY_MAX];
static size_t p_enemyCount = 0, p_enemiesUsed = 0, p_enemiesKilled = 0, p_enemyCapacity = 0;
static uint8_t p_lastEnemySpot = 0;

static int64_t p_gulpEffect = -1;

static void p_generateEnemy()
{
	size_t index = p_enemyCapacity;

	MMS0_ENEMY* enemy = NULL;

	if(p_enemyCount >= MMS0_ENEMY_STOPGEN) return;

	for(size_t ze = 0; ze < p_enemyCapacity; ++ze)
	{
		enemy = p_enemies + ze;

		if(enemy->dead) // < dead enemies are replaced by new enemies
		{
			index = ze;
			break;
		}
	}

	if(index >= MMS0_ENEMY_MAX) return;

	enemy = p_enemies + index;

	memset(enemy, 0, sizeof(MMS0_ENEMY));

	enemy->vert = true;
	enemy->direction = MMS0_DIRECTION_UP;

	switch(p_lastEnemySpot)
	{
		case 0: enemy->rect.origin.x = MMS0_ENEMY_SPOT1_X; enemy->rect.origin.y = MMS0_ENEMY_SPOT_Y; break;
		case 1: enemy->rect.origin.x = MMS0_ENEMY_SPOT2_X; enemy->rect.origin.y = MMS0_ENEMY_SPOT_Y; break;
		case 2: enemy->rect.origin.x = MMS0_ENEMY_SPOT3_X; enemy->rect.origin.y = MMS0_ENEMY_SPOT_Y; break;
	}

	enemy->rect.dimens.w = MMS0_ENEMY_HEIGHT;
	enemy->rect.dimens.h = MMS0_ENEMY_WIDTH;

	++p_enemiesUsed;
	++p_enemyCount;

	if(index == p_enemyCapacity) ++p_enemyCapacity;

	p_lastEnemySpot = (p_lastEnemySpot + 1) % MMS0_ENEMY_SPOTCOUNT;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS0_startEnemyValues()
{
	p_enemyCount = 0;
	p_enemiesUsed = 0;
	p_enemiesKilled = 0;
	p_enemyCapacity = 0;

	p_gulpEffect = -1;
}

void MMS0_createEnemySprite(const size_t chapter0spriteTex, const uint64_t time)
{
	PLEX_ANIMATION* enemyAnimDown = NULL;
	PLEX_ANIMATION* enemyAnimUp = NULL;
	PLEX_ANIMATION* enemyAnimLeft = NULL;
	PLEX_ANIMATION* enemyAnimRight = NULL;

	PLEX_ANIMATION* enemyAnimDrink = NULL;

	PLEX_ANIMATION_PLATE enemyPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0spriteTex);

	if(p_enemySprite != NULL) return;

	p_enemySprite = PLEX_genSprite(&enemyPlate);

	PLEX_addAnimation(p_enemySprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_enemySprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_enemySprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_enemySprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_enemySprite, 2000, PLEX_getGameTime());

	enemyAnimUp = PLEX_getAnimation(0, p_enemySprite);
	enemyAnimRight = PLEX_getAnimation(1, p_enemySprite);
	enemyAnimDown = PLEX_getAnimation(2, p_enemySprite);
	enemyAnimLeft = PLEX_getAnimation(3, p_enemySprite);
	enemyAnimDrink = PLEX_getAnimation(4, p_enemySprite);

	PLEX_addAnimationFrame(41, enemyAnimUp);
	PLEX_addAnimationFrame(42, enemyAnimUp);
	PLEX_addAnimationFrame(43, enemyAnimUp);
	PLEX_addAnimationFrame(44, enemyAnimUp);
	PLEX_addAnimationFrame(45, enemyAnimUp);

	PLEX_addAnimationFrame(46, enemyAnimRight);
	PLEX_addAnimationFrame(47, enemyAnimRight);
	PLEX_addAnimationFrame(48, enemyAnimRight);
	PLEX_addAnimationFrame(49, enemyAnimRight);

	PLEX_addAnimationFrame(50, enemyAnimDown);
	PLEX_addAnimationFrame(51, enemyAnimDown);
	PLEX_addAnimationFrame(52, enemyAnimDown);
	PLEX_addAnimationFrame(53, enemyAnimDown);
	PLEX_addAnimationFrame(54, enemyAnimDown);

	PLEX_addAnimationFrame(55, enemyAnimLeft);
	PLEX_addAnimationFrame(56, enemyAnimLeft);
	PLEX_addAnimationFrame(57, enemyAnimLeft);
	PLEX_addAnimationFrame(58, enemyAnimLeft);

	PLEX_addAnimationFrame(59, enemyAnimDrink);
	PLEX_addAnimationFrame(60, enemyAnimDrink);

	PLEX_startSprite(PLEX_getGameTime(), p_enemySprite);
}

static void p_checkEnemyGen(const double perc)
{
	size_t enemyExpectation = perc/0.125;

	if(!enemyExpectation) enemyExpectation = 1;

	if(p_enemiesUsed < enemyExpectation) p_generateEnemy();
}

static void p_checkGulpSE()
{
	if(p_anyEnemyDrinking)
	{
		if(p_gulpEffect == -1) p_gulpEffect = MM_COMMON_loopSoundEffect(MM_COMMON_SOUNDEFFECT_GULP);
	}else MMS0_stopGulpEffect();

	p_anyEnemyDrinking = false;
}

// enemies are killed when they collide with the table. In some instances, it takes more than collision. This prevents an enemy who hits the bottom of a table moving right or left from dying from it, for example.
void MMS0_killEnemy(const size_t index, const size_t tableIndex)
{
	const size_t tableDirec = MMS0_getTableDirec(tableIndex);

	const PLEX_RECT tableShape = MMS0_getTableSpace(tableIndex);

	MMS0_ENEMY* enemy = p_enemies + index;

	if(tableDirec == MMS0_DIRECTION_UP && enemy->rect.origin.y + enemy->rect.dimens.h >= tableShape.origin.y + tableShape.dimens.h) return;

	if(!enemy->dead)
	{
		enemy->dead = true;
		++p_enemiesKilled;
		--p_enemiesUsed;
		MM_COMMON_playSoundEffectVolume(1, MM_COMMON_SOUNDEFFECT_GROAN);

		if(index == p_enemyCapacity - 1 && p_enemyCapacity) --p_enemyCapacity;
	}
}

void MMS0_updateEnemy(const double enemyMomentum, PLEX_MPREC* emomXs, PLEX_MPREC* emomYs, const size_t index, const uint64_t timePass, const uint64_t time)
{
	const PLEX_RECT prizeRect = MMS0_prizeRect();

	MMS0_ENEMY* enemy = p_enemies + index;

	PLEX_MPREC* emomX = emomXs + index;
	PLEX_MPREC* emomY = emomYs + index;

	bool pushed = false;

	*emomX = 0;
	*emomY = 0;

	// if the prize is pushed then the enemy stops drinking
	if(MMS0_prizeDirection() != MMS0_DIRECTION_NONE) enemy->drinking = false;

	if(enemy->dead) return;

	// the enemy cannot move on his own while being pushed
	if(MMS0_isPlayerPushing())
	{
		const size_t playerDirection = MMS0_getPlayerDirection();

		if(PLEX_rectCollision(enemy->rect, MMS0_getPlayerPushRect(), 0, 0))
		{
			MM_COMMON_playSoundEffectVolume(1, MM_COMMON_SOUNDEFFECT_QUICKGROAN);

			switch(playerDirection)
			{
				case MMS0_DIRECTION_UP: *emomY = 0 - MMSO_ENEMY_PUSHSPEED; break;
				case MMS0_DIRECTION_RIGHT: *emomX = MMSO_ENEMY_PUSHSPEED; break;
				case MMS0_DIRECTION_DOWN: *emomY = MMSO_ENEMY_PUSHSPEED; break;
				case MMS0_DIRECTION_LEFT: *emomX = 0 - MMSO_ENEMY_PUSHSPEED; break;
			};

			pushed = true;

			enemy->drinking = false;
		}
	}

	if(!pushed)
	{
		if(enemy->drinking)
		{
			enemy->rect.origin.x = prizeRect.origin.x + MMS0_ENEMY_DRINKDIST + prizeRect.dimens.w/2; // < enemy is fixed to 'the prize' while drinking

			p_anyEnemyDrinking = true; // < needed for the drinking sound effect, so it doesn't play in duplicate.
			MMS0_factorCoffeeDrink(PLEX_getGameSecondsPassed());
			enemy->direction = MMS0_DIRECTION_NONE;
		}else{
			if(enemy->rect.origin.y + enemy->rect.dimens.h < MMS0_ENEMY_ENEMYDRINKLINE) enemy->vert = false; // enemy cannot move up past the 'enemy drink line'

			// enemy will move right or left whatever direction towards the prize. Vert may also change outside this if the enemy hits a table. Enemy will go up if vert is true. Right or left towards the direction of 'the prize' if it is false.
			if(!enemy->vert)
			{
				if(enemy->rect.origin.x + enemy->rect.dimens.w < prizeRect.origin.x) enemy->direction = MMS0_DIRECTION_RIGHT;
				else if(enemy->rect.origin.x > prizeRect.origin.x + prizeRect.dimens.w) enemy->direction = MMS0_DIRECTION_LEFT;
				else
				{
					enemy->direction = MMS0_DIRECTION_UP;
					enemy->vert = true;
				}
			}else enemy->direction = MMS0_DIRECTION_UP;

			switch(enemy->direction)
			{
				case 0: *emomY -= enemyMomentum; break;
				case 1: *emomX += enemyMomentum; break;
				case 3: *emomX -= enemyMomentum; break;
			};
		}
	}

	PLEX_drawSprite(MMS0_drawLayer(enemy->rect), enemy->direction, PLEX_UNIT(enemy->rect.origin.x), PLEX_UNIT(enemy->rect.origin.y), PLEX_UNIT(enemy->rect.dimens.w), PLEX_UNIT(enemy->rect.dimens.h), p_enemySprite, true, time);
}

void MMS0_updateAllEnemies(const double perc) // also updates enemy generation
{
	p_checkEnemyGen(perc);
	p_checkGulpSE();
}

void MMS0_moveEnemy(const size_t index, const PLEX_MPREC moveX, const PLEX_MPREC moveY)
{
	MMS0_ENEMY* enemy = p_enemies + index % MMS0_ENEMY_MAX;

	enemy->rect.origin.x += moveX;
	enemy->rect.origin.y += moveY;
}

void MMS0_stopGulpEffect()
{
	MM_COMMON_stopSoundEffect(p_gulpEffect);
	p_gulpEffect = -1;
}

void MMS0_setVert(const size_t index){ p_enemies[index % MMS0_ENEMY_MAX].vert = true; }

void MMS0_setHorz(const size_t index){ p_enemies[index % MMS0_ENEMY_MAX].vert = false; }

void MMS0_setDrinking(const size_t index){ p_enemies[index % MMS0_ENEMY_MAX].drinking = true; }

void MMS0_freeEnemySprite(){ if(p_enemySprite != NULL) PLEX_destroySprite(&p_enemySprite); }

bool MMS0_enemyDead(const size_t index){ return p_enemies[index % MMS0_ENEMY_MAX].dead; }

size_t MMS0_enemiesKilled(){ return p_enemiesKilled; }

size_t MMS0_enemyCapacity(){ return p_enemyCapacity; }

PLEX_RECT MMS0_getEnemyRect(const size_t index){ return p_enemies[index % MMS0_ENEMY_MAX].rect; }

bool MMS0_enemyVert(const size_t index){ return p_enemies[index % MMS0_ENEMY_MAX].vert; }
