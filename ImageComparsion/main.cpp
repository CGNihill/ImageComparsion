#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <utility>

#include "App.h"

using namespace std;

static bool isN(const string& s) {
	return std::all_of(s.begin(), s.end(), ::isdigit);
}

pair<string, string> createNewTemplate();
void checkPathTemplate(vector<pair<string, string>>&, pair<string, string>&);

int main() {
	App& app = App::getAppInstance();

	cout << "- Set new file path or use recent" << endl;

	vector<string> mainPaths = app.getPathList();
	for (size_t i = 0; i < mainPaths.size(); i++) {
		cout << i+1 << ")\t" << mainPaths[i] << endl;
	}

	// select my Path
	string path;
	bool passed = true;
	do
	{
		getline(cin, path);

		if (isN(path) && stoull(path) < 0 && stoull(path) > mainPaths.size() + 1) {
			passed = false;
			cout << "- There is no such answer\n- Try again" << endl;
		}
		else if (!app.checkPath(path)) {
			passed = false;
			cout << "- The path does not exist\n- Try again" << endl;
		}
		else {
			passed = true;
		}
	} while (!passed);
	// update User Data
	if (isN(path))
		path = mainPaths[-1];
	bool b = true;
	for (auto& p : mainPaths) {
		if (p == path) {
			b = false;
		}
	}
	if (b) {
		mainPaths.push_back(path);
		app.setPathList(mainPaths);
	}

	// set path template
	cout << "- Set path template :" << endl;
	cout << "- 1) NO\n- 2) Create new Template\n- 3) Delete Template" << endl;

	vector<pair<string, string>> pathT = app.getPathTemplates();
	for (size_t i = 0; i < pathT.size(); i++) {
		cout << "- " << i + 4 << ")\t" << pathT[i].first << " | " << pathT[i].second << endl;
	}

	passed = false;
	string Ptemplate = "";
	do
	{
		size_t choise;
		cin >> choise;

		if (!(choise <= pathT.size() + 3)) {
			passed = false;
			cout << "- There is no such answer\n- Try again" << endl;
		}
		else {
			passed = true;
		}
		// main choises
		if (choise == 1) {
			Ptemplate = "";
		}
		else if (choise == 2 && passed) {
			try
			{
				pair<string, string> newT = createNewTemplate();
				if (newT.first.empty() || newT.second.empty()) {
					passed = false;
					continue;
				}
				checkPathTemplate(pathT, newT);
				Ptemplate = newT.second;
			}
			catch (const std::exception& e)
			{
				passed = false;
				cerr << "- !!! " << e.what() << endl;
			}

		}
		else if (choise == 3) {
			cout << "- Select the template number or set another number to cancel" << endl;
			cin >> choise;
			if (choise < pathT.size() + 2 && choise > 2) {
				pathT.erase(pathT.begin() + (choise - 3));
				passed = false;
			}
		}
		else {
			Ptemplate = pathT[choise - 3].second;
		}

	} while (!passed);
	app.setPathTemplates(pathT);

	// get all images from path
}

pair<string, string> createNewTemplate() {
	cout << "- For creating a new template u need to set the local path starting from main path, for example:\n"
		<< "- --- main path: C:\\\\User\\Local Name\\project --- local path \\ saves\\screenshot\\@S\\...\n"
		<< "- Where @S is non constant value" << endl;

	string pathTemplate = "";
	cin >> ws;
	getline(cin, pathTemplate);

	cout << "- Now set a new name for template" << endl;

	string pathTemplateName = "";

	getline(cin, pathTemplateName);

	while (1) {
		cout << "- Template : " << pathTemplateName << '|' << pathTemplate << endl;
		cout << "- 1) Continue\n- 2) Cancel\n- 3) Reset" << endl;
		short i;
		cin >> i;
		if (i == 1) {
			break;
		}
		else if (i == 2) {
			pathTemplate = pathTemplateName = "";
			break;
		}
		else if (i == 3) {
			return createNewTemplate();
		}
		else {
			cout << "- There is no such answer\n- Try again" << endl;
		}
	}

	return make_pair(pathTemplateName, pathTemplate);
}

void checkPathTemplate(vector<pair<string, string>>& PTemp, pair<string, string>& newT) {
	for (auto& t : PTemp) {
		string tn = t.first, ntn = newT.first;
		if (t.second == newT.second && transform(tn.begin(), tn.end(), tn.begin(), [](unsigned char c) { return tolower(c); }) != transform(ntn.begin(), ntn.end(), ntn.begin(), [](unsigned char c) { return tolower(c); })) {
			cout << "- This template already exist by name \"" << t.first << "\"\n- Rename template [Y/N]" << endl;
			char a;
			cin >> a;
			if (tolower(a) == 'y') {
				t.first = newT.first;
				return;
			}
		}
		else {
			PTemp.push_back(newT);
		}
	}
}
