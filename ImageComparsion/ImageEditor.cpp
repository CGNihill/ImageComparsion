#include "ErrLog.hpp"
#include "ImageEditor.h"

#include <vector>
#include <map>
#include <utility>
#include <filesystem>
#include <algorithm>

#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

std::vector<ImageEditor::Img> ImageEditor::images = {};
int ImageEditor::mainCompareResolution = {};

void ImageEditor::loadImagesSingleCollage(std::vector<fs::path> imagesPath, std::pair<std::string, std::string> namings)
{
	Orientation o = Orientation::H;

	Img img;
	for (size_t i = 0; i < imagesPath.size(); i++) {
		img.images.push_back(std::make_pair(cv::imread(imagesPath[i].string()), namings));
		if (img.images[img.images.size() - 1].first.empty()) {
			std::string log = "Failed to load image: " + imagesPath[i].string();
			LOG(true, log);
		}
		size_t ims = (img.images.size() - 1);

		if (i > 0 && o != getImageOrinetation(img.images[ims].first)) {
			std::string log = "Images have different orientation [check file naming or redu  the renders whith correct image orientation\n"
				+ imagesPath[i].string() + "\n" + imagesPath[i - 1].string() + "\n";
			LOG(true, log);
		}

		o = getImageOrinetation(img.images[ims].first);
		img.o = o;

		images.push_back(img);
	}
	std::cout << img.images.size() << std::endl;
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
	std::cout << images.size() << std::endl;
	std::sort(d.begin(), d.end());
	std::cout << d.size() << std::endl;

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
	/*
	* - get images secondary size
	* - create a summ and add 10-15% for text
	* - create the canvas using the summ
	* - set images on canvas
	* - write text on canvas
	*/

	for (auto& a : images) {
		int s = 0;
		for (auto const& ic : a.images) {
			s += (a.o == Orientation::H) ? ic.first.rows : ic.first.cols;
		}

		s += (s * 0.1); // add 10%
		int space = (s * 0.1) / a.images.size();

		a.Compare = (a.o == Orientation::H) ? cv::Mat(s, mainCompareResolution, CV_8UC3) : cv::Mat(mainCompareResolution, s, CV_8UC3);
		a.Compare.setTo(cv::Scalar(50, 50, 50));

		int coordinate = 0;
		for (auto const& ic : a.images) {
			if (a.o == Orientation::H) {
				ic.first.copyTo(a.Compare(cv::Rect(0, coordinate, mainCompareResolution, ic.first.rows)));
				coordinate += (ic.first.rows + space);
			}
			else {
				ic.first.copyTo(a.Compare(cv::Rect(coordinate, 0, ic.first.cols, mainCompareResolution)));
				coordinate += (ic.first.cols + space);
			}
		}

		writeTextToCompare(a.images, s, a.Compare);
	}
}

void ImageEditor::uploadColages(fs::path outPath, std::string outputName)
{
	int i = 0;
	for (auto const& ic : images) {
		cv::imwrite(outPath.string() + "/" + outputName + std::to_string(i) + ".png", ic.Compare);
		cv::Exception e;
		cv::error(e);
		std::cerr << e.what() << std::endl;
	}
}

ImageEditor::Orientation ImageEditor::getImageOrinetation(cv::Mat& im)
{
	Orientation o = Orientation::H;
	if (im.rows > im.cols)
		o = Orientation::V;
	return o;
}

void ImageEditor::resizeImages(Img& imgs)
{
	for (auto& i : imgs.images) {
		cv::Mat& ic = i.first;
		std::pair<int, int> newDimensions;
		(imgs.o == Orientation::H) ? newDimensions = calculateNewSize(ic.cols, ic.rows) : newDimensions = calculateNewSize(ic.rows, ic.cols);
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

void ImageEditor::writeTextToCompare(std::vector<std::pair<cv::Mat, std::pair<std::string, std::string>>> &images, int space, cv::Mat &colage)
{
	for (auto const& a : images) {
		cv::putText(colage,
			a.second.second,
			cv::Point(0, 0),
			cv::FONT_HERSHEY_DUPLEX,
			1.0,
			CV_RGB(255, 0, 0),
			2);
	}
}
