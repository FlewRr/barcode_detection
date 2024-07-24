#ifndef DETECTION_INCLUDE_DETECTION_H_20241607
#define DETECTION_INCLUDE_DETECTION_H_20241607

#include <opencv2/opencv.hpp>

class Detector{
    void preprocess(cv::Mat& img) const noexcept;
    void get_edge_map(cv::Mat& img) const;
    std::vector<std::vector<cv::Point>> get_contours(cv::Mat img) const;
public:
    Detector() = default;
    ~Detector() = default;

    std::vector<cv::Rect> detect(std::string filename) const;
};


std::vector<cv::Rect> get_markup(const char* filename);

double iou(const cv::Rect& rec1, const cv::Rect& rec2);

std::tuple<double, double, double> count_metrics(const std::vector<cv::Rect>& predictions, const std::vector<cv::Rect>& ground_truth);

#endif