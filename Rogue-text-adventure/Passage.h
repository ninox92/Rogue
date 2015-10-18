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


	void Add(Room* r, Direction d);

	Room* GetRoom(Direction d);
};

