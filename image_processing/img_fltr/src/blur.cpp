#include "blur.h"


cv::Mat blur(cv::Mat src, cv::Size ksize){
    cv::Mat kernel = cv::Mat_<double>(ksize.width, ksize.height, 1.0/(ksize.width*ksize.height));
    cv::Mat dst = filter(src, kernel);

    return dst;
}

