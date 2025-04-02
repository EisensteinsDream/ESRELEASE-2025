#include "minigame/minigame2/minigame2.h"

static size_t p_enemyCount = 0, p_totalEnemyCount = 0, p_defeatedEnemyCount = 0;
static MMS_MINIGAME2ENEMY p_enemies[MMS2_ENEMYCOUNT];

static MMS_MINIGAME2ENEMY p_enemyGens[MMS2_ENEMYGENCOUNT];

// creates a new enemy based on stats

static MMS_MINIGAME2ENEMY p_createEnemy(const char* const name, const double health, const PLEX_RECT space, const double minMoveSpeed, const double maxMoveSpeed, const uint64_t thoughtDelay, const uint64_t shotDuration, const uint64_t shotMax, const uint64_t reloadDuration, const double damagePotential, const double accuracyPotential, const size_t pointGain, const double treasureChance, const double likelyCashTreasure, const double likelyHealthTreasure, const double cashTreasureAmount, MMS_F_AIPATTERN aiPattern, const size_t startImage, PLEX_ANIMATION_PLATE animPlate, const uint64_t time)
{
	MMS_MINIGAME2ENEMY ret;

	ret.name = PLEX_createString25(name);
	ret.health = health;
	ret.space = space;
	ret.adaptSpace = space;
	ret.aiPattern = aiPattern;

	ret.damagePotential = damagePotential;
	ret.accuracyPotential = accuracyPotential;

	ret.speedPerc = 0.5;

	ret.pointGain = pointGain;

	ret.minMoveSpeed = minMoveSpeed;
	ret.maxMoveSpeed = maxMoveSpeed;

	ret.thoughtDelay = thoughtDelay;

	ret.treasureChance = treasureChance;
	ret.likelyCashTreasure = likelyCashTreasure;
	ret.likelyHealthTreasure = likelyHealthTreasure;
	ret.cashTreasureAmount = cashTreasureAmount;

	ret.shootDuration = shotDuration;
	ret.shotMax = shotMax;
	ret.shotCount = shotMax;

	ret.reloadDuration = reloadDuration;
	ret.reloadTime = 0;

	ret.phase = MMS_MINIGAME2ENEMYPHASE_STANDING;

	ret.aniIndex = 0;

	ret.birthTime = time;
	ret.lastActionTime = time;
	ret.phaseCheckTime = time;

	ret.lastHitTime = 0;
	ret.lastShotTime = 0;

	ret.rollStart = 0;
	ret.diveStart = 0;
	ret.shootTime = 0;

	ret.startImage = startImage;
	ret.sprite = PLEX_genSprite(&animPlate);

	ret.closestCover = -1;
	ret.coverDistance = -1;

	ret.tex = PLEX_animationPlateTex(animPlate);
	ret.wperc = PLEX_animationPlateWPerc(animPlate);
	ret.hperc = PLEX_animationPlateHPerc(animPlate);

	return ret;
}

// checks whether or not an enemy is active

static bool p_enemyActive(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = NULL;

	if(index >= p_enemyCount) return false;

	enemy = p_enemies + index;

	if(enemy->reloadTime) return false;

	if(enemy->rollStart && time - enemy->rollStart < MMS2_ROLLDURATION) return false;

	if(enemy->diveStart && time - enemy->diveStart < PLEX_spriteCycleLen(8, enemy->sprite)) return false;

	return enemy->phase != MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE && enemy->phase != MMS_MINIGAME2ENEMYPHASE_NODROPIPNGTREASURE && enemy->phase != MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED && enemy->phase != MMS_MINIGAME2ENEMYPHASE_DEAD;
}

// updates the enemy based on it's current phase

static void p_enemyUpdatePhase(MMS_MINIGAME2ENEMY* enemy, const uint64_t time)
{
	switch(enemy->phase)
	{
		case MMS_MINIGAME2ENEMYPHASE_STANDING:
			if(!enemy->shootTime) enemy->aniIndex = 0;
			else
			{
				switch(enemy->shootDirec)
				{
					case 0: enemy->aniIndex = 13; break;
					case 1: enemy->aniIndex = 14; break;
					case 2: enemy->aniIndex = 15; break;
				};
			}
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVELEFT:
			if(!enemy->shootTime) enemy->aniIndex = 1;
			else enemy->aniIndex = 16;
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVERIGHT:
			if(!enemy->shootTime) enemy->aniIndex = 2;
			else enemy->aniIndex = 17;
		break;

		case MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE:
			enemy->aniIndex = 3;
			enemy->shootTime = 0;
		break;

		case MMS_MINIGAME2ENEMYPHASE_NODROPIPNGTREASURE:
		case MMS_MINIGAME2ENEMYPHASE_DEAD:
			enemy->aniIndex = 4;
			enemy->shootTime = 0;
		break;

		case MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED:
			enemy->aniIndex = 5;
			enemy->shootTime = 0;
		break;

		case MMS_MINIGAME2ENEMYPHASE_CROUCHING:
			if(!enemy->shootTime) enemy->aniIndex = 6;
			else
			{
				switch(enemy->shootDirec)
				{
					case 0: enemy->aniIndex = 20; break;
					case 1: enemy->aniIndex = 21; break;
					case 2: enemy->aniIndex = 22; break;
				};
			}
		break;

		case MMS_MINIGAME2ENEMYPHASE_ROLLLEFT:
			enemy->aniIndex = 7;
			enemy->shootTime = 0;

			enemy->rollStart = time;
		break;

		case MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT:
			enemy->aniIndex = 8;
			enemy->shootTime = 0;

			enemy->rollStart = time;
		break;

		case MMS_MINIGAME2ENEMYPHASE_DIVELEFT:
			if(!enemy->shootTime) enemy->aniIndex = 9;
			else enemy->aniIndex = 18;

			enemy->diveStart = time;
		break;

		case MMS_MINIGAME2ENEMYPHASE_DIVERIGHT:
			if(!enemy->shootTime) enemy->aniIndex = 10;
			else enemy->aniIndex = 19;

			enemy->diveStart = time;
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVEDOWN:
			enemy->aniIndex = 11;
			enemy->shootTime = 0;
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVEUP:
			enemy->aniIndex = 12;
			enemy->shootTime = 0;
		break;

		case MMS_MINIGAME2ENEMYPHASE_RELOADING:
			enemy->aniIndex = 23;
			enemy->reloadTime = time;
		break;

		default: break;
	};
}

