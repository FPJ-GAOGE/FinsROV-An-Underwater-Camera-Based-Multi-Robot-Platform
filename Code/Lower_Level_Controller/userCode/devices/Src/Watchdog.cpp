//
// Created by admin on 2023/12/5.
//
#include "Watchdog.h"



void Watchdog::Init(){
    MX_IWDG_Init();
}

void Watchdog::Receive(){
    Flag_serial = true;// Uart data received. //串口收到数据
}

void Watchdog::Handle(){
    if(Flag_serial){// Reset `Count_ms_dog` after data reception. //收到数据后重置Count_ms_dog
        Count_ms_dog = 0;
        Flag_serial = false;
    }
    else Count_ms_dog++;// Increment `Count_ms_dog` when no data are received. //未收到数据Count_ms_dog增加
    if(Count_ms_dog < 2000) HAL_IWDG_Refresh(&hiwdg); // If no data are received for 2 seconds, restart the program. //2秒未收到数据，重启程序
}

