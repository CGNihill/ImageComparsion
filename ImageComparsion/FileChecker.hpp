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
	std::vector<fs::path> imgs;

	try
	{
		for (const fs::directory_entry& d : fs::recursive_directory_iterator(p)) {

			try
			{
				if (fs::is_symlink(d.path())) {
					continue;
				}

				if (fs::is_regular_file(d.path()) && d.path().extension().string() == ".png") {
					imgs.push_back(d.path());
				}
			}
			catch (const fs::filesystem_error& fe)
			{
				std::cerr << "Error accessing file " << d.path() << ": " << fe.what() << std::endl;
			}

		}
	}
	catch (const fs::filesystem_error& fe)
	{
		std::cerr << "Error accessing directory " << p << ": " << fe.what() << std::endl;
	}

	return imgs;
}

inline std::vector<fs::path> FileChecker::getImgs(fs::path mainP, std::vector<std::string>subP)
{
	std::vector<fs::path> imgs{}, allPaths;

	for (size_t i = 0; i < subP.size(); i++) {
		if (subP[i] == "@S") {
			for (auto const& d : fs::directory_iterator(mainP)) {
				if (d.exists() && fs::is_directory(d)) {
					std::vector<fs::path> tmp = getImgs(d, { subP.begin() + i + 1, subP.end() });
					imgs.insert(imgs.end(), tmp.begin(), tmp.end());
				}
			}
			return imgs;
		}

		mainP += subP[i];
	}

	for (auto const& d : fs::directory_iterator(mainP))
		if (fs::is_regular_file(d) && d.path().extension().string() == ".png")
			imgs.push_back(d);

	return imgs;
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

	if (pt != "")
		return getImgsRecursive(mp);

	return getImgs(mp, temp);
}


