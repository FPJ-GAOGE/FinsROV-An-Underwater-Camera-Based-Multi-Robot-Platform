//
// Created by admin on 2023/10/30.
//

#ifndef CONTROL_FRAME_MAIN_PWM_H
#define CONTROL_FRAME_MAIN_PWM_H

#include "Usermain.h"
#include "Extension.h"
#include "PID.h"
#include <array>
#include <unordered_map>
#include <functional>

using namespace std;

class Propeller_I2C;

enum Motion_State{
    STOP,
    FLOAT,
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    CLOCKWISE,
    ANTICLOCKWISE,
    MOTION_STATE_NUM
};

typedef struct Propeller_Command{
    uint8_t len;
    const char* str;
    void (Propeller_I2C::*handler)();
}Propeller_Command_t;


struct Propeller_Parameter_t{
    std::array<int8_t, 8> Sign;
    std::array<uint8_t, 4> InID;
    std::array<uint8_t, 4> OutID;
    int32_t InitPWM;
    std::array<int32_t, 8> Compensation; // 死区补偿值
    std::array<int32_t, 4> FloatPWM;
    std::array<int32_t, 4> FrontPWM;
    std::array<int32_t, 4> BackPWM;
    std::array<int32_t, 4> LeftPWM;
    std::array<int32_t, 4> RightPWM;
    std::array<int32_t, 4> ClockwisePWM;
    std::array<int32_t, 4> AnticlockwisePWM;
    std::array<int32_t, 4> StopPWM;
    PID_Regulator_t DepthPID_P;
    PID_Regulator_t PitchPID_P;
    PID_Regulator_t RollPID_P;
    PID_Regulator_t YawPID_P;
    PID_Regulator_t YawInPID_P;
    PID_Regulator_t YawOutPID_P;
    PID_Regulator_t RollInPID_P;
    PID_Regulator_t RollOutPID_P;
    PID_Regulator_t PitchInPID_P;
    PID_Regulator_t PitchOutPID_P;

    Propeller_Parameter_t() = default;
};

typedef struct Propeller_PWM_Component{
    float Depth;
    float Roll,Pitch,Yaw;
    float Vx,Vy,Vz;
    float Roll_angle, Pitch_angle, Yaw_angle;
} Propeller_PWM_Component_t;


class Propeller_I2C: public Device
{
private:
    //uint8_t RxBuffer[SERIAL_LENGTH_MAX];
    int32_t current_PWM[PROPELLER_NUM]; // PWM值，1500为不转，1500-2000正转，1000-1500反转，离1500越远转速越快
    //int32_t data_receive[5];
    float Target_depth;
    float Target_roll = 0.0;
    float Target_roll_v = 0.0;
    float Target_pitch = 0.0;
    float Target_pitch_v = 0.0;
    float Target_yaw = 0.0;
    float Target_yaw_v = 0.0;
    float yaw_diff;
    float yaw_v_diff;
    float pitch_diff;
    float pitch_v_diff;
    float roll_diff;
    float roll_v_diff;
    float Target_speed[3];
    bool flag_float;
    bool flag_angle;
    bool flag_range;
    bool flag_roll;
    bool flag_PWM_output;
    Motion_State motion_state;
    int roll_state;
    int roll_state_total;
    PID DepthPID, RollPID, PitchPID;
    PID VxPID, VyPID, YawPID;
    PID RollAnglePID, PitchAnglePID, YawAnglePID, YawInPID, YawOutPID;
    PID RollInPID, RollOutPID;
    PID PitchInPID, PitchOutPID;

    void float_ctrl();
    void speed_ctrl();
    void angle_ctrl();
    float deg2rad(float);
    float rad2deg(float);
    float normalize_angle(float euler_angle);

    void vertical_PWM_allocation();
    void horizontal_PWM_allocation();

    unordered_map<char, Motion_State> msg_state_map;
    std::array<std::array<int32_t, 4>, MOTION_STATE_NUM> state_PWM_map;
    Propeller_PWM_Component_t PWM_component;
    Propeller_Parameter_t Parameter;
    static Propeller_Command_t propeller_command[];

public:
    void Init();
    void Handle();
    void Receive();
    
    void command_test();
    void command_set_angle_closeloop();
    void command_set_angle_value();
};


/*extern void Anglectrl_servo();

extern void Speedctrl_propeller_init();

extern void Speedctrl_propeller();

extern void Anglectrl_servo_init();
*/

#endif //CONTROL_FRAME_MAIN_PWM_H
