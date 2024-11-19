#include "App.h"
#include "ErrLog.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

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
}

App& App::getAppInstance() {
	if (!(app)) {
		app = new App();
	}
	return *app;
}