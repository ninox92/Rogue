#pragma once
#include <list>
#include <random>
#include <vector>
#include <stack>
#include "Game.h"
#include "Room.h"
#include "MST.h"
#include "BFS.h"
#include "Dijkstras.h"


class Map
{
private:
	Game* game = nullptr;
	FileController* fileController = nullptr;

	std::random_device dev;
	std::default_random_engine dre{ dev() };
	std::uniform_int_distribution<int> dirDist{ 1,4 };
	
	int level = 0;
	int width = 10;
	int height = 10;
	int ptX = 0, ptY = 0;

	std::vector<Passage*> passages;
	std::vector<Room*> rooms;

	BFS bfs;
	MST mst;
	Dijkstras dijkstras;

	Room* start = nullptr;
	Room* end = nullptr;

	Room* createRoom(int id, int x, int y);
	void setPassages(Room* p1, Room* p2);
	std::vector<Room*> getNeighbours(int x, int y);
	

	void init();
	void build();
	
	int minKey(Room* c);
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
	Room* const getRoom(int x, int y);
	Room* const getRoom(int ID);

	std::vector<Room*> const getRooms() { return this->rooms; }
	Direction getDirection(Room& cur, Room& next);
	Direction getOpositeDirection(Direction d);

	void setLevel(int l) { this->level = l; }
	void setStartRoom(Room* s) { this->start = s; }
	void setEndRoom(Room* e) { this->end = e; }
	
	void resetRooms();
	void collapseByExplosion();
	int talisman();

	void revealAllRooms();
	void revealMST();
	void revealDijkstra();
	void revealBFS();

	void setFileController(FileController* f) { this->fileController = f; }
};

