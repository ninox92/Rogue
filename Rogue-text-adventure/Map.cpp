#pragma once
#include <queue>
#include <iostream>
#include <map>
#include "ConsoleColor.h"
#include "Map.h"
#include "Room.h"


using std::queue;
using std::stack;
using std::list;
using std::map;
using std::string;
using std::vector;

Map::Map()
{
}

Map::Map(int width, int height, Game* game) : game(game), width(width), height(height), rooms(width*height)
{
}


Map::~Map()
{//Deconstructor
}

void Map::create() {
	this->init();
	this->build();
	
	dijkstras.Compute(*this, getStartRoom()->getID(), getEndRoom()->getID());
	
	//this->collapseByExplosion();
	//this->prims(getStartRoom(), getEndRoom());
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
			this->rooms[y*width + x] = createRoom(y*width + x, (x + 1), (y + 1));
		}
	}
	//Set Begin
	setStartRoom(rooms[ptY*width + ptX]);
	if (this->level == 1) {
		//Begin level needs Start point
		getStartRoom()->setType(RoomType::START);
	}
	else {
		//Begin is a latter Down, to the previous level
		getStartRoom()->setType(RoomType::LATTER_UP);
	}

	ptX = xDist(dre);//Set Begin X
	ptY = 0;// Set Begin Y
	//Set End
	if (this->level == 10)//Max level
	{
		setEndRoom(rooms[ptY*width + ptX]);
		getEndRoom()->setType(RoomType::END);
	}
	else {
		//End room is a latter up 
		setEndRoom(rooms[ptY*width + ptX]);
		getEndRoom()->setType(RoomType::LATTER_DOWN);
	}
}

///Depth first search
void Map::build() {
	// link all the rooms togehter
	
	stack<Room*> stack;
	stack.push(getStartRoom());
	Room* current = stack.top();
	while (stack.size() > 0) {
		vector<Room*> neighbours = getNeighbours(current->getX() - 1, current->getY() - 1);

		if (neighbours.size() > 0) {
			Room* r = nullptr;

			std::uniform_int_distribution<int> neighDist{ 0, (int)neighbours.size() };
			int size = neighDist(dre);
			
			if (size == 0) { size = 1; }
			//create a passage between the neighbour and current room
			for (int i = 0; i < size; i++) {
				r = neighbours.at(i);
				setPassages(current, r);
				//show();
			}
			if (r != nullptr) {
				r->setReached(true);
				r->visit();
				stack.push(r);
				current = r;
			}			
		}
		else if (stack.size() > 0) {
			stack.pop();
			if(stack.size() != 0)
				current = stack.top();
		}
	}

	/*
	stack<Room*> stack;
	stack.push(getStartRoom());
	Room* current = stack.top();
	while (stack.size() > 0) {
		vector<Room*> neighbours = getNeighbours(current->getX()-1, current->getY()-1);
		
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
		
	}*/
	show();
}

int Map::minKey(Room* c)
{
	//int min = INT_MAX, min_index;
	int min = INT_MAX, min_index=-1;
	for (const auto& p : c->getAllPossiblePassages())
	{
		Room* next = p.second->GetRoom(p.first);
		if (next->isReached() == false && next->getEnemiesCount() < min)
			min_index = next->getID(), min = next->getEnemiesCount();
	}
	std::cout << "minKey: " << min_index << ", weight " << min << std::endl;
	return min_index;
}


///Breadth First Search
list<int> Map::BFS(Room* begin, Room* end)
{
	queue<Room*> q; // Queue for BFS
	map<int, list<int>> path;
	
	q.push(begin);
	path[begin->getID()].push_back(begin->getID());
	

	while (!q.empty())
	{
		begin = q.front();
		begin->setReached(true);
		q.pop();


		for (const auto& p : begin->getAllPossiblePassages()) {
			if (p.second->IsCollapsed() == false) {
				Room* next = p.second->GetRoom(p.first);

				if (!next->isReached()) {
					//if not already has been found
					next->setReached(true);
					path[next->getID()] = path[begin->getID()];
					path[next->getID()].push_back(next->getID());
					q.push(next);
				}
				if (end == next) {
					return path[end->getID()];
				}
			}
		}
	}
	return path[end->getID()];
}


