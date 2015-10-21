#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Direction.cpp"


class InputController
{
private:
	std::string input;
	std::map<std::string, Direction> stringDirMap = {
		{ "North", Direction::NORTH },
		{ "East", Direction::EAST },
		{ "South", Direction::SOUTH },
		{ "West", Direction::WEST }
	};

public:
	InputController();
	~InputController();

	void printMessage(std::string s);
	std::string WaitAndGetInput();
	Direction getDirectionFromInput(std::map<std::string, Direction> possibleDirections);

};

