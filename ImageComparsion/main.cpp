#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <utility>

#include "App.h"
#include "UserIOMain.h"
#include "ErrLog.hpp"

using namespace std;

int main() {
	UserIOMain u;
	u.mainProcess();
	return 0;
}