// switches the enemy phase

static void p_enemyPhaseSwitch(const size_t index, const MMS_MINIGAME2ENEMYPHASE phase, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = NULL;

	if(index >= p_enemyCount) return;

	enemy = p_enemies + index;

	if(enemy->phase == phase) return;

	enemy->rollStart = 0;
	enemy->diveStart = 0;

	if(!enemy->shotCount) enemy->shootTime = 0;

	enemy->phase = phase;

	p_enemyUpdatePhase(enemy, time);
}

// switches the enemy phase - passively (ie. only if other phases are a certain way)

static void p_enemyPhaseSwitchPassive(const size_t index, const MMS_MINIGAME2ENEMYPHASE phase, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(!p_enemyActive(index, time) || time - enemy->lastActionTime < enemy->thoughtDelay) return;

	p_enemyPhaseSwitch(index, phase, time);

	enemy->lastActionTime = time;
}

// switches an enemy phase - forcefully (ignores everything and forces the phase to change)

static void p_enemyPhaseSwitchNonPassive(const size_t index, const MMS_MINIGAME2ENEMYPHASE phase, const uint64_t time)
{
	p_enemyPhaseSwitch(index, phase, time);
}

// returns the enemy phase at index

static MMS_MINIGAME2ENEMYPHASE p_getEnemyPhase(const size_t index)
{
	const MMS_MINIGAME2ENEMY* enemy = NULL;

	if(index >= p_enemyCount) return MMS_MINIGAME2ENEMYPHASE_NONE;

	enemy = p_enemies + index;

	return enemy->phase;
}

// tells the enemy at index to start shooting

static void p_enemyStartShoot(const size_t index, const uint8_t shootDirec, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = NULL;

	if(index >= p_enemyCount) return;

	enemy = p_enemies + index;

	if(!enemy->shotCount) return;

	if(enemy->shootTime)
	{
		if(shootDirec != enemy->shootDirec) enemy->shootDirec = shootDirec;
		return;
	}

	if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVEUP || enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVEDOWN || enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLLEFT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_DEAD || enemy->phase == MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE || enemy->phase == MMS_MINIGAME2ENEMYPHASE_NODROPIPNGTREASURE || enemy->phase == MMS_MINIGAME2ENEMYPHASE_RELOADING)
	{
		enemy->shootTime = 0;
		return;
	}else{
		if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVERIGHT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVERIGHT) enemy->shootDirec = 2;
		else{
			if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVELEFT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVELEFT) enemy->shootDirec = 0;
			else enemy->shootDirec = shootDirec % 3;
		}
	}

	enemy->shootTime = time;

	p_enemyUpdatePhase(enemy, time);
}

// pulls a generated enemy from the room's enemy generator

static void p_pullGenEnemy(const size_t index, const double x, const double y, MMS_F_AIPATTERN aiPattern, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* newEnemy = NULL;

	if(p_enemyCount >= MMS2_ENEMYCOUNT) return;

	if(index >= MMS2_ENEMYGENCOUNT)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONPULLENEMYGEN, MMS2_ERRORMESS_ENEMYCOUNT);
		return;
	}

	newEnemy = p_enemies + p_enemyCount;

	*newEnemy = p_enemyGens[index];

	newEnemy->space.origin = PLEX_convPoint(x, y);

	newEnemy->aiPattern = aiPattern;

	MMS2_setEnemySprite(newEnemy->startImage, newEnemy, time);

	MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_COWBOYBIRTH);

	++p_enemyCount;
	++p_totalEnemyCount;
}

// updates the enemy generator, checking to see whether new enemy should be generated

static void p_checkEnemyGenerator(const uint64_t time)
{
	double x = 0;
	double y = 0;

	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = MMS2_currentEnemyGenerator();

	if(enemGenerator == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONCHECKENEMYGENERATOR, MMS2_ERRORMESS_ENEMYGENERATOR);
		return;
	}

	if(enemGenerator->contents == NULL) return;

	PLEX_updateGenerator(enemGenerator->contents, time);

	if(p_enemyCount >= MMS2_ENEMYCOUNT) return;

	while(PLEX_generatedCount(*enemGenerator->contents) > p_enemyCount && p_totalEnemyCount < enemGenerator->start + enemGenerator->max)
	{
		const size_t patternIndex = PLEX_randomNumber(0, enemGenerator->aiPatternCount);

		const size_t typeIndex = PLEX_randomNumber(0, enemGenerator->typeCount);

		MMS_MINIGAME2AIPATTERNCONTAINER aiPattern;

		size_t type = 0;

		if(!PLEX_pullGenerated(p_enemyCount, time, &x, &y, enemGenerator->contents)) break;

		aiPattern = enemGenerator->aiPatterns[patternIndex];

		type = enemGenerator->generatorTypes[typeIndex];

		p_pullGenEnemy(type, x, y, aiPattern.contents, time);
	}
}

// sets the enemy movement speed percentage (for example to distinguish walking and running)

static void p_setEnemySpeedPerc(const size_t index, const double perc)
{
	MMS_MINIGAME2ENEMY* enemy = NULL;

	double lPerc = perc;

	if(index > p_enemyCount) return;

	enemy = p_enemies + index;

	if(lPerc < 0) lPerc = 0;
	if(lPerc > 1) lPerc = 1;

	enemy->speedPerc = lPerc;
}

// factors in whether or not the enemy is shooting the player

static void p_factorShootPlayer(MMS_MINIGAME2ENEMY* enemy, const uint64_t time)
{
	const double accuracyPerc = PLEX_randomPercentage();

	double lAccuracyPerc = enemy->accuracyPotential;
	double lDamagePerc = enemy->damagePotential;

	double modify = 1;

	if(enemy->shootDirec == 0 && (MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT) ||  MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT))) modify = 0.75;

	if(enemy->shootDirec == 1 && (MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT))) modify = 0.75;

	if(enemy->shootDirec == 2 && ( MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT))) modify = 0.75;

	if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_CROUCHING && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCH) &&  !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT)) modify *= 0.75;

	if(enemy->phase != MMS_MINIGAME2ENEMYPHASE_CROUCHING && (MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCH) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT))) modify *= 0.75;

	lAccuracyPerc *= modify;
	lDamagePerc *= modify;

	if(lAccuracyPerc < accuracyPerc){
		MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_SHOTMISS);
	}else{
		MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_SMALLSHOT);

		PLEX_doScreenEffect(PLEX_SCREENEFFECT_TINTFADE, 255, 0, 0, 200, false, false, MMS2_SHOTDURATION, 0.5, time);

		MMS2_setPlayerShotTime(time);

		MMS2_decrementHealth(lDamagePerc);
	}
}

