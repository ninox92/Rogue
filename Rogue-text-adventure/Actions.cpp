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
	EXTREME_DIJKSTRA, // Place a extreme weight in the first node of the dijkstra path
	BFS,//Find shortest route
	LVLUP,// Lvl up hero
	HPUP, // restore health
	REVEAL, // Reveal the whole map

	//Stats
	UP_ATTACK,
	UP_DEFENSE,
	UP_MINDFULLNESS,

	//Inventory
	TALISMAN,
	GRENADE,
	COMPASS,
};

#endif