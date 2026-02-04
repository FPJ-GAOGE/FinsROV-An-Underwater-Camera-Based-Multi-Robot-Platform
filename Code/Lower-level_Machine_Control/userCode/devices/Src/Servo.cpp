//
// Created by admin on 2023/12/5.
//
#include "Servo.h"

int32_t ID_V30[4] = {8, 9, 10, 11}; // 4个舵机接在PWM扩展板的编号，左上-左下-右上-右下
int32_t ID_V31[4] = {8, 9, 10, 11};
int32_t ID_V32[4] = {8, 9, 11, 10};
int32_t ID_V33[4] = {8, 9, 10, 11};
int32_t ID_V40[4] = {8, 9, 10, 11}; // 还需测试

void Servo::Init()
{
    for (int i = 0; i < SERVO_NUM; ++i)
    {
        data[i] = 1500;
    }
    __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, data[3]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, data[0]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, data[2]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, data[1]);
    HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
}

void Servo_I2C::Init()
{
    switch (Robot_Version)
    {
    case V30:
        std::memcpy(ID, ID_V30, sizeof(ID));
        break;
    case V31:
        std::memcpy(ID, ID_V31, sizeof(ID));
        break;
    case V32:
        std::memcpy(ID, ID_V32, sizeof(ID));
        break;
    case V33:
        std::memcpy(ID, ID_V33, sizeof(ID));
        break;
    case V40:
        std::memcpy(ID, ID_V40, sizeof(ID));
        break;
    }
    TCA_SetChannel(4);
    PCA_Write(PCA9685_MODE1, 0x0);
    PCA_Setfreq(50); // Hz
    for (int i = 0; i < SERVO_NUM; ++i)
    {
        data[i] = 1500;
        //------TODO：i+8为舵机在扩展版上的接口编号，根据接线修改，目前为8-11号
        PCA_Setpwm(i + 8, 0, floor(data[i] * 4096 / 20000 + 0.5f));
    }
    HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
}

void Servo::Receive()
{
    data_extract(RxBuffer, data, SERVO_NUM);
    // HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
}

void Servo_I2C::Receive()
{
    data_extract(RxBuffer, data, SERVO_NUM);
    // HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
}

void Servo::Handle()
{
    __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, data[3]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, data[0]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, data[2]);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, data[1]);
}

void Servo_I2C::Handle()
{
    // if(tim_id == 10){
    TCA_SetChannel(4);

    bool flag_range = true;
    for (int i = 0; i < SERVO_NUM; ++i)
    {
        if (data[i] < 500 || data[i] > 2500)
            flag_range = false;
    }
    if (flag_range)
    {
        for (int i = 0; i < SERVO_NUM; ++i)
        {
            PCA_Setpwm(ID[i], 0, floor(data[i] * 4096 / 20000 + 0.5f));
        }
    }

    //}
}

void Servo::data_extract(uint8_t *rx, int32_t *data, int32_t num)
{
    if (strncmp((char *)rx, "MOT:", 4) == 0)
    {

        char *data_str = (char *)rx + 4;
        char *token = strtok(data_str, ",");
        int i = 0;
        while (token != NULL && i < num)
        {
            data[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }
    }
}

void Servo_I2C::data_extract(uint8_t *rx, int32_t *data, int32_t num)
{
    // 示例：假设 PWM 命令格式是 "MOT:1000,2000,1500,1800,1600,1400\n"
    if (strncmp((char *)rx, "MOT:", 4) == 0)
    {
        char *data_str = (char *)rx + 4;
        char *token = strtok(data_str, ",");
        int i = 0;
        while (token != NULL && i < num)
        {
            data[i] = atoi(token);
					  if (i == 2) {data[i] = 3000 - data[i];} // 这行新版没有
            token = strtok(NULL, ",");
            i++;
        }
    }
}