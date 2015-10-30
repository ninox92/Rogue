#include "Compass.h"
#include "Hero.h"
#include "Map.h"


Compass::Compass()
{
	SetType("Compass");
	//Use this->Identify() || GetType() to get the name
}


Compass::~Compass()
{
}

void Compass::Use(Hero * h)
{
}

void Compass::Use(Map & m, Hero * h)
{
	m.revealDijkstra();
	_used = true;
}
