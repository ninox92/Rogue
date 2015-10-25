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

std::string Passage::Display()
{
	if (map.size() == 0) return "";
	if (IsCollapsed()) return "~";

	if (Exists(Direction::NORTH) || Exists(Direction::SOUTH))
		return "|";
	if (Exists(Direction::EAST) || Exists(Direction::WEST))
		return "-";

	return "";
}
