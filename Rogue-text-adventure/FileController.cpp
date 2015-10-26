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
	string line;
	string nextLine;

	while (getline(input_file, line)) {
		
		// Room Description
		if(line == "#roomSize" || line == "#roomClean" || line == "#roomLayout" || line == "#roomLight")
		{
			string id = line.erase(0, 1);
			getline(input_file, nextLine);
			vector<string> v = split(nextLine, ';');
			roomDescription[id] = v;
		}
	}
}

string FileController::roomDescriptionToString()
{
	string roomSize, roomClean, roomLayout, roomLight;
	
	for (map<string, vector<string>>::iterator i = roomDescription.begin(); i != roomDescription.end(); ++i)
	{
		string id = i->first;
		int randomIndex = rand() % i->second.size();

		if(id == "roomSize") 
			roomSize = i->second[randomIndex];
		if (id == "roomClean")
			roomClean = i->second[randomIndex];
		if (id == "roomLayout")
			roomLayout = i->second[randomIndex];
		if (id == "roomLight")
			roomLight = i->second[randomIndex];
	}
	
	return "Room Description: It is a " + roomSize + " " + roomClean + " " + roomLayout + " The room is lit by a " + roomLight + ".";
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