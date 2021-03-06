#pragma once
#include <iostream>
#include <math.h>
#include "Room.h"
#include "Map.h"
#include "RandomItem.h"

Room::Room() : GameObject(){}// Default constructor
Room::Room(int id, int x, int y, Map* map, FileController* f) : ID(id), map(map), col(x), row(y), GameObject()
{
	int cLevel = map->getLevel();
	double f1 = std::fmod(map->getMaxLevel(), 2);// maxlevel / 2
	double f2 = std::fmod(map->getLevel(), 10);// level / 10
	float equalizer = map->getLevel() >= f1 ? f2 : 1;
	this->spawnChange = ceil((cLevel * 10) * ceil(equalizer));
	eDist = std::uniform_int_distribution<int>( 1, maxEnemies );
	setFileController(f);
	this->createItem();
	this->createTrap();
	this->createEnemies(true);
}


Room::~Room()
{
}

void Room::setType(RoomType type)
{
	this->type = type;
	if (RoomType::END == type)
		createEndBoss();
}


Passage * const Room::getPassage(Direction d)
{
	if (hasPassage(d)) {
		return passages[d];
	}
	return nullptr;
}

Passage * const Room::getPassage(int nX, int nY)
{
	Direction d = Direction::NONE;
	int cX = getX();
	int cY = getY();

	if (nX < cX) d = Direction::WEST;
	if (nX > cX) d = Direction::EAST;
	if (nY > cY) d = Direction::SOUTH;
	if (nY < cY) d = Direction::NORTH;

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
	for (const auto& p : getAllPossiblePassages()) {
		p.second->Explore();
	}
	this->_isVisited = true;
}

std::string Room::displayHorizontal() {
	std::string right = (hasPassage(Direction::EAST) ? getPassage(Direction::EAST)->Display() : " ");
	std::string left = (hasPassage(Direction::WEST) ? getPassage(Direction::WEST)->Display() : " ");
	//if (type == RoomType::START || type == RoomType::END || type == RoomType::LATTER_UP || type == RoomType::LATTER_DOWN)
		//return  left + getToken() + right;
	if (!this->_isVisited) return left + "." + right;
	
	return left + getToken() + right;
}

std::string Room::displayVertical()
{
	return (hasPassage(Direction::SOUTH) ? " "+getPassage(Direction::SOUTH)->Display()+" " : "   ");
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

bool Room::checkAllEnemiesDeath(vector<NPC*> enemies)
{
	bool b = true;
	for (auto &e : enemies)	{
		if(e->getHealth() != 0)	{
			b = false;
		}
	}
	return b;
}

std::string Room::getPassageDesc()
{
	std::string s = "Exits: ";
	if (hasPassage(Direction::EAST))
		s += "East" + getPassage(Direction::EAST)->Identify() + ". ";
	if (hasPassage(Direction::NORTH))
		s += "North" + getPassage(Direction::NORTH)->Identify() + ". ";
	if (hasPassage(Direction::SOUTH))
		s += "South" + getPassage(Direction::SOUTH)->Identify() + ". ";
	if (hasPassage(Direction::WEST))
		s += "West" + getPassage(Direction::WEST)->Identify() + ". ";

	return s;
}

std::map<string, NPC*> Room::getEnemiesMap()
{
	std::map<string, NPC*> m;
	
	for (auto &e : this->enemies)
	{
		m.insert({e->getNpcInputName(),e});
	}

	return m;
}

string Room::getEnemiesMapString()
{
	std::map<string, NPC*> m = getEnemiesMap();

	string s = "[";
	for (auto& kv : m) {
		if (!kv.second->isDeath()) {
			s += kv.first + ":";
		}
	}
	s = s.substr(0, s.size() - 1);
	s += "]";

	return s;
}

void Room::createEnemiesWhileRest()
{
	createEnemies(false);
}

void Room::collapsePassage(Direction dir)
{
	if (hasPassage(dir))
		passages[dir]->SetCollapsed(true);
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
		smap.insert({ "north", Direction::NORTH });
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
	if (getWeight() != 0) return std::to_string(getWeight());
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

void Room::createTrap()
{
	int chance = dist(dre);
	if (chance > spawnChange) return;

	this->isTrapActive = true;
	this->trapDesc = fileController->trapDescriptionToString();
	int trapWeight = 2;
	setWeight(getWeight() + trapWeight);
}

void Room::createEnemies(bool checkSpawn)
{
	//check if this room even gets some enemies
	if (checkSpawn) {
		int chance = dist(dre);
		if (chance > spawnChange) return;
	}

	//if so, create some
	enemiesCount = eDist(dre);

	if (enemiesCount != 0) {

		// Enemies in the room
		enemies = fileController->getRandomEnemies(enemiesCount);

		// Enemies not death
		enemiesDeath = false;

		// Enemies roomDesc
		if (enemiesCount == 1)
			enemiesDesc = std::to_string(enemiesCount) + " " + enemies[0]->getNpcCleanName() + " " + enemies[0]->getDesc();
		else
			enemiesDesc = std::to_string(enemiesCount) + " " + enemies[0]->getNpcCleanName() + "s " + enemies[0]->getDesc();

		int mapLevel = map->getLevel();
		int maxEnemiesLvl = mapLevel + 2;

		// Max level of the enemies stays below 10
		if(maxEnemiesLvl >= 10) {
			maxEnemiesLvl = 10;
			mapLevel = maxEnemiesLvl - 2;
		}

		std::random_device rd;
		std::default_random_engine dre {rd()};
		std::uniform_int_distribution<int> dist{ mapLevel, maxEnemiesLvl };
		int lvlEnemy = dist(dre);

		for (auto &e : enemies)
		{
			setWeight(getWeight() + e->getHealth());
			e->setLevel(lvlEnemy);
		}
	}
}

void Room::createEndBoss()
{
	// Enemies in the room
	enemies = fileController->getRandomEndBoss();

	// Enemies not death
	enemiesDeath = false;

	// Enemies roomDesc
	enemiesDesc = "A " + enemies[0]->GetType() + " " + enemies[0]->getDesc();

	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::uniform_int_distribution<int> dist{ this->bossMinLvl, this->bossMaxLvl };
	int lvlEnemy = dist(dre);

	for (auto &e : enemies)
	{
		setWeight(getWeight() + e->getHealth());
		e->setLevel(lvlEnemy);
	}
}

void Room::createItem()
{
	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::uniform_int_distribution<int> dist{ 1, 100 };

	int chance = dist(dre);
	if (chance > 0) {//10% chance of item
		item = new RandomItem(fileController);
	}
}
