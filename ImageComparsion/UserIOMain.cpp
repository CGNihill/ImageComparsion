#include "UserIOMain.h"
#include "App.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

static bool isN(const string& s) {
	return std::all_of(s.begin(), s.end(), ::isdigit);
}

void UserIOMain::mainProcess() {

	cout << "- Set new file path or use recent" << endl;

	vector<string> mainPaths = this->app.getPathList();
	for (size_t i = 0; i < mainPaths.size(); i++) {
		cout << i + 1 << ")\t" << mainPaths[i] << endl;
	}

	// select my Path
	string path;
	bool passed = true;
	do
	{
		cin >> ws;
		getline(cin, path);

		if (isN(path) && stoull(path) < 0 && stoull(path) > mainPaths.size() + 1) {
			passed = false;
			cout << "- There is no such answer\n- Try again" << endl;
		}
		else if (!isN(path) && !this->app.checkPath(path)) {
			passed = false;
			cout << "- The path does not exist\n- Try again" << endl;
		}
		else {
			passed = true;
		}
	} while (!passed);
	// update User Data
	if (isN(path))
		path = mainPaths[(size_t)(stoull(path) - 1)];
	bool b = true;
	for (auto& p : mainPaths) {
		if (p == path) {
			b = false;
		}
	}
	if (b) {
		mainPaths.push_back(path);
		this->app.setPathList(mainPaths);
	}

	// set path template
	cout << "- Set path template :" << endl;
	cout << "- 1) NO\n- 2) Create new Template\n- 3) Delete Template" << endl;

	vector<pair<string, string>> pathT = this->app.getPathTemplates();
	for (size_t i = 0; i < pathT.size(); i++) {
		cout << "- " << i + 4 << ")\t" << pathT[i].first << " | " << pathT[i].second << endl;
	}

	passed = false;
	string Ptemplate = "";
	do
	{
		size_t choise;
		cin.clear();
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
				checkTemplate(pathT, newT);
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
			cin.clear();
			cin >> choise;
			if (choise < pathT.size() + 2 && choise > 2) {
				pathT.erase(pathT.begin() + (choise - 3));
				passed = false;
			}
		}
		else {
			Ptemplate = pathT[choise - 4].second;
		}

	} while (!passed);
	this->app.setPathTemplates(pathT);

	cout << "- Set Collage Template" << endl;
	vector<pair<string, string>> combinations = this->app.getCombinationList();
	cout << "- 0) Use all combinations\n- 1) Create new" << endl;
	for (size_t i = 0; i < combinations.size(); i++) {
		cout << "- " << i + 2 << ") " << combinations[i].first << " | " << combinations[i].second << endl;
	}

	vector<string> collageTemplate;
	do {
		cout << "- Set : ";
		size_t c;
		cin.clear();
		cin >> c;

		if (!(c < (combinations.size() + 1) || c > 0)) {
			passed = false;
			cout << "- There is no such answer\n- Try again" << endl;
		}
		else
			passed = true;
		if (c == 0) {
			for (auto& t : combinations) {
				collageTemplate.push_back(t.second);
			}
		}
		else if (c == 1) {
			pair<string, string> nct = this->createNewCollageTemplate();
			this->checkTemplate(combinations, nct);
			this->app.setCombinationList(combinations);
			collageTemplate.push_back(nct.second);
		}
		else {
			collageTemplate.push_back(combinations[c - 2].second);
		}

		if (passed && c > 0) {
			cout << "- Add one more template? [y/n]" << endl;
			char ch;
			cin >> ch;
			if (tolower(ch) == 'y')
				passed = 0;
		}
	} while (!passed);
	cout << "start collage creation" << endl;
	app.startCollageCreation(path, Ptemplate, collageTemplate);
}

