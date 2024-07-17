#include "detector.h"


void Detector::preprocess(cv::Mat& img) const noexcept{ 
    // blur(img, img, cv::Size(5, 5));
    if (img.channels() == 3)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

void Detector::get_edge_map(cv::Mat& img) const{
    int thr = cv::threshold(img, img, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    cv::medianBlur(img, img, 9);

    cv::Canny(img, img, thr/2, thr, 5);
    int element_size = int(std::sqrt(img.cols * img.rows) * 0.02);
    cv::Mat element = cv::getStructuringElement( 
        cv::MORPH_RECT, 
        cv::Size(element_size/2, element_size/2)); 
    dilate(img, img, element);

    cv::Mat morph_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
    cv::morphologyEx(img, img, cv::MORPH_GRADIENT, morph_element);
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

cv::Mat Detector::detect(std::string filename) const{
    cv::Mat img = cv::imread(cv::samples::findFile(filename));
    cv::Mat out_img = img.clone();
        if(img.empty())
        throw std::invalid_argument("Could not read the image.");

    preprocess(img);
    get_edge_map(img);
    std::vector<std::vector<cv::Point>> contours = get_contours(img);

    for (auto contour: contours){
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);
            if (cv::contourArea(approx) > 300){
                cv::Rect rect = cv::boundingRect(approx);
                cv::rectangle(out_img, rect, cv::Scalar(255, 0, 0), 3);
            }
        }

    return out_img;    
}
