//
// Created by admin on 2023/11/28.
//

#include "Legacy.h"


volatile float vccMoni = 0;
volatile float vccBat = 0;

void bsp_ADC_vccMoni(){
    static uint8_t calibrationCplt = 0;
    static uint32_t calibrationCnt = 0;
    static uint32_t vrefSum = 0,vrefValue = 0;
    if(calibrationCplt == 0){
        if (calibrationCnt == 0){
            calibrationCnt ++;
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 2);
            vrefValue = HAL_ADC_GetValue(&hadc1);
            vrefSum += vrefValue;
        }else if(calibrationCnt < 200){
            calibrationCnt ++;
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 2);
            vrefValue = HAL_ADC_GetValue(&hadc1);
            vrefSum += vrefValue;
        }else{
            calibrationCplt = 1;
            vrefValue = vrefSum/200.0f;
            HAL_ADC_Stop(&hadc1);

            HAL_ADC_Start(&hadc3);
            HAL_ADC_PollForConversion(&hadc3, 2);
            vccMoni = HAL_ADC_GetValue(&hadc3)*1.25f/(float)vrefValue;

        }

    }else{
        HAL_ADC_Start(&hadc3);
        HAL_ADC_PollForConversion(&hadc3, 2);
        vccMoni = HAL_ADC_GetValue(&hadc3)*1.25f/(float)vrefValue;

    }
    vccBat = vccMoni/22.0f*222.0f;
}

/**
 * @brief 利用串口重定向函数，可选usb虚拟串口或硬件串口，使用需安装相应驱动
 * @param fmt
 * @param ...
 */
void usart_printf(const char *fmt,...){

        static uint8_t tx_buf[256] = {0};//TODO 爆栈？
        static va_list ap;
        static uint16_t len;

        va_start(ap,fmt);

        /*len = vsprintf((char*)tx_buf,fmt,ap);*/

        va_end(ap);

        //HAL_UART_Transmit_DMA(&huart1,tx_buf,len);
//    CDC_Transmit_FS(tx_buf,len);

    }

    flash_data_t flashData;
    void bsp_flash_write(flash_data_t *_flashData){
        HAL_FLASH_Unlock();
        FLASH_EraseInitTypeDef eraseInit;
        eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
        eraseInit.Sector = FLASH_SECTOR_9;
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    HAL_FLASHEx_Erase(&eraseInit,nullptr);
    uint32_t flash_ptr = FLASH_SECTOR_9_ADDRESS;

    for (uint32_t *ptr = (uint32_t*)_flashData;ptr < (uint32_t*)(sizeof(flash_data_t)/4 + _flashData);ptr++){
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_ptr,*ptr);
        flash_ptr += 4;
    }
    HAL_FLASH_Lock();
}
void bsp_flash_read(flash_data_t *_flashData){
    uint32_t flash_ptr = FLASH_SECTOR_9_ADDRESS;
    memcpy(_flashData,(uint32_t*)FLASH_SECTOR_9_ADDRESS,sizeof(flash_data_t)/4);
}