// factors the phase and it's aspects for enemy at 'index'

static void p_factorPhase(const size_t index, const bool passive, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = NULL;

	double secondsPass = 0;

	double momentumX = 0;
	double momentumY = 0;

	PLEX_RECT newSpace;

	if(index >= p_enemyCount) return;

	enemy = p_enemies + index;

	secondsPass = (time - enemy->phaseCheckTime)/1000.0;

	enemy = p_enemies + index;

	switch(enemy->phase)
	{
		case MMS_MINIGAME2ENEMYPHASE_MOVELEFT:
			if(passive) momentumX = 0 - (enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * enemy->speedPerc);
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVERIGHT:
			if(passive) momentumX = enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * enemy->speedPerc;
		break;

		case MMS_MINIGAME2ENEMYPHASE_ROLLLEFT:
			momentumX = 0 - (enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * 0.1);
		break;

		case MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT:
			momentumX = enemy->minMoveSpeed + ((enemy->maxMoveSpeed - enemy->minMoveSpeed) * 0.1);
		break;

		case MMS_MINIGAME2ENEMYPHASE_DIVELEFT:
			momentumX = 0 - (enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * 0.1);
		break;

		case MMS_MINIGAME2ENEMYPHASE_DIVERIGHT:
			momentumX = enemy->minMoveSpeed + ((enemy->maxMoveSpeed - enemy->minMoveSpeed) * 0.1);
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVEDOWN:
			if(passive) momentumY = enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * enemy->speedPerc;
		break;

		case MMS_MINIGAME2ENEMYPHASE_MOVEUP:
			if(passive) momentumY = 0 - (enemy->minMoveSpeed + (enemy->maxMoveSpeed - enemy->minMoveSpeed) * enemy->speedPerc);
		break;

		default: return;
	};

	newSpace = enemy->space;

	newSpace.origin.x = enemy->space.origin.x + momentumX * secondsPass;
	newSpace.origin.y = enemy->space.origin.y + momentumY * secondsPass;

	if(newSpace.origin.x > -4 && newSpace.origin.x + newSpace.dimens.w < PLEX_WIDTHUNITMAX() + 4 && newSpace.origin.y + newSpace.dimens.h > PLEX_HEIGHTUNITMAX()/4 && newSpace.origin.y + newSpace.dimens.h < PLEX_HEIGHTUNITMAX() - 4)
	{
		enemy->space = newSpace;
	}else{
		if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVELEFT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVERIGHT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLLEFT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_CROUCHING, time);
		else p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);
	}

	enemy->phaseCheckTime = time;
}

// ai function that tells the enemy to get into the closest margin

static bool p_aiSeekMargins(const bool roll, MMS_MINIGAME2ENEMY* enemy, const size_t index, const double speedPerc, const uint64_t time)
{
	const MMS_MINIGAME2ENEMYPHASE left = roll ? MMS_MINIGAME2ENEMYPHASE_ROLLLEFT : MMS_MINIGAME2ENEMYPHASE_MOVELEFT;
	const MMS_MINIGAME2ENEMYPHASE right = roll ? MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT : MMS_MINIGAME2ENEMYPHASE_MOVERIGHT;

	if(enemy->space.origin.x + enemy->space.dimens.w * 1.5 < 0) return false;
	if(enemy->space.origin.x - enemy->space.dimens.w/2 > PLEX_WIDTHUNITMAX(true)) return false;

	if(enemy->space.origin.x < PLEX_WIDTHUNITMAX(true)/2) p_enemyPhaseSwitchPassive(index, left, time);
	else p_enemyPhaseSwitchPassive(index, right, time);

	return true;
}

// the base ai function that tells the enemy to get to the closest cover

static bool p_aiSeekCoverBase(const MMS_MINIGAME2ENEMYPHASE rightPhase, const MMS_MINIGAME2ENEMYPHASE leftPhase, const double maxDistance, const double speedPerc, MMS_MINIGAME2ENEMY* enemy, const size_t index, const uint64_t time)
{
	const double ex = enemy->space.origin.x + enemy->space.dimens.w/2;
	const double ey = enemy->space.origin.y + enemy->space.dimens.h * 0.95;

	double irx = 0;
	double iry = 0;
	double irw = 0;
	double irh = 0;

	PLEX_MPREC lenX = 0;
	PLEX_MPREC lenY = 0;
	PLEX_MPREC distance = 0;

	MMS_MINIGAME2COVER* cover = NULL;

	MMS_MINIGAME2ENEMYPHASE phase = MMS_MINIGAME2ENEMYPHASE_NONE;

	if(enemy->closestCover == -1) return false;

	cover = MMS2_cover(enemy->closestCover);

	irx = cover->space.origin.x + cover->space.dimens.w * 0.05;
	iry = cover->space.origin.y;
	irw = cover->space.dimens.w * 0.9;
	irh = cover->space.dimens.h * 0.95;

	distance = PLEX_distance(PLEX_convPoint(ex, ey), PLEX_convPoint(irx + irw/2, iry + irh/2), &lenX, &lenY);

	if(distance < 4)
	{
		enemy->space.origin.x = irx + irw/2 - enemy->space.dimens.w/2;
		enemy->space.origin.y = iry + irh/2 - enemy->space.dimens.h * 0.9;
		enemy->coverLocked = true;
		return false;
	}

	if(ex < irx)
	{
		phase = rightPhase;
	}else if(ex > irx + irw){
		phase = leftPhase;
	}else if(ey > iry + irh){
		phase = MMS_MINIGAME2ENEMYPHASE_MOVEUP;

		// cheap way to prevent a weird bug that has enemies endlessly move upward in place and not shoot
		if(PLEX_rectCollisionNoMove(enemy->space, cover->space))
		{
			enemy->space.origin.x = irx + irw/2 - enemy->space.dimens.w/2;
			enemy->space.origin.y = iry + irh/2 - enemy->space.dimens.h * 0.9;
			enemy->coverLocked = true;
			return false;
		}
	}else if(ey < iry){
		phase = MMS_MINIGAME2ENEMYPHASE_MOVEDOWN;

		// cheap way to prevent a weird bug that has enemies endlessly move upward in place and not shoot
		if(PLEX_rectCollisionNoMove(enemy->space, cover->space))
		{
			enemy->space.origin.x = irx + irw/2 - enemy->space.dimens.w/2;
			enemy->space.origin.y = iry + irh/2 - enemy->space.dimens.h * 0.9;
			enemy->coverLocked = true;
			return false;
		}
	}else return false;

	p_setEnemySpeedPerc(index, speedPerc);

	p_enemyPhaseSwitchPassive(index, phase, time);

	return true;
}

