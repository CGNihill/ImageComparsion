#include "App.h"

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
		throw std::runtime_error("locase user data load error");

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

	std::cout << UserData.composeUserData() << std::endl;
}

App& App::getAppInstance() {
	if (!(app)) {
		app = new App();
	}
	return *app;
}