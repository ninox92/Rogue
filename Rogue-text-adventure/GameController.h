#pragma once
#include <string>
#include <map>

#include "Actions.cpp"
#include "FightActions.cpp"
#include "InputController.h"
#include "NPC.h"

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

		std::map<std::string, Actions> inventoryMap = {
			{ "talisman", Actions::TALISMAN },
			{ "grenade", Actions::GRENADE },
			{ "compass", Actions::COMPASS },
		};

		std::map<std::string, Actions> actionHiddenMap = {
			///Hidden actions :)
			{ "mst",		Actions::MST },
			{ "dijkstra",	Actions::DIJKSTRA },
			{ "edijkstra",	Actions::EXTREME_DIJKSTRA },
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

		std::map<std::string, FightActions> fightActionMap = {
			{ "fight", FightActions::FIGHT },
			{ "flee", FightActions::FLEE },
			{ "invertory", FightActions::INVERTORY }
		};

		std::map<std::string, std::string> legenda = {
			{ "|-", "Passage way" },
			{ ".", "Unexplored room" },
			{ "*", "Explored room" },
			{ "S", "Start room" },
			{ "F", "Finish room" },
			{ "H", "Latter up" },
			{ "L", "Latter down" },
			{ "~", "Collaped passage way" }
		};

		void MST();
		void Dijkstra();
		void EDijkstra();
		void BSF();
		void LVLUP();
		void HPUP();
		void Reveal();

		void UseCompass();
		void UseGrenade();
		void UseTalisman();

	public:
		GameController(Game* game);
		~GameController();

		void askWhatToDo();
		void askToUpdateStats();

		void Fight();
		void askFightAction();
		void doHeroAttack(bool b);
		void doNpcAttack(std::vector<NPC*> e);
		void Flee(bool b);
		void Search();
		void Rest();

		void showInvertory();
		void showMap();
		void showHeroStats();

		bool chanceCalc();
		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
		std::string getFightActionString();
		std::map<std::string, FightActions> getFightActions();
};