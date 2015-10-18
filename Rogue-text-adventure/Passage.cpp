#include "Passage.h"
#include "Room.h"



Passage::Passage()
{
}

Passage::~Passage()
{
}

void Passage::Add(Room * r, Direction d)
{
	this->map.insert({ d,r });
}

Room * Passage::GetRoom(Direction d)
{
	if (map.find(d) != map.end()) return map[d];
	return nullptr;
}
