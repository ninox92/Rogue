#pragma once
#include <map>
#include <string>
#include "Direction.cpp"
#include "GameObject.h"
class Room;
class FileController;

class Passage
	: public GameObject
{
private:
	std::map<Direction, Room*> map;
	bool _collapsed = false;
	bool _explored = false;
	bool _shortest = false;

public:
	Passage();//Default Constructor
	~Passage();

	void Add(Room* r, Direction d);

	bool Exists(Direction d);
	Room* GetRoom(Direction d);

	bool const IsCollapsed() { return this->_collapsed; }
	void SetCollapsed(bool c) { this->_collapsed = c; }
	void Explore() { this->_explored = true; }
	bool IsExplored() { return this->_explored; }
	bool IsShortest() { return _shortest; }
	void SetShortest(bool s) { _shortest = s; }
	void RandomName(FileController* f);
	std::string Display();
};

