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
	switch (d)
	{
	case Direction::NORTH:
		return north;
		break;
	case Direction::EAST:
		return east;
		break;
	case Direction::SOUTH:
		return south;
		break;
	case Direction::WEST:
		return west;
		break;
	case Direction::NONE:
	default:
		return nullptr;
		break;
	}
}

void Room::visit() {
	this->_isVisited = true;
}
std::string Room::displayHorizontal() {
	std::string right = (east == nullptr ? " " : "-");
	std::string left = (west == nullptr ? " " : "-");
	if (type == RoomType::START || type == RoomType::END || type == RoomType::LATTER_UP || type == RoomType::LATTER_DOWN)
		return  left + getToken() + right;
	if (!this->_isVisited) return left + "." + right;
	
	return left + getToken() + right;
}

std::string Room::displayVertical()
{
	std::string bot = (south == nullptr ? "   " : " | ");
	return bot;
}

void Room::setPassage(Direction dir, Passage* p)
{
	std::cout << "Create passage :";
	switch (dir)
	{
	case Direction::NORTH:
		north = p;
		std::cout << "NORTH" << std::endl;
		break;
	case Direction::EAST:
		east = p;
		std::cout << "EAST" << std::endl;
		break;
	case Direction::SOUTH:
		south = p;
		std::cout << "SOUTH" << std::endl;
		break;
	case Direction::WEST:
		west = p;
		std::cout << "WEST" << std::endl;
		break;
	case Direction::NONE:
	default:
		std::cout << "ERROR" << std::endl;
		break;
	}
}

std::map<std::string, Direction> Room::getAllPossibleMoveDirections()
{
	std::map<std::string, Direction> smap;
	if (north != nullptr)
		smap.insert( { "north", Direction::NORTH } );
	if (east != nullptr)
		smap.insert({ "east", Direction::EAST });
	if (south != nullptr)
		smap.insert({ "south", Direction::SOUTH });
	if (west != nullptr)
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