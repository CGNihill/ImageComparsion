#pragma once

#include "ErrLog.hpp"

#include <string>
#include <vector>
#include <utility>
#include <sstream>

struct {
	std::vector<std::string> paths, pathTemplates, combinations;

	std::vector<std::pair<std::string, std::string>> naming; // fileNamePatern | output naming

	void parseUserData(std::vector<std::string> lines) {
        size_t pl = (size_t)std::stoull(lines[0]);
        size_t cl = (size_t)std::stoull(lines[pl + 1]);
        size_t nl = (size_t)std::stoull(lines[pl + cl + 2]);
        size_t ptl = (size_t)std::stoull(lines[pl + cl + nl + 3]);
		
		for(size_t i = 0; i < pl; i++)
			paths.push_back(lines[i+1]);
		
		for (size_t i = 0; i < cl; i++)
			combinations.push_back(lines[i + pl + 2]);

		for (size_t i = 0; i < nl; i++) {
            std::string cs = lines[i + cl + pl + 3];

			size_t p = cs.find('|');
            if (p == std::string::npos) {
				LOG(false, "local data file sintaxis error (NAMING)");
                continue;
            }

			naming.push_back(std::make_pair(cs.substr(0, p), cs.substr(1+p)));
		}
	
        for (size_t i = 0; i < ptl; i++)
            pathTemplates.push_back(lines[i + cl + pl + nl + 4]);
    }

    std::string composeUserData() {
        std::string s = "";

        s += std::to_string(paths.size()) + "\n";

        for (auto& l : paths)
            s += l + '\n';

        s += std::to_string(combinations.size()) + "\n";

        for (auto& l : combinations)
            s += l + '\n';

        s += std::to_string(naming.size()) + "\n";
        
        for (auto& l : naming)
            s += l.first + '|' + l.second + '\n';

        s += std::to_string(pathTemplates.size()) + "\n";

        for (auto& l : pathTemplates)
            s += l + '\n';


        return s;
    }



} UserData;