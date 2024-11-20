#pragma once

#include "App.h"

#include <string>
#include <vector>
class UserIOMain
{
private:
	App &app = App::getAppInstance();
public:
	UserIOMain() = delete;
	UserIOMain(UserIOMain&&) = delete;
	UserIOMain(UserIOMain const &) = delete;

	void mainProcess();
	std::pair<std::string, std::string> createNewTemplate();
	void checkPathTemplate(std::vector<std::pair<std::string, std::string>>&, std::pair<std::string, std::string>&);

	// main process
	// settings
	// additional functions
};

