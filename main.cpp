#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include "otsu.h"


int main(){
    cv::Mat A = cv::imread(cv::samples::findFile("/home/sfleur/barcode_detection/images/EAN13_09_0062.jpg"),  cv::IMREAD_GRAYSCALE);
    cv::Mat B = cv::imread(cv::samples::findFile("/home/sfleur/barcode_detection/images/EAN13_09_0062.jpg"),  cv::IMREAD_GRAYSCALE);

    int thr = otsu_method(A);


    cv::Mat C = threshold(A, thr, 255, 0, 0);
    cv::Mat D = threshold(B, 0, 255, 0, 1);

    cv::resize(C, C, cv::Size(1366, 720), 0, 0);
    cv::resize(D, D, cv::Size(1366, 720), 0, 0);
    cv::imshow("C", C);
    cv::imshow("D", D);
    cv::waitKey();
}   