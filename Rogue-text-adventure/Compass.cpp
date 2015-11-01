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
	std::cout << "Je haalt het kompas uit je zak." << std::endl;
	std::cout << "Het trilt in je hand en projecteert in grote lichtgevende letters in de lucht:" << std::endl;


	m.compass();
	_used = true;
}
