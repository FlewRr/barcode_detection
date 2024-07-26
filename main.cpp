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


// int main(int argc, char* argv[]){
//     std::vector<std::string> files; 
//     std::vector<std::string> markup_files; 
//     double tp = 0, fp = 0, fn = 0, recall = 0, precision = 0, working_time = 0;


//     if (argc <= 2){
//         throw std::invalid_argument("Invalid parameters.");
//     }

//     std::string path(argv[1]);
//     for (const auto & entry : std::filesystem::directory_iterator(path))
//         files.push_back(entry.path());   

//     std::string markup_path(argv[2]);
//     for (const auto& entry: std::filesystem::directory_iterator(markup_path))
//         markup_files.push_back(entry.path());
        
//     std::sort(files.begin(), files.end());
//     std::sort(markup_files.begin(), markup_files.end());


//     auto t_start = std::chrono::high_resolution_clock::now();
//     for (int i = 0; i < files.size(); ++i){
//         Detector detector;
//         auto work_start = std::chrono::high_resolution_clock::now();
//         std::vector<cv::Rect> preds = detector.detect(files[i]);
//         auto work_end = std::chrono::high_resolution_clock::now();
//         working_time += std::chrono::duration<double, std::milli>(work_end-work_start).count() * 0.001;

//         std::vector<cv::Rect> ground_truth = get_markup(&markup_files[i][0]);

//         std::tuple<double, double, double> results = count_metrics(preds, ground_truth);
//         tp += std::get<0>(results);
//         fp += std::get<1>(results);
//         fn += std::get<2>(results);

//     }   
//     auto t_end = std::chrono::high_resolution_clock::now();
//     recall = tp/(tp+fn);
//     precision = tp/(tp+fp);
//     std::cout << "TP: " << tp << "\n" << "FP: " << fp << "\n" << "FN: " << fn << "\n" << "Precision: " << precision << "\n" << 
//     "Recall: " << recall << "\n" << "Time elapsed: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() * 0.001 << "\n" << "Average time for single image: "<< working_time / 218 << "\n";
// }


int main() {
    cv::Mat A = cv::imread("/home/sfleur/barcode_detection/barcode_detection/photo_2023-10-01_15-47-52.jpg");
    cv::Mat B;

    blur(A, B, 15);

    cv::imwrite("/home/sfleur/barcode_detection/barcode_detection/1.jpg", B);
}