#include <iostream>
using namespace std;

/*

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <chrono>

#include "opencv2/opencv.hpp"
using namespace std;

#define pathLeft "images/l3/left.png"
#define pathRight "images/l3/right.png"

#define cores 4
#define maxSSDPP (100 * 3)

cv::Mat leftIm, rightIm;
cv::Mat dispLeft, dispRight;

int blockSize = 4;
int medianFilter = 0;

int sqr(int v)
{
	return v * v;
}

void findDispLeft()
{
	int h = leftIm.size().height, w = leftIm.size().width;
	if (dispLeft.size() != leftIm.size())
	{
		dispLeft = cv::Mat(h, w, CV_8UC1);
	}

	dispLeft = cv::Scalar(0);

	auto t_st = chrono::high_resolution_clock::now();

	for (int blockI = 0; blockI < h; blockI += blockSize)
	{
		cout << blockI << "\n";

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
						cv::Vec3b lp = leftIm.at<cv::Vec3b>(blockI + i, blockJ + j);
						cv::Vec3b rp = rightIm.at<cv::Vec3b>(blockI + i, rBlockJ + j);

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
				cv::rectangle(dispLeft, rect, cv::Scalar( min(pow(minSSDshift, 1.2), 255.0)), cv::FILLED);
			}
			else
			{
				cv::rectangle(dispLeft, rect, cv::Scalar(0), cv::FILLED);
			}
		}
	}

	if (medianFilter)
	{
		cv::medianBlur(dispLeft, dispLeft, blockSize * 2 + 1);
	}

	auto t_end = chrono::high_resolution_clock::now();

	double duration = chrono::duration<double>(t_end - t_st).count();

	cout.precision(5);
	cout << "Duration for left disparity blSize = " << blockSize << " equal " << fixed << duration << "s\n";
}

int main(int argc, char* argv[])
{
	leftIm = cv::imread(pathLeft);
	rightIm = cv::imread(pathRight);

	// BM
	/*
	while (true)
	{
		findDispLeft();

		cv::imshow("left", leftIm);
		cv::imshow("right", rightIm);
		cv::imshow("leftDisparity", dispLeft);

		int c = cv::waitKey();
		if (c == 27)
		{
			break;
		}
		else if (c == '+')
		{
			if (blockSize < 64)
			{
				blockSize <<= 1;
				cout << "block size = " << blockSize << "\n";
			}
		}
		else if (c == '-')
		{
			if (blockSize > 4)
			{
				blockSize >>= 1;
				cout << "block size = " << blockSize << "\n";
			}
		}
		else if (c == 'm')
		{
			medianFilter ^= 1;
			cout << "medianFilter = " << medianFilter << "\n";
		}
	}

*/

int main()
{




	return 0;
}