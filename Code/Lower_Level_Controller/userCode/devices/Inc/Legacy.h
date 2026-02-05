//
// Created by admin on 2023/11/28.
//
#include "main.h"
#include "tim.h"
#include "adc.h"
#include "gpio.h"
#include "usart.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#ifndef CONTROL_FRAME_MAIN_LEGACY_H
#define CONTROL_FRAME_MAIN_LEGACY_H

#define FLASH_SECTOR_9_ADDRESS 0x080A0000

typedef struct {
    /*uint32_t robot_ID;
    uint32_t yaw_zero;
    uint32_t pitch_zero;
    uint32_t pat[125];*/
    uint32_t pressure_offset[4];
}flash_data_t;

typedef struct {
    float x,y,z;
    float temp;
}ist8310_t;

extern flash_data_t flashData;

extern void bsp_ADC_vccMoni();
extern void usart_printf(const char *fmt,...);
extern void bsp_flash_write(flash_data_t *_flashData);
extern void bsp_flash_read(flash_data_t *_flashData);


#endif //CONTROL_FRAME_MAIN_LEGACY_H
