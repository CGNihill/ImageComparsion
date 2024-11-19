#include "App.h"
#include "ErrLog.hpp"
#include "FileChecker.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <filesystem>

#include <iostream>

typedef FileChecker fc;
App* App::app = nullptr;

App::App() {
	// load user data;
	std::ifstream f("locale.txt");
	if (!f.is_open()) {
		// create a new local data file and set default valuse
		std::ofstream nf("locale.txt", std::ios::trunc);
		nf.write(UserData.defaultValForEmpty.c_str(), UserData.defaultValForEmpty.length());
		nf.close();

		// reopen locale data and check
		f.open("locale.txt");
		if (!f.is_open())
			LOG(true, "local user data load error");
	}

	std::stringstream s;
	s << f.rdbuf();
	f.close();

	std::string l = "";
	std::vector<std::string> lines;
	while (getline(s, l))
		lines.push_back(l);

	if (lines.size() < 3)
		return;

	// read loaded data
	UserData.parseUserData(lines);
	// check existing paths
	UserData.paths = fc::checkMainPaths(UserData.paths);
}

App& App::getAppInstance() {
	if (!(app)) {
		app = new App();
	}
	return *app;
}

bool App::checkPath(std::string const &p) {
	return std::filesystem::exists(p);
}

// get User Data
std::vector<std::string> App::getPathList() {
	return UserData.paths;
}
std::vector<std::string> App::getCombinationList() {
	return UserData.combinations;
}
std::vector<std::pair<std::string, std::string>> App::getPathTemplates() {
	return UserData.pathTemplates;
}
std::vector<std::pair<std::string, std::string>> App::getNamings() {
	return UserData.naming;
}