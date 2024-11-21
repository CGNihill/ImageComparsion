#include "PathTemplateEdit.h"
#include "FileChecker.hpp"

#include <vector>
#include <filesystem>

std::vector<std::vector<std::string>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates)
{
	std::vector<std::filesystem::path> aImgL = FileChecker::getAllImages(mainPath, pathTemplate);
	return std::vector<std::vector<std::string>>();
}
