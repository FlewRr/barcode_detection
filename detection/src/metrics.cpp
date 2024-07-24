#include <detection.h>

double iou(const cv::Rect& rec1, const cv::Rect& rec2){
    cv::Rect intersection = rec1 & rec2;
    double intersection_area = intersection.area();
    double union_area = rec1.area() + rec2.area() - intersection.area();
    
    if (union_area == 0)
        return 0;

    return intersection_area / union_area;
}

std::tuple<double, double, double> count_metrics(const std::vector<cv::Rect>& predictions, const std::vector<cv::Rect>& ground_truth){
    if (predictions.size() == 0)
        return std::tuple<double, double, double>(0, ground_truth.size(), 0);

    int TP = 0, FP = 0, FN = 0;
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
        if (values[max_ind] > 0.5){
            flags[max_ind] = true;
            TP += 1;
        }
        else{
            FP += 1;
        }
    }

    for (const bool& flag: flags){
        if (!flag)
            FN += 1;
    }

    return std::tuple<double, double, double>(TP, FP, FN);
}