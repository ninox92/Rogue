#pragma once
#include <map>
#include "Direction.cpp"

class Room;

class Passage
{
	std::map<Direction, Room*> map;
public:
	Passage();//Default Constructor
	~Passage();

	//virtual std::string Identify() = 0;//PURE abstract function
	//To override use:
	//virtual std::string Identify() override { return ""; /*new content here*/ }
	void Add(Room* r, Direction d);
	Room* GetRoom(Direction d);
};

