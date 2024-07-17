#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <numeric>
#include <cmath>
#include "otsu.h"
#include "img_fltr.h"
#include "gradient.h"
#include "hough_transform.h"
#include "detection.h"

#include <filesystem>
#include <vector>

int main(int argc, char* argv[]){
    std::vector<std::string> files; 

    if (argc <= 2){
        throw std::invalid_argument("Invalid parameters.");
    }

    std::string path(argv[1]);
    for (const auto & entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path());   

    for (int i = 0; i < 100; ++i){
        std::string name = argv[2] + std::string("/") + std::to_string(i) + ".jpg";
        cv::Mat A = cv::imread(cv::samples::findFile(files[i]));
        Detector detector;
        // cv::Rect rect = detector.detect(files[i]);
        std::vector<std::vector<cv::Point>> crs = detector.detect(files[i]);
        // cv::drawContours(A, crs, -1, cv::Scalar(255, 0, 0), 3);
        for (auto contour: crs){
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);
            if (cv::contourArea(approx) > 300){
                cv::Rect rect = cv::boundingRect(approx);
                cv::rectangle(A, rect, cv::Scalar(255, 0, 0), 3);
            }
        }
        cv::imwrite(name, A);
    }   
}