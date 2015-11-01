#pragma once
#include "GameObject.h"

class Map;
class Hero;
//Item Base class
class Item
	: public GameObject
{
protected:
	bool _used = false;
public:
	Item();
	virtual ~Item();

	virtual void Use(Hero* h) = 0;
	virtual void Use(Map& m, Hero* h) = 0;
	bool IsUsed() { return this->_used; }
};

