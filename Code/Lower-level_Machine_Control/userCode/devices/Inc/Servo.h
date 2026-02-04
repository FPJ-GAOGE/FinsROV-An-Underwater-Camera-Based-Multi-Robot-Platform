//
// Created by admin on 2023/12/5.
//

#ifndef CONTROL_FRAME_MAIN_SERVO_H
#define CONTROL_FRAME_MAIN_SERVO_H

#include "Usermain.h"
#include "Extension.h"
#include "PID.h"
#include <cstdint>

class Servo : public Device
{

public:
    // uint8_t RxBuffer[SERIAL_LENGTH_MAX];
    int32_t data[SERVO_NUM]; // PWM值，500-2500对应0-180度，线性关系
    void data_extract(uint8_t *rx, int32_t *data, int32_t num);

    void Init();
    void Handle();
    void Receive();
    // static Servo servo;
};

class Servo_I2C : public Device
{

public:
    // uint8_t RxBuffer[SERIAL_LENGTH_MAX];
    int32_t ID[SERVO_NUM];   // 舵机编号
    int32_t data[SERVO_NUM]; // PWM值，500-2500对应0-180度，线性关系
    void data_extract(uint8_t *rx, int32_t *data, int32_t num);

    void Init();
    void Handle();
    void Receive();
};

#endif // CONTROL_FRAME_MAIN_SERVO_H
