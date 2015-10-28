#pragma once
#include "Dijkstras.h"
#include <limits>
#include "Map.h"
#include <set>
#include <algorithm>
#include <functional>     // std::greater

Dijkstras::Dijkstras()
{

}


Dijkstras::~Dijkstras()
{
}

//N E // number of nodes and edges
//E lines containing an edge(u, v, w) on each line // edge(u, v, w) means weight of edge u-v is w. Nodes u, v are within range 1 to N
//S // starting node
int Dijkstras::Compute(Map* map, int start, int end)
{//http://zobayer.blogspot.nl/2009/12/dijkstras-algorithm-in-c.html

	std::vector<Room*> rooms = map->getRooms();
	if (rooms.size() == 0) return INT_MAX;
	map->resetRooms();
	int n = rooms.size();//Rooms
	int u, v, i, c, w;
	
	//Reset the distance array and set INF as initial value.
	d.resize(n);
	std::fill(d.begin(), d.end(), INT_MAX);
	
	std::priority_queue< pii, std::vector< pii >, std::greater< pii > > Q;

	/*
	The source node will have weight 0. We push (0, start) in the
	priority queue as well that denotes start node has 0 weight.
	*/
	Q.push(pii(0, start));
	d[start] = 0;
	parents[start] = start;//Begin at the start point

	while (!Q.empty()) {
		u = Q.top().second; // node
		c = Q.top().first; // node cost so far
		Room* room = map->getRoom(u);
		Q.pop(); // remove the top item.
		
		/*
		We have discarded the visit array as we do not need it.
		If d[u] has already a better value than the currently
		popped node from queue, discard the operation on this node.
		*/
		if (d[u] < c) continue;

		/*
		For optimization break here if you have found the end point
		*/
		//if (u == end) return d[u];
		/*
		Traverse the adjacent nodes of u. Remember, for the graph,,
		the pair is assumed to be (node, weight). Can be done as
		you like of course.
		*/
		for (const auto& p : room->getAllPossiblePassages()) 
		{
			Room* next = p.second->GetRoom(p.first);
			v = next->getID(); // node 
			w = next->getWeight() + 1; // edge weight

			if (p.second->IsCollapsed() == false) 
			{
				//v = next node ID
				//u = Current node to look adjacent from
				if (d[u] + w < d[v]) {
					d[v] = d[u] + w;
					//printf("v=%d \t u=%d \t d[v]=%d \t (d[u]+w)=%d\n", v, u, d[v], (d[u] + w));
					Q.push(pii(d[v], v));
					parents[v] = u;
				}
			}
		}
	}

	bool valid = this->IsValid(start, end);
	return valid ? d[end] : INT_MAX;
}

std::vector<int> Dijkstras::GetPath(int start, int end)
{
	if (!IsValid(start, end)) return std::vector<int>();
	
	std::vector<int> tmp;
	for (int v = end; v != start; v = parents[v])
		if (v != INT_MAX)
			tmp.push_back(v);

	tmp.push_back(start);

	std::reverse(tmp.begin(), tmp.end());
	PATH = tmp;// set copy
	return PATH;
}

bool Dijkstras::IsValid(int start, int end)
{
	if (d[end] >= INT_MAX) return false;

	for (int v = end; v != start; v = parents[v]) 
		if (v == INT_MAX)
			return false;
		
	return true;
}

void Dijkstras::Display(Map* map, int start, int end)
{
	printf("ID \t Distance \n");
	if (!IsValid(start,end)) {
		printf("to node %d: unreachable\n", end);
		return;
	}
	printf("%d \t %d\n", end, d[end]);

	printf("PATH = ");
	for (const auto& p : GetPath(start,end)) {
		map->getRoom(p)->setShortest(true);
		printf("%d,", p);
	}

	printf("\n\n");
	map->show();
	map->resetRooms();
}
