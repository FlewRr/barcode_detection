#ifndef HOUGH_SRC_AUX_H_20241507
#define HOUGH_SRC_AUX_H_20241507

#include <opencv2/opencv.hpp>
#include <cmath>

void polar_to_cartesian(double rho, double theta, cv::Point& p1, cv::Point& p2);

#endif