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

	if (!cap.isOpened()) {
		cout << "Can't open the video!" << endl;
		return -1;
	}

	for (;;) {
		cap.read(frame);

		if (frame.rows > 0) imshow("Video Frame", frame);
		else break;

		waitKey(30);
	}
	return 0;
}