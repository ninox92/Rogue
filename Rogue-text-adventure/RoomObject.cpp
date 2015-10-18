#include "RoomObject.h";

RoomObject::RoomObject(std::string type) : GameObject() 
{
	SetType(type);
}

RoomObject::~RoomObject() {

}