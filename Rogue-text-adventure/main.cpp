using namespace std;

#include <iostream>
#include "Game.h"

int	main()
{
	Game game;
	do {
		if (game.getRenderState() == RenderState::RENDER) {
			game.render();
		}
	} while (game.getGameState() == GameState::RUNNING);


	return	0;
}
