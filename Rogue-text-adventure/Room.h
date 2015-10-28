#pragma once
#include <map>
#include <random>
#include "GameObject.h"
#include "Hero.h"
#include "Passage.h"
#include "RoomType.cpp"

class Map;

class Room : public GameObject
{
private:
	int ID = -1;
	Map* map = nullptr;
	
	int spawnChange = 0;// % chance that enemies will spawn in this room
	int maxEnemies = 3;//maximum
	int enemiesCount = 0;
	int row = 0;
	int col = 0;
	
	int weight = 0;
	std::random_device rd;

	// Choose a random mean between 1 and 6
	std::default_random_engine dre { rd() };
	std::uniform_int_distribution<int> dist{ 0, 100 };// 0 - 100% spawn chance
	std::uniform_int_distribution<int> eDist;//{ 0, maxEnemies };// amount of enemies that may spawn in one room
	

	RoomType type = RoomType::INIT;
	std::string size;
	
	Hero* hero = nullptr;
	bool _isClean = false;
	bool _isReached = false;
	bool _isVisited = false;
	bool _isShortest = false;

	std::map<Direction, Passage*> passages;

	std::string getToken();
	std::string roomDesc;

	void createEnemies();
public:
	Room();
	Room(int id, int x, int y, Map* map);
	virtual ~Room();
	
	void setType(RoomType type) { this->type = type; }
	RoomType const getType() { return this->type; }

	int const getID() { return this->ID; }
	int const getX() { return this->col; }
	int const getY() { return this->row; }
	int const getMapLevel();
	int const getWeight() { return this->weight; }// == <<--------------------------------------------------------
	std::map<std::string, Direction> getAllPossibleMoveDirections();
	std::map<Direction, Passage*> getAllPossiblePassages();
	Passage* const getPassage(Direction d);
	Passage* const getPassage(int x, int y);

	bool const hasHero() { return hero == nullptr ? false : true; }
	bool const isClean() { return this->_isClean; }// Is the room clean
	bool const isVisited() { return this->_isVisited; } // is the room explored
	bool const isShortest() { return this->_isShortest; }
	bool const isReached() { return this->_isReached; }
	bool const hasPassage(Direction d);
	void visit(); // visit the room

	std::string displayHorizontal();
	std::string displayVertical();

	void setReached(bool b) { this->_isReached = b; }
	void setHero(Hero* h) { this->hero = h; }
	void setShortest(bool s) { this->_isShortest = s; }
	void setPassage(Direction dir, Passage* p);
	void setWeight(int w) { this->weight = w; }

	std::string getRoomDesc() { return this->roomDesc; }
	void setRoomDesc(std::string r) { this->roomDesc = r; }
	std::string getPassageDesc();
	
	void collapsePassage(Direction dir);
	
	void reset() {
		setReached(false);
		setShortest(false);
	}
};
