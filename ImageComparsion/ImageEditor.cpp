#include "ErrLog.hpp"
#include "ImageEditor.h"

#include <vector>
#include <map>
#include <utility>
#include <filesystem>
#include <algorithm>

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

// first for vertical collage second for horizomtal
std::vector<size_t> ImageEditor::getPossibleCompareResolution()
{
	std::map<size_t, short> h;
	for (auto const& i : images) {
		for (auto const& m : i.images) {
			(i.o == Orientation::V) ? h[m.first.rows] = true : h[m.first.cols] = true;
		}
	}

	std::vector<size_t> d;
	for (auto const& [k, v] : h) {
		d.push_back(k);
	}
	std::sort(d.begin(), d.end());

	return d;
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
