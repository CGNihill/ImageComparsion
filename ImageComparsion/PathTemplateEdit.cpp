#include "PathTemplateEdit.h"
#include "FileChecker.hpp"
#include "UserData.hpp"

#include <vector>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

std::vector<std::vector<std::pair<std::string, std::string>>> PathTemplateEdit::cNam = std::vector<std::vector<std::pair<std::string, std::string>>>{};

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

std::vector<std::vector<std::string>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates)
{
	for (std::string const& ct : combinationTemplates) {
		cNam.push_back(UserData.getNamingsByTemplate(ct));
	}

	std::vector<std::filesystem::path> allImgL = FileChecker::getAllImages(mainPath, pathTemplate);

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

	std::vector<std::vector<std::string>> temp;

	for (size_t i = 0; i < usedNames.size(); i++) {
		for (auto const& n : allImgL) {
			for (auto const& nn : usedNames[i]) {
				if (n.filename().string().find(nn) != std::string::npos) {
					temp[i].push_back(n.string());
					break;
				}
			}
		}
	}

	return temp;
}
