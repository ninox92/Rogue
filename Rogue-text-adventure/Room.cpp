#pragma once
#include <iostream>
#include <math.h>
#include "Room.h"
#include "Map.h"


Room::Room() : GameObject(){}// Default constructor
Room::Room(int id, int x, int y, Map* map) : ID(id), map(map), col(x), row(y), GameObject()
{
	int cLevel = map->getLevel();
	double f1 = std::fmod(map->getMaxLevel(), 2);
	double f2 = std::fmod(map->getLevel(), 10);
	float equalizer = map->getLevel() >= f1 ? f2 : 1;
	this->spawnChange = ceil((cLevel * 10) * ceil(equalizer));
	eDist = std::uniform_int_distribution<int>( 0, maxEnemies );
	this->createEnemies();
}


Room::~Room()
{
}


Passage * const Room::getPassage(Direction d)
{
	if (hasPassage(d)) {
		return passages[d];
	}
	return nullptr;
}

bool const Room::hasPassage(Direction d)
{
	bool exists = (passages.find(d) != passages.end());
	return exists;
}

void Room::visit() {
	this->_isVisited = true;
}

std::string Room::displayHorizontal() {
	std::string right = (hasPassage(Direction::EAST) ? "-" : " ");
	std::string left = (hasPassage(Direction::WEST) ? "-" : " ");
	if (type == RoomType::START || type == RoomType::END || type == RoomType::LATTER_UP || type == RoomType::LATTER_DOWN)
		return  left + getToken() + right;
	if (!this->_isVisited) return left + "." + right;
	
	return left + getToken() + right;
}

std::string Room::displayVertical()
{
	std::string bot = (hasPassage(Direction::SOUTH) ? " | " : "   ");
	return bot;
}

void Room::setPassage(Direction dir, Passage* p)
{
	if (!hasPassage(dir)) {
		passages[dir] = p;
	}
	else {
		//exception
	}
}

int const Room::getMapLevel()
{
	if (map == nullptr) return -1;
	return map->getLevel();
}

std::map<std::string, Direction> Room::getAllPossibleMoveDirections()
{
	std::map<std::string, Direction> smap;
	if (hasPassage(Direction::NORTH))
		smap.insert( { "north", Direction::NORTH } );
	if (hasPassage(Direction::EAST))
		smap.insert({ "east", Direction::EAST });
	if (hasPassage(Direction::SOUTH))
		smap.insert({ "south", Direction::SOUTH });
	if (hasPassage(Direction::WEST))
		smap.insert({ "west", Direction::WEST });

	return smap;
}

std::map<Direction, Passage*> Room::getAllPossiblePassages()
{
	std::map<Direction, Passage*> pmap;
	if (hasPassage(Direction::NORTH))
		pmap.insert({Direction::NORTH, getPassage(Direction::NORTH) });
	if (hasPassage(Direction::EAST))
		pmap.insert({Direction::EAST, getPassage(Direction::EAST) });
	if (hasPassage(Direction::SOUTH))
		pmap.insert({Direction::SOUTH, getPassage(Direction::SOUTH) });
	if (hasPassage(Direction::WEST))
		pmap.insert({Direction::WEST, getPassage(Direction::WEST) });

	return pmap;
}


std::string Room::getToken()
{
	std::string s;
	if (hasHero()) return "&";
	if (enemiesCount != 0) return std::to_string(enemiesCount);
	switch (type)
	{
	case RoomType::INIT:
		s = "*";
		break;
	case RoomType::START:
		s = "S";
		break;
	case RoomType::END:
		s = "F";
		break;
	case RoomType::ROOM:
		s = "N";
		break;
	case RoomType::COLLAPSED:
		s = "~";
		break;
	case RoomType::LATTER_UP:
		s = "H";
		break;
	case RoomType::LATTER_DOWN:
		s = "L";
		break;
	default:
		break;
	}
	return s;
}

void Room::createEnemies()
{
	//check if this room even gets some enemies
	int chance = dist(dre);
	if (chance > spawnChange) return;
	//if so, create some
	enemiesCount = eDist(dre);
}
