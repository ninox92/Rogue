#pragma once
#include <string>
#include <map>

#include "Actions.cpp"
#include "FightActions.cpp"
#include "InputController.h"
#include "NPC.h"

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
		std::map<std::string, FightActions> fightActionMap = {
			{ "fight", FightActions::FIGHT },
			{ "flee", FightActions::FLEE },
			{ "object", FightActions::OBJECT },
			{ "potion", FightActions::POTION }
		};
	public:
		GameController();
		~GameController();

		void askGameAction(Map* map, Hero* hero);

		void Fight();
		void askFightAction();
		void doHeroAttack();
		void doNpcAttack(std::vector<NPC*> e);
		void Flee(bool b);
		void Search();
		void Rest();
		void showInvertory();
		void showMap();
		void showHeroStats();

		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
		std::string getFightActionString();
		std::map<std::string, FightActions> getFightActions();
};