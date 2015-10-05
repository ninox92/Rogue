#include "Hero.h"


Hero::Hero(std::string name) : name(name), GameObject("Hero")
{
}

Hero::~Hero()
{
}


void Hero::move(Direction direction) {
	switch (direction)
	{
	case NORTH:
		break;
	case EAST:
		break;
	case SOUTH:
		break;
	case WEST:
		break;

	default:
		break;
	}
}

