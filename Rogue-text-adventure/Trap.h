#include "GameObject.h"
#pragma once
class Trap : public GameObject
{
private:
	bool isDisabled = false;
public:
	Trap();
	~Trap();
	void doAction();
	void disable();
};

