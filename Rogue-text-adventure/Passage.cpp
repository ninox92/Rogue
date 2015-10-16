#include "Passage.h"
#include "Room.h"



Passage::Passage() : next { nullptr }, previous { nullptr }
{
}

Passage::Passage(Room * next, Room * previous) : next{ next }, previous{ previous }
{
}

Passage::~Passage()
{
}
