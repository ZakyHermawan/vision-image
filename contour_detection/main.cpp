#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void show_image(Mat& image, String image_name = "Display image") {
	imshow(image_name, image);
	int k = waitKey(0);
	if (k == 's' or k == 'S') {
		cout << "Image saved" << endl;
		imwrite("contour_detection.png", image);
	}
}

void draw_dots(vector<vector<Point>>& contours, int width, int height, const char arr[]) {
	Mat draw(height, width, CV_8U, Scalar(0));
	int count = 0;
	for (int i = 0; i < contours.size(); i++) {
		for (int j = 0; j < contours[i].size(); ++j) {
			++count;
			circle(draw, contours[i][j], 2, Scalar(255, 255, 255), 1);
		}
	}
	cout << arr << " have " << count << "points" << endl;
	imshow(arr, draw);
	imwrite("contours.png", draw);

}

int main() {
	Mat img = imread("vb.png");

	// Change to greyscale image
	Mat grey_image;
	cvtColor(img, grey_image, COLOR_BGR2GRAY);

	// for pixel value > 150, converted to 255 (white)
	// for pixel value <= 150, converted to 0 (black)
	Mat threshold_image;
	threshold(grey_image, threshold_image, 150, 255, THRESH_BINARY);

	// find contours from binary image
	// hierarchy [next, previous, first_child, parent]
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// CHAIN_APPROX_SIMPLE: remove redundant points to save memory
	// RETR_TREE: retrieves all of the contours and reconstruct a full hierarchy of nested contours
	findContours(threshold_image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	draw_dots(contours, img.size().width, img.size().height, "Simple Contours");

	// Copy, so we kept the original image
	Mat image_copy{ img.clone() };
	drawContours(image_copy, contours, -1, Scalar(255, 0, 0), 2);


	show_image(image_copy);
}