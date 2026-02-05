//
// Created by admin on 2023/11/27.
//
#include "usermain.h"
#include "Matrix.h"
#include "Extension.h"
#include "MahonyAHRS.h"
#include "Legacy.h"

#ifndef CONTROL_FRAME_MAIN_SENSOR_H
#define CONTROL_FRAME_MAIN_SENSOR_H



#define B02_IIC_ADDRESS 0xEC

#define MS5837_30BA_ResetCommand     0x1E                //��λ
#define	MS5837_30BA_PROM_RD 	       0xA0                //PROM��ȡ,{0XA0,0XA2,0XA4,0XA8,0XAA,0XAC,0XAE}
#define MS5837_30BA_ADC_RD           0x00                //ADC��ȡ

#define MS5837_30BA_D1_OSR256					 0x40
#define MS5837_30BA_D1_OSR512					 0x42
#define MS5837_30BA_D1_OSR1024					 0x44
#define MS5837_30BA_D1_OSR2048					 0x46
#define MS5837_30BA_D1_OSR4096					 0x48
#define MS5837_30BA_D2_OSR256					 0x50
#define MS5837_30BA_D2_OSR512					 0x52
#define MS5837_30BA_D2_OSR1024					 0x54
#define MS5837_30BA_D2_OSR2048					 0x56
#define MS5837_30BA_D2_OSR4096					 0x58

#define PRESSURE_0_V30 1005.646
#define PRESSURE_1_V30 1004.711
#define PRESSURE_2_V30 1004.350
#define PRESSURE_3_V30 1005.058

#define PRESSURE_0_V31 1014.227
#define PRESSURE_1_V31 1003.288
#define PRESSURE_2_V31 1003.028
#define PRESSURE_3_V31 1003.799

#define PRESSURE_0_V32 1009.775
#define PRESSURE_1_V32 1010.957
#define PRESSURE_2_V32 1010.074
#define PRESSURE_3_V32 1009.850

#define PRESSURE_0_V33 1004.227
#define PRESSURE_1_V33 1003.288
#define PRESSURE_2_V33 1003.028
#define PRESSURE_3_V33 1003.799

#define PRESSURE_0_V40 1003.599
#define PRESSURE_1_V40 1004.981
#define PRESSURE_2_V40 1004.411
#define PRESSURE_3_V40 1003.102

typedef struct Sensor_Site{
    float x[SENSOR_NUM];
    float y[SENSOR_NUM];
    float z[SENSOR_NUM];
} Sensor_Site_t;

enum class PS_HANDLE_STATE {
        GET_TEMPERATURE = 0X00,
        GET_PRESSURE = 0X01,
        CALCULATE = 0X02
    };

class PressureSensor: public  Device{

    unsigned char MS5837_30BA_Crc4(int id);
    unsigned long MS5837_30BA_GetConversion(uint8_t command);
    uint8_t MS5837_30BA_PROM(int id);
    void MS5837_30BA_ReSet(void);
    float MS5837_30BA_GetData(int id);
    //signed int MS5837_30BA_GetTemp(int id);

    void Init_single(int id);
    void Handle_single(int id);
    void Handle_all();
    void Calibrate_single(int id);
    void Calibrate();
    void OutputData_single(int id);
    void OutputData();
    void Solve_plane_3(float* data,float* h,float* x,float* y,float* z);
    void Solve_plane(float* data,float* h,float* x,float* y,float* z,int num);
    void Update_plane();//计算水面方程

    void Delay_us(uint32_t us);

    //void get_angle(float q[4], float *yaw, float *pitch, float *roll);

    signed int dT,TEMP;
    uint32_t Cal_C[6][7];
    int32_t OFFi,SENSi,Ti;
    int64_t OFF2;
    int64_t SENS2;
    uint32_t TEMP2;
    int64_t OFF_,SENS;
    uint32_t D1_Pres,D2_Temp;
    unsigned char flag_ok[6];
    
    int32_t CurrentID;

    Sensor_Site_t site;

public:

    void Init();
    void Handle();
    void Receive();

    float Temperature;
    signed int data_temp[6];
    float data_pressure_offset[6]; // 压强零偏值，在水上测量
    float data_pressure_raw[6]; // 水下压强原始值
    float data_pressure[6]; // 水下压强去掉零偏，即为深度值
    float data_plane[5]; // 水面方程Ax+By+Cz+D=0,A*A+B*B+C*C=0,5个数据分别为A、B、C、D、拉格朗日乘数
    float data_depth; // 深度数据，单位cm
    float data_roll,data_pitch;
    float data_level[3];
    //float quat[4];
    float pitch,roll; // 俯仰角、横滚角
    bool flag_calibrate; // 校准水压计零偏的标志
    bool flag_read_pres; // 读取水压计读数的标志

    //uint8_t flag_Busy;
    static PressureSensor pressure_sensor;
    PS_HANDLE_STATE ps_state = PS_HANDLE_STATE::GET_TEMPERATURE;

};

class Sonar: public Device{

    //uint8_t RxBuffer[SERIAL_LENGTH_MAX];
    int32_t data;
    int32_t data_offset;

public:

    void Init();
    void Handle();
    void Receive();
    static Sonar sonar;
};

#endif //CONTROL_FRAME_MAIN_SENSOR_H
