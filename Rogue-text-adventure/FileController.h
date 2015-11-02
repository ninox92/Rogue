#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "NPC.h"
#include <random>

using std::string;
using std::map;
using std::vector;

class FileController
{
	private:
		const string textfile { "file.txt" };
		map<string, vector<string>> descriptions;

		std::random_device rd;
		std::default_random_engine dre{ rd() };
	public:
		FileController();
		~FileController();

		void readFile();

		string getRandomDesc(string id);
		string roomDescriptionToString();
		string trapDescriptionToString();

		vector<NPC*> getRandomEnemies(int nEnemies);
		vector<NPC*> getRandomEndBoss();

		vector<string> &split(const string &s, char delim, vector<string> &elems);
		vector<string> split(const string &s, char delim);
};