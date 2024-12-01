#pragma once

#include "UserData.hpp"

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class PathTemplateEdit
{
private:
	static std::vector<std::vector<std::pair<std::string, std::string>>> cName;
	static std::vector<std::string> cleanName(std::string);

	PathTemplateEdit() = delete;
	PathTemplateEdit(PathTemplateEdit&&) = delete;
	PathTemplateEdit(PathTemplateEdit const &) = delete;

public:
	static std::vector < std::vector<std::vector<fs::path>>> getSortedImageList(std::string, std::string, std::vector<std::string>, UD&);
	static void clear();
};