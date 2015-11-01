#include "FileController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
	int i = rand() % descriptions.find(id)->second.size();
	return descriptions.find(id)->second[i];
}

// 5 x 3 x 3 x 3 = 135
string FileController::roomDescriptionToString()
{	
	return "Room Description: It is a " + getRandomDesc("roomSize") + " " + getRandomDesc("roomClean") 
			+ " " + getRandomDesc("roomLayout") + " The room is lit by a " + getRandomDesc("roomLight") + ".";
}

string FileController::trapDescriptionToString()
{
	return getRandomDesc("trapDesc");
}

vector<NPC*> FileController::getRandomEnemies(int nEnemies)
{
	int i = rand() % descriptions.find("npcName")->second.size();

	vector<NPC*> enemies;
	for (int a = 0; a < nEnemies; a++)
	{
		string npcName = descriptions.find("npcName")->second[i];
		npcName += " " + std::to_string(a + 1);
		string npcDesc = descriptions.find("npcDesc")->second[i];
		string npcAttackDesc = descriptions.find("npcAttackDesc")->second[i];

		enemies.push_back(new NPC(npcName, npcDesc, npcAttackDesc));
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