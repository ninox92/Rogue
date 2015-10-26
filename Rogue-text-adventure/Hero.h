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
	const int maxLevel = 10;
	int health = 10;
	int maxHealth = 10;
	int experience = 0;
	int maxExperience = 20;

	int attack = 1;
	int defense = 1;
	int mindfulness = 1;

	int backpack;// Items[] 

public:
	Hero(std::string name);
	~Hero();

	void move(Room* next);
	bool lookForPassage(Direction dir);
	void move(Direction dir);

	void upExp(int exp) { experience += exp; }
	void upAttack() { attack++; }
	void upDefense() { defense++; }
	void upMindfulness() { mindfulness++; }

	Room* const getCurrentRoom() { return this->currentRoom; }

	std::string const getName() { return this->name; }
	int getLevel() { return this->level; }
	int getMaxLevel() { return this->maxLevel; }
	int getHealth() { return this->health; }
	int getMaxHealth() { return this->maxHealth; }
	int getExp() { return this->experience; }
	int getMaxExp() { return this->maxExperience; }
	int getAttack() { return this->attack; }
	int getDefense() { return this->defense; }
	int getMindfulness() { return this->mindfulness; }
};