void Map::show() {
	string rowS = "";
	int row = 1;
	for (int y = 0; y < height; y++) {
		
		for (int x = 0; x < width; x++)
		{
			Room* r = getRoom(x, y);
			if (row == (width+1)) {
				std::cout << "\n" + rowS + "\n";
				row = 1;
				rowS = "";
			}
			if (r->isReached() && ! r->isShortest()) {
				std::cout << green;
			}
			else if (r->isShortest()) {
				std::cout << red;
			}
			std::cout << r->displayHorizontal();
			std::cout << white;//reset color
			rowS += r->displayVertical();
			row++;
		}
	}
	std::cout << "\n\n";
}


void Map::collapseByExplosion()
{
	this->mst.Kruskals(*this);
	this->mst.Print();
	//this->mst.Display(*this);

	std::vector<edge> nonMST = this->mst.GetNonMSTEdges(*this);

	int max = rooms.size() < 15 ? rooms.size()/2 : 15;
	int min = rooms.size() < 10 ? 1 : 10;
	std::uniform_int_distribution<int> d{ min, max };
	std::uniform_int_distribution<int> dd{ 0, (int)nonMST.size()-1 };
	int size = d(dre), count=0;
	int u, v;

	//Destroy 10-15 Passages
	while (count < size) {
		edge pair = nonMST[dd(dre)];
		u = pair.first;
		v = pair.second;

		Room* ur = rooms.at(u);
		Room* uv = rooms.at(v);

		Direction d = getDirection(*ur, *uv);
		ur->collapsePassage(d);
		count++;
		show();
	}
	
}

//Find shortest path in the maze
//returns amount of steps hero needs to make until the stairs down
int Map::talisman()
{
	int steps = 0;
	Hero* h = game->getHero();
	if (h == nullptr) return -1;
	resetRooms();
	if (h->getCurrentRoom()->getMapLevel() != level) return -1;

	list<int> path = BFS(h->getCurrentRoom(), getEndRoom());
	list<int>::iterator it;
	for (it = path.begin(); it != path.end(); ++it) {
		rooms[(*it)]->setShortest(true);
		steps++;
	}
	return steps;
}

void Map::resetRooms()
{//reset BSF && isShortest
	for (auto& r : rooms) {
		r->reset();
	}
}

Room* Map::createRoom(int id, int x, int y) {
	std::default_random_engine dre;
	return new Room(id, x, y, this);
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

vector<Room*> Map::getNeighbours(int x, int y)
{
	vector<Room*> tmp; 
	int maxX = y  * width + (width - 1);
	int minX = y  * width;

	int north = (y-1) * width + x;
	int east = y * width + (x+1);
	int south = (y+1) * width + x;
	int west = y * width + (x-1);

	int southH = y*width + (x + 1) - width - 1;
	
	//if (north >= 0 && y >= 0 && y <= (height - 1))
	if (north >= 0 && y >= 0 && y <= (height-1) && !rooms[north]->isVisited() )
	{
		tmp.push_back(rooms[north]);
	}
	//if (east >= minX && east <= maxX) {
	if(east >= minX && east <= maxX && !rooms[east]->isVisited()) {
		tmp.push_back(rooms[east]);
	}
	
	//if (south >= 0 && south <= rooms.size() - 1 && y <= (height - 1)) {
	if (south >= 0 && south <= rooms.size()-1 && y <= (height - 1) && !rooms[south]->isVisited()) {
		tmp.push_back(rooms[south]);
	}

	if (west >= minX && west <= maxX && !rooms[west]->isVisited()) {
	//if (west >= minX && west <= maxX){
		tmp.push_back(rooms[west]);
	}

	return tmp;
}


Room* const Map::getRoom(int x, int y)
{
	return this->rooms[y*width + x];
}

Room * const Map::getRoom(int ID)
{
	return this->rooms[ID];
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


