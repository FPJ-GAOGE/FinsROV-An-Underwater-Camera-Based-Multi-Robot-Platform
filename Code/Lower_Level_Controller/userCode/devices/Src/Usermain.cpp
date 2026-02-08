//
// Created by LEGION on 2021/10/4.
//
//This file contains the main function and the interrupt service routines (ISRs).
//The usage of each module follows three steps: initialization, data acquisition, and execution.
//Initialization and execution are performed within the timer interrupt routine.
//Serial (UART) data reception is handled within the UART interrupt routine.
//
//此文件为主函数和中断服务函数所在地
//每个元件的使用包含三个步骤，初始化、获取数据、执行
//初始化和执行在定时器中断函数进行
//获取串口数据在串口中断函数进行
#include "Usermain.h"
#include "IMU.h"
#include "Propeller.h"
#include "Servo.h"
#include "Sensor.h"
#include "Legacy.h"
#include "Watchdog.h"
#include "LED.h"
#include "Buzzer.h"
#include "gpio.h"
#include "UART_Base.h"


//Adjust according to the vehicle version: V30, V31, V32, V33, V40.
//根据潜器版本调整，V30，V31，V32，V33，V40
VERSION_E Robot_Version = V33;


// Statically instantiated objects.
// 静态实例化对象
// IMU imu;
static Servo servo;
static Servo_I2C servo_i2c;
static Propeller_I2C propeller_i2c;
static Sonar sonar;
static Watchdog watchdog;
static LED led;
static Buzzer buzzer;


// Array of device pointers for unified management and invocation of device operations.
// ------ TODO: Select the required devices.
// 设备指针数组，用于统一管理和调用设备操作
//------TODO:选用需要的设备
static Device *device[] = {
        &IMU::imu,                         //IMU 
        &PressureSensor::pressure_sensor,  //Pressure Sensor 水压计
        &propeller_i2c,                    //Propeller（PWM control via the PWM expansion board） 推进器（PWM扩展板控制）
        //&propeller,                      //Propeller（PWM control via the Robomaster_C board） 推进器（C板PWM控制）
				&servo_i2c,                        //Servo（PWM control via the PWM expansion board） 舵机（PWM扩展板控制）
				//&servo,                          //Servo（PWM control via the Robomaster_C board） 舵机（C板PWM控制）
        //&watchdog,                       //Watchdog 窗口看门狗
        &led,                              //LED
        //&buzzer                          //Buzzer 蜂鸣器
};

// Macro definition for the number of devices.
// 定义设备数量宏
#define DEVICE_NUM (sizeof(device) / sizeof(device[0]))

volatile bool system_init_flag = false;
volatile bool tick_300hz = false;
uint8_t RxBuffer[SERIAL_LENGTH_MAX] = {0};
volatile uint8_t key_raw_state = 1;
uint32_t key_last_stamp;
volatile int32_t time_start = 0, time_end = 0, time_interval = 0, cnt = 0;

// Timer interrupt service routine (ISR) for periodic device processing.
// 定时器中断服务函数, 用于周期性处理设备
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(!system_init_flag) return;
    if(htim == &htim1){ //300Hz
        tick_300hz = true;
    }
}

// UART receive interrupt service routine (ISR) for handling device-specific UART reception tasks.
// 串口接收中断服务函数, 用于处理设备的串口接收任务
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t datasize)//HAL_UART_RxCpltCallback
{
    if(huart->Instance==USART6) {
        // if (datasize >= 2){
            // if (strncmp((char *)RxBuffer, "IM", 2) == 0)
            //     device[0]->Receive();
            // else if (strncmp((char *)RxBuffer, "PS", 2) == 0)
            //     device[1]->Receive();
            // else if (strncmp((char *)RxBuffer, "PR", 2) == 0)
            //     device[2]->Receive();
            // else if (strncmp((char *)RxBuffer, "SE", 2) == 0)
            //     device[3]->Receive();
            // else if (strncmp((char *)RxBuffer, "LE", 2) == 0)
            //     device[4]->Receive();
            for(int i=0;i<DEVICE_NUM;++i){
                device[i]->Receive();
            // }
        }
        
        std::memset(RxBuffer, 0, SERIAL_LENGTH_MAX);
        // Re-enable UART reception.
				// 重新开启接收
        HAL_UARTEx_ReceiveToIdle_IT(&huart6, RxBuffer, SERIAL_LENGTH_MAX);
    }
}

// UART transmit interrupt callback function.
// 串口发送中断回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    #define HANDLE_UART_TX(ID)                            \
        do {                                              \
            if (huart == uartHandleList[ID]) {            \
                UARTBaseLite<ID>::GetInstance().OnTxDone(); \
                return;                                   \
            }                                             \
        } while (0)

    HANDLE_UART_TX(1);
    HANDLE_UART_TX(6);

    #undef HANDLE_UART_TX
    // if(huart == &huart1) {
    //     UARTBaseLite<1>::GetInstance().OnTxDone();
    // }
    // else if(huart == &huart6){
    //     UARTBaseLite<6>::GetInstance().OnTxDone();
    // }
}

