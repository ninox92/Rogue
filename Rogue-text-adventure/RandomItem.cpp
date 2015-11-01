#include "RandomItem.h"
#include "Map.h"
#include "Hero.h"



RandomItem::RandomItem(FileController * f)
{
}

RandomItem::~RandomItem()
{
}


void RandomItem::Use(Hero* h)
{
	if (!IsUsed())
		h->upAttack();
}

void RandomItem::Use(Map & m, Hero * h)
{
}
