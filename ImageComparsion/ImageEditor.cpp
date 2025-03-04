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

// load images for one comparsion
void ImageEditor::loadImagesSingleCollage(std::vector<fs::path> imagesPath, std::vector<std::string> namings)
{
	Orientation o = Orientation::H;

	Img img;

	for (size_t i = 0; i < imagesPath.size(); i++) {
		img.images.push_back(std::make_pair(cv::imread(imagesPath[i].string()), namings[i]));

		size_t ims = (img.images.size() - 1);

		if (img.images[ims].first.empty()) {
			std::string log = "Failed to load image: " + imagesPath[i].string();
			LOG(true, log);
		}

		if (i > 0 && o != getImageOrinetation(img.images[ims].first)) {
			std::string log = "Images have different orientation [check file naming or redu  the renders whith correct image orientation\n"
				+ imagesPath[i].string() + "\n" + imagesPath[i - 1].string() + "\n";
			LOG(true, log);
		}

		o = getImageOrinetation(img.images[ims].first);
	}

	img.o = o;
	images.push_back(img);
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
/*
void ImageEditor::startCompareGeneration()
{
	for (auto& a : images) {
		int s = 0;

		for (auto const& ic : a.images) {
			if (ic.first.empty()) {
				LOG(true, "Empty image found. Skipping...");
				continue;
			}
			s += (a.o == Orientation::H) ? ic.first.rows : ic.first.cols;
		}

		s += static_cast<int>(s * 0.1);
		int space = static_cast<int>((s * 0.1) / a.images.size());

		if (a.o == Orientation::H) {
			a.Compare = cv::Mat(s, mainCompareResolution, CV_8UC3);
		}
		else {
			a.Compare = cv::Mat(mainCompareResolution, s, CV_8UC3);
		}

		a.Compare.setTo(cv::Scalar(50, 50, 50));

		int coordinate = 0;

		for (auto const& ic : a.images) {
			if (ic.first.empty()) {
				LOG(true, "Empty image encountered. Skipping...");
				continue;
			}

			if (a.o == Orientation::H) {
				if (coordinate + ic.first.rows > a.Compare.rows) {
					LOG(true, "Image height exceeds canvas size. Skipping...");
					continue;
				}

				if (ic.first.cols != mainCompareResolution) {
					LOG(true, "Image width does not match canvas width. Resizing...");
					cv::resize(ic.first, ic.first, cv::Size(mainCompareResolution, ic.first.rows));
				}

				ic.first.copyTo(a.Compare(cv::Rect(0, coordinate, mainCompareResolution, ic.first.rows)));
				coordinate += (ic.first.rows + space);
			}
			else {
				if (coordinate + ic.first.cols > a.Compare.cols) {
					LOG(true, "Image width exceeds canvas size. Skipping...");
					continue;
				}

				if (ic.first.rows != mainCompareResolution) {
					LOG(false, "Image height does not match canvas height. Resizing...");
					cv::resize(ic.first, ic.first, cv::Size(ic.first.cols, mainCompareResolution));
				}

				ic.first.copyTo(a.Compare(cv::Rect(coordinate, 0, ic.first.cols, mainCompareResolution)));
				coordinate += (ic.first.cols + space);
			}
		}

		writeTextToCompare(a.images, s, a.Compare);
	}
}
*/


void ImageEditor::startCompareGeneration()
{

	for (auto& a : images) {
		int s = 0;
		for (auto const& ic : a.images) {
			s += (a.o == Orientation::H) ? ic.first.rows : ic.first.cols;
		}

		s += (int)(s * 0.05); // add 10%
		int space = (s * 0.05) / a.images.size();
		int check = space * a.images.size();
		for (auto const& ic : a.images) {
			check += (a.o == Orientation::H) ? ic.first.rows : ic.first.cols;
		}
		/*	if (s != check) {
				std::cout << s << " " << check << std::endl;
				exit(0);
			}*/

			//a.Compare = (a.o == Orientation::H) ? cv::Mat(check, mainCompareResolution, CV_8UC3) : cv::Mat(mainCompareResolution, check, CV_8UC3);
		a.Compare = (a.o == Orientation::H) ? cv::Mat::zeros(check, mainCompareResolution, CV_8UC3) : cv::Mat::zeros(mainCompareResolution, check, CV_8UC3);
		a.Compare.setTo(cv::Scalar(22, 22, 22));

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

		writeTextToCompare(a, space);
	}
}

void ImageEditor::uploadColages(fs::path outPath, std::string outputName)
{
	int i = 0;
	for (auto const& ic : images) {
		try
		{
			i++;
			bool p = cv::imwrite(outPath.string() + "/" + outputName + std::to_string(i) + ".png", ic.Compare);
			if (!p) {
				LOG(false, "Failed to load Compare");
			}
		}
		catch (const cv::Exception& e)
		{
			std::cerr << e.what() << std::endl << e.code << std::endl << e.err << std::endl << e.file << std::endl << e.func << std::endl << e.line << std::endl << e.msg << std::endl;
		}
	}
}

void ImageEditor::clear()
{
	images.clear();
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
	long double p = ImageEditor::mainCompareResolution / (long double)first;

	return { ImageEditor::mainCompareResolution, (int)(second * p) };
}

void ImageEditor::writeTextToCompare(Img& imgs, int space)
{
	int nsp = space * 0.6;
	int nnsp = space * 0.2;
	std::cout << space << '\t' << nsp << std::endl;

	int s = 0;
	for (auto const& a : imgs.images) {
		s += (imgs.o == Orientation::H) ? a.first.rows : a.first.cols;
		s += nnsp + nsp;
		
		double size = (double(1) / 22) * nsp;

		cv::putText(imgs.Compare,
			a.second,
			cv::Point(nnsp, s),
			cv::FONT_HERSHEY_DUPLEX,
			size,
			CV_RGB(255, 255, 255),
			(2 * size));

		s += nnsp;
	}
}

void ImageEditor::makeColorCompare() {}

void ImageEditor::makeExposureCompare() {}

