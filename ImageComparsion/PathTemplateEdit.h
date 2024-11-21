#pragma once

#include <vector>
#include <string>

class PathTemplateEdit
{
private:
	PathTemplateEdit() = delete;
	PathTemplateEdit(PathTemplateEdit&&) = delete;
	PathTemplateEdit(PathTemplateEdit const &) = delete;

public:
	static std::vector<std::vector<std::string>> getSortedImageList(std::string, std::string, std::vector<std::string>);
};