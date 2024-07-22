#ifndef IMG_FILTR_SRC_FILTER_H_20241107
#define IMG_FILTR_SRC_FILTER_H_20241107

#include <opencv2/opencv.hpp>

void filter(const cv::Mat& src, cv::Mat& dst, cv::Mat kernel);

#endif