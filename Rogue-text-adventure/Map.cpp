#include <stack>
#include <iostream>
#include "Map.h"



Map::Map() : width(0), height(0), rooms(0)
{
}

Map::Map(int width, int height) : width(width), height(height), rooms(width*height)
{
	this->build();
}


Map::~Map()
{//Deconstructor
}


void Map::build() {
	std::uniform_int_distribution<int> xDist { 0, width -1 };
	//ptx =
	ptX = xDist(dre);//Set Begin X
	ptY = height - 1;// Set Begin Y
	
	//Build basic map
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			this->rooms[y*width + x] = createRoom((x + 1), (y + 1));
		}
	}

	Room* start = rooms[ptY*width + ptX];
	start->setType(RoomType::START);

	rooms[3]->setType(RoomType::END);


	std::stack<Room*> stack;
	stack.push(start);

	Room* current = start;
	while (stack.size() > 0) {
		std::vector<Room*> neighbours = getNeighbours(current->getX()-1, current->getY()-1);
		
		
		if (neighbours.size() > 0) {
			std::cout << "Neighbours : " << neighbours.size() << std::endl;
			Room* r;
			if (neighbours.size() > 1) {
				//search for random
				std::uniform_int_distribution<int> neighDist{ 0, (int) neighbours.size() - 1 };
				r = neighbours.at(neighDist(dre));
				
			}
			else
			{
				r = neighbours.at(0);
			}
			
			Direction d = getDirection(*current, *r);
			
			//create a passage between the neighbour and current room
			stack.push(r);

			r->visit();
			std::cout << display();
			current = r;
		}
		else if (stack.size() > 1) {
			std::cout << "Is already found" << ", stack size: "<<stack.size()<<std::endl;
			stack.pop();
			current = stack.top();
		}
		else {
			return;
		}
		//get all neighbours from top stack
		
		
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
			s += this->rooms[y*width + x]->display();
			row++;
		}
	}
	return s + "\n\n";
}

Room* Map::createRoom(int x, int y) {
	return new Room("small", x, y);
}

void Map::setPassages()
{
}

std::vector<Room*> Map::getNeighbours(int x, int y)
{
	std::cout << "x{" << x << "} Y{" << y << "}";
	std::vector<Room*> tmp; 
	int maxX = y  * width + (width - 1);
	int minX = y  * width;

	int north = (y-1) * width + x;
	int east = y * width + (x+1);
	int south = (y+1) * width + x;
	int west = y * width + (x-1);

	int southH = y*width + (x + 1) - width - 1;

	if (north >= 0 && y >= 0 && y <= (height-1) && !rooms[north]->isVisited()) 
	{
		std::cout << "NORTH found";
		//rooms[north]->setType(RoomType::END);
		tmp.push_back(rooms[north]);
	}
	if(east >= minX && east <= maxX && !rooms[east]->isVisited()) {
		std::cout << "EAST found";
		//rooms[east]->setType(RoomType::END);
		tmp.push_back(rooms[east]);
	}
	if (south >= 0 && south <= rooms.size()-1 && y <= (height - 1) && !rooms[south]->isVisited()) {
		std::cout << "SOUTH found";
		//rooms[south]->setType(RoomType::END);
		tmp.push_back(rooms[south]);
	}
	if (west >= minX && west <= maxX && !rooms[west]->isVisited()){
		std::cout << "WEST found";
		//rooms[west]->setType(RoomType::END);
		tmp.push_back(rooms[west]);
	}

	return tmp;
}


Direction Map::getDirection(Room& cur, Room& next) {
	Direction d = Direction::NONE;
	int cX = cur.getX();
	int cY = cur.getY();

	int nX = next.getX();
	int nY = next.getY();

	if (nX < cX) d = Direction::WEST;
	if (nX > cX) d = Direction::EAST;
	if (nY > cX) d = Direction::SOUTH;
	if (nY < cY) d = Direction::NORTH;

	return d;
}
