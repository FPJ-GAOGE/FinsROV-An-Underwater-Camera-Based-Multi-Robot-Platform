//
// Created by admin on 2023/9/19.
//
#include <Kalman_Filter.h>
#include <vector>

// 更新滤波器，输入测量值，输出滤波后的估计值
double KalmanFilter::update(double measurement)
{
    // 预测步骤
    double pred = est;
    double P_pred = P + Q;

    // 计算卡尔曼增益
    double K = P_pred / (P_pred + R);

    // 更新步骤
    est = pred + K * (measurement - pred);
    P = (1 - K) * P_pred;

    return est;
}   