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

	if (n.find('}') != std::string::npos)
		LOG(true, "File naming Exception File -> " + n + " \'{\' not exists \'}\' exists");

	temp.push_back(n);
	return temp;
}

// template / image Tipe / path List
std::vector<std::vector<std::vector<fs::path>>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates, UD &Ud)
{
	for (std::string const& ct : combinationTemplates) {
		cName.push_back(Ud.getNamingsByTemplate(ct));
	}

	std::vector<std::filesystem::path> allImgL = FileChecker::getAllImages(mainPath, pathTemplate);

	std::vector<std::vector<std::vector<std::string>>> cleanedNamings;
	cleanedNamings.resize(cName.size());

	for (size_t i = 0; i < cName.size(); i++) {
		for (auto const& v : cName[i]) {
			cleanedNamings[i].push_back(cleanName(v.first));
		}
	}

	std::vector<std::vector<std::vector<fs::path>>> tf;
	tf.resize(cleanedNamings.size());
	for (size_t i = 0; i < cleanedNamings.size(); i++) {
		tf[i].resize(cleanedNamings[i].size());
	}

	for (size_t i = 0; i < allImgL.size(); i++) {
		for (size_t j = 0; j < cleanedNamings.size(); j++) {
			for (size_t o = 0; o < cleanedNamings[j].size(); o++) {
				bool b = true;
				size_t t = 0;
				for (auto const& s : cleanedNamings[j][o]) {
					if (allImgL[i].filename().string().find(s) == std::string::npos || t > allImgL[i].filename().string().find(s)) {
						b = false;
						break;
					}
					t = allImgL[i].filename().string().find(s);
				}
				if (b) {
					tf[j][o].push_back(allImgL[i]);
					break;
				}
			}
		}
	}

	for (auto &s : tf) {
		for (auto &a : s) {
			std::sort(a.begin(), a.end());
		}
	}

	return tf;
}

void PathTemplateEdit::clear()
{
	cName.clear();
}

