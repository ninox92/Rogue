#include <string>
#include <map>
#include <iostream>
#include "Direction.cpp"
#pragma once

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
	std::map<Direction, std::string> enumDirMap = {
		{ Direction::NORTH, "north" },
		{ Direction::EAST, "east" },
		{ Direction::SOUTH, "south" },
		{ Direction::WEST, "west" }
	};

public:
	InputController();
	~InputController();

	std::string WaitAndGetInput();
	Direction getDirectionFromInput();

};

