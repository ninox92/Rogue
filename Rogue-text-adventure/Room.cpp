#include "Room.h"


Room::Room() : GameObject("Empty Room"){}// Default constructor
Room::Room(std::string size, std::string token, int row, int col) : 
	size(size), token(token), row(row), col(col), GameObject(size + " Room")
{
}


Room::~Room()
{
}


bool Room::isClean()
{
	return this->clean;
}

bool Room::isExplored() {
	return true;//this->explored;
}
void Room::visit() {
	this->explored = true;
}
std::string Room::display() {
	if (!this->isExplored()) return " *";
	return " "+this->token;
}