#include "Room.h"
#pragma once
class Map
{
private:
	int width = 10;
	int height = 10;
	Room* rooms;
	int size;
	Room createRoom(int x, int y);
public:
	Map(int width, int height);
	~Map();
	void build();
	std::string display();
};

