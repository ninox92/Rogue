#pragma once
#include <limits>  
#include <vector>
#include <queue>

class Map;
class Room;
typedef std::pair< int, int > pii;

const int MAX = 1024;
const int INF = 0x3f3f3f3f;

class Dijkstras
{
private:
	
	/*
	pair object for graph is assumed to be (node, weight). d[] array
	holds the shortest path from the source. It contains INF if not
	reachable from the source.
	*/
	std::vector< pii > G[MAX];
	int d[MAX];

public:
	Dijkstras();
	~Dijkstras();

	void Compute(Map& map, int start, int end);
	void Display(Map& map, int end);
};

