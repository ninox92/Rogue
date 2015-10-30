#include "Grenade.h"
#include <iostream>
#include "Map.h"

Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}



void Grenade::Use(Hero * h)
{
}

void Grenade::Use(Map & m, Hero * h)
{
	if (!IsUsed()) {
		std::cout << "De kerker schudt op zijn grondvesten, alle tegenstanders in de kamer zijn verslagen!" << std::endl;
		std::cout << "Een donderend geluid maakt duidelijk dat gedeeltes van de kerker zijn ingestort..." << std::endl;
		m.collapseByExplosion();
	}
	else {
		std::cout << "Je vreest dat een extra handgranaat een cruciale passage zal blokkeren." << std::endl;
		std::cout << "Het is beter om deze niet meer te gebruiken op deze verdieping." << std::endl;
	}
	_used = true;
}
