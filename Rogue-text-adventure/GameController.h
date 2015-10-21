#pragma once
#include <string>
#include <map>

#include "Actions.cpp"

class GameController {
	private:
		std::map<std::string, Actions> actionMap = {
			{ "Fight", Actions::FIGHT },
			{ "Flee", Actions::FLEE },
			{ "Search", Actions::SEARCH },
			{ "Rest", Actions::REST },
			{ "Invertory", Actions::INVERTORY },
			{ "Map", Actions::MAP }
		};
	public:
		GameController();
		~GameController();
		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
};
