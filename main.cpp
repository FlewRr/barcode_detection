#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <numeric>
#include <cmath>
#include "otsu.h"
#include "img_fltr.h"
#include "gradient.h"
#include "hough_transform.h"

int main(){
    // cv::Mat A_rgb = cv::imread(cv::samples::findFile("/home/sfleur/barcode_detection/barcode_detection/images/EAN13_09_0077.jpg"));
    // cv::Mat A;
    // blur(A_rgb, A_rgb, cv::Size(3, 3));
    // cvtColor(A_rgb, A, cv::COLOR_BGR2GRAY);

    // int thr = otsu_method(A);
    // A = threshold(A, thr, 255, 0, 0);
    // cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/threshold.png", A);
    // // double median = medianMat(A, 256), sigma = 0.33;
    // // int lower_thresh = int(std::max(0.0, (1.0 - sigma) * median));
    // // int upper_thresh = int(std::min(255.0, (1.0 + sigma) * median));
    // cv::Canny(A, A, thr/2-5, thr+10, 3);
    // // cv::Mat element = getStructuringElement( 
    // // cv::MORPH_RECT, 
    // // cv::Size(5, 5)); 
    // // cv::morphologyEx(A, A, cv::MORPH_CLOSE, element);
    // cv::dilate(A, A, cv::Mat());
    // cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/canny.png", A);
    // std::vector<cv::Vec4i> linesP;
    // cv::HoughLinesP(A, linesP, 1, CV_PI/180, 50); 

    // for( size_t i = 0; i < linesP.size(); i++ )
    // {
    // cv::Vec4i l = linesP[i];
    // line(A_rgb, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
    // }

    // cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/hough.png", A_rgb);
}   