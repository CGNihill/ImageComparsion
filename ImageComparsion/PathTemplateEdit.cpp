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

// template / image Tipe / path List
std::vector<std::vector<std::vector<fs::path>>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates)
{
	for (std::string const& ct : combinationTemplates) {
		cName.push_back(UserData.getNamingsByTemplate(ct));
	}

	std::vector<std::filesystem::path> allImgL = FileChecker::getAllImages(mainPath, pathTemplate);

	std::vector<std::vector<fs::path>> temp;

	std::vector<std::vector<std::vector<std::string>>> cleanedNamings;
	cleanedNamings.reserve(cName.size());

	for (size_t i = 0; i < cName.size(); i++) {
		for (auto const& v : cName[i]) {
			cleanedNamings[i].push_back(cleanName(v.first));
		}
	}

	for (size_t i = 0; i < cleanedNamings.size(); i++) {
		for (auto const& v : allImgL) {
			bool b = false;
			for (auto const& c : cleanedNamings[i]) {
				size_t f = 0, j;
				for (j = 0; j < c.size(); j++) {
					if (v.filename().string().find(c[j]) == std::string::npos || v.filename().string().find(c[j]) < f)
						break;
					f = v.filename().string().find(c[j]);
				}
				if (!(j < c.size())) {
					b = true;
					break;
				}
			}
			if (b) {
				temp[i].push_back(allImgL[i]);
			}
		}
	}

	std::vector<std::vector<std::vector<fs::path>>> fin;
	fin.reserve(temp.size());

	std::map<std::string, std::vector<fs::path>> mapP;

	for (size_t i = 0; i < temp.size(); i++) {
		for (auto const& v : temp[i]) {
			mapP[v.filename().string().substr(0, v.filename().string().find('(') - 1)].push_back(v);
		}
		size_t j = 0;

		for (auto const& [k,v] : mapP) {
			
			for (auto const& b : v) {
				fin[i][j].push_back(b);
			}
			j++;
		}
	}

	return fin;
}

