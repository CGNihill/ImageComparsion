#include "ImageEditor.h"

#include <vector>
#include <utility>
#include <filesystem>

#include <opencv2/core.hpp>

void ImageEditor::loadImagesSingleCollage(std::vector<fs::path> imagesPath, std::vector<std::pair<std::string, std::string>> namings)
{
}

std::vector<std::pair<size_t, size_t>> ImageEditor::getPossibleCompareResolution()
{
	return std::vector<std::pair<size_t, size_t>>();
}

void ImageEditor::setCompareResolution(size_t resByOrientation, Orientation orientation)
{
}

void ImageEditor::startCompareGeneration()
{
}

void ImageEditor::uploadColages(fs::path outPath, std::string outputName)
{
}
