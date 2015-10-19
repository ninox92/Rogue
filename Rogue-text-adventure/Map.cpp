#include <stack>
#include <iostream>
#include "ConsoleColor.h"
#include "Map.h"
#include <queue>


Map::Map()
{
}

Map::Map(int width, int height, Game* game) : game(game), width(width), height(height), rooms(width*height)
{
	this->dre = game->getDRE();
}


Map::~Map()
{//Deconstructor
}

void Map::create() {
	this->init();
	this->build();
}

void Map::init()
{
	std::uniform_int_distribution<int> xDist{ 0, width - 1 };
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
	//Set Begin
	setStartRoom(rooms[97]);//rooms[ptY*width + ptX];
	if (this->level == 1) {
		//Begin level needs Start point
		getStartRoom()->setType(RoomType::START);
	}
	else {
		//Begin is a latter Down, to the previous level
		getStartRoom()->setType(RoomType::LATTER_DOWN);
	}

	//Set End
	if (this->level == 10)//Max level
	{
		setEndRoom(rooms[3]);
		getEndRoom()->setType(RoomType::END);
	}
	else {
		//End room is a latter up 
		setEndRoom(rooms[3]);
		getEndRoom()->setType(RoomType::LATTER_UP);
	}
}

///Depth first search
void Map::build() {

	std::stack<Room*> stack;
	stack.push(getStartRoom());

	Room* current = stack.top();
	while (stack.size() > 0) {
		std::vector<Room*> neighbours = getNeighbours(current->getX()-1, current->getY()-1);
		
		
		if (neighbours.size() > 0) {
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
			//create a passage between the neighbour and current room
			setPassages(current, r);
			stack.push(r);

			r->visit();
			current = r;
		}
		else if (stack.size() > 1) {
			stack.pop();
			current = stack.top();
		}
		else {
			return;
		}
		
	}

}

///Breadth First Search
void Map::BFS()
{
	Room* current = game->getHero()->getCurrentRoom();
	std::queue<Room*> queue;
	queue.push(current);
	
	while (!queue.empty())
	{
		current = queue.front();
		current->setBFS(true);
		queue.pop();

		for (const auto& p : current->getAllPossiblePassages()) {
			Room* next = p.second->GetRoom(p.first);
			if (!next->isBFS()) {
				next->setBFS(true);
				queue.push(next);
			}
		}
	}
}

void Map::show() {
	std::string rowS = "";
	int row = 1;
	for (int y = 0; y < height; y++) {
		
		for (int x = 0; x < width; x++)
		{
			Room* r = this->rooms[y*width + x];
			if (row == (width+1)) {
				std::cout << "\n" + rowS + "\n";
				row = 1;
				rowS = "";
			}
			if (r->isBFS()) {
				std::cout << green;
			}
			std::cout << r->displayHorizontal();
			std::cout << white;//reset color
			rowS += r->displayVertical();
			row++;
		}
		
	}
	std::cout << "\n\n";
}

Room* Map::createRoom(int x, int y) {
	return new Room(x, y);
}


void Map::setPassages(Room* p1, Room* p2)
{
	Direction d = getDirection(*p1, *p2);
	Direction od = getOpositeDirection(d);

	Passage* p = new Passage();
	p->Add(p1, od);
	p->Add(p2, d);

	p1->setPassage(d, p);
	p2->setPassage(od, p);
	passages.push_back(p);
}

std::vector<Room*> Map::getNeighbours(int x, int y)
{
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
		//rooms[north]->setType(RoomType::END);
		tmp.push_back(rooms[north]);
	}
	if(east >= minX && east <= maxX && !rooms[east]->isVisited()) {
		//rooms[east]->setType(RoomType::END);
		tmp.push_back(rooms[east]);
	}
	if (south >= 0 && south <= rooms.size()-1 && y <= (height - 1) && !rooms[south]->isVisited()) {
		//rooms[south]->setType(RoomType::END);
		tmp.push_back(rooms[south]);
	}
	if (west >= minX && west <= maxX && !rooms[west]->isVisited()){
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
	if (nY > cY) d = Direction::SOUTH;
	if (nY < cY) d = Direction::NORTH;

	return d;
}

Direction Map::getOpositeDirection(Direction d)
{
	Direction dd = Direction::NONE;
	switch (d)
	{
	case Direction::NONE:
		dd = d;
		break;
	case Direction::NORTH:
		dd = Direction::SOUTH;
		break;
	case Direction::EAST:
		dd = Direction::WEST;
		break;
	case Direction::SOUTH:
		dd = Direction::NORTH;
		break;
	case Direction::WEST:
		dd = Direction::EAST;
		break;
	default:
		dd = Direction::NONE;
		break;
	}
	return dd;
}


