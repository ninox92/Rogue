#include "Room.h"
#include <random>
#include <vector>
#pragma once
class Map
{
private:

	std::random_device dev;
	std::default_random_engine dre{ dev() };
	std::uniform_int_distribution<int> dirDist{ 1,4 };
	
	int width = 10;
	int height = 10;
	int ptX, ptY;
	std::vector<Room*> rooms;
	Room* createRoom(int x, int y);
	void setPassages();
	std::vector<Room*> getNeighbours(int x, int y);

	Direction getDirection(Room& cur, Room& next);
public:
	Map();//Default constructor
	Map(int width, int height);// Preferred Constructor
	~Map();
	void build();
	int size() const { return width * height; }
	std::string display();
};

