#ifndef ROOM_O
#define ROOM_O

enum class RoomType
{
	INIT, // *
	START,// S
	END,  // F
	ROOM, // explored ? N : . 
	LATTER_UP, // H
	LATTER_DOWN, // L
	COLLAPSED, // ~
};

#endif