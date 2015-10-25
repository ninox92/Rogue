#pragma once
#include <vector>
#include <algorithm>
#define edge std::pair< int, int >

class Room;
class Map;

class MST
{
private:
	int total = 0;
	int Nodes = 0;
	int Edges = 0;
	std::vector<int> parent;
	
	//w=weight
	//u=src
	//v=dest
	// ( w (u, v) ) format
	std::vector< edge > EDGES;
	std::vector< std::pair< int, edge > > GRAPH, _MST;


	int findset(int x, std::vector<int> parent);

public:
	MST();
	~MST();

	void Kruskals(Map& map);
	std::vector< edge > GetNonMSTEdges(Map& map);
	void Print();
	void Display(Map& map);
	std::vector< std::pair< int, edge > > const GetMST() { return _MST; }
	int const Size() { return this->total; }

};

