#pragma once

#include "ErrLog.hpp"

#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <sstream>

#include <iostream>

struct UD {
	std::string defaultValForEmpty{ "0\n0\n0\n0" };

	std::vector<std::string> paths;

	std::vector<std::pair<std::string, std::string>> naming, pathTemplates, combinations; // (File Name Patern | Output Naming) , (template Name | Path), (combination name | combination)

	void parseUserData(std::vector<std::string> lines) {
		size_t pl = (size_t)std::stoull(lines[0]);
		size_t cl = (size_t)std::stoull(lines[pl + 1]);
		size_t nl = (size_t)std::stoull(lines[pl + cl + 2]);
		size_t ptl = (size_t)std::stoull(lines[pl + cl + nl + 3]);

		for (size_t i = 0; i < pl; i++)
			paths.push_back(lines[i + 1]);

		for (size_t i = 0; i < cl; i++) {
			std::string cs = lines[i + pl + 2];

			size_t p = cs.find('|');
			if (p == std::string::npos) {
				LOG(false, "local data file sintaxis error (COMBINATION)");
				continue;
			}

			combinations.push_back(std::make_pair(cs.substr(0, p), cs.substr(1 + p)));
		}

		for (size_t i = 0; i < nl; i++) {
			std::string cs = lines[i + cl + pl + 3];

			size_t p = cs.find('|');
			if (p == std::string::npos) {
				LOG(false, "local data file sintaxis error (NAMING)");
				continue;
			}

			naming.push_back(std::make_pair(cs.substr(0, p), cs.substr(1 + p)));
		}

		for (size_t i = 0; i < ptl; i++) {
			std::string cs = lines[i + cl + pl + nl + 4];

			size_t p = cs.find('|');
			if (p == std::string::npos) {
				LOG(false, "local data file sintaxis error (PATH_TEMPLATES)");
				continue;
			}

			pathTemplates.push_back(std::make_pair(cs.substr(0, p), cs.substr(1 + p)));
		}
	}

	std::string composeUserData() {
		std::string s = "";

		s += std::to_string(paths.size()) + "\n";

		for (auto& l : paths)
			s += l + '\n';

		s += std::to_string(combinations.size()) + "\n";

		for (auto& l : combinations)
			s += l.first + '|' + l.second + '\n';

		s += std::to_string(naming.size()) + "\n";

		for (auto& l : naming)
			s += l.first + '|' + l.second + '\n';

		s += std::to_string(pathTemplates.size()) + "\n";

		for (auto& l : pathTemplates)
			s += l.first + '|' + l.second + '\n';

		return s;
	}

	std::vector<std::pair<std::string, std::string>> getNamingsByTemplate(std::string comb) {
		if (naming.size() == 0)
			LOG(true, "Naming Size is 0");
		std::vector<std::pair<std::string, std::string>> temp;
		size_t i;
		while ((i = comb.find('.')) != std::string::npos) {
			size_t l = stoull(comb.substr(0, i));
			comb.erase(0, (l + 2));
			if (l > (naming.size() - 1)) {
				LOG(true, "naming by template index does't exist");
			}

			temp.push_back(naming[l]);

			if (comb.find('.') == std::string::npos){
				size_t l = stoull(comb);
				temp.push_back(naming[l]);

			}
		}
		return temp;
	}

};

static UD UserData;