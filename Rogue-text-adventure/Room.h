#pragma once
#include <map>
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
	
	bool _hasHero;
	bool _isClean;
	bool _isVisited;

	Passage* north = nullptr;
	Passage* east = nullptr;
	Passage* south = nullptr;
	Passage* west = nullptr;

	std::string getToken();
	std::string roomDesc;
public:
	Room();
	Room(int x, int y);
	virtual ~Room();
	
	void setType(RoomType type) { this->type = type; }
	RoomType const getType() { return this->type; }

	int const getX() { return this->col; }
	int const getY() { return this->row; }
	Passage* const getPassage(Direction d);

	bool const hasHero() { return this->_hasHero; }
	bool const isClean() { return this->_isClean; }// Is the room clean
	bool const isVisited() { return this->_isVisited; } // is the room explored
	void visit(); // visit the room

	std::string displayHorizontal();
	std::string displayVertical();

	void setHero(bool h) { this->_hasHero = h; }
	void setPassage(Direction dir, Passage* p);
	std::map<std::string, Direction> getAllPossibleMoveDirections();

	std::string getRoomDesc() { return this->roomDesc; }
	void setRoomDesc(std::string r) { this->roomDesc = r; }
};

