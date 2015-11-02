#pragma once
#include <algorithm>
#include "NPC.h"

NPC::NPC(std::string type, std::string size, std::string desc, std::string attackDesc) : GameObject()
{
	SetType(type);
	setSize(size);
	setDesc(desc);
	setAttackDesc(attackDesc);
}

NPC::~NPC()
{
}

void NPC::setLevel(int l)
{
	level = l;

	for (int i = 1; i < l; i++)
	{
		exp += (int)(0.5f + (exp / 2));
		health += (int)(0.5f + (health / 2));
		maxHealth += (int)(0.5f + (maxHealth / 2));
		maxDamage += (int)(0.5f + (maxDamage / 2));
	}
}

string NPC::getNpcName()
{
	string s = GetType();
	s[0] = toupper(s[0]);
	return s;
}

string NPC::getNpcCleanName()
{
	string s = GetType();
	return this->size + " " + s.substr(0, s.size() - 2);
}

string NPC::getNpcInputName()
{
	string s = GetType();
	std::replace(s.begin(), s.end(), ' ', '-');
	return s;
}

string NPC::getLvlAndHp()
{
	return "Level(" + std::to_string(level) + "), Health(" + std::to_string(health) + "/" + std::to_string(maxHealth) + ")";
}

string NPC::getAttackDesc(bool hit, int dmg)
{
	if(hit)
	{
		return getNpcName() + " " + this->attackDesc + " and do " + std::to_string(dmg) + " damage!";
	}
	return getNpcName() + " " + this->attackDesc + " and missed!";
}

void NPC::loseHealth(int h)
{
	this->health = this->health - h;
	if (this->health <= 0) {
		this->health = 0;
		this->death = true;
	}
}
