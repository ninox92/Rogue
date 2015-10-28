#pragma once
#include "NPC.h";

NPC::NPC(std::string type, std::string desc, std::string attackDesc) : GameObject()
{
	SetType(type);
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

string NPC::getLvlAndHp()
{
	return "Level(" + std::to_string(level) + "), Health(" + std::to_string(health) + "/" + std::to_string(maxHealth) + ")";
}