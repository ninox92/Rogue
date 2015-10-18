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
		{ "north", Direction::NORTH },
		{ "east", Direction::EAST },
		{ "south", Direction::SOUTH },
		{ "west", Direction::WEST }
	};

public:
	InputController();
	~InputController();

	std::string WaitAndGetInput();
	Direction getDirectionFromInput(std::map<std::string, Direction> possibleDirections);

};

