#include "GameObject.h";

GameObject::GameObject(std::string type) : type(type)
{

}
GameObject::~GameObject() {

}
std::string GameObject::Identify() {
	return " is a "+this->type;
}