// the function that tells the enemy to seek the closest cover

static bool p_aiSeekCover(const bool roll, const bool dive, const double maxDistance, const double speedPerc, MMS_MINIGAME2ENEMY* enemy, const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMYPHASE rightPhase = MMS_MINIGAME2ENEMYPHASE_MOVERIGHT;
	MMS_MINIGAME2ENEMYPHASE leftPhase = MMS_MINIGAME2ENEMYPHASE_MOVELEFT;

	if(roll)
	{
		rightPhase = MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT;
		leftPhase = MMS_MINIGAME2ENEMYPHASE_ROLLLEFT;
	}

	if(dive)
	{
		rightPhase = MMS_MINIGAME2ENEMYPHASE_DIVERIGHT;
		leftPhase = MMS_MINIGAME2ENEMYPHASE_DIVELEFT;
	}

	return p_aiSeekCoverBase(rightPhase, leftPhase, maxDistance, speedPerc, enemy, index, time);
}

// base function that tells the enemy to avoid the player's cursor

static bool p_aiSeekAvoidCursorBase(const MMS_MINIGAME2ENEMYPHASE rightPhase, const MMS_MINIGAME2ENEMYPHASE leftPhase, const double distance, const double speedPerc, MMS_MINIGAME2ENEMY* enemy, const size_t index, const uint64_t time)
{
	const PLEX_MPREC aDistance = PLEX_UNIT(distance);

	const PLEX_MPREC aX = PLEX_UNIT(enemy->space.origin.x + enemy->space.dimens.w);
	const PLEX_MPREC aY = PLEX_UNIT(enemy->space.origin.y + enemy->space.dimens.h);

	const PLEX_POINT pointA = PLEX_convPoint(aX, aY);
	const PLEX_POINT pointB = PLEX_convPoint(PLEX_MX(), PLEX_MY());

	PLEX_MPREC lenX = 0;
	PLEX_MPREC lenY = 0;

	PLEX_MPREC distance2 = 0;

	MMS_MINIGAME2ENEMYPHASE phase;

	distance2 = PLEX_distance(pointA, pointB, &lenX, &lenY);

	if(enemy->space.origin.x < 2)
	{
		phase = rightPhase;

		p_setEnemySpeedPerc(index, speedPerc);

		p_enemyPhaseSwitchPassive(index, phase, time);

		return true;
	}

	if(enemy->space.origin.x - enemy->space.dimens.w > PLEX_WIDTHUNITMAX(true) - 3)
	{
		phase = leftPhase;

		p_setEnemySpeedPerc(index, speedPerc);

		p_enemyPhaseSwitchPassive(index, phase, time);

		return true;
	}

	if(distance2 >= aDistance) return false;

	if(aX < PLEX_MX()) phase = leftPhase;
	else phase = rightPhase;

	p_setEnemySpeedPerc(index, speedPerc);

	p_enemyPhaseSwitchPassive(index, phase, time);

	return true;
}

// ai function that tells the enemy to avoid the cursor

static bool p_aiSeekAvoidCursor(const bool roll, const bool dive, const double distance, const double speedPerc, MMS_MINIGAME2ENEMY* enemy, const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMYPHASE rightPhase = MMS_MINIGAME2ENEMYPHASE_MOVERIGHT;
	MMS_MINIGAME2ENEMYPHASE leftPhase = MMS_MINIGAME2ENEMYPHASE_MOVELEFT;

	if(roll)
	{
		rightPhase = MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT;
		leftPhase = MMS_MINIGAME2ENEMYPHASE_ROLLLEFT;
	}

	if(dive)
	{
		rightPhase = MMS_MINIGAME2ENEMYPHASE_DIVERIGHT;
		leftPhase = MMS_MINIGAME2ENEMYPHASE_DIVELEFT;
	}

	return p_aiSeekAvoidCursorBase(rightPhase, leftPhase, distance, speedPerc, enemy, index, time);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemEnemy()
{
	p_enemyCount = 0;
	p_totalEnemyCount = 0;
	p_defeatedEnemyCount = 0;
}

void MMS2_initSystemEnemy(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time)
{
	PLEX_ANIMATION_PLATE enemPlate, enemPlate3, enemPlate4; // no need for an enem plate 2

	enemPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter2SpriteTex);
	// no enem plate 2
	enemPlate3 = PLEX_createAnimationPlate(0.125, 0.03125, chapter2SpriteTex3);
	enemPlate4 = PLEX_createAnimationPlate(0.125, 0.03125, chapter2SpriteTex4);

	// enemy generators

	// trail 0

	MMS2_placeEnemyGen(0, MMS2_LANGUAGE_TRAIL0_ENEMY0, 1, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 0.5, 10, 200, 750, 6, 10000, 0.005, 0.75, 50, 0.5, 0.5, 0.25, 10, 0, enemPlate, time);

	MMS2_placeEnemyGen(1, MMS2_LANGUAGE_TRAIL0_ENEMY1, 2, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 0.25, 14, 500, 750, 12, 15000, 0.01, 0.75, 100, 0.8, 0.5, 0.25, 25, 168, enemPlate, time);

	// trail 1

	MMS2_placeEnemyGen(2, MMS2_LANGUAGE_TRAIL0_ENEMY2, 2, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 0.25, 5, 1000, 2000, 3, 20000, 0.025, 0.65, 250, 0.25, 0.25, 0.25, 100, 96, enemPlate3, time);

	MMS2_placeEnemyGen(3, MMS2_LANGUAGE_TRAIL0_ENEMY3, 4, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 0.75, 20, 500, 500, 6, 7500, 0.015, 0.8, 125, 0.8, 0.75, 0.5, 200, 72, enemPlate4, time);

	// trail 2

	MMS2_placeEnemyGen(4, MMS2_LANGUAGE_TRAIL0_ENEMY4, 4, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 2, 30, 500, 1000, 14, 5000, 0.01, 1, 500, 0.75, 0.1, 0.25, 500, 168, enemPlate3, time);

	MMS2_placeEnemyGen(5, MMS2_LANGUAGE_TRAIL0_ENEMY5, 8, PLEX_convRect(PLEX_convPoint(10, 10), PLEX_convDimens(2, 3)), 1, 17, 500, 1000, 8, 10000, 0.04, 0.5, 1000, 1, 0.4, 0.6, 1000, 0, enemPlate4, time);
}

