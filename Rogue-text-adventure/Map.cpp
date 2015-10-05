
#include <iostream>
#include "Map.h"



Map::Map(int width, int height) : width(width), height(height), size(width*height)
{
	this->rooms = new Room[size];
	this->build();
}


Map::~Map()
{//Deconstructor

	delete[] this->rooms;
}


void Map::build() {

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			rooms[y*width + x] = createRoom((x + 1), (y + 1));
		}
	}

}
std::string Map::display() {
	std::string s = "";
	int row = 1;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			
			if (row == (width+1)) {
				s += "\n";
				row = 1;
			}
			s += this->rooms[y*width + x].display();
			row++;
		}
	}
	return s + "\n\n";
}

Room Map::createRoom(int x, int y) {
	return Room("small", "N", x, y);
}