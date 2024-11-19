#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

inline void myerr(bool ex, std::string what, std::string file, size_t line) {
	std::string e = file + '\t' + std::to_string(line) + "\n\t" + what;
	std::cerr << e << std::endl;
	if (ex) {
		std::exit(3);
	}
}

#define LOG(ex, log) myerr(ex, log, __FILE__, __LINE__)