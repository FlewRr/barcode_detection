#include <detection.h>
#include "pugixml.hpp"


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