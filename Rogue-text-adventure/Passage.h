#pragma once
#include <map>
#include <string>
#include "Direction.cpp"

class Room;

class Passage
{
private:
	std::map<Direction, Room*> map;
	bool _collapsed = false;
	bool _explored = false;
	bool _shortest = false;

public:
	Passage();//Default Constructor
	~Passage();

	//virtual std::string Identify() = 0;//PURE abstract function
	//To override use:
	//virtual std::string Identify() override { return ""; /*new content here*/ }
	void Add(Room* r, Direction d);

	bool Exists(Direction d);
	Room* GetRoom(Direction d);

	bool const IsCollapsed() { return this->_collapsed; }
	void SetCollapsed(bool c) { this->_collapsed = c; }
	void Explore() { this->_explored = true; }
	bool IsExplored() { return this->_explored; }
	bool IsShortest() { return _shortest; }
	void SetShortest(bool s) { _shortest = s; }
	std::string Display();
};

