#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	VideoCapture capture(0);

	if (!capture.isOpened()) {
		cout << "Fail to open\n";
		return -1;
	}

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);

	// initialize video object
	VideoWriter video("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

	while (true) {

		// save captured image
		Mat frame;
		capture.read(frame);


		if (frame.empty()) {
			cout << "frame kosong" << endl;
			break;
		}

		// flip the frame, so it looks like a mirror
		Mat flipped;
		flip(frame, flipped, 1);
		imshow("Frame", flipped);
        video.write(frame);

		// exit if user press ESC
        char c = (char)waitKey(10);
		if (c == 27) {
			break;
		}
	}

	// close video capturing device and video writer
	capture.release();
	video.release();


	destroyAllWindows();
	return 0;

}