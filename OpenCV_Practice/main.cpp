#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <iostream>


using namespace cv;
using namespace std;

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

	if (!cap.isOpened()) {
		cout << "Can't open the video!" << endl;
		return -1;
	}
	if (!cap2.isOpened()) return -1;

	Mat edges;
	namedWindow("my camera", 1);

	for (;;) {
		cap.read(frame);
		Mat frame2;
		cap2 >> frame2;

		Mat ROI = frame(Rect(0, 0, frame2.cols, frame2.rows));
		addWeighted(ROI, 0.5, frame2, 0.3, 0, ROI);

		//if (frame.rows > 0) imshow("my camera", frame);
		//else break;

		imshow("my camera", frame);

		//waitKey(30);
		if (waitKey(30) == 27) break;
	}
	return 0;
}