//
// Created by admin on 2023/9/19.
//

#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <string>
#include <vector>
//#include <Dense>//包含Eigen矩阵运算库，用于矩阵计算
#include <cmath>
//using Eigen::MatrixXd;

template <typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

class KalmanFilter {
public:
    KalmanFilter(double process_noise, double measurement_noise, double estimation_error, double initial_estimate)
        : Q(process_noise), R(measurement_noise), P(estimation_error), est(initial_estimate) {}

    double update(double measurement);

private:
    double Q;       // 过程噪声方差
    double R;       // 测量噪声方差
    double P;       // 估计误差协方差
    double est;   // 当前状态估计
};

#endif
