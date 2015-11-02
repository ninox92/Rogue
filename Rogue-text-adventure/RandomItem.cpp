#include "RandomItem.h"
#include "Map.h"
#include "Hero.h"



RandomItem::RandomItem(FileController * f)
{
	std::string size = f->getRandomDesc("sizes");
	std::string itm = f->getRandomDesc("items");
	std::string color = f->getRandomDesc("colors");
	this->SetType(size + " " + color + " " + itm);
}

RandomItem::~RandomItem()
{
}


void RandomItem::Use(Hero* h)
{
	if (IsUsed()) return;
	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::uniform_int_distribution<int> dist{ 1, 5 };
	int ability = dist(dre);
	std::string what = "";
	switch (ability) {
	case 1://attack
		h->upAttack();
		what = "attack";
		break;
	case 2://defense
		h->upDefense();
		what = "defense";
		break;
	case 3://mindfullness
		h->upMindfulness();
		what = "mindfullness";
		break;
	case 4://health
		h->upHealth();
		what = "health";
		break;
	case 5://damage
		h->upDmg();
		what = "damage";
		break;
	}
	std::cout << "This item gave you 1 extra " + what << std::endl;
}

void RandomItem::Use(Map & m, Hero * h)
{
}
