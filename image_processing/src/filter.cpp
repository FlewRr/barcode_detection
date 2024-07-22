#include "filter.h"


void filter(const cv::Mat& src, cv::Mat& dst, cv::Mat kernel){
    if (src.channels() != 3){
        throw std::invalid_argument("Number of channels different from 3 are not supported.");
    }
    src.convertTo(src, CV_64FC3);
    cv::Mat img_conv(src.rows + kernel.rows - 1, src.cols + kernel.cols - 1, CV_64FC3, CV_RGB(0, 0, 0));
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
                img_conv.at<cv::Vec3d>(i+1, j+1)[0] = src.at<cv::Vec3d>(i, j)[0];
                img_conv.at<cv::Vec3d>(i+1, j+1)[1] = src.at<cv::Vec3d>(i, j)[1];
                img_conv.at<cv::Vec3d>(i+1, j+1)[2] = src.at<cv::Vec3d>(i ,j)[2];
        }
    }

    dst = cv::Mat(src.rows, src.cols, CV_64FC3, CV_RGB(0, 0, 0));

    for (int x = (kernel.rows-1)/2; x < src.rows - ((kernel.rows - 1)/ 2); ++x){
        for (int y = (kernel.cols-1)/2; y < src.cols - ((kernel.cols - 1)/2); ++y){
            double comp1 = 0;
            double comp2 = 0;
            double comp3 = 0;

            for (int u =-(kernel.rows-1)/2; u <= (kernel.rows-1)/2; ++u) {
                for (int v=-(kernel.cols-1)/2; v <= (kernel.cols-1)/2; ++v){
                    comp1 += img_conv.at<cv::Vec3d>(x+u, y+v)[0] * kernel.at<double>(u+((kernel.rows-1)/2), v+((kernel.cols-1)/2));
                    comp2 += img_conv.at<cv::Vec3d>(x+u, y+v)[1] * kernel.at<double>(u+((kernel.rows-1)/2), v+((kernel.cols-1)/2));
                    comp3 += img_conv.at<cv::Vec3d>(x+u, y+v)[2] * kernel.at<double>(u+((kernel.rows-1)/2), v+((kernel.cols-1)/2));

                }
            }

            dst.at<cv::Vec3d>(x-((kernel.rows-1)/2), y-((kernel.cols-1)/2))[0] = comp1;
            dst.at<cv::Vec3d>(x-((kernel.rows-1)/2), y-((kernel.cols-1)/2))[1] = comp2;
            dst.at<cv::Vec3d>(x-((kernel.rows-1)/2), y-((kernel.cols-1)/2))[2] = comp3;

        }
    }

    dst.convertTo(dst, CV_8UC3);
}