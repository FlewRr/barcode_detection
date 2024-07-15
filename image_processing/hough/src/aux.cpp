#include "aux.h"

void polar_to_cartesian(double rho, double theta, cv::Point& p1, cv::Point& p2){
    int x0 = rho * std::cos(theta);
    int y0 = rho * std::sin(theta);

    p1.x = cvRound(x0 + 1000 * (-std::sin(theta)));
    p1.y = cvRound(y0 + 1000 * (std::cos(theta)));

    p2.x = cvRound(x0 - 1000 * (-std::sin(theta)));
    p2.y = cvRound(y0 - 1000 * (std::cos(theta)));
}