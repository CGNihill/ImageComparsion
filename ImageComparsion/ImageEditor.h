#pragma once

#include <vector>
#include <utility>
#include <filesystem>

#include <opencv2/core.hpp>

namespace fs = std::filesystem;

class ImageEditor
{
public:
	enum Orientation { H, V };

	ImageEditor() = delete;
	ImageEditor(ImageEditor&&) = delete;
	ImageEditor(ImageEditor const&) = delete;
	

	static void loadImagesSingleCollage(std::vector<fs::path> imagesPath, std::vector<std::pair<std::string, std::string>> namings);
	static std::vector<std::pair<size_t, size_t>> getPossibleCompareResolution();
	static void setCompareResolution(size_t resByOrientation, Orientation orientation);
	static void startCompareGeneration();
	static void uploadColages(fs::path outPath, std::string outputName);

private:
	struct Img {
		std::vector<std::pair<cv::Mat, std::pair<std::string, std::string>>> images; // Images and naming in Compare
		cv::Mat Compare;
		Orientation o;
	};

	static std::vector<Img> images;

	static Orientation getImageOrinetation(cv::Mat&);
};
