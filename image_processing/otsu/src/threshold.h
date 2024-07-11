#include <opencv2/opencv.hpp>

cv::Mat threshold(cv::Mat img, int threshold, int max_value, int threshold_type=0, int otsu_flag=0);