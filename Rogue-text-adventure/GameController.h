#pragma once
#include <string>
#include <map>

#include "Actions.cpp"
#include "InputController.h"

class Map;
class Hero;

class GameController {
	private:
		Map* cMap;
		Hero* cHero;
		InputController inputController;
		std::map<std::string, Actions> actionMap = {
			{ "fight", Actions::FIGHT },
			{ "flee", Actions::FLEE },
			{ "search", Actions::SEARCH },
			{ "rest", Actions::REST },
			{ "invertory", Actions::INVERTORY },
			{ "map", Actions::MAP },
			{ "stats", Actions::STATS }
		};
	public:
		GameController();
		~GameController();

		void askGameAction(Map* map, Hero* hero);

		void Fight();
		void Flee(bool b);
		void Search();
		void Rest();
		void showInvertory();
		void showMap();
		void showHeroStats();

		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
};