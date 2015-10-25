#include "InputController.h"
#include <algorithm>

using namespace std;



InputController::InputController()
{
}


InputController::~InputController()
{
}

void InputController::printMessage(std::string s)
{
	cout << s << endl << endl;
}

string InputController::WaitAndGetInput()
{
	cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

Direction InputController::getDirectionFromInput(std::map<std::string, Direction> dirMap)
{
	std::string dirs = "[";
	for (const auto& kv : dirMap) {
		dirs += kv.first + ":";
	}
	dirs = dirs.substr(0, dirs.size() - 1);
	dirs += "]";
	
	cout << "Wich way should we explore?" << endl;
	cout << dirs << endl;
	string s_dir = WaitAndGetInput();
	bool exists = stringDirMap.find(s_dir) != stringDirMap.end();
	if (!exists) getDirectionFromInput(dirMap);//recursive call if not found

	return this->stringDirMap[s_dir];
}
