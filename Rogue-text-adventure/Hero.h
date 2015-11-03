#pragma once
#include "GameObject.h"
#include "Direction.cpp"
#include "Game.h"
#include "Item.h"
class Room;

class Hero : public GameObject
{
private:
	std::string name = "";
	Room* currentRoom = nullptr;

	bool death = false;

	int remainingStatsPoints = 0;
	int level = 1;
	const int maxLevel = 10;

	int minDamage = 2;
	int maxDamage = 6;

	int health = 20;
	int maxHealth = 20;

	int experience = 0;
	int maxExperience = 100;

	int attack = 1;
	int defense = 1;
	int mindfulness = 1;

	int chanceToAttack = 80;
	int chanceToDefend = 60;
	int chanceToMindfulness = 80;

	std::map<std::string, Item*> items;

	Game* game = nullptr;
	void upAbility() { if (remainingStatsPoints > 0) remainingStatsPoints--; }

public:
	Hero(std::string name, Game* game);
	~Hero();

	void move(Room* next);
	void setCurrentRoom(Room* c);
	bool lookForPassage(Direction dir);
	void move(Direction dir);

	void upExp(int exp);
	void upHealth();
	void upAttack() { attack++; upAbility(); }
	void upDefense() { defense++; upAbility(); }
	void upMindfulness() { mindfulness++; upAbility(); }
	void upLvl();
	void upDmg();
	

	void loseHealth(int h);
	bool isDeath() { return this->death; }

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
	int getMinDamage() { return this->minDamage; }
	int getMaxDamage() { return this->maxDamage; }

	std::string getHealthString();
	std::string getExpString(int exp);

	int getChanceToAttack();
	int getChanceToDefend();
	int getChanceToMindfulness();

	int getRemainingStatPoints() { return this->remainingStatsPoints; }
	std::map<std::string, Item*> getItems() { return this->items; }
	void AddItem(std::string key, Item* i);
	void UseItem(std::string key);
	void UseItem(std::string key, Map& map);
	bool HasItem(std::string key);
	bool IsItemUsed(std::string key);

	void ResetHealth() { this->health = maxHealth; }
};

