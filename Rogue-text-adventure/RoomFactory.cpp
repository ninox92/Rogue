#include "Map.h"
#include "RoomFactory.h"
#include "RoomDescription.cpp"

RoomFactory::~RoomFactory() {}

Room* RoomFactory::createRoom(int id, int x, int y, Map* m) {

	// Make an new Room with x, y
	Room* r = new Room(id, x, y, m);

	// Generate Room Desc, set it in the room
	std::string s = RoomDescription::ToString();
	r->setRoomDesc(s);

	// Return the Room
	return r;
}