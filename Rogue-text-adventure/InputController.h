#pragma once
#include <string>
#include <map>
#include "Direction.cpp"


class InputController
{
private:
	std::string input;
	std::map<std::string, Direction> stringDirMap = {
		{ "north", Direction::NORTH },
		{ "east", Direction::EAST },
		{ "south", Direction::SOUTH },
		{ "west", Direction::WEST }
	};

public:
	InputController();
	~InputController();
	void clearConsole();
	void pressEnterToContinue();
	void printEmptyLine();
	void printMsg(std::string s);
	void printMessage(std::string s);
	std::string WaitAndGetInput();
	void printDirections(std::map<std::string, Direction> dirMap);
	Direction getDirectionFromInput();
};