#pragma once

#include "UserData.hpp"

#include <fstream>
#include <vector>

class App
{
private:
	static App* app;
	App();


public:
	App(App&&) = delete;
	App(const App&) = delete;

	static App& getAppInstance();

	bool checkPath(std::string const&);

	// get User Data
	std::vector<std::string> getPathList();
	std::vector<std::pair<std::string, std::string>> getCombinationList();
	std::vector<std::pair<std::string, std::string>> getPathTemplates();
	std::vector<std::pair<std::string, std::string>> getNamings();

	// update User Data
	void setPathList(std::vector<std::string>&);
	void setCombinationList(std::vector <std::pair<std::string, std::string>>&);
	void setPathTemplates(std::vector <std::pair<std::string, std::string>>&);
	void setNamings(std::vector <std::pair<std::string, std::string>>&);

	void updateUserData();

	void startCollageCreation(std::string, std::string, std::vector<std::string>);


	//void getImageList(std::string);


	// load user data
	// scan refs by main path
	// add new paths
	// change naming
};

