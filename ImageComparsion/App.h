#pragma once

#include "UserData.hpp"

#include <fstream>

class App
{
private:
	static App* app;
	App();
	
public:
	App(App&&) = delete;
	App(const App&) = delete;

	static App& getAppInstance();


	// load user data
	// scan refs by main path
	// add new paths
	// change naming
};

