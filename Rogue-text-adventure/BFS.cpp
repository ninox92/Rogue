#include "BFS.h"
#include "Room.h"
#include "Map.h"
#include <map>
using std::queue;
using std::list;
using std::map;

BFS::BFS()
{
}


BFS::~BFS()
{
}

std::list<int> BFS::ComputePath(Map * map, int start, int end)
{
	queue<int> q; // Queue for BFS
	std::map<int, list<int>> path;

	map->resetRooms();
	q.push(start);
	path[start].push_back(start);

	int u, v;
	while (!q.empty())
	{
		u = q.front();
		Room* c = map->getRoom(u);
		q.pop();


		for (const auto& p : c->getAllPossiblePassages()) {
			if (p.second->IsCollapsed() == false) {
				Room* next = p.second->GetRoom(p.first);
				v = next->getID();
				if (!next->isReached()) {
					//if not already has been found
					next->setReached(true);
					path[v] = path[u];
					path[v].push_back(u);
					q.push(v);
				}
				if (end == next->getID()) {
					return path[end];
				}
			}
		}
	}
	return path[end];
}

int BFS::ComputeSteps(Map * map, int start, int end)
{
	int steps = 0;
	
	list<int> path = ComputePath(map, start, end);
	list<int>::iterator it;
	for (it = path.begin(); it != path.end(); ++it) {
		steps++;
	}

	map->resetRooms();
	return steps -1;
}

int BFS::ComputeStepsAndDisplay(Map * map, int start, int end)
{
	int steps = 0;
	map->resetRooms();

	list<int> path = ComputePath(map, start, end);
	list<int>::iterator it;
	for (it = path.begin(); it != path.end(); ++it) {
		map->getRoom((*it))->setShortest(true);
		steps++;
	}
	map->getRoom(end)->setShortest(true);
	map->show();
	map->resetRooms();
	return steps -1;
}
