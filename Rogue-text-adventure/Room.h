#pragma once
#include "GameObject.h"
#include "Hero.h"
#include "Passage.h"

#include "RoomType.cpp"


class Room : public GameObject
{
private:
	int row;
	int col;
	
	RoomType type = RoomType::INIT;
	std::string size;
	
	bool clean;
	bool visited;

	Passage* north = nullptr;
	Passage* east = nullptr;
	Passage* south = nullptr;
	Passage* west = nullptr;

	std::string getToken();
public:
	Room();
	Room(int x, int y);
	virtual ~Room();
	
	void setType(RoomType type) { this->type = type; }
	RoomType const getType() { return this->type; }

	int const getX() { return this->col; }
	int const getY() { return this->row; }

	bool const isClean() { return this->clean; }// Is the room clean
	bool const isVisited() { return this->visited; } // is the room explored
	void visit(); // visit the room

	std::string displayHorizontal();
	std::string displayVertical();

	void setPassage(Direction dir, Passage* p);
	std::string getAllPossibleMoveDirections();
};

