#include "threshold.h"
#include "otsu_threshold.h"

void threshold(const cv::Mat& img, cv::Mat& dst, int threshold, int max_value, int threshold_type, int otsu_flag){
    if (threshold_type > 1 || threshold_type < 0)
        throw std::invalid_argument("Incorrect threshold_type value");

    if (otsu_flag == 1)
        threshold = otsu_method(img);

    dst = img.clone();
    for (int i = 0; i < dst.rows; ++i){
        for (int j = 0; j < dst.cols; ++j){
            if (dst.at<uchar>(i, j) > threshold){
                if (threshold_type == 0)
                    dst.at<uchar>(i, j) = max_value;
                else
                    dst.at<uchar>(i, j) = 0;
            }
            else{
                if (threshold_type == 0)
                    dst.at<uchar>(i, j) = 0;
                else
                    dst.at<uchar>(i, j) = max_value;
            }
        }
    }
}
