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
		static Room* createRoom(int x, int y);
};