#ifndef ACTIONS_O
#define ACTIONS_O
enum class Actions
{
	FIGHT,
	FLEE,
	SEARCH,
	REST,
	INVERTORY,
	MAP,
	STATS,

	//Hidden actions
	MST, //minimum spanning tree
	DIJKSTRA, //Find shortest route in MST
	BFS,//Find shortest route
	LVLUP,// Lvl up hero
	HPUP, // restore health
	REVEAL // Reveal the whole map
};

#endif