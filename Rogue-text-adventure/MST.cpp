#pragma once
#include "MST.h"
#include "Room.h"
#include "Map.h"


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

void MST::Kruskals(Map& map)
{
	std::vector<Room*> rooms = map.getRooms();
	if (rooms.size() == 0) return;
	map.resetRooms();

	int w, u, v;
	Nodes = rooms.size();
	this->parent.reserve(Nodes);


	for (auto& r : rooms) {
		u = r->getID();
		parent.push_back(u);
		for (const auto& p : r->getAllPossiblePassages())
		{
			Room* next = p.second->GetRoom(p.first);
			w = next->getWeight() + 1;
			v = next->getID();
			Edges++;
			if (next->isReached() == false) {
				edge e{ u, v };
				EDGES.push_back(e);
				GRAPH.push_back(std::pair< int, edge >(w, e));
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
			parent[pu] = parent[pv]; // link
		}
	}
	map.resetRooms();
}

std::vector<edge> MST::GetNonMSTEdges(Map& map)
{
	std::vector<Room*> rooms = map.getRooms();
	if (rooms.size() == 0) return std::vector<edge>();
	map.resetRooms();
	std::vector<edge> tmp;
	int u, v;

	for (auto& r : rooms) {
		u = r->getID();
		parent.push_back(u);
		for (const auto& p : r->getAllPossiblePassages()){
			Room* next = p.second->GetRoom(p.first);
			v = next->getID();
			if (next->isReached() == false) {
				edge e{ u, v };
				if (std::find(EDGES.begin(), EDGES.end(), e) == EDGES.end()) {
					tmp.push_back(e);
					next->setReached(true);
				}
			}
		}
	}
	return tmp;
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

void MST::Display(Map& map)
{
	std::vector<Room*> rooms = map.getRooms();
	if (rooms.size() == 0) return;

	int i, u, v, sz;
	// this is just style...
	sz = _MST.size();
	for (i = 0; i < sz; i++)
	{
		u = _MST[i].second.first;
		v = _MST[i].second.second;

		Room* ur = rooms.at(u);
		Room* uv = rooms.at(v);

		Direction d = map.getDirection(*ur, *uv);
		ur->getPassage(d)->SetShortest(true);


	}
	map.show();

	//Reset
	for (i = 0; i < sz; i++)
	{
		u = _MST[i].second.first;
		v = _MST[i].second.second;

		Room* ur = rooms.at(u);
		Room* uv = rooms.at(v);

		Direction d = map.getDirection(*ur, *uv);
		ur->getPassage(d)->SetShortest(false);
	}
}