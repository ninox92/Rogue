#pragma once
#include "Item.h"
class Grenade :
	public Item
{
public:
	Grenade();
	~Grenade();

	virtual void Use(Hero* h) override;
	virtual void Use(Map& m, Hero* h) override;
};

