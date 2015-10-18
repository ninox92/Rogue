#pragma once
#include "Hero.h"
#include "Room.h"

Hero::Hero(std::string name) : name(name), GameObject()
{
	SetType("Hero");
}

Hero::~Hero()
{
}

void Hero::move(Room * next)
{
	if (currentRoom != nullptr) currentRoom->setHero(false);
	currentRoom = next;
	currentRoom->setHero(true);
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
