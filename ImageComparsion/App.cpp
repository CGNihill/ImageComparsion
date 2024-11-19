#include "App.h"
#include "ErrLog.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

#include <iostream>

App* App::app = nullptr;

App::App() {
	// load user data;
	std::ifstream f("locale.txt");
	if (!f.is_open())
		LOG(true, "local user data load error");

	std::stringstream s;
	s << f.rdbuf();
	f.close();

	std::string l = "";
	std::vector<std::string> lines;
	while (getline(s, l))
		lines.push_back(l);

	if (lines.size() < 3)
		return;

	UserData.parseUserData(lines);

	//std::cout << "out compose start" << std::endl;
	std::string sss = UserData.composeUserData();
	std::cout << sss.length() << std::endl;
	std::cout << sss << std::endl;
	//std::cout << "out compose end" << std::endl;
}

App& App::getAppInstance() {
	if (!(app)) {
		app = new App();
	}
	return *app;
}