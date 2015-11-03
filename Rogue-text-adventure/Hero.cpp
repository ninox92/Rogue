#pragma once
#include "Hero.h"
#include "Room.h"
#include "Game.h"
#include "Room.h"
#include "Map.h"
#include "Compass.h"
#include "Grenade.h"
#include <iostream>
#include "Talisman.h"

Hero::Hero(std::string name, Game* game) : name(name), game(game), GameObject()
{
	SetType("Hero");
	AddItem("compass", new Compass());
	AddItem("grenade", new Grenade());
	AddItem("talisman", new Talisman());
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

std::string Hero::getHealthString()
{
	return "You have " + std::to_string(health) + " of the " + std::to_string(maxHealth) + " vitality points left.";
}

std::string Hero::getExpString(int exp)
{
	return "You've earned " + std::to_string(exp) + "Exp, current progress to the next level: (" + std::to_string(getExp()) + "/" + std::to_string(getMaxExp()) + ")";
}

int Hero::getChanceToAttack()
{
	int i = this->chanceToAttack + this->attack;

	if(i >= 100)
		i = 100;

	return i;
}

int Hero::getChanceToDefend()
{
	int i = this->chanceToDefend - this->defense;

	if (i <= 1)
		i = 1;

	return i;
}

int Hero::getChanceToMindfulness()
{
	int i = this->chanceToMindfulness + this->mindfulness;

	if (i >= 100)
		i = 100;

	return i;
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

void Hero::upHealth()
{
	this->maxHealth += (int)(0.5f + (this->maxHealth / 2));
	ResetHealth();
}

void Hero::upLvl()
{
	if (this->level != this->maxLevel) {
		remainingStatsPoints += 3;
		upHealth();
		ResetHealth();
		upDmg();
		this->level++;
		std::cout << getName() << ", Congratulations, you've reached level " << level << std::endl;
	}
}

void Hero::upDmg()
{
	this->minDamage += (int)(0.5f + (this->minDamage / 2));
	this->maxDamage += (int)(0.5f + (this->maxDamage / 2));
}

void Hero::loseHealth(int h)
{
	this->health = this->health - h;
	if (this->health <= 0) {
		this->health = 0;
		this->death = true;
	}
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