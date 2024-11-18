#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "App.h"

using namespace std;

void writef(string text) {
	ofstream f("local2.txt");
	f.write(text.c_str(), text.length());
	f.close();
}

string readf() {
	ifstream f("local2.txt");
	stringstream s;
	s << f.rdbuf();
	return s.str();
}

int main() {
	//cout << readf()/* << endl;
	//string s = readf();
	//writef(s + " hello world\n");
	//cout << readf() << endl;
	//s = readf();
	//for (auto ss : s) {
	//	cout << (ss == '\n');
	//}
	//cout << endl;*/

	App& app = App::getAppInstance();
}