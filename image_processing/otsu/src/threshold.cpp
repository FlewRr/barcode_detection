#include "threshold.h"
#include "otsu_threshold.h"

cv::Mat threshold(cv::Mat img, int threshold, int max_value, int threshold_type, int otsu_flag){
    if (threshold_type > 1 || threshold_type < 0)
        throw std::invalid_argument("Incorrect threshold_type value");

    if (otsu_flag == 1)
        threshold = otsu_method(img);

    for (int i = 0; i < img.rows; ++i){
        for (int j = 0; j < img.cols; ++j){
            if (img.at<uchar>(i, j) > threshold){
                if (threshold_type == 0)
                    img.at<uchar>(i, j) = max_value;
                else
                    img.at<uchar>(i, j) = 0;
            }
            else{
                if (threshold_type == 0)
                    img.at<uchar>(i, j) = 0;
                else
                    img.at<uchar>(i, j) = max_value;
            }
        }
    }

    return img;
}