void MMS2_checkRunSystemEnemy(const bool coverHit, const PLEX_RECT coverRect, const double coverLayer, const double coverAbsorb, const uint64_t time)
{
	if(MMS2_currentRoomCalm()) return;

	uint32_t layer = 0;

	PLEX_POINT midPoint;

	for(size_t ze = 0; ze < p_enemyCount; ++ze)
	{
		const MMS_MINIGAME2ENEMYPHASE phase = p_getEnemyPhase(ze);

		MMS_MINIGAME2ENEMY* enemy = p_enemies + ze;

		PLEX_RECT dr;

		uint8_t r = 255;
		uint8_t g = 255;
		uint8_t b = 255;

		bool inactive = false;

		enemy->adaptSpace.origin.x = enemy->space.origin.x + MMS2_leanX();
		enemy->adaptSpace.origin.y = enemy->space.origin.y + MMS2_leanY();

		midPoint = PLEX_convPoint(enemy->space.origin.x + enemy->space.dimens.w/2, enemy->space.origin.y + enemy->space.dimens.h/2);

		dr.origin.x = PLEX_UNIT(enemy->adaptSpace.origin.x);
		dr.origin.y = PLEX_UNIT(enemy->adaptSpace.origin.y);
		dr.dimens.w = PLEX_UNIT(enemy->adaptSpace.dimens.w);
		dr.dimens.h = PLEX_UNIT(enemy->adaptSpace.dimens.h);

		layer = MMS2_getEnemyLayer(dr);

		if(phase == MMS_MINIGAME2ENEMYPHASE_DEAD) continue;

		if(phase == MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE || phase == MMS_MINIGAME2ENEMYPHASE_NODROPIPNGTREASURE)
		{
			if(MMS2_playerIsNotShooting(time))
			{
				uint32_t esw = 0;
				uint32_t esh = 0;

				if(phase == MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE)
				{
					const double tx = enemy->space.origin.x + enemy->space.dimens.w/2;
					const double ty = enemy->space.origin.y + enemy->space.dimens.h;

					if(PLEX_randomPercentage() < enemy->likelyCashTreasure) MMS2_addTreasureBoxCash(tx, ty, enemy->cashTreasureAmount);
					else
					{
						if(PLEX_randomPercentage() < enemy->likelyHealthTreasure) MMS2_addTreasureBoxHealth(tx, ty);
						else MMS2_addTreasureBoxAmmo(tx, ty);
					}
				}

				p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_DEAD, time);

				PLEX_textureWH(enemy->sprite->plate.base, &esw, &esh);

				if(esw && esh) MMS2_addGravesite(enemy->tex, enemy->startImage + 68, enemy->space, enemy->wperc, enemy->hperc, 0);

				continue;
			}

			inactive = true;
		}

		if(MMS2_playerIsNotShooting(time) && p_getEnemyPhase(ze) == MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED) p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_STANDING, time);

		if(!inactive)
		{
			enemy->coverLocked = false;

			if(MMS2_playerIsShooting(time))
			{
				if(enemy->phase != MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE && enemy->phase != MMS_MINIGAME2ENEMYPHASE_DEAD && enemy->phase != MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED && PLEX_rectCollisionNoMove(MMS2_shotArea(), dr))
				{
					const MMS_MINIGAME2GUN* const gun = MMS2_selectedGun();

					double damage = gun->outerDamage;

					bool covered = false;

					if(PLEX_rectCollisionNoMove(MMS2_innerShotArea(), dr)) damage += gun->innerDamage;

					covered = coverHit && coverLayer <= layer && PLEX_rectCollisionNoMove(coverRect, dr);

					if(!covered || coverAbsorb != 1)
					{
						damage *= coverAbsorb;

						if(enemy->health > damage)
						{
							enemy->health -= damage;
							enemy->lastShotTime = time;
							enemy->lastActionTime = time;

							MM_COMMON_playSoundEffect( MM_COMMON_SOUNDEFFECT_QUICKGROAN);

							p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED, time);

							MMS2_bloodSplatter(time);
						}else{
							if(PLEX_randomPercentage() < enemy->treasureChance) p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_DROPPINGTREASURE, time);
							else p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_NODROPIPNGTREASURE, time);

							MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_GROAN);

							MMS2_incrementPoints(enemy->pointGain);

							enemy->health = 0;

							++p_defeatedEnemyCount;
							continue;
						};
					}
				}
			}

			if(enemy->phase != MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED && enemy->reloadTime)
			{
				if(time - enemy->reloadTime > enemy->reloadDuration)
				{
					enemy->reloadTime = 0;
					enemy->shootTime = 0;
					enemy->shotCount = enemy->shotMax;

					p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_STANDING, time);
				}else{
					p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_RELOADING, time);
				}
			}

			if(enemy->shootTime)
			{
				if(enemy->space.origin.x < 0 && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT) && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT)) MMS2_drawEnemyOffscreenArrow(true);

				if(enemy->space.origin.x + enemy->space.dimens.w > PLEX_WIDTHUNITMAX(true) && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT) && !MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT)) MMS2_drawEnemyOffscreenArrow(false);

				if(time - enemy->shootTime > enemy->shootDuration)
				{
					--enemy->shotCount;
					enemy->shootTime = 0;

					p_factorShootPlayer(enemy, time);

					if(!enemy->shotCount) p_enemyPhaseSwitchNonPassive(ze, MMS_MINIGAME2ENEMYPHASE_RELOADING, time);
					else p_enemyUpdatePhase(enemy, time);
				}
			}
		}

		for(size_t uh = 0; uh < MMS2_coverCount(); ++uh)
		{
			PLEX_MPREC distance, distx = 0, disty = 0;

			PLEX_POINT comp;

			MMS_MINIGAME2COVER* cover = MMS2_cover(uh);

			if(!cover->health || cover->space.origin.x < -4 || cover->space.origin.x + cover->space.dimens.w > PLEX_WIDTHUNITMAX(true) || cover->space.origin.y + cover->space.dimens.h < 4 || cover->space.origin.y > PLEX_HEIGHTUNITMAX(true) - 4)
			{
				if(uh == enemy->closestCover) enemy->closestCover = -1;
				continue;
			}

			comp = PLEX_convPoint(cover->space.origin.x + cover->space.dimens.w/2, cover->space.origin.y + cover->space.dimens.h/2);

			distance = PLEX_distance(midPoint, comp, &distx, &disty);

			if(enemy->closestCover == -1 || distance < enemy->coverDistance)
			{
				enemy->closestCover = uh;
				enemy->coverDistance = distance;
			}
		}

		if(p_getEnemyPhase(ze) == MMS_MINIGAME2ENEMYPHASE_BEINGDAMAGED)
		{
			g = 0;
			b = 0;
		}

		PLEX_drawSpriteTinted(layer, enemy->aniIndex, dr.origin.x, dr.origin.y, dr.dimens.w, dr.dimens.h, r, g, b, enemy->sprite, true, time);

		if(time - enemy->diveStart > MMS2_ROLLDURATION && (enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_ROLLLEFT)) p_enemyPhaseSwitchPassive(ze, MMS_MINIGAME2ENEMYPHASE_CROUCHING, time);

		if(time - enemy->rollStart > PLEX_spriteCycleLen(8, enemy->sprite))
		{
			if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVELEFT) p_enemyPhaseSwitchPassive(ze, MMS_MINIGAME2ENEMYPHASE_ROLLLEFT, time);
			if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_DIVERIGHT) p_enemyPhaseSwitchPassive(ze, MMS_MINIGAME2ENEMYPHASE_ROLLRIGHT, time);
		}

		enemy->aiPattern(ze, time);

		p_factorPhase(ze, p_enemyActive(ze, time), time);

		// ensures enemies that are attached to a flying cover don't fly when becoming unattached
		if(!enemy->coverLocked && enemy->space.origin.y + enemy->space.dimens.h < 4) enemy->space.origin.y = 4 - enemy->space.dimens.h;
	}

	p_checkEnemyGenerator(time);
}

