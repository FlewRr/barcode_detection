#include "detector.h"


void Detector::preprocess(cv::Mat& img) const noexcept{ 
    blur(img, img, cv::Size(5, 5));
    if (img.channels() == 3)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

void Detector::get_edge_map(cv::Mat& img) const{
    int threshold = cv::threshold(img, img, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);

    cv::medianBlur(img, img, 9);
    cv::Canny(img, img, threshold/2, threshold, 3);
    dilate(img, img, cv::Mat(), cv::Point(-1, -1));
}

std::vector<std::vector<cv::Point>> Detector::get_contours(cv::Mat img) const{
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierachy;

        cv::findContours(img , contours , hierachy , cv::RETR_EXTERNAL , cv::CHAIN_APPROX_SIMPLE);
        std::sort(contours.begin(), contours.end(), [](std::vector<cv::Point> const & c1, std::vector<cv::Point> const & c2){
                    return cv::contourArea(c1) > cv::contourArea(c2);
        });

        return contours;

}

cv::Rect Detector::detect(std::string filename) const{
    cv::Mat img = cv::imread(cv::samples::findFile(filename));

        if(img.empty())
        throw std::invalid_argument("Could not read the image.");

    preprocess(img);
    get_edge_map(img);
    std::vector<std::vector<cv::Point>> contours = get_contours(img);

    cv::Rect rect = cv::boundingRect(contours[0]);

    return rect;
}
