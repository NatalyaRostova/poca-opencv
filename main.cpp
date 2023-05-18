#include <chrono>
#include <iostream>

#include "bezier_curve.h"

int main() {
    auto start = std::chrono::system_clock::now();
    std::vector<cv::Point> src;
    src.push_back(cv::Point(100, 100));
    src.push_back(cv::Point(100, 100));
    src.push_back(cv::Point(200, 100));
    src.push_back(cv::Point(300, 340));
    auto ret = poca_opencv::GenerateBezierCurve(src);
    cv::Mat img = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    for (size_t i = 1; i < ret.size(); ++i) {
        cv::line(img, ret[i - 1], ret[i], cv::Scalar(230, 230, 0), 2);
    }
    for (size_t i = 0; i < src.size(); ++i) {
        cv::circle(img, src[i], 2, cv::Scalar(230, 230, 255), 2);
    }
    auto end = std::chrono::system_clock::now();
    std::cout << "use: " << std::chrono::duration<double>(end - start).count() / 1000.0
              << "ms\n";
    cv::imwrite("output.jpg", img);
    return 0;
}