#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class PathTemplateEdit
{
private:
	static std::vector<std::vector<std::pair<std::string, std::string>>> cNam;
	static std::vector<std::string> cleanName(std::string);

	PathTemplateEdit() = delete;
	PathTemplateEdit(PathTemplateEdit&&) = delete;
	PathTemplateEdit(PathTemplateEdit const &) = delete;

public:
	static std::vector<std::vector<std::string>> getSortedImageList(std::string, std::string, std::vector<std::string>);
};