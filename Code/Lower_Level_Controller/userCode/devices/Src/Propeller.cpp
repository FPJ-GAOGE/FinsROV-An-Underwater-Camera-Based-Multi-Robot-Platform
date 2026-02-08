//
// Created by admin on 2023/10/30.
//
#include "Propeller.h"
#include "Sensor.h"
#include "IMU.h"
#include <algorithm>
#include <cmath>

// V33
std::array<int8_t, 8> Sign = {1, -1, 1, 1, -1, -1, 1, -1}; // Mark propeller direction: Clockwise = 1, Counter-Clockwise = -1.; the index corresponds to the propeller ID. // 推进器正反桨，正1反-1，序号为推进器序号
std::array<uint8_t, 4> InID = {1, 2, 6, 5};                // V33-1,2 Channel indices on the expansion board for the four internal thrusters: front-left, rear-left, front-right, rear-right. //内部的4个推进器接到扩展板上的序号，左前-左后-右前-右后
std::array<uint8_t, 4> OutID = {0, 3, 7, 4};               // V33-1,2 Channel indices on the expansion board for the four external thrusters: front-left, rear-left, front-right, rear-right. //外部的4个推进器接到扩展板上的序号，左前-左后-右前-右后
int32_t InitPWM = 1610; // Initial PWM value for thruster initialization. // 推进器初始化的PWM（V33-0,1）
//int32_t InitPWM = 1540; // Initial PWM value for thruster initialization. //推进器初始化的PWM（V33-2）
std::array<int32_t, 8> Compensation = {50, 50, 50, 50, 50, 50, 50, 50}; // Dead-zone compensation value. // 死区补偿值
// Vertical thrusters.
// 垂直推进器
std::array<int32_t, 4> FloatPWM = {
    InitPWM,
    InitPWM - Sign[InID[1]] * 100,
    InitPWM,
    InitPWM - Sign[InID[3]] * 90
};
// Horizontal thrusters.
// 水平推进器
uint8_t longitudinal_speed = 80;
uint8_t lateral_speed = 80;
uint8_t rotate_speed = 40;
std::array<int32_t, 4> StopPWM = {InitPWM, InitPWM, InitPWM, InitPWM};
std::array<int32_t, 4> FrontPWM = {
    InitPWM - Sign[OutID[0]] * longitudinal_speed,
    InitPWM - Sign[OutID[1]] * longitudinal_speed,
    InitPWM - Sign[OutID[2]] * longitudinal_speed,
    InitPWM - Sign[OutID[3]] * longitudinal_speed
};
std::array<int32_t, 4> BackPWM = {
    InitPWM + Sign[OutID[0]] * longitudinal_speed,
    InitPWM + Sign[OutID[1]] * longitudinal_speed,
    InitPWM + Sign[OutID[2]] * longitudinal_speed,
    InitPWM + Sign[OutID[3]] * longitudinal_speed
};
std::array<int32_t, 4> LeftPWM = {
    InitPWM + Sign[OutID[0]] * lateral_speed,
    InitPWM - Sign[OutID[1]] * lateral_speed,
    InitPWM - Sign[OutID[2]] * lateral_speed,
    InitPWM + Sign[OutID[3]] * lateral_speed
};
std::array<int32_t, 4> RightPWM = {
    InitPWM - Sign[OutID[0]] * lateral_speed,
    InitPWM + Sign[OutID[1]] * lateral_speed,
    InitPWM + Sign[OutID[2]] * lateral_speed,
    InitPWM - Sign[OutID[3]] * lateral_speed
};
std::array<int32_t, 4> ClockwisePWM = {
    InitPWM - Sign[OutID[0]] * rotate_speed,
    InitPWM - Sign[OutID[1]] * rotate_speed,
    InitPWM + Sign[OutID[2]] * rotate_speed,
    InitPWM + Sign[OutID[3]] * rotate_speed
};
std::array<int32_t, 4> AntiClockwisePWM = {
    InitPWM + Sign[OutID[0]] * rotate_speed,
    InitPWM + Sign[OutID[1]] * rotate_speed,
    InitPWM - Sign[OutID[2]] * rotate_speed,
    InitPWM - Sign[OutID[3]] * rotate_speed
};
// PID
PID_Regulator_t DepthPID(10, 0.02, 10, 100, 50, 50, 200);
PID_Regulator_t PitchPID(10, 0.02, 50, 50, 25, 25, 100);
PID_Regulator_t RollPID(1.8, 0.02, 100, 50, 25, 25, 100);
PID_Regulator_t YawPID(12, 0.06, 300, 10, 100, 50, 300);
PID_Regulator_t YawInPID(5, 0, 0, 200, 100, 100, 400);
PID_Regulator_t YawOutPID(2, 0.01, 2, 10, 5, 5, 20);
PID_Regulator_t RollInPID(8, 0, 0, 100, 50, 50, 200);
PID_Regulator_t RollOutPID(0.5, 0.002, 1, 5, 2.5, 2.5, 10);
PID_Regulator_t PitchInPID(8, 0, 0, 100, 50, 50, 200);
PID_Regulator_t PitchOutPID(1, 0.005, 1, 5, 2.5, 2.5, 10);
// IMU
// PID_Regulator_t PitchInPID(2, 0, 40, 100, 50, 50, 200);
// PID_Regulator_t PitchOutPID(7, 0.5, 100, 5, 2.5, 2.5, 10);

