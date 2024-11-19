#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class FileChecker {
private:
public:
	FileChecker() = delete;
	FileChecker(FileChecker&&) = delete;
	FileChecker(const FileChecker&) = delete;

	static std::vector<std::string> checkMainPaths(std::vector<std::string> pl) {
		std::vector<std::string> epl;

		for (fs::path p : pl) {
			if (fs::exists(p)) {
				epl.push_back(p.string());
			}
		}

		return epl;
	}
};