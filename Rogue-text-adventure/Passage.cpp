#include "Passage.h"
#include "Room.h"


Passage::Passage() : GameObject()
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

void Passage::RandomName(FileController* f)
{
	std::string passageName = f->getRandomDesc("passages");
	std::string material = f->getRandomDesc("materials");
	SetType(material + " " + passageName);
}

std::string Passage::Display()
{
	if (map.size() == 0) return "";
	if (!IsExplored()) return " ";
	if (IsCollapsed()) return "~";
	if (IsShortest()) return "#";
	if (Exists(Direction::NORTH) || Exists(Direction::SOUTH))
		return "|";
	if (Exists(Direction::EAST) || Exists(Direction::WEST))
		return "-" ;

	return "";
}
