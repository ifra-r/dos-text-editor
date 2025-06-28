#pragma once
#include "directory.h"
class dos {
public:
	directory* current;
	directory* root;

	dos();
	~dos();

	string get_dir_path(directory* d);   void insertChar(char ch);
    void deleteChar();
    void moveCursor(int rowOffset, int colOffset);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void printDocument();
	void pwd();
	void cd(string dirname);
	void cd_to_parent();
	void cd_root();

	void mkdir(const string& dirName);
	void rmdir(const string& dirName);

	file* findFile(string n);
	void createFile(const std::string& fileName);
	void deleteFile(const std::string& fileName);
	void copyFile(file* f);
	void copyFileWithName(string n);
	void moveFile(string fname);
	void renameFile(string oldname, string newname);

	void Tree();
	void dir();

	void help();
};

