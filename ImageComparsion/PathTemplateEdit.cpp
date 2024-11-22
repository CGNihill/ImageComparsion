#include "PathTemplateEdit.h"
#include "FileChecker.hpp"
#include "UserData.hpp"

#include <vector>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

std::vector<std::vector<std::pair<std::string, std::string>>> PathTemplateEdit::cName = std::vector<std::vector<std::pair<std::string, std::string>>>{};

std::vector<std::string> PathTemplateEdit::cleanName(std::string n)
{
	std::vector<std::string> temp;
	while (n.find('{') != std::string::npos) {
		size_t f = n.find('{'), l = n.find('}');

		if (l == std::string::npos)
			LOG(true, "File naming Exception File -> " + n + "\t \'}\' does not exist");

		temp.push_back(n.substr(0, f - 1));
		n.erase(n.begin(), n.begin() + l);
	}

	if (n.find('}') == std::string::npos)
		LOG(true, "File naming Exception File -> " + n + " \'{\' not exists \'}\' exists");

	return temp;
}

std::vector<std::vector<std::vector<fs::path>>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates)
{
	for (std::string const& ct : combinationTemplates) {
		cName.push_back(UserData.getNamingsByTemplate(ct));
	}

	std::vector<std::filesystem::path> allImgL = FileChecker::getAllImages(mainPath, pathTemplate);

	std::vector<std::vector<std::vector<fs::path>>> temp;

	for (size_t i = 0; i < cName.size(); i++) {
		for (fs::path const& f : allImgL) {
			std::vector<size_t> l;
			for (auto const& v : cName[i]) {
				l.push_back(v.first.find(f.filename().string()));
			}
			size_t k = 0;
			for (auto const& v : l) {
				if (k > v && v == std::string::npos)
					break;
				temp.
			}
		}
	}

	/*
	std::vector<std::map<std::string, char>> nameMap;
	nameMap.reserve(combinationTemplates.size());

	for (size_t i = 0; i < nameMap.size(); i++) {
		for (auto const& v : cNam[i]) {
			for (auto const& vv : cleanName(v.first))
				nameMap[i][vv] = 0;
		}

	}

	std::vector<std::vector<std::string>> usedNames;
	usedNames.reserve(nameMap.size());

	for (size_t i = 0; i < usedNames.size(); i++) {
		for (auto const& [k, v] : nameMap[i])
			usedNames[i].push_back(k);

	}

	std::vector<std::vector<fs::path>> temp;

	for (size_t i = 0; i < usedNames.size(); i++) {
		for (auto const& n : allImgL) {
			for (auto const& nn : usedNames[i]) {
				if (n.filename().string().find(nn) != std::string::npos) {
					temp[i].push_back(n);
					break;
				}
			}
		}
	}*/

	for (auto const& arr : temp) {
		std::sort(arr.begin(), arr.end());
	}

	return temp;
}