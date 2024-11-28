#include "ErrLog.hpp"
#include "ImageEditor.h"

#include <vector>
#include <map>
#include <utility>
#include <filesystem>
#include <algorithm>

#include <opencv2/opencv.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>

namespace fs = std::filesystem;

std::vector<ImageEditor::Img> ImageEditor::images = {};
int ImageEditor::mainCompareResolution = {};

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
std::vector<int> ImageEditor::getPossibleCompareResolution()
{
	std::map<int, short> h;
	for (auto const& i : images) {
		for (auto const& m : i.images) {
			(i.o == Orientation::V) ? h[m.first.rows] = true : h[m.first.cols] = true;
		}
	}

	std::vector<int> d;
	for (auto const& [k, v] : h) {
		d.push_back(k);
	}
	std::sort(d.begin(), d.end());

	return d;
}

void ImageEditor::setCompareResolution(int resolution)
{
	mainCompareResolution = resolution;
	for (auto& img : images)
		resizeImages(img);
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

void ImageEditor::resizeImages(Img& imgs)
{
	for (auto& i : imgs.images) {
		cv::Mat& ic = i.first;
		std::pair<int, int> newDimensions;
		(imgs.o == Orientation::H)? newDimensions = calculateNewSize(ic.rows, ic.cols) : newDimensions = calculateNewSize(ic.cols, ic.rows);
		cv::Mat ric;
		(imgs.o == Orientation::H) ? cv::resize(ic, ric, cv::Size(newDimensions.first, newDimensions.second)) : cv::resize(ic, ric, cv::Size(newDimensions.second, newDimensions.first));
		ic = ric;
	}
}

std::pair<int, int> ImageEditor::calculateNewSize(int first, int second)
{
	long double p = (long double)first / ImageEditor::mainCompareResolution;

	return { ImageEditor::mainCompareResolution, (int)(second * p) };
}
