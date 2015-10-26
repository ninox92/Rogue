#pragma once
#include <limits>  
#include <vector>
#include <queue>
#include <list>
#include <map>

class Map;
class Room;
typedef std::pair< int, int > pii;

class Dijkstras
{
private:
	
	/*
	pair object for graph is assumed to be (node, weight). d[] array
	holds the shortest path from the source. It contains INF if not
	reachable from the source.
	*/
	std::map<int, int> parents;
	std::vector<int> d;
	std::list<int> PATH;
	

public:
	Dijkstras();
	~Dijkstras();

	int Compute(Map* map, int start, int end);
	std::list<int> GetPath(int start, int end);
	bool IsValid(int start, int end);
	void Display(Map* map, int start, int end);

};

