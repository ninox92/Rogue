#pragma once
#include "Room.h"

class RoomFactory 
{
	private:
		RoomFactory() {};
	public:
		~RoomFactory();
		static RoomFactory* Instance() {
			static RoomFactory r;
			return &r;
		}
		static Room* createRoom(int id, int x, int y, Map* m);
};