void MMS2_endSystemEnemy()
{
	MMS2_clearEnemySprites();
}

void MMS2_clearEnemySprites()
{
	for(size_t ze = 0; ze < MMS2_ENEMYGENCOUNT; ++ze)
	{
		MMS_MINIGAME2ENEMY* enemy = p_enemyGens + ze;

		if(enemy->sprite != NULL) PLEX_destroySprite(&enemy->sprite);
	}
}

void MMS2_setEnemySprite(const size_t startImage, struct MMS_MINIGAME2ENEMY* enemy, const uint64_t time)
{
	PLEX_ANIMATION* standing = NULL;

	PLEX_ANIMATION* walkLeft = NULL;
	PLEX_ANIMATION* walkRight = NULL;

	PLEX_ANIMATION* droppingTreasure = NULL;

	PLEX_ANIMATION* dead = NULL;

	PLEX_ANIMATION* damaged = NULL;

	PLEX_ANIMATION* crouching = NULL;

	PLEX_ANIMATION* rollLeft = NULL;
	PLEX_ANIMATION* rollRight = NULL;

	PLEX_ANIMATION* diveLeft = NULL;
	PLEX_ANIMATION* diveRight = NULL;

	PLEX_ANIMATION* walkDown = NULL;
	PLEX_ANIMATION* walkUp = NULL;

	PLEX_ANIMATION* standShootLeft = NULL;
	PLEX_ANIMATION* standShootMiddle = NULL;
	PLEX_ANIMATION* standShootRight = NULL;

	PLEX_ANIMATION* walkLeftShoot = NULL;
	PLEX_ANIMATION* walkRightShoot = NULL;

	PLEX_ANIMATION* diveLeftShoot = NULL;
	PLEX_ANIMATION* diveRightShoot = NULL;

	PLEX_ANIMATION* crouchShootLeft = NULL;
	PLEX_ANIMATION* crouchShootMiddle = NULL;
	PLEX_ANIMATION* crouchShootRight = NULL;

	PLEX_ANIMATION* reload = NULL;

	// standing

	PLEX_addAnimation(enemy->sprite, 1, time);

	// right anim

	PLEX_addAnimation(enemy->sprite, 1000, time);

	// left anim

	PLEX_addAnimation(enemy->sprite, 1000, time);

	// treasure drop

	PLEX_addAnimation(enemy->sprite, 1, time);

	// dead

	PLEX_addAnimation(enemy->sprite, 1, time);

	// damaged

	PLEX_addAnimation(enemy->sprite, 1, time);

	// crouching

	PLEX_addAnimation(enemy->sprite, 1, time);

	// roll left

	PLEX_addAnimation(enemy->sprite, 100, time);

	// roll right

	PLEX_addAnimation(enemy->sprite, 100, time);

	// dive left

	PLEX_addAnimation(enemy->sprite, 500, time);

	// dive right

	PLEX_addAnimation(enemy->sprite, 500, time);

	// move up

	PLEX_addAnimation(enemy->sprite, 1000, time);

	// move down

	PLEX_addAnimation(enemy->sprite, 1000, time);

	// stand shoot left

	PLEX_addAnimation(enemy->sprite, 250, time);

	// stand shoot middle

	PLEX_addAnimation(enemy->sprite, 250, time);

	// stand shoot right

	PLEX_addAnimation(enemy->sprite, 250, time);

	// walk left shoot

	PLEX_addAnimation(enemy->sprite, 500, time);

	// walk right shoot

	PLEX_addAnimation(enemy->sprite, 500, time);

	// dive left shoot

	PLEX_addAnimation(enemy->sprite, 250, time);

	// dive right shoot

	PLEX_addAnimation(enemy->sprite, 250, time);

	// crouch shoot left

	PLEX_addAnimation(enemy->sprite, 250, time);

	// crouch shoot middle

	PLEX_addAnimation(enemy->sprite, 250, time);

	// crouch shoot right

	PLEX_addAnimation(enemy->sprite, 250, time);

	// reloading

	PLEX_addAnimation(enemy->sprite, 250, time);

	// --------- ADD ANIMATION: ---------------------------

	standing = PLEX_getAnimation(0, enemy->sprite);

	PLEX_addAnimationFrame(startImage, standing);

	walkLeft = PLEX_getAnimation(1, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 1, walkLeft);
	PLEX_addAnimationFrame(startImage + 2, walkLeft);
	PLEX_addAnimationFrame(startImage + 3, walkLeft);
	PLEX_addAnimationFrame(startImage + 4, walkLeft);

	walkRight = PLEX_getAnimation(2, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 5, walkRight);
	PLEX_addAnimationFrame(startImage + 6, walkRight);
	PLEX_addAnimationFrame(startImage + 7, walkRight);
	PLEX_addAnimationFrame(startImage + 8, walkRight);

	droppingTreasure = PLEX_getAnimation(3, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 9, droppingTreasure);

	dead = PLEX_getAnimation(4, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 10, dead);

	damaged = PLEX_getAnimation(5, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 11, damaged);

	crouching = PLEX_getAnimation(6, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 12, crouching);

	rollLeft = PLEX_getAnimation(7, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 13, rollLeft);
	PLEX_addAnimationFrame(startImage + 14, rollLeft);
	PLEX_addAnimationFrame(startImage + 15, rollLeft);

	rollRight = PLEX_getAnimation(8, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 16, rollRight);
	PLEX_addAnimationFrame(startImage + 17, rollRight);
	PLEX_addAnimationFrame(startImage + 18, rollRight);

	diveLeft = PLEX_getAnimation(9, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 19, diveLeft);
	PLEX_addAnimationFrame(startImage + 20, diveLeft);
	PLEX_addAnimationFrame(startImage + 21, diveLeft);

	diveRight = PLEX_getAnimation(10, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 22, diveRight);
	PLEX_addAnimationFrame(startImage + 23, diveRight);
	PLEX_addAnimationFrame(startImage + 24, diveRight);

	walkDown = PLEX_getAnimation(11, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 25, walkDown);
	PLEX_addAnimationFrame(startImage, walkDown);
	PLEX_addAnimationFrame(startImage + 26, walkDown);

	walkUp = PLEX_getAnimation(12, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 27, walkUp);
	PLEX_addAnimationFrame(startImage + 28, walkUp);
	PLEX_addAnimationFrame(startImage + 29, walkUp);

	standShootLeft = PLEX_getAnimation(13, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 30, standShootLeft);
	PLEX_addAnimationFrame(startImage + 31, standShootLeft);

	standShootMiddle = PLEX_getAnimation(14, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 32, standShootMiddle);
	PLEX_addAnimationFrame(startImage + 33, standShootMiddle);

	standShootRight = PLEX_getAnimation(15, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 34, standShootRight);
	PLEX_addAnimationFrame(startImage + 35, standShootRight);

	walkLeftShoot = PLEX_getAnimation(16, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 36, walkLeftShoot);
	PLEX_addAnimationFrame(startImage + 37, walkLeftShoot);
	PLEX_addAnimationFrame(startImage + 38, walkLeftShoot);
	PLEX_addAnimationFrame(startImage + 39, walkLeftShoot);

	walkRightShoot = PLEX_getAnimation(17, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 40, walkRightShoot);
	PLEX_addAnimationFrame(startImage + 41, walkRightShoot);
	PLEX_addAnimationFrame(startImage + 42, walkRightShoot);
	PLEX_addAnimationFrame(startImage + 43, walkRightShoot);

	diveLeftShoot = PLEX_getAnimation(18, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 44, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 45, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 46, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 47, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 48, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 49, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 50, diveLeftShoot);
	PLEX_addAnimationFrame(startImage + 51, diveLeftShoot);

	diveRightShoot = PLEX_getAnimation(19, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 52, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 53, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 54, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 55, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 56, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 57, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 58, diveRightShoot);
	PLEX_addAnimationFrame(startImage + 59, diveRightShoot);

	crouchShootLeft = PLEX_getAnimation(20, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 60, crouchShootLeft);
	PLEX_addAnimationFrame(startImage + 61, crouchShootLeft);

	crouchShootMiddle = PLEX_getAnimation(21, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 62, crouchShootMiddle);
	PLEX_addAnimationFrame(startImage + 63, crouchShootMiddle);

	crouchShootRight = PLEX_getAnimation(22, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 64, crouchShootRight);
	PLEX_addAnimationFrame(startImage + 65, crouchShootRight);

	reload = PLEX_getAnimation(23, enemy->sprite);

	PLEX_addAnimationFrame(startImage + 66, reload);
	PLEX_addAnimationFrame(startImage + 67, reload);

	PLEX_startSprite(time, enemy->sprite);
}

