//
// Created by LEGION on 2021/10/17.
//

#include "IMU.h"
#include "ist8310driver.h"
#include "UART_Base.h"
#include "Sensor.h"
#include "Usermain.h"

IMU IMU::imu;

bool is_output_angle = 0;
// bool is_output_accl = 0;

void IMU::Init()
{
    if (BMI088_init() != BMI088_NO_ERROR)
        Error_Handler();
#ifdef IMU_USE_MAG
    if (ist8310_init() != IST8310_NO_ERROR)
        Error_Handler();
#endif
    // BMI088_read(raw_data.gyro, raw_data.accel, &raw_data.temp);
 
    //加速度计复位后默认是暂停模式，这9行代码，向地址0x7D处写入0x04值，使加速度计进入正常模式
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);    //PA4置0，片选加速度计
    uint8_t data = (0x7D & 0x7F);    //Bit #0和Bit #1-7，Bit #0是0，表示写
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
    while(HAL_SPI_GetState(&hspi1)==HAL_SPI_STATE_BUSY_TX);    //等待SPI发送完成
    data = 0x04;    //Bit #8-15
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
    while(HAL_SPI_GetState(&hspi1)==HAL_SPI_STATE_BUSY_TX);    //等待SPI发送完成
    HAL_Delay(1);    //延时1ms
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);    //PA4置1，取消片选加速度计


    PID_Regulator_t _tempPID(1500, 0.08, 0, MPU6500_TEMP_PWM_MAX, MPU6500_TEMP_PWM_MAX, 0, MPU6500_TEMP_PWM_MAX);

    tempPid.PIDInfo = _tempPID;

    pro_data.ins_quat[0] = 1.0f;
    pro_data.ins_quat[1] = 0.0f;
    pro_data.ins_quat[2] = 0.0f;
    pro_data.ins_quat[3] = 0.0f;
    pro_data.ins_angle[0] = 0.0f;
    pro_data.ins_angle[1] = 0.0f;
    pro_data.ins_angle[2] = 0.0f;
    raw_data.gyro_offset[0] = 0.0f;
    raw_data.gyro_offset[1] = 0.0f;
    raw_data.gyro_offset[2] = 0.0f;
    raw_data.accel_offset[0] = 0.07f;
    raw_data.accel_offset[1] = -0.17f;
    raw_data.accel_offset[2] = 0.0f;

    if (HAL_SPI_Init(&hspi1) != HAL_OK)
        Error_Handler();
    SPI1_DMA_init((uint32_t)buf.gyro_dma_tx_buf, (uint32_t)buf.gyro_dma_rx_buf, SPI_DMA_GYRO_LENGHT);

    dma_state = IMU_DMA_IDLE;

}

void IMU::Handle()
{
    // 普通使用
    // BMI088_read(raw_data.gyro, raw_data.accel, &raw_data.temp);
    // ist8310_read_mag(raw_data.mag);    //读取磁力计数据，存储在mag中
    // offset_correction();
    // MahonyAHRSupdate(pro_data.ins_quat, pro_data.gyro[0], pro_data.gyro[1], pro_data.gyro[2], pro_data.accel[0], pro_data.accel[1], pro_data.accel[2], pro_data.mag[0], pro_data.mag[1], pro_data.mag[2]);    //对得到的加速度计、陀螺仪和磁力计数据进行计算得到四元数，直接在数组quat中更新
	// // MahonyAHRSupdateIMU(pro_data.ins_quat, pro_data.gyro[0], pro_data.gyro[1], pro_data.gyro[2], pro_data.accel[0], pro_data.accel[1], pro_data.accel[2]);    //对得到的加速度计、陀螺仪数据进行计算得到四元数，直接在数组quat中更新
	// get_angle(pro_data.ins_quat, pro_data.ins_angle, pro_data.ins_angle+1, pro_data.ins_angle+2);    //对四元数计算得到弧度制欧拉角，直接在INS_angle数组中更新

    // 开启IMU DMA传输
    if (dma_state == IMU_DMA_IDLE)
    {
        dma_state = IMU_DMA_READ_GYRO;
        trigger_gyro_dma();
    }
    // if(PressureSensor::pressure_sensor.ps_state == PS_HANDLE_STATE::CALCULATE){
    //     for(int i=0; i<3;i++){
    //         send_float(pro_data.gyro[i], 2, 0);
    //     }
    // }
}

