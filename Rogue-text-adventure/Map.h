#pragma once
#include <list>
#include <random>
#include <vector>
#include <stack>
#include "Game.h"
#include "Room.h"

class Map
{
private:
	Game* game = nullptr;

	std::random_device dev;
	std::default_random_engine dre{ dev() };
	std::uniform_int_distribution<int> dirDist{ 1,4 };
	
	int level = 0;
	int width = 10;
	int height = 10;
	int ptX = 0, ptY = 0;

	std::vector<Passage*> passages;
	std::vector<Room*> rooms;

	Room* start = nullptr;
	Room* end = nullptr;

	Room* createRoom(int id, int x, int y);
	void setPassages(Room* p1, Room* p2);
	std::vector<Room*> getNeighbours(int x, int y);
	Direction getDirection(Room& cur, Room& next);
	Direction getOpositeDirection(Direction d);

	void init();
	void build();
	std::list<int> BFS(Room* begin, Room* end);
	void kruskals();
	int findset(int x, int * parent);
	void printKruskals();
	int minKey(Room* c);
	void resetRooms();
public:
	Map();//Default constructor
	Map(int width, int height, Game* game);// Preferred Constructor
	~Map();

	
	void create();
	void show();

	int getWidth() const { return this->width; }
	int getHeight() const { return this->height; }
	int size() const { return width * height; }
	int getLevel() const { return this->level; }
	int getMaxLevel() const { return this->game->getMaxLevel(); }
	Room* const getStartRoom() { return this->start; }
	Room* const getEndRoom() { return this->end; }
	std::vector<Room*> const getRooms() { return this->rooms; }

	void setLevel(int l) { this->level = l; }
	void setStartRoom(Room* s) { this->start = s; }
	void setEndRoom(Room* e) { this->end = e; }
	
	int talisman();
};

