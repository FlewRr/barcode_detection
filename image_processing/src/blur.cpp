#include "image_processing.h"

void integral_image(const cv::Mat& src, cv::Mat& dst){
    // dst = cv::Mat(src.rows, src.cols, CV_64FC3);
    // for (int y = 1; y < dst.rows; ++y){
    //     for (int c = 0; c < 3; ++c){
    //         dst.at<cv::Vec3d>(y, 0)[c] = dst.at<cv::Vec3d>(y-1, 0)[c] + src.at<cv::Vec3d>(y, 0)[c];
    //     }
    // }
    // for (int x = 1; x < dst.cols; ++x){
    //     for (int c = 0; c < 3; ++c){
    //         dst.at<cv::Vec3d>(0, x)[c] = dst.at<cv::Vec3d>(0, x-1)[c] + src.at<cv::Vec3d>(0, x)[c];
    //     }
    // }
    // for (int y = 1; y < dst.rows; ++y){
    //     for (int x = 1; x < dst.cols; ++x){
    //         for (int c = 0; c < 3; ++c){
    //             dst.at<cv::Vec3d>(y, x)[c] = dst.at<cv::Vec3d>(y, x-1)[c] + dst.at<cv::Vec3d>(y-1, x)[c] - dst.at<cv::Vec3d>(y-1, x-1)[c] + src.at<cv::Vec3d>(y, x)[c];
    //         }
    //     }
    // }

    // dst.convertTo(dst, CV_32S);

    cv::Mat img = src.clone();
    img.convertTo(img, CV_64FC3);
    dst = cv::Mat(img.rows, img.cols, CV_64FC3);

    for (int row = 0; row < src.rows; ++row){
        double* p = dst.ptr<double>(row);
        double* q = img.ptr<double>(row);
        double* prev;
        for (int col = 0; col < 3 * src.cols; ++col){
            if (col < 3 && row == 0){
                p[col] = q[col];
            }
            else if (col < 3){
                p[col] = prev[col] + q[col];
            }
            else if (row == 0){
                p[col] = p[col-3] + q[col];
            }
            else{
                p[col] = p[col-3] + prev[col] - prev[col-3] + q[col];
            }
        }
        prev = dst.ptr<double>(row);
    }
}

void blur(const cv::Mat& src, cv::Mat& dst, int ksize){
     if (src.empty() || src.channels() != 3) {
        throw std::invalid_argument("Input image must be a non-empty 3-channel RGB image.");
    }

    if (ksize % 2 == 0 || ksize < 1) {
        throw std::invalid_argument("Kernel size must be a positive odd number.");
    }

    int radius = (ksize - 1) / 2;
    dst = cv::Mat::zeros(src.size(), CV_64FC3);
    cv::Mat integral;
    //  = cv::Mat(src.rows, src.cols, CV_64FC3);
    // cv::Mat img = src.clone();
    // img.convertTo(img, CV_64FC3);
    integral_image(src, integral);

    for (int y = radius; y < src.rows-radius; ++y) {
        for (int x = radius; x < src.cols-radius; ++x) {
            for (int c = 0; c < 3; ++c) {
                if (x - radius == 0 && y - radius == 0){
                    double sum = integral.at<cv::Vec3d>(y+radius, x+radius)[c];
                    dst.at<cv::Vec3d>(y-radius, x-radius)[c] = sum / (ksize * ksize);
                }
                else if (x - radius == 0){
                    double sum = integral.at<cv::Vec3d>(y+radius, x+radius)[c] - integral.at<cv::Vec3d>(y-radius-1, x+radius)[c];
                    dst.at<cv::Vec3d>(y-radius, x-radius)[c] = sum / (ksize * ksize);
                }
                else if (y - radius == 0){
                    double sum = integral.at<cv::Vec3d>(y+radius, x+radius)[c] - integral.at<cv::Vec3d>(y-radius, x+radius-1)[c];
                    dst.at<cv::Vec3d>(y-radius, x-radius)[c] = sum / (ksize * ksize);
                }
                else{
                    double sum = integral.at<cv::Vec3d>(y+radius, x+radius)[c]
                    - integral.at<cv::Vec3d>(y-radius-1, x+radius)[c] 
                    - integral.at<cv::Vec3d>(y+radius, x-radius-1)[c]
                    + integral.at<cv::Vec3d>(y-radius-1, x-radius-1)[c];
                    
                    dst.at<cv::Vec3d>(y-radius, x-radius)[c] = sum / (ksize * ksize);
                }
            }
        }
    }

    cv::Rect cropped(cv::Point(ksize, dst.rows-ksize), cv::Point(dst.cols-ksize, ksize));
    dst = cv::Mat(dst, cropped);
    dst.convertTo(dst, CV_8UC3);
}