Propeller_Parameter_t Parameter_V33 = {
    Sign, InID, OutID, InitPWM,
    Compensation,
    FloatPWM, FrontPWM, BackPWM, LeftPWM, RightPWM,
    ClockwisePWM, AntiClockwisePWM, StopPWM,
    DepthPID, PitchPID, RollPID, YawPID,
    YawInPID, YawOutPID, RollInPID, RollOutPID, PitchInPID, PitchOutPID
};

Propeller_Command_t Propeller_I2C::propeller_command[] = {
    {3, "ACL", &Propeller_I2C::command_set_angle_closeloop},
    {3, "ANG", &Propeller_I2C::command_set_angle_value},
    {3, "TES", &Propeller_I2C::command_test}
};

void Propeller_I2C::Init()
{
    Parameter = Parameter_V33;

    DepthPID.PIDInfo = Parameter.DepthPID_P;
    PitchPID.PIDInfo = Parameter.PitchPID_P;
    RollPID.PIDInfo = Parameter.RollPID_P;
    YawPID.PIDInfo = Parameter.YawPID_P;

    PitchAnglePID.PIDInfo = Parameter.PitchPID_P;
    RollAnglePID.PIDInfo = Parameter.RollPID_P;
    YawAnglePID.PIDInfo = Parameter.YawPID_P;

    YawInPID.PIDInfo = Parameter.YawInPID_P;
    YawOutPID.PIDInfo = Parameter.YawOutPID_P;

    RollInPID.PIDInfo = Parameter.RollInPID_P;
    RollOutPID.PIDInfo = Parameter.RollOutPID_P;

    PitchInPID.PIDInfo = Parameter.PitchInPID_P;
    PitchOutPID.PIDInfo = Parameter.PitchOutPID_P;

    Target_speed[0] = 0;
    Target_speed[1] = 0;
    flag_float = false;
    flag_roll = false;
    flag_PWM_output = false;
    flag_angle = false;
    roll_state = 0;
    roll_state_total = 1;
    motion_state = STOP;

    msg_state_map['W'] = FRONT;
    msg_state_map['S'] = BACK;
    msg_state_map['A'] = LEFT;
    msg_state_map['D'] = RIGHT;
    msg_state_map['Z'] = FLOAT;
    msg_state_map['E'] = CLOCKWISE;
    msg_state_map['Q'] = ANTICLOCKWISE;

    state_PWM_map[STOP]          = Parameter.StopPWM;
    state_PWM_map[FRONT]         = Parameter.FrontPWM;
    state_PWM_map[BACK]          = Parameter.BackPWM;
    state_PWM_map[LEFT]          = Parameter.LeftPWM;
    state_PWM_map[RIGHT]         = Parameter.RightPWM;
    state_PWM_map[FLOAT]         = Parameter.StopPWM;
    state_PWM_map[CLOCKWISE]     = Parameter.ClockwisePWM;
    state_PWM_map[ANTICLOCKWISE] = Parameter.AnticlockwisePWM;

    TCA_SetChannel(4);  // Expand a single I2C bus into eight channels. // 1路 I2C 扩展为 8路
    HAL_Delay(5);
    PCA_Write(PCA9685_MODE1, 0x0);
    PCA_Setfreq(50); // Hz
    for (int i = 0; i < PROPELLER_NUM; ++i)
    {
        current_PWM[i] = Parameter.InitPWM;
				
				// ------ TODO: `i` denotes the thruster channel index on the expansion board. Update this mapping according to the wiring; currently set to channels 0–7.
        //------TODO：i为推进器在扩展板上的接口编号，根据接线修改，目前为0-7号
        PCA_Setpwm(i, 0, floor(current_PWM[i] * 4096 / 20000 + 0.5f));
    }

    HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
};

