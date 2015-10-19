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

bool Passage::Exists(Direction d)
{
	return (map.find(d) != map.end());
}

Room * Passage::GetRoom(Direction d)
{
	if (Exists(d)) return map[d];
	return nullptr;
}
