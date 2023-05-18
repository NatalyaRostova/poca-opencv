#ifndef _POCA_BAZIER_CURVE_H_
#define _POCA_BAZIER_CURVE_H_

#include <opencv2/opencv.hpp>
#include <vector>

namespace poca_opencv {
    void GenerateBezierControlPoints(const cv::Point &prev, const cv::Point &mid,
                                     const cv::Point &next, cv::Point &c1, cv::Point &c2,
                                     double curvity);

    std::vector<cv::Point> GenerateBezierCurve(const std::vector<cv::Point> &src);
}  // namespace poca_opencv

#endif