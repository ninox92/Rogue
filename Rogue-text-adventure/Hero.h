#pragma once
#include "GameObject.h"
#include "Direction.cpp"
#include "Game.h"
class Room;

class Hero : public GameObject
{
private:
	std::string name = "";
	Room* currentRoom = nullptr;
	int x = -1;
	int y = -1;

	int remainingStatsPoints = 0;
	int level = 1;
	const int maxLevel = 10;
	int maxDamage = 4;
	int health = 20;
	int maxHealth = 20;
	int experience = 0;
	int maxExperience = 100;

	int attack = 1;
	int defense = 1;
	int mindfulness = 1;

	int backpack;// Items[] 
	Game* game = nullptr;
public:
	Hero(std::string name, Game* game);
	~Hero();

	void move(Room* next);
	void setCurrentRoom(Room* c);
	bool lookForPassage(Direction dir);
	void move(Direction dir);

	void upExp(int exp);
	void upHealth() { health += (int)(0.5f + (health / 2)); }
	void upAttack() { attack++; remainingStatsPoints--; }
	void upDefense() { defense++; remainingStatsPoints--; }
	void upMindfulness() { mindfulness++; remainingStatsPoints--; }
	void upLvl();

	void loseHealth(int h);

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

	std::string getHealthString();

	int getRemainingStatPoints() { return this->remainingStatsPoints; }
	void ResetHealth() { this->health = maxHealth; }
};

