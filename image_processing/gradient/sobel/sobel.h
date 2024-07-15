#ifndef GRADIENT_SOBEL_SOBEL_H_20241307
#define GRADIENT_SOBEL_SOBEL_H_20241307

#include <iostream>
#include <cmath>
#include <numeric>
#include <opencv2/opencv.hpp>


double compute_filter(cv::Mat src, cv::Mat kernel, int x, int y);

void create_sobel_kernel(cv::Mat& kernel_x, cv::Mat& kernel_y);

cv::Mat sobel(cv::Mat src);

#endif