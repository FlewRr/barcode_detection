#include "blur.h"


void blur(cv::Mat src, cv::Mat& dst, cv::Size ksize){
    cv::Mat kernel = cv::Mat_<double>(ksize.width, ksize.height, 1.0/(ksize.width*ksize.height));
    dst = filter(src, kernel);
}

