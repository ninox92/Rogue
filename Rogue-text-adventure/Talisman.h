#pragma once
#include "Item.h"
class Talisman :
	public Item
{
public:
	Talisman();
	~Talisman();

	virtual void Use(Hero* h) override;
	virtual void Use(Map& m, Hero* h) override;
};