pair<string, string> UserIOMain::createNewTemplate() {
	cout << "- For creating a new template u need to set the local path starting from main path, for example:\n"
		<< "- --- main path: C:\\\\User\\Local Name\\project --- local path \\ saves\\screenshot\\@S\\...\n"
		<< "- Where @S is non constant value" << endl;

	string pathTemplate = "";
	cin >> ws;
	getline(cin, pathTemplate);

	cout << "- Now set a new name for template" << endl;

	string pathTemplateName = "";

	cin.clear();
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
pair<string, string> UserIOMain::createNewCollageTemplate() {
	pair<string, string> out;

	cout << "- Set collage template name" << endl;
	cin.clear();
	cin >> out.first;

	cout << "- Now you need to set the combination of the images by the naming index\n"
		<< "- For example\n- Names -> 1) @S_Lumen_Day | 2) @S_Lumen_Night | 3) @S_PT_Day | 4) @S_PT_Night ..."
		<< "\n- Template -> 1.3 | 2.4 | 1.2 | 2.3 | ...\n" << endl;

	cout << "- Current naming list (for changing the naming list or other UserData go to settings)" << endl;
	for (size_t i = 0; i < this->app.getNamings().size(); i++) {
		cout << "- " << i << ") " << this->app.getNamings()[i].first << " | " << this->app.getNamings()[i].second << endl;
	}

	cout << "\n- Set the combination" << endl;

	cin >> ws;
	cin >> out.second;

	return out;
}

string UserIOMain::addNewMainPath()
{
	string p;
	cout << "- Set new main path" << endl;
	cin.clear();
	getline(cin, p);
	if (!app.checkPath(p)) {
		cout << "- Path does not exist" << endl;
		cout << "- Try again" << endl;
		return addNewMainPath();
	}

	return p;
}

vector<pair<string, string>> UserIOMain::addNewNamings()
{
	vector<pair<string, string>> n;

	while (1) {
		cout << "- Write [q] for exit from this function" << endl;

		cout << "- If you want to add a new name u need to know some thinks about syntaxis\n"
			<< "- 1) You will set 2 thinks\n-\tFirst is the naming of the photos in explorer\n-\tFor the second you will set the name of refered photo in the final collage\n"
			<< "- 2) If u will set a single name, for example (lumen | LUMEN) this application will search \'lumen\' in all the file name\n"
			<< "- 3) You can use some variables, for example ({1}_lumen_{2} | {2}_LUMEN_{1}), in this case if the file will have a name like Camera1_lumen_Day, the otput name will be Day_LUMEN_Camera1 or DAY_LUMEN_CAMERA1" << endl;

		string s, ss;
		cout << "- Set the file name" << endl;
		cin.clear();
		cin >> s;
		cout << "- Set the Collage Name" << endl;
		cin.clear();
		cin >> ss;

		if (s == "q" || ss == "q")
			break;

		bool b = false;
		vector<char> c;
		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == '{')
				c.push_back(s[i]);
			else if (s[i] == '}' && c.size() > 0) {
				c.pop_back();
			}
			else if (s[i] == '}' && c.size() == 0){
				cout << "- Sintaxis erro\n-\tTry again" << endl;
				b = true;
				break;
			}
		}
		if (b)
			continue;

		b = true;
		for (auto const& v : app.getNamings()) {
			if (v.first == s && ss == v.second){
				b = false;
				break;
			}
		}

		if (b) {
			n.push_back(make_pair(s, ss));
		}
	}

	return n;
}

void UserIOMain::checkTemplate(vector<pair<string, string>>& PTemp, pair<string, string>& newT) {
	for (auto& t : PTemp) {
		string tn = t.first, ntn = newT.first;
		if (t.second == newT.second && transform(tn.begin(), tn.end(), tn.begin(), [](unsigned char c) { return tolower(c); }) != transform(ntn.begin(), ntn.end(), ntn.begin(), [](unsigned char c) { return tolower(c); })) {
			cout << "- This template already exist by name \"" << t.first << "\"\n- Rename template [Y/N]" << endl;
			char a;
			cin.clear();
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

void UserIOMain::settings() {
	while (1) {
		cout << "- Set the parameters what u whant to change:" << endl;
		cout << "- 0) Return to main" << endl;
		cout << "- 1) Main Path" << endl;
		cout << "- 2) Path Template" << endl;
		cout << "- 3) File Namings" << endl;
		cout << "- 4) Comparsion Template" << endl;

		unsigned short i;

		cin.clear();
		cin >> i;

		switch (i)
		{
		case 0:
			return;
			break;
		case 1: {
			vector<string> p = app.getPathList();
			p.push_back(addNewMainPath());
			app.setPathList(p);
		}break;
		case 2: {
			vector<pair<string, string>> p = app.getPathTemplates();
			p.push_back(createNewTemplate());
			app.setPathTemplates(p);
		}break;
		case 3: {
			vector<pair<string, string>> p = app.getNamings();
			vector<pair<string, string>> v = addNewNamings();
			p.insert(p.end(), v.begin(), v.end());
			app.setNamings(p);
		}break;
		case 4: {
			vector<pair<string, string>> p = app.getCombinationList();
			p.push_back(createNewCollageTemplate());
			app.setCombinationList(p);
		}break;
		default:
			cout << "- There is no such answer\n- Try again" << endl;
			break;
		}

		app.updateUserData();
	}
}