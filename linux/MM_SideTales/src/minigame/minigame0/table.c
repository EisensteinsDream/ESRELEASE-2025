#include "minigame/minigame0/minigame0.h"

static PLEX_SPRITE* p_table = NULL;

static PLEX_RECT p_tableSpace[MMS0_TABLE_MAX];
static bool p_tableReset[MMS0_TABLE_MAX];

static PLEX_MPREC p_tableMomentumX[MMS0_TABLE_MAX];
static PLEX_MPREC p_tableMomentumY[MMS0_TABLE_MAX];
static size_t p_tableDirec[MMS0_TABLE_MAX];

void MMS0_createTableSprite(const size_t chapter0spriteTex, const uint64_t time)
{
	PLEX_ANIMATION_PLATE table = PLEX_createAnimationPlate(0.125, 0.125, chapter0spriteTex);

	PLEX_ANIMATION* tableAnim = NULL;

	if(p_table != NULL) return;

	p_table = PLEX_genSprite(&table);

	PLEX_addAnimation(p_table, 1, PLEX_getGameTime());

	tableAnim = PLEX_getAnimation(0, p_table);

	PLEX_addAnimationFrame(32, tableAnim);
}

void MMS0_startTablePositions()
{
	const double w = 4;
	const double h = 3;

	for(size_t ze = 0; ze < MMS0_TABLE_MAX; ++ze)
	{
		const uint32_t x = (ze % 2) *  PLEX_WIDTHUNITMAX()/2 + PLEX_WIDTHUNITMAX()/4 - w/2;
		const uint32_t y = MMS0_theLine() + ((ze >= 2) * (MMS0_theLine2() - MMS0_theLine()));

		p_tableMomentumX[ze] = 0;
		p_tableMomentumY[ze] = 0;

		p_tableSpace[ze] = PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(w, h));
		p_tableDirec[ze] = MMS0_DIRECTION_NONE;
		p_tableReset[ze] = false;
	}
}

void MMS0_updateTable(const double tableMomentum, PLEX_MPREC* tmomXs, PLEX_MPREC* tmomYs, const size_t index, const uint64_t time)
{
	const PLEX_RECT space = p_tableSpace[index];

	const size_t playerDirection = MMS0_getPlayerDirection();

	PLEX_MPREC* tmomX = p_tableMomentumX + index;
	PLEX_MPREC* tmomY = p_tableMomentumY + index;

	p_tableReset[index] = false;

	if(p_tableDirec[index] == MMS0_DIRECTION_NONE)
	{
		*tmomX = 0;
		*tmomY = 0;

		if(MMS0_isPlayerPushing())
		{
			if(PLEX_rectCollision(space, MMS0_getPlayerPushRect(), 0, 0))
			{
				MM_COMMON_playSoundEffectVolume(0.5, MM_COMMON_SOUNDEFFECT_TABLESCREECH);

				switch(playerDirection)
				{
					case MMS0_DIRECTION_UP: p_tableDirec[index] = MMS0_DIRECTION_UP; break;
					case MMS0_DIRECTION_RIGHT: p_tableDirec[index] = MMS0_DIRECTION_RIGHT; break;
					case MMS0_DIRECTION_DOWN: p_tableDirec[index] = MMS0_DIRECTION_DOWN; break;
					case MMS0_DIRECTION_LEFT: p_tableDirec[index] = MMS0_DIRECTION_LEFT; break;
				};
			}
		}
	}

	if(p_tableDirec[index] == MMS0_DIRECTION_NONE)
	{
		PLEX_RECT playerSpace = MMS0_getPlayerSpace();

		if(p_tableSpace[index].origin.y < MMS0_theLine()){ p_tableSpace[index].origin.y = MMS0_theLine(); p_tableReset[index] = true; }
		if(p_tableSpace[index].origin.y > MMS0_theLine2()){ p_tableSpace[index].origin.y = MMS0_theLine2(); p_tableReset[index] = true; }
		if(p_tableSpace[index].origin.x < 2){ p_tableSpace[index].origin.x = 2; p_tableReset[index] = true; }
		if(p_tableSpace[index].origin.x + p_tableSpace[index].dimens.w > PLEX_WIDTHUNITMAX() - 2){ p_tableSpace[index].origin.x = PLEX_WIDTHUNITMAX() - 2 - p_tableSpace[index].dimens.w; p_tableReset[index] = true; }

		if(PLEX_rectCollisionNoMove(playerSpace, p_tableSpace[index]))
		{
			if(playerSpace.origin.y < p_tableSpace[index].origin.y) playerSpace.origin.y = p_tableSpace[index].origin.y - playerSpace.dimens.h - 0.1;
			else playerSpace.origin.y = p_tableSpace[index].origin.y + p_tableSpace[index].dimens.h + 0.1;

			MMS0_setPlayerSpace(playerSpace);
		}
	}

	switch(p_tableDirec[index])
	{
		case MMS0_DIRECTION_UP: *tmomY -= tableMomentum; break;
		case MMS0_DIRECTION_RIGHT: *tmomX += tableMomentum; break;
		case MMS0_DIRECTION_DOWN: *tmomY += tableMomentum; break;
		case MMS0_DIRECTION_LEFT: *tmomX -= tableMomentum; break;
	};

	*(tmomXs + index) = *tmomX;
	*(tmomYs + index) = *tmomY;

	PLEX_drawSprite(MMS0_drawLayer(space), 0, PLEX_UNIT(space.origin.x), PLEX_UNIT(space.origin.y), PLEX_UNIT(space.dimens.w), PLEX_UNIT(space.dimens.h), p_table, true, time);
}

void MMS0_moveTable(const size_t index)
{
	const size_t tindex = index % MMS0_TABLE_MAX;

	p_tableSpace[tindex].origin.x += p_tableMomentumX[tindex];
	p_tableSpace[tindex].origin.y += p_tableMomentumY[tindex];
}

void MMS0_freeTableSprite(){ if(p_table != NULL) PLEX_destroySprite(&p_table); }

void MMS0_setTableDirection(const size_t direction, const size_t index){ p_tableDirec[index % MMS0_TABLE_MAX] = direction; }

PLEX_RECT MMS0_getTableSpace(const size_t index){ return p_tableSpace[index % MMS0_TABLE_MAX]; }

size_t MMS0_getTableDirec(const size_t index){ return p_tableDirec[index % MMS0_TABLE_MAX]; }

bool MMS0_getTableReset(const size_t index){ return p_tableReset[index % MMS0_TABLE_MAX]; }
