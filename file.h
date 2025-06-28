#pragma once
#include "utility.h"
using namespace std;

class file {
public:
	string filename;
	int size;
	string path;
public:
	file(string nameoffile, string path);
	file(string nameoffile);
	void setSize(int s);
	int getSize();
	void setPath(string p);
	string getPath();

};

