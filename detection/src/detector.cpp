#include "detector.h"

void Detector::preprocess(cv::Mat& img) const noexcept{ 
    blur(img, img, cv::Size(7, 7));
    if (img.channels() == 3)
        cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

void Detector::get_edge_map(cv::Mat& img) const{
    int thr = cv::threshold(img, img, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    cv::Canny(img, img, thr/2, thr, 5);

    int element_size = int(std::sqrt(img.cols * img.rows) * 0.02);
    cv::Mat element = cv::getStructuringElement( 
        cv::MORPH_RECT, 
        cv::Size(element_size/2, element_size/2)); 
    dilate(img, img, element);

    cv::Mat morph_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
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

cv::Mat Detector::detect(const std::string filename) const{
    cv::Mat img = cv::imread(cv::samples::findFile(filename));
    cv::Mat out_img = img.clone();
        if(img.empty())
        throw std::invalid_argument("Could not read the image.");

    preprocess(img);
    get_edge_map(img);
    cv::imwrite("/home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images/edge_map.jpg", img);
    std::vector<std::vector<cv::Point>> contours = get_contours(img);

    for (auto contour: contours){
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.04 * cv::arcLength(contour, true), true);
            cv::Rect rect = cv::boundingRect(contour);
            cv::rectangle(out_img, rect, cv::Scalar(0, 0, 255), 3);
                // cv::Rect rect = cv::boundingRect(approx);
                // double ratio = (double)rect.width / rect.height;
                // double inv_ratio = 1/ratio;

                // int element_size = int(std::sqrt(img.cols * img.rows) * 0.02);
            //     cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));    

            //     if ((ratio < 4 || inv_ratio < 4) && (ratio > 1.5 || inv_ratio > 1.5)){
            //         cv::Mat cropped_rect = cv::Mat(out_img, rect);
            //         // cvtColor(cropped_rect, cropped_rect, cv::COLOR_BGR2GRAY);
            //         // cv::threshold(cropped_rect, cropped_rect, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
            //         // cv::Mat gradient;
            //         // cv::Sobel(cropped_rect, gradient, CV_64F, 1, 0, 3, 3);
            //         // convertScaleAbs(gradient, gradient);
            //         // int grad_non_black_pixels = cv::countNonZero(cropped_rect);
            //         // int grad_total_pixels = cropped_rect.cols * cropped_rect.rows;
            //         // double grad_black_ratio= (double)(grad_total_pixels - grad_non_black_pixels) / grad_total_pixels;
                   
            //         cv::morphologyEx(cropped_rect, cropped_rect, cv::MORPH_CLOSE, element);
            //         cropped_rect = cropped_rect.reshape(1, cropped_rect.rowsZ)
            //         int non_black_pixels = cv::countNonZero(cropped_rect);
            //         int total_pixels = cropped_rect.cols * cropped_rect.rows;
            //         // double white_ratio = (double)non_black_pixels/total_pixels;
            //         double black_ratio = (double)(total_pixels - non_black_pixels) / total_pixels;
            //         // cv::imwrite("/home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images/cropped_bar.jpg", cropped_rect);

            //         if (black_ratio > 0.4){
            //         cv::rectangle(out_img, rect, cv::Scalar(0, 0, 255), 3);
            //         }
            //     }
            // if (ratio < 1.1 && inv_ratio < 1.1 && ratio > 0.9 && inv_ratio > 0.9){
            //         cv::Mat cropped_rect = cv::Mat(out_img, rect);    
            //         // cvtColor(cropped_rect, cropped_rect, cv::COLOR_BGR2GRAY);
            //         // cv::threshold(cropped_rect, cropped_rect, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);  
            //         cv::morphologyEx(cropped_rect, cropped_rect, cv::MORPH_CLOSE, element);
            //         int non_black_pixels = cv::countNonZero(cropped_rect);
            //         int total_pixels = cropped_rect.cols * cropped_rect.rows;
            //         // double white_ratio = (double)non_black_pixels/total_pixels;
            //         double black_ratio = (double)(total_pixels - non_black_pixels) / total_pixels;
            //         cv::imwrite("//home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images/cropped_qr.jpg", cropped_rect);
            //         if (black_ratio > 0.4){
            //         cv::rectangle(out_img, rect, cv::Scalar(255, 0, 0), 3);
            //         }
            // }
        }

    return out_img;    
}
