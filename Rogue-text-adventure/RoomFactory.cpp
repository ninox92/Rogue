#include "RoomFactory.h"
#include "RoomDescription.cpp"

RoomFactory::~RoomFactory() {}

Room* RoomFactory::createRoom(int x, int y) {

	// Make an new Room with x, y
	Room* r = new Room(x, y);

	// Generate Room Desc, set it in the room
	std::string s = RoomDescription::ToString();
	r->setRoomDesc(s);

	// Return the Room
	return r;
}