#include <string>
#pragma once

class GameObject
{
public:
	GameObject(std::string type);
	~GameObject();
	std::string Identify();
private:
	std::string type;
	
};