// Configure the PWM parameters according to UART commands.
// 根据串口指令设置PWM参数
void Propeller_I2C::Receive()
{
    int32_t data_receive[8];
    uint8_t command_num = sizeof(propeller_command) / sizeof(Propeller_Command_t);
    for (uint8_t i=0; i<command_num; i++)
    {
        if (strncmp((char *)RxBuffer, propeller_command[i].str, propeller_command[i].len) == 0)
        {
            (this->*(propeller_command[i].handler))();
        }
    }
    if (flag_float)
    {
			// Update the PWM outputs of the four outer-ring motors for front/back/left/right motion (open-loop motion is possible when yaw-angle control is disabled).
        // 外圈四个电机更新为前后左右运动的PWM(在没有yaw角控制的情况下可开环运动)
        if (strncmp((char *)RxBuffer, "DN", 2) == 0)
        {
            Target_depth += 1;
            return;
        }

        else if (strncmp((char *)RxBuffer, "UP", 2) == 0)
        {
            Target_depth -= 1;
            return;
        }

        else if (msg_state_map.count(RxBuffer[0]))
        {
            motion_state = msg_state_map[RxBuffer[0]];
            // if(flag_angle){
            //     for (int i = 0; i < 4; ++i)
            //     {
            //         current_PWM[Parameter.OutID[i]] = current_PWM[Parameter.OutID[i]] + state_PWM_map[motion_state][i] - Parameter.InitPWM;
            //     }
            // }
            // else{
            //     for (int i = 0; i < 4; ++i)
            //     {
            //         current_PWM[Parameter.OutID[i]] = state_PWM_map[motion_state][i];
            //     }
            // }
        }

				// Disable PID control and reset the PWM outputs to their initial values.
        // 关闭PID控制，更新为初始的PWM
        else if (strncmp((char *)RxBuffer, "OFF", 3) == 0)
        {
            flag_float = false;
            flag_angle = false;
            for (int i = 0; i < 8; ++i)
            {
                current_PWM[i] = Parameter.InitPWM;
            }
            Target_depth = 30;
            current_PWM[Parameter.OutID[0]] = current_PWM[Parameter.OutID[1]] = current_PWM[Parameter.OutID[2]] = current_PWM[Parameter.OutID[3]] = Parameter.InitPWM;
        }

        // // 外圈四个电机更新为给定的PWM，更新深度
        // if (strncmp((char *)RxBuffer, "PRO:", 4) == 0)
        // {
        //     char *data_str = (char *)RxBuffer + 4;
        //     char *token = strtok(data_str, ",");
        //     int i = 0;
        //     while (token != NULL && i < 5)
        //     {
        //         data_receive[i] = atoi(token);
        //         token = strtok(NULL, ",");
        //         i++;
        //     }
        //     for (int i = 0; i < 4; ++i)
        //     {
        //         current_PWM[Parameter.OutID[i]] = data_receive[i];
        //     }
        //     Target_depth = data_receive[4] / 10.0;
        // }

        // // 更新速度与角速度
        // if (strncmp((char *)RxBuffer, "VEL:", 4) == 0)
        // {
        //     char *data_str = (char *)RxBuffer + 4;
        //     char *token = strtok(data_str, ",");
        //     int i = 0;
        //     while (token != NULL && i < 3)
        //     {
        //         data_receive[i] = atoi(token);
        //         token = strtok(NULL, ",");
        //         i++;
        //     }
        //     Target_speed[0] = data_receive[0];
        //     Target_speed[1] = data_receive[1];
        //     Target_yaw = data_receive[2] * 3.14 / 180;
        // }

        // Update Yaw. //更新Yaw角度
        else if (strncmp((char *)RxBuffer, "RPY:", 4) == 0)
        {
            if (strncmp((char *)RxBuffer, "RPY:ON", 6) == 0){
                flag_angle = true;
            }
            else if (strncmp((char *)RxBuffer, "RPY:OFF", 7) == 0){
                flag_angle = false;
                current_PWM[Parameter.OutID[0]] = current_PWM[Parameter.OutID[1]] = current_PWM[Parameter.OutID[2]] = current_PWM[Parameter.OutID[3]] = Parameter.InitPWM;
            }
        //     else {
        //         char *data_str = (char *)RxBuffer + 4;
        //         char *token = strtok(data_str, ",");
        //         int i = 0;
        //         while (token != NULL && i < 3)
        //         {
        //             data_receive[i] = atoi(token);
        //             token = strtok(NULL, ",");
        //             i++;
        //         }
        //         Target_roll = data_receive[0] * 3.14 / 180;
        //         Target_pitch = data_receive[1] * 3.14 / 180;
        //         Target_yaw = data_receive[2] * 3.14 / 180;
        //     }
        }

        // // 当开启角度控制时先默认输出角度数据，可以通过串口输入改为输出PWM数据
        // if(flag_angle){
        //     if (strncmp((char *)RxBuffer, "PWM:BEG", 7) == 0){
        //         flag_PWM_output = true;
        //     }
        //     else if (strncmp((char *)RxBuffer, "PWM:END", 7) == 0){
        //         flag_PWM_output = false;
        //     }
        // }

        // Update Depth. //更新深度
        else if (strncmp((char *)RxBuffer, "H:", 2) == 0)
        {
            char *data_str = (char *)RxBuffer + 2;
            Target_depth = atoi(data_str) / 10.0;
        }
    }

    else
    {
				// Enable PID control and initialize the PWM outputs to their default values.
        // 开启PID控制，更新为初始PWM
        if (strncmp((char *)RxBuffer, "ON", 2) == 0)
        {
            flag_float = true;
            for (int i = 0; i < 8; ++i)
            {
                current_PWM[i] = Parameter.InitPWM;
            }
            Target_depth = (PressureSensor::pressure_sensor.data_depth - 1.0 > 30.0) ? (PressureSensor::pressure_sensor.data_depth - 1.0) : 30.0;
        }
    }
}

