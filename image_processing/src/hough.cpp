#include "image_processing.h"
#include "aux.h"

#define BIN_WIDTH 1
#define NUM_BINS 180 / BIN_WIDTH

void hough_transform(cv::Mat& image, std::vector<std::tuple<cv::Point, cv::Point>>& lines, int threshold){
    int max_dist = std::hypot(image.rows, image.cols);
    double rho = 0, theta = 0;

    std::vector<std::vector<int>> votes(2 * max_dist, std::vector<int>(NUM_BINS+1, 0));

    for (int i = 0; i < image.rows; ++i){
        for (int j = 0; j < image.cols; ++j){
            if (image.at<uchar>(i, j) == 255) {
                for (int theta = 0; theta <= 180; theta += BIN_WIDTH){
                    rho = std::round(j * std::cos(CV_PI * theta / 180) + i * std::sin(CV_PI * theta / 180)) + max_dist;
                    votes[rho][theta]++;
                }
            }
        }
    }


    for (int i = 0; i < votes.size(); ++i){
        for (int j = 0; j < votes[i].size(); ++j){
            if (votes[i][j] >= threshold) {
                rho = i - max_dist;
                theta = CV_PI * j / 180;

                cv::Point p1, p2;
                polar_to_cartesian(rho, theta, p1, p2);

                lines.push_back(std::make_tuple(p1, p2));
                // cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
            }
        }
    }
}