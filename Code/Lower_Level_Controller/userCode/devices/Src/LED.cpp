//
// Created by admin on 2023/12/9.
//
#include "LED.h"

void LED::Init(){
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
}

void LED::Receive(){

}

void LED::Handle(){
    aRGB_led_change(LED_PERIOD);
}


void LED::aRGB_led_show(uint32_t aRGB){
    static uint8_t alpha;
    static uint16_t red,green,blue;
    alpha = (aRGB & 0xFF000000) >> 24;
    red = ((aRGB & 0x00FF0000) >> 16) * alpha;
    green = ((aRGB & 0x0000FF00) >> 8) * alpha;
    blue = ((aRGB & 0x000000FF) >> 0) * alpha;
    __HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_1, blue);
    __HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, green);
    __HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, red);

}

/**
 * @brief 跑马灯函数，需周期性调用
 * @param period 跑马灯循环周期
 */
void LED::aRGB_led_change(uint32_t period){
    static uint32_t aRGB_value = 0xffff0000;
    static uint32_t lastTick = 0;
    static float lastPhase = 0;
    uint32_t red,green,blue;
    red = ((aRGB_value & 0x00FF0000) >> 16) ;
    green = ((aRGB_value & 0x0000FF00) >> 8) ;
    blue = ((aRGB_value & 0x000000FF) >> 0) ;

    float interval = HAL_GetTick()- lastTick;
    if(lastTick == 0){//处理首次进入
        lastTick = HAL_GetTick();
        return;
    }
    interval = interval * 765/(float)period;
    //if(interval == 0)interval = 1;
    uint32_t phase =  (uint32_t)(interval+ lastPhase)%765;
    uint32_t group = phase/255;
    uint32_t sub_phase = phase%255;

    switch(group){
        case 0:
            red = 255 - sub_phase;
            green = sub_phase;
            blue = 0;
            break;
        case 1:
            red = 0;
            green = 255 - sub_phase;
            blue = sub_phase;
            break;
        case 2:
            red = sub_phase;
            green = 0;
            blue = 255 - sub_phase;
            break;
        default:
            red = 255;
            green = 0;
            blue = 0;
            break;
    }
    aRGB_value = 0xff000000;
    aRGB_value |= red << 16;
    aRGB_value |= green << 8;
    aRGB_value |= blue;

    aRGB_led_show(aRGB_value);

    lastTick = HAL_GetTick();
    lastPhase = lastPhase + interval;
}