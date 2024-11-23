#pragma once

#include "App.h"

#include <string>
#include <vector>
class UserIOMain
{
private:
	App &app = App::getAppInstance();
	void checkTemplate(std::vector<std::pair<std::string, std::string>>&, std::pair<std::string, std::string>&);
	std::pair<std::string, std::string> createNewTemplate();
	std::pair<std::string, std::string> createNewCollageTemplate();

	// settings
	std::string addNewMainPath();
	std::vector<std::pair<std::string, std::string>> addNewNamings();

public:
	UserIOMain() = default;

	UserIOMain(UserIOMain&&) = delete;
	UserIOMain(UserIOMain const &) = delete;

	void mainProcess();
	void settings();
	// main process
	// settings
	// additional functions
};

