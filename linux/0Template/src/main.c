#include "game.h"

// NOTE: The entry point. In most cases you will not need to modify this. Perhaps delete the comment with in the while loop in the middle for release. Perhaps delete this comment. Preferably, you want to put your stuff in game.c.

int main(const int argc, char** args)
{
	if(!(PROJ)_startGame())
	{
		return 1;
	}

	while((PROJ)_updateGame())
	{
		// Optionally put stuff in here for early testing and it will run after updating the game. Ideally, though, you want to leave this blank and put everything you need in the (PROJ)_updateGame() function. You can, however, use it in a pinch.
	}

	(PROJ)_endGame();

	return 0;
}

// This is for SDL and windows compilation. Really no good reason to modify it in most cases. The handles it passes are irrelevant to PLEX.

#if (PLEX_CORE_OS == PLEX_CORE_WINDOWS)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	return main(0, NULL);
}
#endif
