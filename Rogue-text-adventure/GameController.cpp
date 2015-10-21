#include "GameController.h"
#include <algorithm>
#include <string>
using namespace std;

GameController::GameController()
{
}

GameController::~GameController()
{
}

std::string GameController::getGameActionString()
{
	std::string s = "[";
	for (const auto& kv : this->actionMap) {
		s += kv.first + ":";
	}
	s = s.substr(0, s.size() - 1);
	s += "]";
	
	return s;
}

std::map<std::string, Actions> GameController::getGameActions()
{
	return this->actionMap;
}
