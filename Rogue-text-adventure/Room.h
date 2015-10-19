#pragma once
#include <map>
#include "GameObject.h"
#include "Hero.h"
#include "Passage.h"

#include "RoomType.cpp"


class Room : public GameObject
{
private:
	int row = 0;
	int col = 0;
	
	RoomType type = RoomType::INIT;
	std::string size;
	
	bool _hasHero = false;
	bool _isClean = false;
	bool _isBFS = false;
	bool _isVisited = false;
	bool _isShortest = false;

	std::map<Direction, Passage*> passages;

	std::string getToken();
public:
	Room();
	Room(int x, int y);
	virtual ~Room();
	
	void setType(RoomType type) { this->type = type; }
	RoomType const getType() { return this->type; }

	int const getX() { return this->col; }
	int const getY() { return this->row; }
	std::map<std::string, Direction> getAllPossibleMoveDirections();
	std::map<Direction, Passage*> getAllPossiblePassages();
	Passage* const getPassage(Direction d);
	

	bool const hasHero() { return this->_hasHero; }
	bool const isClean() { return this->_isClean; }// Is the room clean
	bool const isVisited() { return this->_isVisited; } // is the room explored
	bool const isShortest() { return this->_isShortest; }
	bool const isBFS() { return this->_isBFS; }
	bool const hasPassage(Direction d);
	void visit(); // visit the room

	std::string displayHorizontal();
	std::string displayVertical();

	void setBFS(bool b) { this->_isBFS = b; }
	void setHero(bool h) { this->_hasHero = h; }
	void setShortest(bool s) { this->_isShortest = s; }
	void setPassage(Direction dir, Passage* p);
	


};

