#pragma once

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class OutLog {
public:
	static void log(string e) {
		fstream olf = fstream("ErrLog.txt", ios::binary | ios::in | ios::out);
		if (!olf.is_open()) {
			cerr << "ErrLog.txt file opennig error" << endl;
			olf.close();
			return;
		}

		olf.write(e.c_str(), e.size());
	}
};