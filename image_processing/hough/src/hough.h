#ifndef HOUGH_SRC_HOUGH_H_20241507
#define HOUGH_SRC_HOUGH_H_20241507

#include <opencv2/opencv.hpp>

void hough_transform(cv::Mat& image, std::vector<std::tuple<cv::Point, cv::Point>>& lines, int threshold);

#endif