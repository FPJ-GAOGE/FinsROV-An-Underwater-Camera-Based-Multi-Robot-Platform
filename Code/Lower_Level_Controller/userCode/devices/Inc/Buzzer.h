//
// Created by admin on 2023/12/9.
//

#ifndef CONTROL_FRAME_MAIN_BUZZER_H
#define CONTROL_FRAME_MAIN_BUZZER_H

#include "Usermain.h"

#define BUZZER_CLOCK_FREQUENCY 84000000
#define BUZZER_CLOCK htim4
#define BUZZER_CLOCK_CHANNEL TIM_CHANNEL_3
#define REFERENCE_MAX_VOL_CCR 5000

class Buzzer: public Device{

    float bsp_BuzzerOn(float _freq,float _targetVolPct);
    void bsp_BuzzerOff();

public:

    uint32_t BuzzerFlag;
    uint8_t buzzerWorkingFlag;

    void Init();
    void Receive();
    void Handle();

};


#endif //CONTROL_FRAME_MAIN_BUZZER_H
