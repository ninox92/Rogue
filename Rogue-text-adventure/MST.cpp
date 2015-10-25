#pragma once
#include "MST.h"
#include "Room.h"



MST::MST()
{
}


MST::~MST()
{
}


int MST::findset(int x, std::vector<int> parent)
{
	if (x != parent[x])
		parent[x] = findset(parent[x], parent);
	return parent[x];
}

void MST::Kruskals(std::vector<Room*> rooms)
{
	if (rooms.size() == 0) return;
	int w, u, v;
	Nodes = rooms.size();
	this->parent.reserve(Nodes);


	for (auto& r : rooms) {
		u = r->getID();
		parent.push_back(u);
		for (const auto& p : r->getAllPossiblePassages())
		{
			Room* next = p.second->GetRoom(p.first);
			w = next->getEnemiesCount() + 1;
			v = next->getID();
			Edges++;
			if (next->isReached() == false) {
				GRAPH.push_back(std::pair< int, edge >(w, edge(u, v)));
				next->setReached(true);
			}
		}
	}


	int i, pu, pv;
	sort(GRAPH.begin(), GRAPH.end()); // increasing weight
	for (i = total = 0; i<Nodes; i++)
	{
		pu = findset(GRAPH[i].second.first, parent);
		pv = findset(GRAPH[i].second.second, parent);
		if (pu != pv)
		{
			_MST.push_back(GRAPH[i]); // add to tree
			total += GRAPH[i].first; // add edge cost
			rooms[pv]->setShortest(true);
			parent[pu] = parent[pv]; // link
		}
	}
}



void MST::Print()
{
	int i, sz;
	// this is just style...
	sz = _MST.size();
	for (i = 0; i<sz; i++)
	{
		//w=weight
		//u=src
		//v=dest
		// ( w (u, v) ) format
		printf("( %d", _MST[i].second.first);
		printf(", %d )", _MST[i].second.second);
		printf(": %d\n", _MST[i].first);
	}
	printf("Minimum cost: %d\n", total);
}

void MST::Display(std::vector<Room*> rooms)
{

}
