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
	case Direction::NORTH:
		break;
	case Direction::EAST:
		break;
	case Direction::SOUTH:
		break;
	case Direction::WEST:
		break;

	default:
		break;
	}
}

