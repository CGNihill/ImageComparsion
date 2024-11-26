#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

inline void myerr(bool ex, std::string what, std::string file, size_t line, std::string func) {
	std::string e = file + '\t' + func + '\t' + std::to_string(line) + "\n\t" + what;
		std::cerr << e << std::endl;
		if (ex)
			exit(0);
}

#define LOG(ex, log) myerr(ex, log, __FILE__, __LINE__, __FUNCTION__)