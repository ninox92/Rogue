#include "Trap.h"



Trap::Trap() : GameObject("Trap")
{
}


Trap::~Trap()
{
}

void Trap::disable() 
{
	this->isDisabled = true;
}

void Trap::doAction() {

}