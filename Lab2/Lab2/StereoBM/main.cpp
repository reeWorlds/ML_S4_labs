#include <iostream>
#include <string>
#include <chrono>

#include "opencv2/opencv.hpp"

using namespace std;

#define cores 8

int sqr(int v)
{
	return v * v;
}

void findDispLeft(cv::Mat& li, cv::Mat& ri, cv::Mat& disp, int blockSize, int maxSSDPP, int medianBlur, double dispChange = 1.0)
{
	int h = li.size().height, w = li.size().width;

	disp = cv::Mat(h, w, CV_8UC1);
	disp = cv::Scalar(0);

#pragma omp parallel for num_threads(cores)
	for (int blockI = 0; blockI < h; blockI += blockSize)
	{
		for (int blockJ = 0; blockJ < w; blockJ += blockSize)
		{
			int th = min(blockI + blockSize, h - 1) - blockI, tw = min(blockJ + blockSize, w - 1) - blockJ;

			int minSSD = 1e9, minSSDshift = 0;
			for (int rBlockJ = blockJ; rBlockJ >= 0; rBlockJ--)
			{
				int mySSD = 0;

				for (int i = 0; i < th; i++)
				{
					for (int j = 0; j < tw; j++)
					{
						cv::Vec3b lp = li.at<cv::Vec3b>(blockI + i, blockJ + j);
						cv::Vec3b rp = ri.at<cv::Vec3b>(blockI + i, rBlockJ + j);

						mySSD += sqr(int(lp.val[0]) - int(rp.val[0]));
						mySSD += sqr(int(lp.val[1]) - int(rp.val[1]));
						mySSD += sqr(int(lp.val[2]) - int(rp.val[2]));
					}
				}

				if (minSSD > mySSD)
				{
					minSSD = mySSD;
					minSSDshift = blockJ - rBlockJ;
				}
			}

			cv::Rect rect(blockJ, blockI, th, tw);

			if (minSSD < maxSSDPP * th * tw)
			{
				cv::rectangle(disp, rect, cv::Scalar(min(pow(minSSDshift * dispChange, 1.2), 255.0)), cv::FILLED);
			}
		}
	}

	if (medianBlur)
	{
		cv::medianBlur(disp, disp, blockSize * 4 + 1);
	}
}

void findDispRight(cv::Mat& li, cv::Mat& ri, cv::Mat& disp, int blockSize, int maxSSDPP, int medianBlur, double dispChange = 1.0)
{
	int h = ri.size().height, w = ri.size().width;

	disp = cv::Mat(h, w, CV_8UC1);
	disp = cv::Scalar(0);

#pragma omp parallel for num_threads(cores)
	for (int blockI = 0; blockI < h; blockI += blockSize)
	{
		for (int blockJ = 0; blockJ < w; blockJ += blockSize)
		{
			int th = min(blockI + blockSize, h - 1) - blockI, tw = min(blockJ + blockSize, w - 1) - blockJ;

			int minSSD = 1e9, minSSDshift = 0;
			for (int lBlockJ = blockJ; lBlockJ + blockSize - 1 < w; lBlockJ++)
			{
				int mySSD = 0;

				for (int i = 0; i < th; i++)
				{
					for (int j = 0; j < tw; j++)
					{
						cv::Vec3b lp = li.at<cv::Vec3b>(blockI + i, lBlockJ + j);
						cv::Vec3b rp = ri.at<cv::Vec3b>(blockI + i, blockJ + j);

						mySSD += sqr(int(lp.val[0]) - int(rp.val[0]));
						mySSD += sqr(int(lp.val[1]) - int(rp.val[1]));
						mySSD += sqr(int(lp.val[2]) - int(rp.val[2]));
					}
				}

				if (minSSD > mySSD)
				{
					minSSD = mySSD;
					minSSDshift = lBlockJ - blockJ;
				}
			}

			cv::Rect rect(blockJ, blockI, th, tw);

			if (minSSD < maxSSDPP * th * tw)
			{
				cv::rectangle(disp, rect, cv::Scalar(min(pow(minSSDshift * dispChange, 1.2), 255.0)), cv::FILLED);
			}
		}
	}

	if (medianBlur)
	{
		cv::medianBlur(disp, disp, blockSize * 4 + 1);
	}
}

void processImage(string pathLeft, string pathRight, string pathSaveDisparityL, string pathSaveDisparityR,
	int blockSize, int medianBlur, double dispChange = 1.0)
{
	cv::Mat leftImage, rightImage, disparityLeft, disparityRight;

	leftImage = cv::imread(pathLeft);
	rightImage = cv::imread(pathRight);

	auto t_st = chrono::high_resolution_clock::now();

	findDispLeft(leftImage, rightImage, disparityLeft, blockSize, 75 * 3, medianBlur, dispChange);
	findDispRight(leftImage, rightImage, disparityRight, blockSize, 75 * 3, medianBlur, dispChange);

	auto t_end = chrono::high_resolution_clock::now();

	cv::imwrite(pathSaveDisparityL, disparityLeft);
	cv::imwrite(pathSaveDisparityR, disparityRight);

	double duration = chrono::duration<double>(t_end - t_st).count();

	cout.precision(5);
	cout << "Done " << pathSaveDisparityL << " + " << pathSaveDisparityR << " in " << fixed << duration << "s\n";
}

int main()
{
	processImage("../images/medium1/left.png", "../images/medium1/right.png", "saves/m1_l.png", "saves/m1_r.png", 3, 0);
	processImage("../images/medium1/left.png", "../images/medium1/right.png", "saves/m1_l_bl.png", "saves/m1_r_bl.png", 3, 1);

	processImage("../images/medium2/left.png", "../images/medium2/right.png", "saves/m2_l.png", "saves/m2_r.png", 3, 0);
	processImage("../images/medium2/left.png", "../images/medium2/right.png", "saves/m2_l_bl.png", "saves/m2_r_bl.png", 3, 1);

	processImage("../images/medium3/left.png", "../images/medium3/right.png", "saves/m3_l.png", "saves/m3_r.png", 3, 0);
	processImage("../images/medium3/left.png", "../images/medium3/right.png", "saves/m3_l_bl.png", "saves/m3_r_bl.png", 3, 1);


	processImage("../images/large1/left.png", "../images/large1/right.png", "saves/l1_l.png", "saves/l1_r.png", 5, 0, 0.5);
	processImage("../images/large1/left.png", "../images/large1/right.png", "saves/l1_l_bl.png", "saves/l1_r_bl.png", 3, 1, 0.5);

	processImage("../images/large2/left.png", "../images/large2/right.png", "saves/l2_l.png", "saves/l2_r.png", 5, 0, 0.5);
	processImage("../images/large2/left.png", "../images/large2/right.png", "saves/l2_l_bl.png", "saves/l2_r_bl.png", 3, 1, 0.5);

	processImage("../images/large3/left.png", "../images/large3/right.png", "saves/l3_l.png", "saves/l3_r.png", 5, 0, 0.5);
	processImage("../images/large3/left.png", "../images/large3/right.png", "saves/l3_l_bl.png", "saves/l3_r_bl.png", 5, 1, 0.5);

	return 0;
}