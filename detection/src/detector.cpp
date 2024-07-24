#include "detection.h"

void Detector::preprocess(cv::Mat& img) const noexcept{ 
    if (img.channels() != 1)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);

    cv::Mat out_img = img.clone();
    cv::bilateralFilter(out_img, img, 13, 75, 75);
}

void Detector::get_edge_map(cv::Mat& img) const{
    int thr = cv::threshold(img, img, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    
    cv::Canny(img, img, thr/2, thr, 5);
    int element_size = int(std::sqrt(img.cols * img.rows) * 0.02);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(element_size, element_size/3)); 
    cv::morphologyEx(img, img, cv::MORPH_CLOSE, element);

    cv::Mat oelement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 9)); // 3x5 - best at that moment
    cv::morphologyEx(img, img, cv::MORPH_OPEN, oelement);

    cv::Mat gradelement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5)); 
    
    cv::morphologyEx(img, img, cv::MORPH_GRADIENT, gradelement);
}

std::vector<std::vector<cv::Point>> Detector::get_contours(cv::Mat img) const{
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(img , contours , hierarchy , cv::RETR_EXTERNAL , cv::CHAIN_APPROX_SIMPLE);
        std::sort(contours.begin(), contours.end(), [](std::vector<cv::Point> const & c1, std::vector<cv::Point> const & c2){
                    return cv::contourArea(c1) > cv::contourArea(c2);
        });

        return contours;

}

std::vector<cv::Rect> Detector::detect(const std::string filename) const{
    cv::Mat img = cv::imread(cv::samples::findFile(filename));
    cv::Mat out_img = img.clone();
    
    if(img.empty())
        throw std::invalid_argument("Could not read the image.");

    preprocess(img);
    get_edge_map(img);

    // cv::imwrite("/home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images/edge_map.jpg", img);

    std::vector<std::vector<cv::Point>> contours = get_contours(img);
    std::vector<cv::Rect> predictions;

    for (auto contour: contours){
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);
            if (approx.size() == 4 && cv::isContourConvex(approx)){
                cv::Rect rect = cv::boundingRect(contour);
                double rect_area = rect.width * rect.height, img_area = img.cols * img.rows;
            if (rect_area / img_area > 0.0065){
                double ratio = (double)rect.width / rect.height;
                double inv_ratio = 1/ratio;
                if ((ratio < 3.1 || inv_ratio < 3.1) && (ratio > 0.9 || inv_ratio > 0.9)){
                    cv::Mat cropped_rect = cv::Mat(img, rect);
                    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)); 
                    cv::morphologyEx(cropped_rect, cropped_rect, cv::MORPH_CLOSE, element);

                    int non_black_pixels = cv::countNonZero(cropped_rect);
                    int total_pixels = cropped_rect.cols * cropped_rect.rows;
                    double black_ratio= (double)(total_pixels - non_black_pixels) / total_pixels;

                    if (black_ratio > 0.6)
                        predictions.push_back(rect);
                }
            }
        }
    }

    return predictions;
}
