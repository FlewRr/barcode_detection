#ifndef OTSU_SRC_THRESHOLD_H_20241107
#define OTSU_SRC_THRESHOLD_H_20241107

#include <opencv2/opencv.hpp>

cv::Mat threshold(const cv::Mat& img, cv::Mat& dst, int threshold, int max_value, int threshold_type=0, int otsu_flag=0);

#endif