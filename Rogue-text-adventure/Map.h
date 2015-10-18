#pragma once
#include "Room.h"
#include <random>
#include <vector>

class Map
{
private:
	std::default_random_engine dre;
	std::uniform_int_distribution<int> dirDist{ 1,4 };
	
	int level = 0;
	int width = 10;
	int height = 10;
	int ptX = 0, ptY = 0;

	std::vector<Passage*> passages;
	std::vector<Room*> rooms;

	Room* start = nullptr;
	Room* end = nullptr;

	Room* createRoom(int x, int y);
	void setPassages(Room* p1, Room* p2);
	std::vector<Room*> getNeighbours(int x, int y);
	Direction getDirection(Room& cur, Room& next);
	Direction getOpositeDirection(Direction d);

	void init();
	void build();
public:
	Map();//Default constructor
	Map(int width, int height, std::default_random_engine dre);// Preferred Constructor
	~Map();

	void create();

	int size() const { return width * height; }
	int getLevel() const { return this->level; }
	Room* const getStartRoom() { return this->start; }
	Room* const getEndRoom() { return this->end; }

	void setLevel(int l) { this->level = l; }
	void setStartRoom(Room* s) { this->start = s; }
	void setEndRoom(Room* e) { this->end = e; }


	std::string show();
};

