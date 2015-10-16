#include "InputController.h"
#include <algorithm>
using namespace std;



InputController::InputController()
{
}


InputController::~InputController()
{
}

string InputController::WaitAndGetInput()
{
	cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

Direction InputController::getDirectionFromInput()
{
	cout << "Wich way should we explore?" << endl;
	cout << "north, east, south, west" << endl;
	string s_dir = WaitAndGetInput();
	bool exists = stringDirMap.find(s_dir) != stringDirMap.end();
	if (!exists) return Direction::NONE;
	return this->stringDirMap[s_dir];
	/*switch (e_dir)
	{
	case Direction::NORTH:
		dir = Direction::NORTH;
		break;
	case Direction::EAST:
		dir = Direction::EAST;
		break;
	case Direction::SOUTH:
		dir = Direction::SOUTH;
		break;
	case Direction::WEST:
		dir = Direction::WEST;
		break;
	default:
		dir = Direction::NONE;
		break;
	}
	return dir;*/
}
