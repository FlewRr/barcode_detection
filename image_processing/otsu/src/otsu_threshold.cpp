#include "otsu_threshold.h"
#include <iostream>
#include <cmath>

int otsu_method(cv::Mat img){
    double histogram[256];
    int total_pixels = img.total();

   for (int i = 0; i < img.rows; ++i){
        for (int j = 0; j < img.cols; ++j){
            histogram[img.at<uchar>(j, i)] += 1;
        }
    }

    for (int i = 0; i < 256; ++i)
        histogram[i] /= total_pixels;

    double probs[256], mean[256];
    double max_between, between[256];
    int threshold;

    for (int i = 0; i < 256; ++i){
        probs[i] = 0.0;
        mean[i] = 0.0;
        between[i] = 0.0;
    }

    probs[0] = histogram[0];

    for (int i = 1; i < 256; ++i){
        probs[i] = probs[i-1] + histogram[i];
        mean[i] = mean[i-1] + i * histogram[i];
    }

    threshold = 0;
    max_between = 0.0;

    for (int i = 0; i < 255; ++i){
        if (probs[i] != 0.0 && probs[i] != 1.0)
            between[i] = std::pow(mean[255] * probs[i] - mean[i], 2) / (probs[i] * (1.0 - probs[i]));
        else
            between[i] = 0.0;

        if(between[i] > max_between){
            max_between = between[i];
            threshold = i;
        }
    }

    return threshold;
}