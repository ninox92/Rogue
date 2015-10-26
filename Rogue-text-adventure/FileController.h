#pragma once
#include <iostream>
#include <map>
#include <vector>

using namespace std;


class FileController
{
	private:
		const string textfile { "file.txt" };
		map<string, vector<string>> roomDescription;
	public:
		FileController();
		~FileController();

		void readFile();

		string roomDescriptionToString();

		vector<string> &split(const string &s, char delim, vector<string> &elems);
		vector<string> split(const string &s, char delim);
};