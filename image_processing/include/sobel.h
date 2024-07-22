#ifndef GRADIENT_SOBEL_SOBEL_H_20241307
#define GRADIENT_SOBEL_SOBEL_H_20241307

#include <iostream>
#include <cmath>
#include <numeric>
#include <opencv2/opencv.hpp>


double compute_filter(const cv::Mat& src, const cv::Mat& kernel, int x, int y);

void create_sobel_kernel(cv::Mat& kernel_x, cv::Mat& kernel_y);

void sobel(const cv::Mat& src, cv::Mat& dst);

#endif