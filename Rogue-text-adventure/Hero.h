#include "GameObject.h"
#include "Direction.cpp"

#pragma once


class Hero : public GameObject
{
private:
	std::string name;

	int x = -1;
	int y = -1;

	int level = 1;
	int health = 10;
	int exp = 0;

	int attack = 1;
	int defense = 1;
	int mindfulness = 1;

	int backpack;// Items[] 

public:
	Hero(std::string name);
	~Hero();
	int getLevel();

	void move(Direction direction);

	void upExp(int exp);
	void upAttack();
	void upDefense();
	void upMindfulness();

	std::string getName();
	int getBackpack();



};

inline int Hero::getLevel()
{
	return level;
}

inline void Hero::upExp(int experience)
{
	Hero::exp += experience;
}

inline void Hero::upAttack()
{
	attack++;
}

inline void Hero::upDefense()
{
	defense++;
}

inline void Hero::upMindfulness()
{
	mindfulness++;
}

inline std::string Hero::getName() {
	return name;
}
 

