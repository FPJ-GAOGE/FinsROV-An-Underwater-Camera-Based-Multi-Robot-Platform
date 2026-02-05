//
// Created by admin on 2023/12/9.
//

#ifndef CONTROL_FRAME_MAIN_LED_H
#define CONTROL_FRAME_MAIN_LED_H

#include "Usermain.h"

class LED: public Device{

    void aRGB_led_show(uint32_t aRGB);
    void aRGB_led_change(uint32_t period);

public:
    void Init();
    void Handle();
    void Receive();
};




#endif //CONTROL_FRAME_MAIN_LED_H
