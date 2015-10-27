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

string FileController::roomDescriptionToString()
{	
	return "Room Description: It is a " + getRandomDesc("roomSize") + " " + getRandomDesc("roomClean") 
			+ " " + getRandomDesc("roomLayout") + " The room is lit by a " + getRandomDesc("roomLight") + ".";
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