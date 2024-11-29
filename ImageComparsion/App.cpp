#include "App.h"
#include "ErrLog.hpp"
#include "FileChecker.hpp"
#include "PathTemplateEdit.h"
#include "ImageEditor.h"

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

void App::updateUserData() {
	std::string uds = UserData.composeUserData();
	std::ofstream f("locale.txt");
	if (!f.is_open()) {
		LOG(false, "local user data file opening error\n\t[programm will continue working without saving data]");
		return;
	}

	f.write(uds.c_str(), uds.length());

	f.close();
}

App& App::getAppInstance() {
	if (!(app)) {
		app = new App();
	}
	return *app;
}

bool App::checkPath(std::string const& p) {
	return std::filesystem::exists(p);
}

// get User Data
std::vector<std::string> App::getPathList() { return UserData.paths; }
std::vector<std::pair<std::string, std::string>> App::getCombinationList() { return UserData.combinations; }
std::vector<std::pair<std::string, std::string>> App::getPathTemplates() { return UserData.pathTemplates; }
std::vector<std::pair<std::string, std::string>> App::getNamings() { return UserData.naming; }

// update User Data
void App::setPathList(std::vector<std::string>& data) { UserData.paths = data; }
void App::setCombinationList(std::vector <std::pair<std::string, std::string>>& data) { UserData.combinations = data; }
void App::setPathTemplates(std::vector <std::pair<std::string, std::string>>& data) { UserData.pathTemplates = data; }
void App::setNamings(std::vector <std::pair<std::string, std::string>>& data) { UserData.naming = data; }


std::pair<std::vector<std::vector<std::vector<fs::path>>>, std::vector<std::vector<std::pair<std::string, std::string>>>>  App::sortImagesAndNamings(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates) {
	updateUserData();
	auto sortedPaths = PathTemplateEdit::getSortedImageList(mainPath, pathTemplate, combinationTemplates, UserData);
	std::vector<std::vector<std::pair<std::string, std::string>>> namings;
	for (size_t i = 0; i < sortedPaths.size(); i++) {
		namings.push_back(UserData.getNamingsByTemplate(combinationTemplates[i]));
	}

	return {sortedPaths, namings};
}

