#include <string>
#include "GameObject.h";
#pragma once

class NPC : public GameObject
{
public:
	NPC(std::string type);
	~NPC();
private:
	int level;
	int exp;

};

