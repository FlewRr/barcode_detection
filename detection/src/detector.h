#ifndef DETECTION_SRC_DETECTOR_H_20241607
#define DETECTION_SRC_DETECTOR_H_20241607

#include <opencv2/opencv.hpp>

class Detector{
    void preprocess(cv::Mat& img) const noexcept;
    void get_edge_map(cv::Mat& img) const;
    std::vector<std::vector<cv::Point>> get_contours(cv::Mat img) const;
public:
    Detector() = default;
    ~Detector() = default;

    cv::Rect detect(std::string filename) const;
};

#endif