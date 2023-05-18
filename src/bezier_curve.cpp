#include "bezier_curve.h"

namespace poca_opencv {
    void GenerateBezierControlPoints(const cv::Point &prev, const cv::Point &mid,
                                     const cv::Point &next, cv::Point &c1, cv::Point &c2,
                                     double curvity) {
        cv::Point v01 = mid - prev;
        cv::Point v12 = next - mid;
        double d01 = v01.ddot(v01);
        double d12 = v12.ddot(v12);

        double fa = curvity * d01 / (d01 + d12);
        double fb = curvity * d12 / (d01 + d12);

        c1 = mid - fa * (next - prev);
        c2 = mid + fb * (next - prev);
    }

    void AddBezierCurve(std::vector<cv::Point> &src, const cv::Point &p0,
                        const cv::Point &p1, const cv::Point &c01, const cv::Point &c10) {
        const float delta = 0.1f;
        for (float s = 0.0f; s < (1.0f + 0.00001f); s += delta) {
            float f0 = pow(1 - s, 3);
            float f1 = pow(1 - s, 2) * s * 3;
            float f2 = pow(s, 2) * (1 - s) * 3;
            float f3 = pow(s, 3);

            cv::Point cur = p0 * f0 + c01 * f1 + c10 * f2 + p1 * f3;
            src.push_back(cur);
        }
    }

    std::vector<cv::Point> GenerateBezierCurve(const std::vector<cv::Point> &src) {
        std::vector<cv::Point> ret;
        if (src.size() < 2) {
            return ret;
        }
        std::vector<cv::Point> control_points(src.size() * 2 - 2);
        cv::Point tmp1 = src[0] - (src[1] - src[0]) / 5;
        cv::Point tmp2;
        GenerateBezierControlPoints(tmp1, src[0], src[1], tmp2, control_points[0], 0.5);
        for (size_t i = 1; i + 1 < src.size(); ++i) {
            GenerateBezierControlPoints(src[i - 1], src[i], src[i + 1],
                                        control_points[i * 2 - 1], control_points[i * 2],
                                        0.5);
        }
        tmp1 = *src.rbegin() - (*(src.rbegin() + 1) - *src.rbegin()) / 5;
        GenerateBezierControlPoints(tmp1, *src.rbegin(), *(src.rbegin() + 1), tmp2,
                                    control_points[src.size() * 2 - 3], 0.5);
        for (size_t i = 0; i + 1 < src.size(); ++i) {
            AddBezierCurve(ret, src[i], src[i + 1], control_points[i * 2],
                           control_points[i * 2 + 1]);
        }
        return ret;
    }
}  // namespace poca_opencv