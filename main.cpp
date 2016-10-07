#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat frame = imread("target.jpg");
	// Mat frameHLS;
	Mat upper_bound, lower_bound;
	Mat filtered;

	namedWindow("Stronghold Track");

	// cvtColor(frame, frameHLS, CV_BGR2HLS);

	inRange(frame, Scalar(240, 240, 240), Scalar(255, 255, 255), filtered);
	//inRange(frame, Scalar(0, 90, 0), Scalar(0, 100, 0), upper_bound);

	// addWeighted(lower_bound, 1.0, upper_bound, 1.0, 0.0, filtered);
	//GaussianBlur(filtered, filtered, cv::Size(9, 9), 2, 2);

	// Find contours
	int largest_area = 0;
    int largest_contour_index = 0;
    Rect bounding_rect;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
    findContours(filtered, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    for( int i = 0; i< contours.size(); i++ )
    {
        //  Find the area of contour
        double a = contourArea(contours[i], false); 
        if(a > largest_area) {
            largest_area = a;
            // Store the index of largest contour
            largest_contour_index = i;               
            // Find the bounding rectangle for biggest contour
            bounding_rect = boundingRect(contours[i]);
        }
    }

    rectangle(frame, bounding_rect,  Scalar(0,255,0), 2, 8, 0);

	imshow("Stronghold Track", frame);
	waitKey();

	return 0;
}
