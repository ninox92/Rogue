#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "NPC.h"

using std::string;
using std::map;
using std::vector;

class FileController
{
	private:
		const string textfile { "file.txt" };
		map<string, vector<string>> descriptions;
	public:
		FileController();
		~FileController();

		void readFile();

		string getRandomDesc(string id);
		string roomDescriptionToString();

		vector<NPC*> FileController::getRandomEnemies(int nEnemies);

		vector<string> &split(const string &s, char delim, vector<string> &elems);
		vector<string> split(const string &s, char delim);
};