void MMS2_setEnemyGenerator(const double minDuration, const double maxDuration, const size_t enemyCount, MMS_F_AIPATTERN aiPattern0, const size_t typeIndex0, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	const uint64_t minGenWait = minDuration/enemyCount;
	const uint64_t maxGenWait = maxDuration/enemyCount;

	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = &room->contents->enemGenerator;

	if(enemGenerator->contents != NULL) PLEX_destroyGenerator(&enemGenerator->contents);

	enemGenerator->contents = PLEX_genGenerator(2, PLEX_WIDTHUNITMAX(true) - 2, 4, PLEX_HEIGHTUNITMAX(true) - 8, 0, 0, 0, 0, maxDuration, minGenWait, maxGenWait, minGenWait, maxGenWait, false);

	enemGenerator->max = enemyCount;

	if(!enemGenerator->aiPatternCount)
	{
		enemGenerator->aiPatternCount = 1;
		enemGenerator->aiPatterns[0].contents = aiPattern0;
	}

	if(!enemGenerator->typeCount)
	{
		enemGenerator->generatorTypes[0] = typeIndex0;
		enemGenerator->typeCount = 1;
	}

	enemGenerator->minDuration = minDuration;
	enemGenerator->maxDuration = maxDuration;
	enemGenerator->enemyCount = enemyCount;

	room->contents->calm = false;
}

