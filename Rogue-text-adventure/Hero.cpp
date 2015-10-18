#include "Hero.h"


Hero::Hero(std::string name) : name(name), GameObject()
{
	SetType("Hero");
}

Hero::~Hero()
{
}