void IMU::Receive()
{
    if (strncmp((char *)RxBuffer, "BEG", 3) == 0)
    {
        flag_Test = true;
    }
    if (strncmp((char *)RxBuffer, "END", 3) == 0)
    {
        flag_Test = false;
    }
    if (strncmp((char *)RxBuffer, "IVA:BEG", 7) == 0)
    {
        is_output_angle = 1;
    }
    if (strncmp((char *)RxBuffer, "IVA:END", 7) == 0)
    {
        is_output_angle = 0;
    }

    // if (strncmp((char *)RxBuffer, "AVA:BEG", 7) == 0)
    // {
    //     is_output_accl = 1;
    // }
    // if (strncmp((char *)RxBuffer, "AVA:BEG", 7) == 0)
    // {
    //     is_output_accl = 0;
    // }
    
}

void IMU::trigger_gyro_dma(void)
{
    if(!(hspi1.hdmatx->Instance->CR & DMA_SxCR_EN) && !(hspi1.hdmarx->Instance->CR & DMA_SxCR_EN))
    {
        HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_RESET);
        SPI1_DMA_enable((uint32_t)buf.gyro_dma_tx_buf, (uint32_t)buf.gyro_dma_rx_buf, SPI_DMA_GYRO_LENGHT);
    }
}

void IMU::trigger_accel_dma(void)
{
    if(!(hspi1.hdmatx->Instance->CR & DMA_SxCR_EN) && !(hspi1.hdmarx->Instance->CR & DMA_SxCR_EN))
    {
        HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_RESET);
        SPI1_DMA_enable((uint32_t)buf.accel_dma_tx_buf, (uint32_t)buf.accel_dma_rx_buf, SPI_DMA_ACCEL_LENGHT);
    }
}

void IMU::trigger_temp_dma(void)
{
    if(!(hspi1.hdmatx->Instance->CR & DMA_SxCR_EN) && !(hspi1.hdmarx->Instance->CR & DMA_SxCR_EN))
    {
        HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_RESET);
        SPI1_DMA_enable((uint32_t)buf.accel_temp_dma_tx_buf, (uint32_t)buf.accel_temp_dma_rx_buf, SPI_DMA_ACCEL_TEMP_LENGHT);
    }
}

void IMU::DMA_IT_Handle()
{
    if (__HAL_DMA_GET_FLAG(hspi1.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(hspi1.hdmarx)) != RESET)
    {
        __HAL_DMA_CLEAR_FLAG(hspi1.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(hspi1.hdmarx));

        switch (dma_state)
        {
        case IMU_DMA_IDLE:
            break;
        case IMU_DMA_READ_GYRO:
            HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_SET);
            BMI088_gyro_read_over(buf.gyro_dma_rx_buf + BMI088_GYRO_RX_BUF_DATA_OFFSET, raw_data.gyro);
            dma_state = IMU_DMA_READ_ACCEL;
            trigger_accel_dma();
            break;
        case IMU_DMA_READ_ACCEL:
            HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_SET);
            BMI088_accel_read_over(buf.accel_dma_rx_buf + BMI088_ACCEL_RX_BUF_DATA_OFFSET, raw_data.accel, &raw_data.time);
            dma_state = IMU_DMA_READ_TEMP;
            trigger_temp_dma();
            break;
        case IMU_DMA_READ_TEMP:
            HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_SET);
            BMI088_temperature_read_over(buf.accel_temp_dma_rx_buf + BMI088_ACCEL_RX_BUF_DATA_OFFSET, &raw_data.temp);
            imu_temp_control(raw_data.temp);
            ist8310_read_mag(raw_data.mag);
            offset_correction();
            MahonyAHRSupdate(pro_data.ins_quat, pro_data.gyro[0], pro_data.gyro[1], pro_data.gyro[2], pro_data.accel[0], pro_data.accel[1], pro_data.accel[2], pro_data.mag[0], pro_data.mag[1], pro_data.mag[2]);    //对得到的加速度计、陀螺仪和磁力计数据进行计算得到四元数，直接在数组quat中更新
            // MahonyAHRSupdateIMU(pro_data.ins_quat, pro_data.gyro[0], pro_data.gyro[1], pro_data.gyro[2], pro_data.accel[0], pro_data.accel[1], pro_data.accel[2]);    //对得到的加速度计、陀螺仪数据进行计算得到四元数，直接在数组quat中更新
            get_angle(pro_data.ins_quat, pro_data.ins_angle, pro_data.ins_angle+1, pro_data.ins_angle+2);    //对四元数计算得到弧度制欧拉角，直接在INS_angle数组中更新
            attitude_update();
            // 测试输出
            if (PressureSensor::pressure_sensor.ps_state == PS_HANDLE_STATE::CALCULATE)
            {
            // send_float(pro_data.ins_angle[0]*180/PI, 2, 0);
            // send_float(pro_data.ins_angle[1]*180/PI, 2, 0);
            // send_float(pro_data.ins_angle[2]*180/PI, 2, 1);
            // send_float(pro_data.accel[0], 2, 0);
            // send_float(pro_data.accel[1], 2, 0);
            // send_float(pro_data.accel[2], 2, 1);
							for(int i=0; i<3;i++)
							 {
									 send_float(PressureSensor::pressure_sensor.data_pressure[i], 2, 0);
							 }
							 send_float(PressureSensor::pressure_sensor.data_pressure[3], 2, 1);
            }
            dma_state = IMU_DMA_IDLE;
            break;
        }
    }
}

