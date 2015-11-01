#pragma once
#include "Item.h"
class FileController;
class RandomItem :
	public Item
{
public:
	RandomItem(FileController* f);
	~RandomItem();

	virtual void Use(Hero* h) override;
	virtual void Use(Map& m, Hero* h) override;
};

