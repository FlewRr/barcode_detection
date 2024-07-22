#ifndef IMG_FILTR_SRC_BLUR_H_20241107
#define IMG_FILTR_SRC_BLUR_H_20241107

#include "filter.h"

void blur(const cv::Mat& src, cv::Mat& dst, cv::Size ksize);

#endif