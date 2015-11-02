#include "FileController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

FileController::FileController()
{
	readFile();
}

FileController::~FileController()
{
}

void FileController::readFile()
{
	ifstream input_file{ textfile };
	string line, nextLine;

	while (getline(input_file, line)) {
		if(line[0] == '#')
		{
			string id = line.erase(0, 1);
			getline(input_file, nextLine);
			descriptions[id] = split(nextLine, ';');;
		}
	}
}

string FileController::getRandomDesc(string id)
{
	int size = descriptions.find(id)->second.size() - 1;
	std::uniform_int_distribution<int> dist{ 0, size };

	int i = dist(dre);
	return descriptions.find(id)->second[i];
}

string FileController::roomDescriptionToString()
{	
	return "Room Description: It is a " + getRandomDesc("roomSize") + " " + getRandomDesc("roomClean") 
			+ " " + getRandomDesc("roomLayout") + " The room is lit by a " + getRandomDesc("roomLight") + " and there is " + getRandomDesc("roomWall");
}

string FileController::trapDescriptionToString()
{
	return getRandomDesc("trapDesc");
}

vector<NPC*> FileController::getRandomEnemies(int nEnemies)
{
	int size = descriptions.find("npcName")->second.size() - 1;
	std::uniform_int_distribution<int> dist{ 0, size };
	int i = dist(dre);

	int size2 = descriptions.find("npcSize")->second.size() - 1;
	std::uniform_int_distribution<int> dist2{ 0, size2 };
	int i2 = dist2(dre);

	int size3 = descriptions.find("npcDesc")->second.size() - 1;
	std::uniform_int_distribution<int> dist3{ 0, size3 };
	int i3 = dist3(dre);

	vector<NPC*> enemies;
	for (int a = 0; a < nEnemies; a++)
	{
		string npcName = descriptions.find("npcName")->second[i];
		npcName += " " + std::to_string(a + 1);
		string npcSize = descriptions.find("npcSize")->second[i2];
		string npcDesc = descriptions.find("npcDesc")->second[i3];

		int size4 = descriptions.find("npcAttackDesc")->second.size() - 1;
		std::uniform_int_distribution<int> dist4{ 0, size4 };
		int i4 = dist4(dre);
		string npcAttackDesc = descriptions.find("npcAttackDesc")->second[i4];

		enemies.push_back(new NPC(npcName, npcSize, npcDesc, npcAttackDesc));
	}

	return enemies;
}

vector<string>& FileController::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


vector<string> FileController::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}