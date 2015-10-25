#include "Dijkstras.h"

#include <limits>
#include "Map.h"
#include <set>
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
void Dijkstras::Compute(Map & map, int start, int end)
{//http://zobayer.blogspot.nl/2009/12/dijkstras-algorithm-in-c.html

	std::vector<Room*> rooms = map.getRooms();
	if (rooms.size() == 0) return;
	int n = rooms.size();//Rooms
	map.resetRooms();
	map.show();
	std::priority_queue< pii, std::vector< pii >, std::greater< pii > > Q;

	int u, v, i, c, w;

	/*
	Reset the distance array and set INF as initial value. The
	source node will have weight 0. We push (0, start) in the
	priority queue as well that denotes start node has 0 weight.
	*/
	memset(d, INF, sizeof d);
	Q.push(pii(0, start));
	d[start] = 0;

	while (!Q.empty()) {
		u = Q.top().second; // node
		c = Q.top().first; // node cost so far
		Room* room = map.getRoom(u);
		Q.pop(); // remove the top item.

		/*
		We have discarded the visit array as we do not need it.
		If d[u] has already a better value than the currently
		popped node from queue, discard the operation on this node.
		*/
		if (d[u] < c) continue;
		//if (u == end) return d[u];
		/*
		Traverse the adjacent nodes of u. Remember, for the graph,,
		the pair is assumed to be (node, weight). Can be done as
		you like of course.
		*/
		for (const auto& p : room->getAllPossiblePassages()) {
			if (p.second->IsCollapsed() == false) {
				Room* next = p.second->GetRoom(p.first);
				v = next->getID(); // node 
				w = next->getEnemiesCount() + 1; // edge weight
				next->setReached(true);
				map.show();
				if (d[v] > d[u] + w) {
					d[v] = d[u] + w;
					Q.push(pii(d[v], v));
				}
			}
		}

	}

	map.show();
	Display(map, end);
	map.resetRooms();
}

void Dijkstras::Display(Map & map, int endID)
{
	printf("Vertex ID \t Distance from source\n");
	if(d[endID] >= INF)printf("\t to node %d: unreachable\n", endID);
	else printf("\t to node %d: %d\n", endID, d[endID]);
}
