#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <numeric>
#include "otsu.h"
#include "img_fltr.h"
#include "gradient.h"





int main(){
    cv::Mat A = cv::imread(cv::samples::findFile("/home/sfleur/barcode_detection/barcode_detection/images/Excise_stamp_0002.jpg"));
    
    cv::Mat gradient = sobel(A);

    cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/blur.png", gradient);
  
}   