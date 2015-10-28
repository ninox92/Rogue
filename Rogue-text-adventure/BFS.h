#pragma once
#include <list>
#include <queue>

class Map;
class BFS
{
public:
	BFS();
	~BFS();

	std::list<int> ComputePath(Map* map, int start, int end);
	int ComputeSteps(Map* map, int start, int end);
	int ComputeStepsAndDisplay(Map* map, int start, int end);
};