void MMS2_placeEnemyGen(const size_t index, const char* const name, const double health, const PLEX_RECT space, const double minMoveSpeed, const double maxMoveSpeed, const uint64_t thoughtDelay, const uint64_t shotDuration, const uint64_t shotMax, const uint64_t reloadDuration, const double damagePotential, const double accuracyPotential, const size_t pointGain, const double treasureChance, const double likelyCashTreasure, const double likelyHealthTreasure, const double cashTreasureAmount, const size_t startImage, PLEX_ANIMATION_PLATE animPlate, const uint64_t time)
{
	if(index >= MMS2_ENEMYGENCOUNT)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONPLACEENEMYGEN, MMS2_ERRORMESS_ENEMYCOUNT);
		return;
	}

	p_enemyGens[index] = p_createEnemy(name, health, space, minMoveSpeed, maxMoveSpeed, thoughtDelay, shotDuration, shotMax, reloadDuration, damagePotential, accuracyPotential, pointGain, treasureChance, likelyCashTreasure, likelyHealthTreasure, cashTreasureAmount, NULL, startImage, animPlate, time);
}

void MMS2_addGeneratorAIPattern(struct MMS_MINIGAME2ROOM* room, MMS_F_AIPATTERN aiPattern)
{
	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = &room->contents->enemGenerator;

	if(enemGenerator->aiPatternCount >= MMS2_AIPATTERNCOUNT) return;

	enemGenerator->aiPatterns[enemGenerator->aiPatternCount].contents = aiPattern;
	++enemGenerator->aiPatternCount;
}

void MMS2_addEnemyGeneratorTypeIndex(struct MMS_MINIGAME2ROOM* room, const size_t index)
{
	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = &room->contents->enemGenerator;

	if(enemGenerator->typeCount >= MMS2_GENERATORINDEXCOUNT) return;

	enemGenerator->generatorTypes[enemGenerator->typeCount] = index;
	++enemGenerator->typeCount;
}

void MMS2_startEnemyGenerator(struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = &room->contents->enemGenerator;

	enemGenerator->start = p_defeatedEnemyCount;

	PLEX_startGenerator(enemGenerator->contents, time);
}

void MMS2_resetEnemyGenerator(struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = &room->contents->enemGenerator;

	MMS2_clearEnemyCount();

	if(!enemGenerator->aiPatternCount) return;
	if(!enemGenerator->typeCount) return;

	MMS2_setEnemyGenerator(enemGenerator->minDuration, enemGenerator->maxDuration, enemGenerator->enemyCount, enemGenerator->aiPatterns[0].contents, enemGenerator->generatorTypes[0], room, time);
}

void MMS2_incrementEnemyCount()
{
	if(p_enemyCount >= MMS2_ENEMYCOUNT) return;

	++p_enemyCount;
}

void MMS2_incrementTotalEnemyCount()
{
	if(p_totalEnemyCount >= MMS2_ENEMYCOUNT) return;

	++p_totalEnemyCount;
}

void MMS2_clearEnemyCount(){ p_enemyCount = 0; }

uint32_t MMS2_getEnemyLayer(const PLEX_RECT rect)
{
	double layer = PLEX_WH(true) - (rect.origin.y + rect.dimens.h);

	if(layer < 0) layer = rect.dimens.h;

	return MMS2_DRAWLAYER_ENEMYLAYERBASE + layer;
}

size_t MMS2_enemyCount(){ return p_enemyCount; }

size_t MMS2_defeatedEnemyCount(){ return p_defeatedEnemyCount; }

struct MMS_MINIGAME2ENEMY* MMS2_enemy(const size_t index){ return p_enemies + index; }

struct MMS_MINIGAME2ENEMY* MMS2_enemyGen(const size_t index){ return p_enemyGens + index; }

// AI HOOKS:

void MMS2_ai_dodger(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(!p_aiSeekAvoidCursor(true, false, 5, 0.5, enemy, index, time))
	{
		if(!p_aiSeekAvoidCursor(false, false, 10, 0.25, enemy, index, time)) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);

		if(!enemy->shootTime) p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
	}
}

void MMS2_ai_coward(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(!p_aiSeekCover(false, false, 5, 0.5, enemy, index, time) && !enemy->shootTime)
	{
		if(!p_aiSeekCover(false, false, 7, 1, enemy, index, time) && !enemy->shootTime)
		{
			p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);

			if(!enemy->shootTime) p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
		}
	}
}

void MMS2_ai_runner(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_STANDING)
	{
		const MMS_MINIGAME2ENEMYPHASE phase = enemy->space.origin.x < PLEX_WW(true)/2 ? MMS_MINIGAME2ENEMYPHASE_MOVERIGHT : MMS_MINIGAME2ENEMYPHASE_MOVELEFT;

		p_enemyPhaseSwitchPassive(index, phase, time);
	}

	if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVELEFT && enemy->space.origin.x < 0) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_MOVERIGHT, time);

	if(enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVERIGHT && enemy->space.origin.x > PLEX_WIDTHUNITMAX(true)) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_MOVELEFT, time);

	if(!enemy->shootTime && (enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVELEFT || enemy->phase == MMS_MINIGAME2ENEMYPHASE_MOVERIGHT)) p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
}

void MMS2_ai_sneak(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(!p_aiSeekMargins(false, enemy, index, 1, time && !enemy->shootTime))
	{
		p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);
		p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
	}
}

void MMS2_ai_diver(const size_t index, const uint64_t time)
{
	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(!p_aiSeekAvoidCursor(false, true, 5, 0.5, enemy, index, time))
	{
		if(!p_aiSeekAvoidCursor(true, false, 10, 0.25, enemy, index, time)) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);

		if(!enemy->shootTime) p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
	}
}

void MMS2_ai_sharpshooter(const size_t index, const uint64_t time)
{
	uint8_t desiredShootDirec = 1;

	MMS_MINIGAME2ENEMY* enemy = p_enemies + index;

	if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCH) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT)) p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_STANDING, time);
	else p_enemyPhaseSwitchPassive(index, MMS_MINIGAME2ENEMYPHASE_CROUCHING, time);

	if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANLEFT)) desiredShootDirec = 0;

	if(MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_LEANRIGHT)) desiredShootDirec = 2;

	if(!enemy->shootTime || enemy->shootDirec != desiredShootDirec) p_enemyStartShoot(index, PLEX_randomNumber(0, 3), time);
}

void MMS2_ai_maniac(const size_t index, const uint64_t time)
{
	const size_t number = PLEX_randomNumber(0, 6);

	switch(number)
	{
		case 0: MMS2_ai_dodger(index, time); break;
		case 1: MMS2_ai_coward(index, time); break;
		case 2: MMS2_ai_sneak(index, time); break;
		case 3: MMS2_ai_runner(index, time); break;
		case 4: MMS2_ai_diver(index, time); break;
		default: MMS2_ai_sharpshooter(index, time);
	};
}
