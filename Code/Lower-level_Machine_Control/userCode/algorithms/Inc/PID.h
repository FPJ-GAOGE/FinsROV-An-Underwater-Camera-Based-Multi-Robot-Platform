//
// Created by LEGION on 2021/10/19.
//

#ifndef RM_FRAME_C_PID_H
#define RM_FRAME_C_PID_H

#include "Usermain.h"

struct PID_Regulator_t {
    float ref;
    float fdb;
    float err[4];
    float errSum;
    float kp;
    float ki;
    float kd;
    float componentKp;
    float componentKi;
    float componentKd;
    float componentKpMax;
    float componentKiMax;
    float componentKdMax;
    float output;
    float outputMax;
    PID_Regulator_t(){};
    PID_Regulator_t(float kp, float ki, float kd, float pM, float iM, float dM, float oM):
        kp(kp), ki(ki), kd(kd), componentKpMax(pM), componentKiMax(iM), componentKdMax(dM), outputMax(oM){};
    PID_Regulator_t(const PID_Regulator_t& OTHER){
        std::memcpy(this, &OTHER, sizeof(PID_Regulator_t));
    }
};


class PID{
public:
    PID_Regulator_t PIDInfo{};
    void Reset(PID_Regulator_t * pidRegulator);
    void Reset();
    float PIDCalc(float target,float feedback);
    float PIDCalc(float target,float feedback,float max);
};

#endif //RM_FRAME_C_PID_H
