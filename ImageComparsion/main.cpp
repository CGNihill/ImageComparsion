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
	try
	{

		UserIOMain u;
		while (1) {
			cout << "- 1) MainProcess\n- 2) Settings\n- 0) Quit" << endl;
			short i;
			cin.clear();
			cin >> i;

			system("cls");
			switch (i)
			{
			case 0:
				return 0;
				break;
			case 1:
				u.mainProcess();
				break;
			case 2:
				u.settings();
				break;
			default:
				break;
			}
			system("cls");

		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}