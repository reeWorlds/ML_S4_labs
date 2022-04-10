#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

using namespace std;

void processImage(string pathLeft, string pathRight, string pathSaveDisparity, int numDisp, int blockSize, int medianBlur)
{
	cv::Mat leftImage, rightImage, grayLeft, grayRight, disparity;

	leftImage = cv::imread(pathLeft);
	rightImage = cv::imread(pathRight);

	cv::cvtColor(leftImage, grayLeft, cv::COLOR_BGR2GRAY);
	cv::cvtColor(rightImage, grayRight, cv::COLOR_BGR2GRAY);

	auto t_st = chrono::high_resolution_clock::now();

	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, numDisp, blockSize, 100, 1000);
	sgbm->compute(grayLeft, grayRight, disparity);

	disparity.convertTo(disparity, CV_16SC1);
	disparity.convertTo(disparity, CV_8UC1, 1.0 / 256.0);

	cv::normalize(disparity, disparity, 0, 255, cv::NORM_MINMAX);

	if (medianBlur)
	{
		cv::medianBlur(disparity, disparity, blockSize * 4 + 1);
	}

	auto t_end = chrono::high_resolution_clock::now();

	cv::imwrite(pathSaveDisparity, disparity);

	double duration = chrono::duration<double>(t_end - t_st).count();

	cout.precision(5);
	cout << "Done " << pathSaveDisparity << " in " << fixed << duration << "s\n";
}


int main()
{
	processImage("../images/medium1/left.png", "../images/medium1/right.png", "saves/m1.png", 128, 3, 0);
	processImage("../images/medium1/left.png", "../images/medium1/right.png", "saves/m1_bl.png", 128, 3, 1);

	processImage("../images/medium2/left.png", "../images/medium2/right.png", "saves/m2.png", 128, 3, 0);
	processImage("../images/medium2/left.png", "../images/medium2/right.png", "saves/m2_bl.png", 128, 3, 1);

	processImage("../images/medium3/left.png", "../images/medium3/right.png", "saves/m3.png", 128, 3, 0);
	processImage("../images/medium3/left.png", "../images/medium3/right.png", "saves/m3_bl.png", 128, 3, 1);


	processImage("../images/large1/left.png", "../images/large1/right.png", "saves/l1.png", 256, 5, 0);
	processImage("../images/large1/left.png", "../images/large1/right.png", "saves/l1_bl.png", 256, 5, 1);

	processImage("../images/large2/left.png", "../images/large2/right.png", "saves/l2.png", 256, 5, 0);
	processImage("../images/large2/left.png", "../images/large2/right.png", "saves/l2_bl.png", 256, 5, 1);

	processImage("../images/large3/left.png", "../images/large3/right.png", "saves/l3.png", 256, 5, 0);
	processImage("../images/large3/left.png", "../images/large3/right.png", "saves/l3_bl.png", 256, 5, 1);

	return 0;
}