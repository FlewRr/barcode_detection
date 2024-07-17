#include "detector.h"


void Detector::preprocess(cv::Mat& img) const noexcept{ 
    // blur(img, img, cv::Size(5, 5));
    if (img.channels() == 3)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

void Detector::get_edge_map(cv::Mat& img) const{
    int thr = cv::threshold(img, img, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/thr.jpg", img);
    cv::medianBlur(img, img, 9);

    cv::Canny(img, img, thr/2, thr, 5);
    int element_size = int(std::sqrt(img.cols * img.rows) * 0.02);
    cv::Mat element = cv::getStructuringElement( 
        cv::MORPH_RECT, 
        cv::Size(element_size/2, element_size/2)); 
    dilate(img, img, element);

    cv::Mat morph_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
    cv::morphologyEx(img, img, cv::MORPH_GRADIENT, morph_element);
    cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/processed_images/morph.jpg", img);
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

std::vector<std::vector<cv::Point>> Detector::detect(std::string filename) const{
    cv::Mat img = cv::imread(cv::samples::findFile(filename));

        if(img.empty())
        throw std::invalid_argument("Could not read the image.");

    preprocess(img);
    get_edge_map(img);
    std::vector<std::vector<cv::Point>> contours = get_contours(img);

    // cv::Rect rect = cv::boundingRect(contours[0]);

    return contours;
}
