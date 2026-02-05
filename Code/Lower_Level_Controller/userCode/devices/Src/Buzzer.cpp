//
// Created by admin on 2023/12/9.
//
#include "Buzzer.h"

void Buzzer::Init(){
    BuzzerFlag = 0;
    HAL_TIM_Base_Start(&BUZZER_CLOCK);
    HAL_TIM_PWM_Start(&BUZZER_CLOCK,BUZZER_CLOCK_CHANNEL);

}

void Buzzer::Receive(){

}

void Buzzer::Handle(){
    if(BuzzerFlag <= 3) {
        bsp_BuzzerOn(50,1);
        BuzzerFlag++;
    }
    else bsp_BuzzerOff();
}

float Buzzer::bsp_BuzzerOn(float _freq,float _targetVolPct){



    uint16_t arr,cpr;
    arr = (uint16_t)((BUZZER_CLOCK_FREQUENCY/ (float)(BUZZER_CLOCK.Instance->PSC+1))/_freq);
    //cpr = (uint16_t)(duty*(float)arr);
    cpr = (uint16_t)(_targetVolPct*REFERENCE_MAX_VOL_CCR*0.5);
    if(cpr > arr/2){
        cpr = arr/2;
    }


    if(!buzzerWorkingFlag){
        buzzerWorkingFlag = 1;

    }
    BUZZER_CLOCK.Instance->ARR = arr;
    __HAL_TIM_SetCompare(&BUZZER_CLOCK,BUZZER_CLOCK_CHANNEL,cpr);

    return (float)cpr/(float)arr*2;
}

void Buzzer::bsp_BuzzerOff(){
    if(buzzerWorkingFlag){
        buzzerWorkingFlag = 0;
        HAL_TIM_PWM_Stop(&BUZZER_CLOCK,BUZZER_CLOCK_CHANNEL);
    }
}