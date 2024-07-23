#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

void filter(cv::Mat src, cv::Mat& dst, cv::Mat kernel);

void blur(const cv::Mat& src, cv::Mat& dst, cv::Size ksize);

int otsu_method(const cv::Mat& img);

double compute_filter(const cv::Mat& src, const cv::Mat& kernel, int x, int y);

void create_sobel_kernel(cv::Mat& kernel_x, cv::Mat& kernel_y);

void sobel(const cv::Mat& src, cv::Mat& dst);

void threshold(const cv::Mat& img, cv::Mat& dst, int threshold, int max_value, int threshold_type=0, int otsu_flag=0);
