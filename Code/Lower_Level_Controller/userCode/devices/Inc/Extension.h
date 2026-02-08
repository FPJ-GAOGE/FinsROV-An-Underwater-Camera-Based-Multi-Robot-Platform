//
// Created by admin on 2023/10/29.
//

#ifndef CONTROL_FRAME_MAIN_EXTENSION_H
#define CONTROL_FRAME_MAIN_EXTENSION_H

#include "Usermain.h"



#define TCA9548A_ADDR         0x70

#define TCA9548A_CHANNEL_0          0x01
#define TCA9548A_CHANNEL_1          0x02
#define TCA9548A_CHANNEL_2          0x04
#define TCA9548A_CHANNEL_3          0x08
#define TCA9548A_CHANNEL_4          0x10
#define TCA9548A_CHANNEL_5          0x20
#define TCA9548A_CHANNEL_6          0x40
#define TCA9548A_CHANNEL_7          0x80

#define PCA9685_ADDR 0x80

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

/*

extern uint8_t RxBuffer_servo[];


extern void I2C_Extension_init();
extern void I2C_Extension();*/

extern void TCA_SetChannel(uint8_t channel);
extern void PCA_Setpwm(uint8_t num, uint32_t on, uint32_t off);
extern void PCA_Write(uint8_t adrr,uint8_t data);
extern void PCA_Setfreq(float freq);
extern uint8_t PCA_Read(uint8_t adrr);




#endif //CONTROL_FRAME_MAIN_EXTENSION_H
