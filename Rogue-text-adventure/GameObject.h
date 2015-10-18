#include <string>
#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	std::string const Identify();
	std::string const GetType();
	void SetType(std::string t) { type = t; }

private:
	std::string type = "";
	
};
