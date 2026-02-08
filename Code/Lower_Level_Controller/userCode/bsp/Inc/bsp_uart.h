#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <stdint.h>


struct bsp_uart_recevieX_handle{
	UART_HandleTypeDef *huart;
	DMA_HandleTypeDef *hdma_uart_rx;
	uint8_t *buf1;
	uint8_t *buf2;
	uint32_t maxNum;
	uint8_t *curBuf;
	uint32_t curNum;
	void  (*dataDecode)(void);
};
#ifdef __cplusplus
extern "C"{
#endif

extern void uart_recieveX_init(struct bsp_uart_recevieX_handle *huartReceive);

extern void uart_recieveX_irq(struct bsp_uart_recevieX_handle *huartReceive);

#ifdef __cplusplus
};
#endif
#endif /*__BSP_UART_H*/
