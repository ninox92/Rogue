#include "GameObject.h"
#include "Hero.h"
#pragma once
class Room : public GameObject
{
private:
	int row;
	int col;
	std::string size;
	std::string token;
	Hero* hero = nullptr;
	bool clean;
	bool explored;

public:
	Room();
	Room(std::string size, std::string token, int row, int col);
	~Room();

	bool isClean();
	bool isExplored();
	void visit();
	std::string display();
};

