#pragma once
#include "utility.h"
#include "file.h"
using namespace std;

class directory {
public:
	string name;
	string path;
	vector <file*> files;
	vector <directory*> subDirectories;
	directory* parent;

	//directory(string dname);
	directory(string dname, string path);
	directory(string n, directory* _parent = nullptr);
	void setParent(directory* p);

	void addSubDirectory(directory* subDir);
	void delSubDirectory(directory* subDir);

	bool containsFile(string name);
	file* getFile(const string& fname);
	void createFile(string file_name, string path);
	void addFile(file* myfile);
	void remFile(file* myfile);
	file* find_file_with_name(string fname);


	void tree(int level = 0);			//to display structure of files and dirs

	bool dirAlreadyExists(string dname);
	directory* get_subdirectory_by_name(const string& dirName);
	void containsDir(directory* d);
	void listContents();
};

//funcs:
//Tree structure management :
//	create files
//	Add / remove files or subdirectories.
//	Search files(FIND, FINDF).
//	Display tree structure(TREE).
//
//Directory navigation :
//	Change directory(CD, CD.., CD\).
//	Print working directory(PWD).

