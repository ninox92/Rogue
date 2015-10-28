#include <iostream>
#include "Game.h"
#include <windows.h>

int	main()
{
	// Uncomment this if u want to restore the console size
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1280, 640, TRUE);
	
	// Game
	Game game;
	do {
		if (game.getRenderState() == RenderState::RENDER) {
			game.render();
		}
	} while (game.getGameState() == GameState::RUNNING);

	return	0;
}
