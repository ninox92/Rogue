#pragma once
#include "NPC.h";

NPC::NPC(std::string type) : GameObject()
{
	SetType(type);
}

NPC::~NPC()
{
}