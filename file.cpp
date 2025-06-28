#include "file.h"
using namespace std;

file::file(string nameoffile, string p) :filename(nameoffile), path(p) {}
file::file(string nameoffile) :filename(nameoffile) {}
void file::setSize(int s) {
	size = s;
}
int file::getSize() {
	return size;
}
void file::setPath(string p) {
	path = p;
}
string file::getPath() {
	return path;
}



