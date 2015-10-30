#pragma once
#include "Hero.h"
#include "Room.h"
#include "Game.h"
#include "Room.h"
#include "Map.h"
#include "Compass.h"
#include "Grenade.h"
#include <iostream>

Hero::Hero(std::string name, Game* game) : name(name), game(game), GameObject()
{
	SetType("Hero");
	AddItem("compass", new Compass());
	AddItem("grenade", new Grenade());
}

Hero::~Hero()
{
}

void Hero::move(Room * next)
{
	setCurrentRoom(next);
	if (next->getType() == RoomType::LATTER_DOWN) {
		//Move down the latter to the next level
		game->nextLevel();
	}
	else if (next->getType() == RoomType::LATTER_UP) {
		//Move up the latter to the previour level
		game->prevLevel();
	}
}

void Hero::setCurrentRoom(Room * c)
{
	/*
	If there is a previous room
	Remove the Hero from it
	*/
	if (currentRoom != nullptr)currentRoom->setHero(nullptr);
	currentRoom = c;
	currentRoom->visit();
	currentRoom->setHero(this);
}

bool Hero::lookForPassage(Direction dir)
{
	Passage* p = currentRoom->getPassage(dir);
	return p == nullptr ? false : true;
}

void Hero::move(Direction dir)
{
	Passage* p = currentRoom->getPassage(dir);
	this->move(p->GetRoom(dir));	
}

void Hero::upExp(int exp)
{
	experience += exp;
	if (exp >= maxExperience) {
		int tmp = experience - maxExperience;
		experience = tmp;
		upLvl();
	}
		
}

void Hero::upLvl()
{
	remainingStatsPoints += 3;
	upHealth();
	ResetHealth();
	this->level++;
	std::cout << getName() << ", Congratulations, you've reached level " << level << std::endl;
}

void Hero::AddItem(std::string key, Item* i)
{
	this->items[key] = i;
}

void Hero::UseItem(std::string key)
{
	if (HasItem(key)) {
		items[key]->Use(this);
	}
}

void Hero::UseItem(std::string key, Map & map)
{
	if (HasItem(key)) {
		items[key]->Use(map, this);
	}
}

bool Hero::HasItem(std::string key)
{
	return (items.count(key) == 1);
}

bool Hero::IsItemUsed(std::string key)
{
	if (HasItem(key)) {
		return items[key]->IsUsed();
	}
	return false;
}
