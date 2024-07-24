#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <numeric>
#include <cmath>
#include <chrono>
#include <filesystem>
#include <vector>

#include "image_processing.h"
#include "detection.h"


int main(int argc, char* argv[]){
    std::vector<std::string> files; 
    std::vector<std::string> markup_files; 
    double tp = 0, fp = 0, fn = 0, recall = 0, precision = 0, working_time = 0;


    if (argc <= 2){
        throw std::invalid_argument("Invalid parameters.");
    }

    std::string path(argv[1]);
    for (const auto & entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path());   

    std::string markup_path(argv[2]);
    for (const auto& entry: std::filesystem::directory_iterator(markup_path))
        markup_files.push_back(entry.path());
        
    std::sort(files.begin(), files.end());
    std::sort(markup_files.begin(), markup_files.end());


    auto t_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < files.size(); ++i){
        // std::string name = "/home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images/"  + std::to_string(i) + ".jpg";
        // cv::Mat output = cv::imread(cv::samples::findFile(files[i]));
        Detector detector;
        // auto work_start = std::chrono::high_resolution_clock::now();
        std::vector<cv::Rect> preds = detector.detect(files[i]);
        // auto work_end = std::chrono::high_resolution_clock::now();
        // working_time += std::chrono::duration<double, std::milli>(work_end-work_start).count() * 0.001;

        std::vector<cv::Rect> ground_truth = get_markup(&markup_files[i][0]);

        std::tuple<double, double, double> results = count_metrics(preds, ground_truth);
        tp += std::get<0>(results);
        fp += std::get<1>(results);
        fn += std::get<2>(results);

        // for (const cv::Rect& rect: preds){
        //     cv::rectangle(output, rect, cv::Scalar(0, 0, 255), 3);
        // }

        // for (const cv::Rect& rect: ground_truth){
        //     cv::rectangle(output, rect, cv::Scalar(255, 0, 0), 3);
        // }

        // cv::imwrite(name, output);
    }   
    // auto t_end = std::chrono::high_resolution_clock::now();
    recall = tp/(tp+fn);
    precision = tp/(tp+fp);
    std::cout << "TP: " << tp << "\n" << "FP: " << fp << "\n" << "FN: " << fn << "\n" << "Precision: " << precision << "\n" << 
    "Recall: " << recall << "\n";
    // << "Time elapsed: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() * 0.001 << "\n" << "Average time for single image: "<< working_time / 218 << "\n";
}



// int main(){
//     int kernel_rows = 3, kernel_cols = 3;
//     cv::Mat img = cv::imread(cv::samples::findFile("/home/rafiz/Desktop/barcode_detection/barcode_detection/Image/[P]ISBN_18_0001.jpg"));

//     cv::Mat img_conv(src.rows + kernel_rows - 1, src.cols + kernel_cols - 1, CV_64FC3, CV_RGB(0, 0, 0));
//     for (int i = 0; i < src.rows; i++) {
//         for (int j = 0; j < src.cols; j++) {
//                 img_conv.at<cv::Vec3d>(i+1, j+1)[0] = src.at<cv::Vec3d>(i, j)[0];
//                 img_conv.at<cv::Vec3d>(i+1, j+1)[1] = src.at<cv::Vec3d>(i, j)[1];
//                 img_conv.at<cv::Vec3d>(i+1, j+1)[2] = src.at<cv::Vec3d>(i ,j)[2];
//         }
//     }


//     cv::Mat preff = cv::Mat(img_conv.rows, img_conv.cols, CV_64FC3, CV_RGB(0, 0, 0)); 

//     for (int i = 1; i < img_conv.rows; i++){
//         for (int k = 0; k < 3; ++k){
//             preff.at<cv::Vec3d>(i, 0)[k] = preff.at<cv::Vec3d>(i-1, 0)[k] + img_conv.at<cv::Vec3d>(i, 0)[k];
//         }
//     }

    
//     for (int i = 1; i < img_conv.cols; i++){
//         for (int k = 0; k < 3; ++k){
//             preff.at<cv::Vec3d>(0, i)[k] = preff.at<cv::Vec3d>(0, i-1)[k] + img_conv.at<cv::Vec3d>(0, i)[k];
//         }
//     }

//     for (int i = 1; i < img_conv.rows; ++i){
//         for (int j = 1; j < img_conv.cols; ++j){
//             for (int k = 0; k < 3; ++k){
//                 preff.at<cv::Vec3d>(i, j)[k] = preff.at<cv::Vec3d>(i-1, j) + preff.at<cv::Vec3d>(i, j-1) + preff.at<cv::Vec3d>(i-1, j-1) + img_conv.at<cv::Vec3d>(i, j);
//             }
//         }
//     }


//     for (int x = (kernel_rows-1)/2; x < img.rows - ((kernel_rows - 1)/2); ++x){
//         for (int y = (kernel_cols-1)/2; y < img.cols - ((kernel_cols -1)/2; ++y)){
//             for (int k = 0; k < 3; ++k){
//                 img.at<cv::Vec3d>(x-((kernel_rows-1)/2), y-((kernel_cols-1)/2))[k] = preff.at<cv::Vec3d>(x, y) + preff.at<cv::Vec3d>(x-((kernel_rows-1)/2), y-((kernel_cols-1)/2)) - preff.at<cv:Vec3d>(x,)
//             }
//         }
//     }



//     std::cout << preff_mx[2][3] + preff_mx[0][0] - preff_mx[2][0];
// }