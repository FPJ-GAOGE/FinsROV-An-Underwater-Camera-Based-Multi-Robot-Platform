//
// Created by admin on 2023/12/5.
//
#include "Usermain.h"

#ifndef CONTROL_FRAME_MAIN_WATCHDOG_H
#define CONTROL_FRAME_MAIN_WATCHDOG_H

class Watchdog: public Device{

public:

    bool Flag_serial;
    uint32_t Count_ms_dog;

    void Init();
    void Handle();
    void Receive();

};



#endif //CONTROL_FRAME_MAIN_WATCHDOG_H
