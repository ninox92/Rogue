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

Direction InputController::getDirectionFromInput(string possibleDirections)
{
	cout << "Wich way should we explore?" << endl;
	cout << possibleDirections << endl;
	string s_dir = WaitAndGetInput();
	bool exists = stringDirMap.find(s_dir) != stringDirMap.end();
	if (!exists) return Direction::NONE;
	return this->stringDirMap[s_dir];
}
