#ifndef ROOM_O
#define ROOM_O

enum class RoomType
{
	INIT, // *
	START,// S
	END,  // F
	ROOM, // explored ? N : . 
	COLLAPSED, // ~
};

#endif