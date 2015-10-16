#include "Room.h"



Room::Room() : GameObject("Empty Room"){}// Default constructor
Room::Room(std::string size, int col, int row) : 
	size(size), col(col), row(row), GameObject(size + " Room")
{
}


Room::~Room()
{
}


void Room::visit() {
	this->visited = true;
}
std::string Room::display() {
	if (type == RoomType::START || type == RoomType::END)
		return " " + getToken();
	if (!this->visited) return " .";
	
	return " " + getToken();
}

void Room::setPassage(Direction dir, Passage p)
{
	switch (dir)
	{
	case Direction::NONE:
		break;
	case Direction::NORTH:
		north = p;
		break;
	case Direction::EAST:
		east = p;
		break;
	case Direction::SOUTH:
		south = p;
		break;
	case Direction::WEST:
		west = p;
		break;
	default:
		break;
	}
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
	default:
		break;
	}
	return s;
}