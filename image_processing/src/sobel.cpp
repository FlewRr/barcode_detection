#include "sobel.h"

void create_sobel_kernel(cv::Mat& kernel_x, cv::Mat& kernel_y){
    kernel_x = (cv::Mat_<float>(3, 3) <<
                -1, 0, 1,
                -2, 0, 2,
                -1, 0, 1);

    kernel_y = (cv::Mat_<float>(3, 3) <<
                -1, -2, -1,
                0,  0,  0,
                1,  2,  1);        
}

double compute_filter(const cv::Mat& src, cv::Mat kernel, int x, int y){
    float value = 0;
    for (int i = -(kernel.rows-1)/2; i <= (kernel.rows-1)/2; ++i){
        for (int j = -(kernel.cols-1)/2; j <= (kernel.cols-1)/2; ++j){
            value += src.at<uchar>(x+i, y+j) * kernel.at<float>(i+((kernel.rows-1)/2), j+((kernel.cols-1)/2));
        }
    }

    return value;
}


void sobel(const cv::Mat& src, cv::Mat& dst){
    if (src.channels() == 3)
        cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    
    src.convertTo(src, CV_8U);
    cv::Mat sobel_x, sobel_y;
    
    create_sobel_kernel(sobel_x, sobel_y);
    dst = cv::Mat(src.rows, src.cols, CV_8U);

    for (int x = 1; x < src.rows; ++x){
        for (int y = 1; y < src.cols; ++y){
            double pixel_x = compute_filter(src, sobel_x, x, y);
            double pixel_y = compute_filter(src, sobel_y, x, y);
        
            dst.at<uchar>(x, y) = cv::saturate_cast<uchar>(std::ceil(std::sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y))));
        }
    }
}
