#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

inline void myerr(bool ex, std::string what, std::string file, size_t line, std::string func) {
	std::string e = file + '\t' + func + '\t' + std::to_string(line) + "\n\t" + what;
	if (ex) {
		throw std::runtime_error(e);
	}
	else {
		std::cerr << e << std::endl;
	}
}

#define LOG(ex, log) myerr(ex, log, __FILE__, __LINE__, __FUNCTION__)