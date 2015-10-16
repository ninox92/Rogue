#include "GameObject.h"
#include "Hero.h"
#include "Passage.h"
#include "RoomType.cpp"
#pragma once

class Room : public GameObject
{
private:
	int row;
	int col;
	
	RoomType type = RoomType::INIT;
	std::string size;

	Hero* hero = nullptr;

	bool clean;
	bool visited;

	Passage north;
	Passage east;
	Passage south;
	Passage west;

	std::string getToken();
public:
	Room();
	Room(std::string size, int col, int row);
	~Room();
	
	void setType(RoomType type) { this->type = type; }
	RoomType const getType() { return this->type; }

	int const getX() { return this->col; }
	int const getY() { return this->row; }

	bool const isClean() { return this->clean; }// Is the room clean
	bool const isVisited() { return this->visited; } // is the room explored
	void visit(); // visit the room

	std::string display();

	void setPassage(Direction dir, Passage p);

};