// DMA传输完成中断
void DMA2_Stream0_IRQHandler(void)
{
    IMU::imu.DMA_IT_Handle();
}

void IMU::ErrorHandle()
{
}

void IMU::get_angle(float q[4], float *yaw, float *pitch, float *roll)
{
    *yaw = atan2f(2.0f * (q[0] * q[3] + q[1] * q[2]), 2.0f * (q[0] * q[0] + q[1] * q[1]) - 1.0f);
    *pitch = asinf(-2.0f * (q[1] * q[3] - q[0] * q[2]));
    *roll = atan2f(2.0f * (q[0] * q[1] + q[2] * q[3]), 2.0f * (q[0] * q[0] + q[3] * q[3]) - 1.0f);
}

void IMU::imu_temp_control(float temp)
{
    uint16_t tempPWM;
    static uint8_t temp_constant_time = 0;
    if (first_temperate)
    {
        tempPid.PIDCalc(IMU_TARGET_TEMP, temp);
        if (tempPid.PIDInfo.output < 0.0f)
        {
            tempPid.PIDInfo.output = 0.0f;
        }
        tempPWM = (uint16_t)tempPid.PIDInfo.output;

        IMU_temp_PWM(tempPWM);

    }
    else
    {
        // 在没有达到设置的温度，一直最大功率加热
        // in beginning, max power
        if (temp > IMU_TARGET_TEMP)
        {
            temp_constant_time++;
            if (temp_constant_time > 200)
            {
                // 达到设置温度，将积分项设置为一半最大功率，加速收敛
                first_temperate = 1;
                tempPid.PIDInfo.componentKiMax = MPU6500_TEMP_PWM_MAX / 2.0f;
            }
        }

        IMU_temp_PWM(MPU6500_TEMP_PWM_MAX - 1);
    }
}

void IMU::IMU_temp_PWM(uint16_t pwm)
{
    __HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, pwm);
}

/**
 * @brief 测得陀螺仪和加速度计零偏值，存入raw_data.accel_offset和raw_data.gyro_offset数组
 * @param accel
 * @param _accel
 */
void IMU::calibrate_offset()
{
    float accel[3], gyro[3], temp;
    for (int i = 0; i < 1000; i++)
    {
        BMI088_read(gyro, accel, &temp);
        raw_data.accel_offset[0] += accel[0];
        raw_data.accel_offset[1] += accel[1];
        raw_data.accel_offset[2] += accel[2];
        raw_data.gyro_offset[0] += gyro[0];
        raw_data.gyro_offset[1] += gyro[1];
        raw_data.gyro_offset[2] += gyro[2];
        HAL_Delay(1);
    }
    raw_data.accel_offset[0] /= 1000;
    raw_data.accel_offset[1] /= 1000;
    raw_data.accel_offset[2] /= 1000;
    raw_data.gyro_offset[0] /= 1000;
    raw_data.gyro_offset[1] /= 1000;
    raw_data.gyro_offset[2] /= 1000;
}

void IMU::offset_correction()
{
    for (int i=0; i<3; i++)
    {
        pro_data.gyro[i] = raw_data.gyro[i] - raw_data.gyro_offset[i];
        pro_data.accel[i] = raw_data.accel[i] - raw_data.accel_offset[i];
    }
    pro_data.mag[0] = (raw_data.mag[0] - MAG_OFFSET_X) * MAG_SCALE_X;
    pro_data.mag[1] = (raw_data.mag[1] - MAG_OFFSET_Y) * MAG_SCALE_Y;
    pro_data.mag[2] = (raw_data.mag[2] - MAG_OFFSET_Z) * MAG_SCALE_Z;
}

void IMU::attitude_update()
{
    // V4 ins_angle 012对应yaw，pitch，roll
    attitude.yaw = pro_data.ins_angle[0];
    attitude.pitch = pro_data.ins_angle[1];
    attitude.roll = pro_data.ins_angle[2];
    attitude.yaw_v = pro_data.gyro[2];
    attitude.pitch_v = pro_data.gyro[1];
    attitude.roll_v = pro_data.gyro[0];
    attitude.neg_yaw_v = - attitude.yaw_v;
    attitude.neg_pitch_v = - attitude.pitch_v;
    attitude.neg_roll_v = - attitude.roll_v;
}