#pragma once

#include <filesystem>
#include <string>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

class FileChecker {
private:
	static std::vector<std::string> parsePathTemplate(std::string);
	static std::vector<fs::path> getImgsRecursive(fs::path);
	static std::vector<fs::path> getImgs(fs::path, std::vector<std::string>);
public:
	FileChecker() = delete;
	FileChecker(FileChecker&&) = delete;
	FileChecker(const FileChecker&) = delete;

	static std::vector<std::string> checkMainPaths(std::vector<std::string>);

	static std::vector<fs::path> getAllImages(fs::path, std::string);
};

inline std::vector<std::string> FileChecker::parsePathTemplate(std::string pl)
{
	std::vector<std::string> ptp{};

	std::replace(pl.begin(), pl.end(), '\\', '/');

	std::stringstream p(pl);
	std::string s;
	while (std::getline(p, s, '/')) {
		if (!s.empty())
			ptp.push_back(s);
	}

	return ptp;
}

inline std::vector<fs::path> FileChecker::getImgsRecursive(fs::path p)
{
	fs::recursive_directory_iterator rdi(p);
	std::vector<fs::path> imgs;
	



	return std::vector<fs::path>();
}

inline std::vector<fs::path> FileChecker::getImgs(fs::path, std::vector<std::string>)
{
	return std::vector<fs::path>();
}

inline std::vector<std::string> FileChecker::checkMainPaths(std::vector<std::string> pl) {
	std::vector<std::string> epl;

	for (fs::path p : pl) {
		if (fs::exists(p)) {
			epl.push_back(p.string());
		}
	}

	return epl;
}

inline std::vector<fs::path> FileChecker::getAllImages(fs::path mp, std::string pt) {
	std::vector<std::string> temp = parsePathTemplate(pt);
	return std::vector<fs::path>();
}