// Key/button interrupt (currently unused).
// 按键中断，暂时无用
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//     if(system_init_flag == 0)return;
//     if (GPIO_Pin == GPIO_PIN_0){
//         key_raw_state = HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin);
//         uint32_t time_interval = HAL_GetTick() - key_last_stamp;
//         key_last_stamp = HAL_GetTick();
//         /*if (time_interval >= 50){
//             if (key_raw_state == 1){
//                 period = 5000;
//             }else{
//                 period = 500;
//             }
//         }*/
//     }
//     IMU::imu.ITHandle(GPIO_Pin);
// }

/**
  * @brief  The application entry point.
  * @retval int
  */
// Entry point of the main function.
// 主函数入口
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM5_Init();
    MX_TIM1_Init();
    MX_TIM4_Init();
    MX_TIM6_Init();
    MX_TIM7_Init();
    MX_TIM10_Init();
    MX_TIM8_Init();
    MX_ADC1_Init();
    MX_ADC3_Init();
    MX_USART1_UART_Init();
    MX_USART6_UART_Init();
    MX_USART3_UART_Init();
    MX_CAN1_Init();
    MX_CAN2_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    //MX_IWDG_Init();
    MX_USB_DEVICE_Init();

    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);


    HAL_TIM_Base_Start_IT(&htim8);
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
    //TODO adc校准？
    //RemoteControl::init();
    bsp_flash_read(&flashData);
    HAL_TIM_Base_Start_IT(&htim10);
    HAL_TIM_PWM_Start_IT(&htim10, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);

		// Initialize all devices.
    // 初始化所有设备
    for(int i = 0; i < DEVICE_NUM; ++i){
        device[i] -> Init();
    }
		
		// Set the initialization-complete flag.
    // 设置初始化完成标志
    system_init_flag = true;
    time_start = HAL_GetTick();

    while (1){
        // time_start = HAL_GetTick();
        if(tick_300hz){
            tick_300hz = false;
            static int a = 0;
            a++;
            for(int i = 0 ; i < DEVICE_NUM ; ++i){
                device[i]->Handle();
//                if (a==150&&i==4)
//                {
//                    time_end = HAL_GetTick();
//                    time_interval = time_end - time_start;
//                    send_int(time_interval, 1);
//                    a = 0;
//                    time_start = HAL_GetTick();
//                }
            }
            
        }
    }
}

void send_float(float value, uint8_t decimalPlaces, bool endSign){
    bool isNegative = 0;
    uint8_t len = 0;
    static char buffer_float[20] = {0};
		
		// Handle negative values.
    // 处理负数
    if(value < 0){
        isNegative = 1;
        value = -value;
    }
    if(isNegative) {
        buffer_float[0] = '-';
        len = 1;
    }

		// Convert the integer part.
    // 转换整数部分
    int32_t intPart = (int)value;
    len += sprintf(buffer_float+len, "%d", intPart);
		
		// Process the fractional part.
    // 处理小数部分
    if (decimalPlaces > 0) {
        buffer_float[len++] = '.';

        float fraction = value - (float)intPart;
        for (uint8_t i = 0; i < decimalPlaces; i++) {
            fraction *= 10;
            int digit = (int)fraction;
            buffer_float[len++] = digit + '0';
            fraction -= digit;
        }
    }

		// If this is the final element, append a newline; otherwise, append a comma.
    // 若结束则换行，否则是逗号
    if(endSign)
        buffer_float[len++] = '\n'; // Null terminator of the string 字符串结束符
    else
        buffer_float[len++] = ',';

    buffer_float[len] = '\0';

    // HAL_UART_Transmit(&huart6, (uint8_t *)buffer, len, 0x00ff);
    UARTBaseLite<6>::GetInstance().Transmit(reinterpret_cast<uint8_t *>(buffer_float),len);
}

void send_int(int32_t value, bool endSign){
    static char buffer_int[20] = {0};
    uint8_t len = 0;
    bool isNegative = 0;

		// Handle negative values.
    // 处理负数
    if(value < 0){
        isNegative = 1;
        value = -value;
    }
    if(isNegative) {
        buffer_int[0] = '-';
        len = 1;
    }

    len += sprintf(buffer_int+len, "%d", value);

    if(endSign)
        buffer_int[len++] = '\n';
    else
        buffer_int[len++] = ',';

    buffer_int[len] = '\0';
    // HAL_UART_Transmit(&huart6, (uint8_t *)buffer, len, 0x00ff);
    UARTBaseLite<6>::GetInstance().Transmit(reinterpret_cast<uint8_t *>(buffer_int),len);
}