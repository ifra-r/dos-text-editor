#include "dos.h"
using namespace std;

dos::dos() {
	root = new directory("V:\\", nullptr);
	current = root;
}
dos::~dos() {
	delete root;
}
//directory navigation functions
void dos::cd(string dirname) {
	directory* temp = current->get_subdirectory_by_name(dirname);
	if (temp != nullptr) {
		current = temp;
		return;
	}
	cout << "directory not found";
}
string dos::get_dir_path(directory* d) {
	directory* temp = d;
	string path = "";
	while (temp != nullptr) {
		path = "\\" + temp->name + path;
		temp = temp->parent;
	}
	return path;
}
void dos::pwd() {
	if (current != nullptr) {
		cout << get_dir_path(current) << endl;		//<< "V:"
	}
	else
		cout << "error! current dir nor set!";
}
void dos::cd_to_parent() {
	directory* p = current->parent;
	if (p != nullptr)
		current = p;
	else
		cout << "already at root dir" << endl;
}
void dos::cd_root() {
	if (root != nullptr) {
		current = root;
		return;
	}
	else
		cout << "already at root dir" << endl;
}
void dos::mkdir(const string& dirName){
	if (current->dirAlreadyExists(dirName)) {
		cout << "dor already exists.." << endl;
		return;
	}
	directory* temp = new directory(dirName, current);			//need to set parent here
	current->addSubDirectory(temp);
}
void dos::rmdir(const string& dirName) {
	directory* temp = current->get_subdirectory_by_name(dirName);
	if (temp) {
		current->delSubDirectory(temp);
		return;
	}
	cout << "dir not found!" << endl;
}
void dos::Tree() {
	current->tree(0);
}
void dos::createFile(const string& fileName) {
	if (current->containsFile(fileName)) {
		cout << "file already exists" << endl;
		return;
	}
	string filepath = get_dir_path(current) + "\\" + fileName;
	current->createFile(fileName, filepath);
}
void dos::deleteFile(const std::string& fileName) {
	file* temp = current->getFile(fileName);
	if (temp) {
		current->remFile(temp);
	}
}
void dos::dir() {
	if (current)
		current->listContents();
	else
		cout << "current not set?!" << endl;
}
void dos::copyFile(file* f) {
	file* temp = current->find_file_with_name(f->filename);
	if (temp != nullptr) {
		current->addFile(temp);
	}
	else
		cout << "file not found!" << endl;
}
void dos::copyFileWithName(string n) {
	file* temp = current->find_file_with_name(n);
	if (temp != nullptr) {
		current->addFile(temp);
	}
	else
		cout << "file not found!" << endl;
}
file* dos::findFile(string n) {
	file* temp = current->find_file_with_name(n);
	return temp;
}
void dos::moveFile(string fname) {
	file* temp = findFile(fname);
	if (temp != nullptr)
		current->addFile(temp);
	else
		cout << "file not found!" << endl;
}
void dos::renameFile(string oldname, string newname) {
	file* f = findFile(oldname);
	if (f == nullptr) {
		cout << "file doesnt exist" << endl;
		return;
	}
	f->filename = newname;
}

void dos::help() {
	cout << "\nAvailable commands:\n"
		<< "cd <dir>       : Change directory\n"
		<< "cd..           : Move to parent directory\n"
		<< "cd/            : Move to root directory\n"
		<< "mkdir <dir>    : Create a new directory\n"
		<< "rmdir <dir>    : Remove a directory\n"
		<< "create <file>  : Create a new file\n"
		<< "delete <file>  : Delete a file\n"
		<< "dir			   : displays contents of current directory\n"
		<< "dir            : List contents of the current directory\n"
		<< "pwd            : Print current working directory\n"
		<< "tree           : Display directory tree\n"


		<< "edit <file>    : Open a file for editing\n"
		<< "exit           : Exit the shell\n";
	return;
}
