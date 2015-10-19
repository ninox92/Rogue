#include "Room.h"

#include <iostream>


Room::Room() : GameObject(){}// Default constructor
Room::Room( int x, int y) : col(x), row(y), GameObject()
{
}


Room::~Room()
{
}


Passage * const Room::getPassage(Direction d)
{
	if (hasPassage(d)) {
		return passages[d];
	}
	return nullptr;
}

bool const Room::hasPassage(Direction d)
{
	return (passages.find(d) != passages.end());
	return nullptr;
}

void Room::visit() {
	this->_isVisited = true;
}
std::string Room::displayHorizontal() {
	std::string right = (hasPassage(Direction::EAST) ? " " : "-");
	std::string left = (hasPassage(Direction::WEST) ? " " : "-");
	if (type == RoomType::START || type == RoomType::END || type == RoomType::LATTER_UP || type == RoomType::LATTER_DOWN)
		return  left + getToken() + right;
	if (!this->_isVisited) return left + "." + right;
	
	return left + getToken() + right;
}

std::string Room::displayVertical()
{
	std::string bot = (hasPassage(Direction::SOUTH) ? "   " : " | ");
	return bot;
}

void Room::setPassage(Direction dir, Passage* p)
{
	std::cout << "Create passage :";
	if (!hasPassage(dir)) {
		passages[dir] = p;
	}
	else {
		//exception
	}
}

std::map<std::string, Direction> Room::getAllPossibleMoveDirections()
{
	std::map<std::string, Direction> smap;
	if (hasPassage(Direction::NORTH))
		smap.insert( { "north", Direction::NORTH } );
	if (hasPassage(Direction::EAST))
		smap.insert({ "east", Direction::EAST });
	if (hasPassage(Direction::SOUTH))
		smap.insert({ "south", Direction::SOUTH });
	if (hasPassage(Direction::WEST))
		smap.insert({ "west", Direction::WEST });

	return smap;
}


std::string Room::getToken()
{
	std::string s;
	if (hasHero()) return "&";
	switch (type)
	{
	case RoomType::INIT:
		s = "*";
		break;
	case RoomType::START:
		s = "S";
		break;
	case RoomType::END:
		s = "F";
		break;
	case RoomType::ROOM:
		s = "N";
		break;
	case RoomType::COLLAPSED:
		s = "~";
		break;
	case RoomType::LATTER_UP:
		s = "H";
		break;
	case RoomType::LATTER_DOWN:
		s = "L";
		break;
	default:
		break;
	}
	return s;
}