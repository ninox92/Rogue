
class Room;
#pragma once

class Passage
{
	Room* previous;
	Room* next;
public:
	Passage();//Default Constructor
	Passage(Room* next, Room* previous);
	~Passage();

	Room* const Next() { return next; }
	Room* const Previous() { return previous; }
};

