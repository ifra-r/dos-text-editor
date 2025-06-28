#include "directory.h"
using namespace std;

//directory::directory(string dn) :name(dn) {}
directory::directory(string dname, string p) :name(dname), path(p) {}
directory::directory(string n, directory* _parent) {
	this->name = n;
	this->parent = _parent;
}
void directory::setParent(directory* p) {
	this->parent = p;
}
void directory::addSubDirectory(directory* subDir) {
	subDirectories.push_back(subDir);
}
void directory::delSubDirectory(directory* subDir) {
	for (auto it = subDirectories.begin(); it != subDirectories.end(); it++) {
		if (*it == subDir) {
			subDirectories.erase(it);
			delete subDir;					//to prevent mem leaks
			return;
		}
	}
	cout << "subdirectory not found" << endl;
}
bool directory::containsFile(string name) {
	for (const auto& file: files) {
		if (file->filename == name) {
			return true;
		}
	}
	return false;
}
file* directory::getFile(const string& fname) {
	for (const auto& file : files) {
		if (file->filename == fname) {
			return file;
		}
	}
	return nullptr;
}
void directory::createFile(string file_name, string path = "") {
	if (containsFile(file_name)) {
		cout << "file already exists";
		return;
	}
	file* newfile = new file(file_name);
	// set its path
	newfile->setPath(this->path);	//	+ '/'	
	addFile(newfile);				// finally add it to vec list files by addfile func
}
void directory::addFile(file* myfile) {
	files.push_back(myfile);
}
void directory::remFile(file* myfile) {
	for (auto it = files.begin(); it != files.end(); it++) {
		if (*it == myfile) {
			files.erase(it);
			delete myfile;
			return;
		}
	}
	cout << "file not found" << endl;
}
void directory::tree(int level) {
	for (int i = 0; i < level; i++) {
		cout << "\t";				// Indentation for the current level
	}
	cout << name << "\\" << endl;	//current directory ka name
	//print all files in this directory
	for (file* my_file : files) {
		for (int i = 0; i < level + 1; i++) {
			cout << "\t";
		}
		cout << my_file->filename << endl;
	}
	//now, print all sub dirs
	for (directory* d : subDirectories) {
		d->tree(level + 1);
	}
}
file* directory::find_file_with_name(string fname) {
	for (auto it = files.begin(); it != files.end(); it++) {
		file* temp = *it;
		if (temp->filename == fname) {
			return temp;
		}
	}
	return nullptr;
}
directory* directory::get_subdirectory_by_name(const string& dirName) {
	for (directory* subdir : subDirectories) {
		if (subdir->name == dirName) {
			return subdir;
		}
	}
	return nullptr;  // Not found
}
bool directory::dirAlreadyExists(string dname) {
	directory* t = get_subdirectory_by_name(dname);
	if (t == nullptr)
		return false;			//dir doesnt exist
	return true;
}
void directory::listContents() {
	cout << name << endl;	// directory name						<< "\\" 
	//print all files in this directory
	for (file* my_file : files) {
		cout << "\t" << my_file->filename << endl;
	} 
	//now, print all sub dirs
	for (directory* d : subDirectories) {
		cout << "\t" << d->name << endl;
	}
}

