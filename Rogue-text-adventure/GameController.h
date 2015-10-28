#pragma once
#include <string>
#include <map>

#include "Actions.cpp"
#include "InputController.h"

class Game;
class Map;
class Hero;

class GameController {
	private:
		Game* game = nullptr;
		Map* cMap = nullptr;
		Hero* cHero = nullptr;
		InputController inputController;

		std::map<std::string, Actions> actionMap = {
			{ "fight",		Actions::FIGHT },
			{ "flee",		Actions::FLEE },
			{ "search",		Actions::SEARCH },
			{ "rest",		Actions::REST },
			{ "invertory",	Actions::INVERTORY },
			{ "map",		Actions::MAP },
			{ "stats",		Actions::STATS }
		};

		std::map<std::string, Actions> actionHiddenMap = {
			///Hidden actions :)
			{ "mst",		Actions::MST },
			{ "dijkstra",	Actions::DIJKSTRA },
			{ "bfs",		Actions::BFS },
			{ "lvlup",		Actions::LVLUP },
			{ "hpup",		Actions::HPUP },
			{ "reveal",		Actions::REVEAL }
		};

		std::map<std::string, Actions> actionStatsMap = {
			///Stats actions 
			{ "up-attack",			Actions::UP_ATTACK },
			{ "up-defense",			Actions::UP_DEFENSE },
			{ "up-mindfullness",	Actions::UP_MINDFULLNESS },
		};

		std::map<std::string, std::string> legenda = {
			{ "|-", "Passage way" },
			{ ".", "Unexplored room" },
			{ "N", "Explored room" },
			{ "S", "Start room" },
			{ "F", "Finish room" },
			{ "H", "Latter up" },
			{ "L", "Latter down" },
			{ "~", "Collaped passage way" }
		};

		void MST();
		void Dijkstra();
		void BSF();
		void LVLUP();
		void HPUP();
		void Reveal();


	public:
		GameController(Game* game);
		~GameController();

		void askGameAction();
		void askForUpdateStats();

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