void Propeller_I2C::Handle()
{

    TCA_SetChannel(4);
    // HAL_Delay(5);
    vertical_PWM_allocation();
    horizontal_PWM_allocation();
    
    for (int i = 0; i < PROPELLER_NUM; ++i)
    {
        // int32_t pwm = Parameter.InitPWM;
        int32_t pwm = current_PWM[i];
        pwm = clamp(pwm, 1000, 2000);
        int32_t duty_count = (pwm * 4096 + 10000) / 20000;
        PCA_Setpwm(i, 0, duty_count);
    }
}

void Propeller_I2C::float_ctrl()
{
        PWM_component.Depth = DepthPID.PIDCalc(Target_depth, PressureSensor::pressure_sensor.data_depth);

        // pid for roll and pitch
        // `ps_state` sets the frequency ratio between the outer and inner control loops to 3:1. //ps_state控制双环频率比为3:1
        if (PressureSensor::pressure_sensor.ps_state == PS_HANDLE_STATE::CALCULATE)
        {
            // roll_diff = PressureSensor::pressure_sensor.data_roll;
            // roll_diff = IMU::imu.attitude.roll;
            // Target_roll_v = RollOutPID.PIDCalc(Target_roll, IMU::imu.attitude.roll);
            Target_roll_v = RollOutPID.PIDCalc(Target_roll, PressureSensor::pressure_sensor.data_roll);
            // pitch_diff = PressureSensor::pressure_sensor.data_pitch;
            // pitch_diff = IMU::imu.attitude.pitch;
            // Target_pitch_v = PitchOutPID.PIDCalc(Target_pitch, IMU::imu.attitude.pitch);
            Target_pitch_v = PitchOutPID.PIDCalc(Target_pitch, PressureSensor::pressure_sensor.data_pitch);
        }
        // PWM_component.Roll = RollInPID.PIDCalc(Target_roll_v, IMU::imu.attitude.roll_v); // IMU
        PWM_component.Roll = RollInPID.PIDCalc(Target_roll_v, IMU::imu.attitude.neg_roll_v); 
        PWM_component.Pitch = PitchInPID.PIDCalc(Target_pitch_v, IMU::imu.attitude.pitch_v);
}

