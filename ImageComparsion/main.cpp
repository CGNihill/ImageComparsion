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
	
	cout << "> Set new file path or use recent" << endl;

	vector<string> mainPaths = app.getPathList();
	for (size_t i = 0; i < mainPaths.size(); i++) {
		cout << i << ")\t" << mainPaths[i] << endl;
	}
	cout << "> There is no such answer\nTry again" << endl;

	// select my Path
	string path;
	bool passed = true;
	do
	{
		getline(cin, path);
		cin >> ws;

		if (!(isN(path) && stoull(path) > 0 && stoull(path) < mainPaths.size() + 1)) {
			passed = false;
			cout << "> There is no such answer\nTry again" << endl;
		}
		else if (!app.checkPath(path)) {
			passed = false;
			cout << "> The path does not exist\nTry again" << endl;
		}
		else {
			passed = true;
		}
	} while (!passed);

	// set path template
	cout << "> Set path template :" << endl;
	cout << "> 0) NO\n> 1) Create new Template\n> 2) Delete Template" << endl;

	vector<pair<string, string>> pathT = app.getPathTemplates();
	for (size_t i = 0; i < pathT.size(); i++) {
		cout << "> " << i + 3 << ")\t" << pathT[i].first << " | " << pathT[i].second << endl;
	}

	passed = false;
	string Ptemplate;
	do
	{
		getline(cin, Ptemplate);
		cin >> ws;

		if (!(isN(Ptemplate) && stoull(Ptemplate) >= 0 && stoull(Ptemplate) < pathT.size() + 2)) {
			passed = false;
			cout << "> There is no such answer\n> Try again" << endl;
		}
		else {
			passed = true;
		}
		// create new template
		if (Ptemplate == "1" && passed) {
			try
			{
				pair<string, string> newT = createNewTemplate();
				checkPathTemplate(pathT, newT);
			}
			catch (const std::exception& e)
			{
				passed = false;
				cerr << "> !!! " << e.what() << endl;
			}
		}

	} while (!passed);


	// get all images from path
}

pair<string, string> createNewTemplate() {
	cout << "> For creating a new template u need to set the local path starting from main path, for example:\n" 
		<< "> --- main path: C:\\\\User\\Local Name\\project --- local path \\ saves\\screenshot\\@S\\...\n" 
		<< "> Where @S is non constant value" << endl;

	string pathTemplate = "";
	getline(cin, pathTemplate);
	cin >> ws;

	cout << "> Now set a new name for template" << endl;

	string pathTemplateName = "";
	getline(cin, pathTemplateName);

	while (1) {
		cout << "> Template : " << pathTemplateName << '|' << pathTemplate << endl;
		cout << "> 1) Continue\n> 2) Cancel\n> 3) Reset" << endl;
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
			cout << "> There is no such answer\n> Try again" << endl;
		}
	}

	return make_pair(pathTemplateName, pathTemplate);
}

void checkPathTemplate(vector<pair<string, string>>& PTemp, pair<string, string>& newT) {
	for (auto& t : PTemp) {
		string tn = t.first, ntn = newT.first;
		if (t.second == newT.second && transform(tn.begin(), tn.end(), tn.begin(), [](unsigned char c){ return tolower(c); }) != transform(ntn.begin(), ntn.end(), ntn.begin(), [](unsigned char c) { return tolower(c); })) {
			cout << "> This template already exist by name \"" << t.first << "\"\n> Rename template [Y/N]" << endl;
			char a;
			cin >> a;
			if (tolower(a) == 'y') {

			}
		}
	}
}
