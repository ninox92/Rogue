using namespace std;

#include <iostream>
#include "Game.h"

int	main()
{
	Game* game = new Game();
	do {
		if (game->getRenderState() == RENDER)
			game->render();
	} while (game->getGameState() == RUNNING);


	return	0;
}
