#include "Trap.h"



Trap::Trap() : GameObject()
{
	SetType("Trap");
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