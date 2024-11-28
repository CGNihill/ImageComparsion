#include "ErrLog.hpp"
#include "ImageEditor.h"

#include <vector>
#include <utility>
#include <filesystem>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace fs = std::filesystem;

void ImageEditor::loadImagesSingleCollage(std::vector<fs::path> imagesPath, std::vector<std::pair<std::string, std::string>> namings)
{
	if (imagesPath.size() != namings.size()) {
		LOG(true, "Wrong function arguments");
	}
	
	Orientation o = Orientation::H;

	for (size_t i = 0; i < imagesPath.size(); i++) {
		Img img;
		img.images.push_back(std::make_pair(cv::imread(imagesPath[i].string()), namings[i]));
		size_t ims = (img.images.size() - 1);

		if (i > 0 && o == getImageOrinetation(img.images[ims].first)) {
			std::string log = "Images have different orientation [check file naming or redu  the renders whith correct image orientation\n"
				+ imagesPath[i].string() + "\n" + imagesPath[i - 1].string() + "\n";
			LOG(true, log);
		}

		o = getImageOrinetation(img.images[ims].first);
		img.o = o;
	}
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

ImageEditor::Orientation ImageEditor::getImageOrinetation(cv::Mat& im)
{
	Orientation o = Orientation::H;
	if (im.rows < im.cols)
		o = Orientation::V;
	return o;
}
