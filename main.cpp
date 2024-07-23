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
#include "pugixml.hpp"


// struct xml_string_writer: pugi::xml_writer{
//     std::string result;

//     virtual void write(const void* data, size_t size)
//     {
//         result.push_back(static_cast<const char*>(data));
//     }
// };

std::vector<cv::Rect> get_markup(const char* filename){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);
    std::vector<cv::Rect> rects;
    for (pugi::xml_node x = doc.child("Result").child("Pages").child("Page").child("Barcodes").child("Barcode"); x; x = x.next_sibling("Barcode")){
        std::vector<cv::Point> points;
        for (pugi::xml_node point = x.child("Polygon").child("Points").child("Point"); point; point = point.next_sibling("Point")){\
            points.push_back(cv::Point(point.attribute("X").as_int(), point.attribute("Y").as_int()));
            // std::cout << point.attribute("X").value() << " " << point.attribute("Y").value() << "\n";
        }
        rects.push_back(cv::boundingRect(points));
        }
 
    return rects;
}

double iou(const cv::Rect& rec1, const cv::Rect& rec2){
    cv::Rect intersection = rec1 & rec2;
    double intersection_area = intersection.area();
    double union_area = rec1.area() + rec2.area() - intersection.area();
    
    if (union_area == 0)
        return 0;

    return intersection_area / union_area;
}

std::tuple<double, double> count_metrics(const std::vector<cv::Rect>& predictions, const std::vector<cv::Rect>& ground_truth){
    if (predictions.size() == 0)
        return std::tuple<double, double>(0, ground_truth.size());

    int TP = 0, FN = 0;
    std::vector<bool> flags(predictions.size(), false);
    std::vector<double> values(predictions.size(), 0);
    bool found = false;
    for (int i = 0; i < ground_truth.size(); ++i){
        for (int j = 0; j < predictions.size(); ++j){
            values[j] = iou(predictions[j], ground_truth[i]);
            if (flags[j]){
                values[j] = -1;
            }
        }

        int max_ind = std::distance(values.begin(), std::max_element(values.begin(), values.end()));
        // std::cout << *std::max_element(values.begin(), values.end()) << "\n" << max_ind;
        if (values[max_ind] > 0.5){
            flags[max_ind] = true;
            TP += 1;
        }
        else{
            FN += 1;
        }
    }

    return std::tuple<double, double>(TP, FN);
}
int main(int argc, char* argv[]){
    std::vector<std::string> files; 
    std::vector<std::string> markup_files; 
    double tp = 0, fn = 0, recall = 0, working_time = 0;


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
        // std::string name = argv[2] + std::string("/") + std::to_string(i) + ".jpg";
        Detector detector;
        auto work_start = std::chrono::high_resolution_clock::now();
        std::vector<cv::Rect> preds = detector.detect(files[i]);
        auto work_end = std::chrono::high_resolution_clock::now();
        working_time += std::chrono::duration<double, std::milli>(work_end-work_start).count() * 0.001;

        std::vector<cv::Rect> ground_truth = get_markup(&markup_files[i][0]);

        // std::cout << files[i] << " " << markup_files[i] << "\n";
        std::tuple<double, double> results = count_metrics(preds, ground_truth);
        tp += std::get<0>(results);
        fn += std::get<1>(results);
    }   
    auto t_end = std::chrono::high_resolution_clock::now();
    recall = tp/(tp+fn);

    std::cout << "TP: " << tp << "\n" << "FN: " << fn << "\n" << 
    "Recall: " << recall << "\n" ;
    // << "Time elapsed: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() * 0.001 << "\n" << "Average time for single image: "<< working_time / files.size() << "\n";
}