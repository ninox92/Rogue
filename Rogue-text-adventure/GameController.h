#pragma once
#include <string>
#include <map>

#include "Actions.cpp"

class GameController {
	private:
		std::map<std::string, Actions> actionMap = {
			{ "fight", Actions::FIGHT },
			{ "flee", Actions::FLEE },
			{ "search", Actions::SEARCH },
			{ "rest", Actions::REST },
			{ "invertory", Actions::INVERTORY },
			{ "map", Actions::MAP }
		};
	public:
		GameController();
		~GameController();
		std::string getGameActionString();
		std::map<std::string, Actions> getGameActions();
};
