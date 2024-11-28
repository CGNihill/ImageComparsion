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
	static std::vector<int> getPossibleCompareResolution();
	static void setCompareResolution(int resolution);
	static void startCompareGeneration();
	static void uploadColages(fs::path outPath, std::string outputName);

private:
	struct Img {
		std::vector<std::pair<cv::Mat, std::pair<std::string, std::string>>> images; // Images and naming in Compare
		cv::Mat Compare;
		Orientation o;
	};

	static std::vector<Img> images;
	static int mainCompareResolution;

	static Orientation getImageOrinetation(cv::Mat&);
	static void resizeImages(Img&);
	static std::pair<int, int> calculateNewSize(int, int);
};