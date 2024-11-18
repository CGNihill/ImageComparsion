#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

struct {
	std::vector<std::string> paths;
	std::vector<std::string> combinations;
	std::vector<std::pair<std::string, std::string>> naming; // fileNamePatern | output naming

	/*
	* line count
	*/
	void parseUserData(std::vector<std::string> lines) {
		int pl = std::stoi(lines[0]);
		int cl = std::stoi(lines[pl+1]);
		int nl = std::stoi(lines[pl+cl+2]);

		int i = 1;
		
		for(; i < pl; i++)
			paths.push_back(lines[i]);
		
		for (i++; i < cl+pl+1; i++)
			combinations.push_back(lines[i]);

		for (i+=2; i < nl + cl + pl + 2; i++) {
			std::cout << lines[i] << std::endl;
			int p = lines[i].find('|');
			if (p == std::string::npos)
				throw std::runtime_error("local data file sintaxis error");


			naming.push_back(std::make_pair(lines[i].substr(0, p), lines[i].substr(p)));
		}
		
	}

	std::string composeUserData(){
		std::string s = "";
		s += paths.size() + '\n';
		for (auto &l : paths) {
			s += l + '\n';
		}

		s += combinations.size() + '\n';
		for (auto& l : combinations) {
			s += l+'\n';
		
		}

		s += naming.size() + '\n';
		for (auto& l : naming) {
			s += l.first + '|' + l.second + '\n';
		}

		return s;
	}


} UserData;