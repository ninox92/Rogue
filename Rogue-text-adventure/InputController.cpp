#include "InputController.h"
#include <algorithm>
#include <iostream>

using namespace std;



InputController::InputController()
{
}


InputController::~InputController()
{
}

void InputController::clearConsole()
{
	system("cls");
}

void InputController::pressEnterToContinue()
{
	system("pause");
	printEmptyLine();
}

void InputController::printEmptyLine()
{
	cout << endl;
}

void InputController::printMsg(std::string s)
{
	cout << s << endl;
}

void InputController::printMessage(string s)
{
	cout << s << endl << endl;
}

string InputController::WaitAndGetInput()
{
	getline(cin, input);
	//cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

string InputController::getFightInput()
{
	getline(cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

void InputController::printDirections(std::map<std::string, Direction> dirMap)
{
	std::string dirs = "[";
	for (const auto& kv : dirMap) {
		dirs += kv.first + ":";
	}
	dirs = dirs.substr(0, dirs.size() - 1);
	dirs += "]";

	cout << "Which way should we explore?" << endl << endl;
	cout << dirs << endl << endl;
}

Direction InputController::getDirectionFromInput()
{
	cout << "Direction: ";
	string s_dir = WaitAndGetInput();
	bool exists = stringDirMap.find(s_dir) != stringDirMap.end();
	if (!exists) getDirectionFromInput();//recursive call if not found

	return this->stringDirMap[s_dir];
}
