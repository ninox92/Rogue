#pragma once
#include "Item.h"

class Compass :
	public Item
{
public:
	Compass();
	~Compass();

	virtual void Use(Hero* h) override;
	virtual void Use(Map& m, Hero* h) override;
};