void Propeller_I2C::speed_ctrl()
{
}

// Dual-loop PID control for yaw angle.
// 双环pid控制Yaw角
void Propeller_I2C::angle_ctrl()
{
    if (PressureSensor::pressure_sensor.ps_state == PS_HANDLE_STATE::CALCULATE)
    {
        yaw_diff = normalize_angle(IMU::imu.attitude.yaw - Target_yaw);
        Target_yaw_v = YawOutPID.PIDCalc(0.0, yaw_diff);
    }
    PWM_component.Yaw = YawInPID.PIDCalc(Target_yaw_v, IMU::imu.attitude.yaw_v);
}

float Propeller_I2C::deg2rad(float degree){
    return degree * PI / 180;
}

float Propeller_I2C::rad2deg(float rad){
    return rad * 180 / PI;
}

// PWM allocation for the internal (vertical-axis) thrusters.
// 垂直方向（内）推进器PWM分配
void Propeller_I2C::vertical_PWM_allocation()
{
    if(flag_float){
        float_ctrl();

        constexpr int8_t factors[4][3] = {
        {-1, -1, -1},  // Motor0
        {-1, -1,  1},  // Motor1
        {-1,  1, -1},  // Motor2
        {-1,  1,  1}   // Motor3
        };

        float depth = PWM_component.Depth;
        float pitch = PWM_component.Pitch;
        float roll = PWM_component.Roll;

        for(int i=0; i<4; i++)
        {
            uint8_t idx = Parameter.InID[i];
            int8_t sign = Parameter.Sign[idx];
            int32_t base = Parameter.FloatPWM[i];
            int32_t comp = Parameter.Compensation[idx];
            int32_t pwm = base - sign * (depth * factors[i][0] + roll * factors[i][1] + pitch * factors[i][2]);
            if (pwm > Parameter.InitPWM) pwm += comp;
            else if(pwm < Parameter.InitPWM) pwm -= comp; // Compensate for the motor dead zone. // 补偿电机死区
            current_PWM[idx] = pwm;
        }
    }
    else{
        for(int i=0; i<PROPELLER_NUM; i++){
            //current_PWM[i] = Parameter.InitPWM;
        }
    }
}

// PWM allocation for the horizontal-axis thrusters.
// 水平方向推进器PWM分配
void Propeller_I2C::horizontal_PWM_allocation()
{
    float yaw;
	  if(flag_float){
			if(flag_angle){
        angle_ctrl();
        yaw = PWM_component.Yaw;
			}
			else{
					yaw = 0;
			}
			for (int i=0; i<4; i++)
			{
					uint8_t idx = Parameter.OutID[i];
					int32_t sign = Parameter.Sign[idx];
					int32_t base = state_PWM_map[motion_state][i];
					int32_t comp = Parameter.Compensation[idx];
					int32_t pwm = base + ((i<2) ? sign : - sign) * yaw;
					if (pwm > Parameter.InitPWM) pwm += comp;
					else if(pwm < Parameter.InitPWM) pwm -= comp; // Compensate for the motor dead zone. // 补偿电机死区
					current_PWM[idx] = pwm;
			}
		}
}


float Propeller_I2C::normalize_angle(float angle)
{
    angle = std::fmod(angle + PI, 2 * PI);
    if (angle < 0) angle += 2 * PI;
    return angle - PI;
}

void Propeller_I2C::command_set_angle_value(){
    if (flag_angle && flag_float)
    {
        char* data_str = (char *)RxBuffer + 4;
        Target_yaw = deg2rad(atoi(data_str));
    }
}

void Propeller_I2C::command_set_angle_closeloop(){
    if (flag_float)
    {
        char* data_str = (char *)RxBuffer + 4;
        if (strncmp(data_str, "ON", 2) == 0)
        {
            flag_angle = true;
            Target_yaw = IMU::imu.attitude.yaw;
        }
        else if (strncmp(data_str, "OF", 2) == 0)
        {
            flag_angle = false;
        }
    }
}

void Propeller_I2C::command_test(){
    if (!flag_float && !flag_angle)
    {
        char* data_str = (char *)RxBuffer + 4;
        char *token = strtok(data_str, ",");
        int i = 0;
        while (token != NULL && i < 8)
        {
            current_PWM[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }
    }
}