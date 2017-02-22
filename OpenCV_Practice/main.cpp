#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

int slider_value;
Mat src1, src2;


void on_trackbar(int, void*) {
	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	Mat dst;

	//addWeighted(src1, alpha, src2, beta, 0.0, dst);
	//imshow("trackbar demo", dst);
}

int main()
{
	Mat frame, frame2;
	VideoCapture cap("Blue Exorcist.mp4");
	VideoCapture cap2(0);

	src1 = imread("a.jpg", CV_LOAD_IMAGE_UNCHANGED);
	src2 = imread("b.jpg", CV_LOAD_IMAGE_UNCHANGED);

	if (!cap.isOpened()) {
		cout << "Can't open the video!" << endl;
		return -1;
	}
	if (!cap2.isOpened()) return -1;


	namedWindow("my camera", 1);

	slider_value = 0;
	int slider_max = 100;

	//namedWindow("trackbar demo", CV_WINDOW_KEEPRATIO);
	createTrackbar("Ratio", "my camera", &slider_value, slider_max, on_trackbar);
	on_trackbar(slider_value, 0);
	
	Mat dst1, dst2;
	double alpha, beta;
	Mat dst;
	for (;;) {
		cap.read(frame);
		cap2 >> frame2;
		dst.create(frame2.size(), frame2.type());
		GaussianBlur(frame2, frame2, Size(3, 3), 0, 0);
		Canny(frame2, dst1, 50, 150, 3);
		//threshold(dst1, dst2, 128, 255, THRESH_BINARY_INV);  //反轉影像，讓邊緣呈現黑線
		cvtColor(dst1, dst1, CV_GRAY2BGR);
		Mat ROI = frame(Rect(0, 0, frame2.cols, frame2.rows));
		
		addWeighted(ROI, 0, frame2, 1, 0, ROI);

		alpha = (double)slider_value / 100.0;
		beta = (1.0 - alpha);
		
		addWeighted(dst1, alpha, frame2, beta, 0.0, ROI);

		//if (frame.rows > 0) imshow("my camera", frame);
		//else break;

		imshow("my camera", frame);
		
		//waitKey(30);
		if (waitKey(30) == 27) break;
	}
	return 0;
}