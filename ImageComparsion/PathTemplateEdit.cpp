#include "PathTemplateEdit.h"
#include "FileChecker.hpp"

#include <vector>
#include <filesystem>

std::vector<std::vector<std::string>> PathTemplateEdit::getSortedImageList(std::string mainPath, std::string pathTemplate, std::vector<std::string> combinationTemplates)
{
	std::vector<std::filesystem::path> allImgL = FileChecker::getAllImages(mainPath, pathTemplate);
	for (std::string const & ct : combinationTemplates)
		std::vector<std::string> namings = UserData.getNamingsByTemplate(ct);

	return std::vector<std::vector<std::string>>();
}
