#pragma once
#include "GameObject.h"
#include "Direction.cpp"

class Room;

class Hero : public GameObject
{
private:
	std::string name = "";
	Room* currentRoom = nullptr;
	int x = -1;
	int y = -1;

	int level = 1;
	int health = 10;
	int experience = 0;

	int attack = 1;
	int defense = 1;
	int mindfulness = 1;

	int backpack;// Items[] 

public:
	Hero(std::string name);
	~Hero();
	

	void move(Room* next) {	currentRoom = next; }



	void upExp(int exp) { experience += exp; }
	void upAttack() { attack++; }
	void upDefense() { defense++; }
	void upMindfulness() { mindfulness++; }

	Room* const getCurrentRoom() { return this->currentRoom; }
	int getLevel() { return this->level; }
	std::string const getName() { return this->name; }
};

