#include "GameObject.h";


GameObject::GameObject()
{
}
GameObject::~GameObject() {

}
std::string const GameObject::GetType()
{
	return this->type;
}
std::string const GameObject::Identify() {
	return " is a "+ GetType();
}