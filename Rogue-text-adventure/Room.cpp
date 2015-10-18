#include "Room.h"

#include <iostream>


Room::Room() : GameObject(){}// Default constructor
Room::Room( int x, int y) : col(x), row(y), GameObject()
{
}


Room::~Room()
{
}


void Room::visit() {
	this->visited = true;
}
std::string Room::displayHorizontal() {
	std::string right = (east == nullptr ? " " : "-");
	std::string left = (west == nullptr ? " " : "-");
	if (type == RoomType::START || type == RoomType::END || type == RoomType::LATTER_UP || type == RoomType::LATTER_DOWN)
		return  left + getToken() + right;
	if (!this->visited) return left + "." + right;
	
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

std::string Room::getAllPossibleMoveDirections()
{
	std::string s;
	if (north != nullptr)
		s += "North;";
	if (east != nullptr)
		s += "East;";
	if (south != nullptr)
		s += "South;";
	if (west != nullptr)
		s += "West;";
	return s;
}


std::string Room::getToken()
{
	std::string s;
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