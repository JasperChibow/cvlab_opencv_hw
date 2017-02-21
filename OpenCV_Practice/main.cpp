#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

int slider_value;
Mat src1, src2;
Mat frame2, dst1;

void on_trackbar(int, void*) {
	
}

int main()
{
	/*Mat img = imread("penggan.jpg");
	Mat resized_img;
	resize(img, resized_img, Size(img.cols / 8, img.rows / 8));
	imshow("Hello World!", resized_img);
	waitKey();*/

	Mat frame;
	VideoCapture cap("Blue Exorcist.mp4");
	VideoCapture cap2(0);

	src1 = imread("a.jpg", CV_LOAD_IMAGE_UNCHANGED);
	src2 = imread("b.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//resize(src1, src1, Size(src1.cols / 6, src1.rows / 6));
	//resize(src2, src2, Size(src2.cols / 6, src2.rows / 6));

	

	

	if (!cap.isOpened()) {
		cout << "Can't open the video!" << endl;
		return -1;
	}
	if (!cap2.isOpened()) return -1;

	Mat edges;
	namedWindow("my camera", 1);

	slider_value = 0;
	int slider_max = 100;

	namedWindow("trackbar demo", CV_WINDOW_KEEPRATIO);
	createTrackbar("Ratio", "trackbar demo", &slider_value, slider_max, on_trackbar);
	

	for (;;) {
		cap.read(frame);
		
		cap2 >> frame2;

		GaussianBlur(frame2, frame2, Size(3, 3), 0, 0);
		Mat dst1, dst2;
		Canny(frame2, dst1, 50, 150, 3);
		//threshold(dst1, dst2, 128, 255, THRESH_BINARY_INV);  //反轉影像，讓邊緣呈現黑線
		
		Mat ROI = frame(Rect(0, 0, frame2.cols, frame2.rows));
		addWeighted(ROI, 0.5, frame2, 0.3, 0, ROI);

		//if (frame.rows > 0) imshow("my camera", frame);
		//else break;

		//imshow("my camera", frame);

		on_trackbar(slider_value, 0);

		//waitKey(30);
		if (waitKey(30) == 27) break;
	}
	
	return 0;
}