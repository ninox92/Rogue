#pragma once
#include <string>
#include "GameObject.h";


class NPC : public GameObject
{
public:
	NPC(std::string type);
	~NPC();
private:
	int level;
	int exp;

};

