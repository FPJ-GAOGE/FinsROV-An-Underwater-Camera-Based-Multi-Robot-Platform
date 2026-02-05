#include "bsp_uart.h"


void uart_recieveX_init(struct bsp_uart_recevieX_handle* huartReceive) {
	UART_HandleTypeDef *huart = huartReceive->huart;
	DMA_HandleTypeDef *hdma_uart_rx = huartReceive->hdma_uart_rx;
    //enable the DMA transfer for the receiver request
    //使能 DMA 串口接收
	
    SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
    //enalbe idle interrupt
    //使能空闲中断
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    //disable DMA
    //失效 DMA
    __HAL_DMA_DISABLE(hdma_uart_rx);
    while(hdma_uart_rx->Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(hdma_uart_rx);
    }
    hdma_uart_rx->Instance->PAR = (uint32_t) & (USART3->DR);
    //memory buffer 1
    //内存缓冲区 1
    hdma_uart_rx->Instance->M0AR = (uint32_t)(huartReceive->buf1);
    //memory buffer 2
    //内存缓冲区 2
    hdma_uart_rx->Instance->M1AR = (uint32_t)(huartReceive->buf2);
    //data length
    //数据长度
    hdma_uart_rx->Instance->NDTR = huartReceive->maxNum;
    //enable double memory buffer
    //使能双缓冲区
    SET_BIT(hdma_uart_rx->Instance->CR, DMA_SxCR_DBM);
    SET_BIT(hdma_uart_rx->Instance->CR, DMA_SxCR_CIRC);//TODO 和手册里写的不一样，完全不懂
    //enable DMA
    //使能 DMA
    __HAL_DMA_ENABLE(hdma_uart_rx);
}



void uart_recieveX_irq(struct bsp_uart_recevieX_handle* huartReceive) {
	UART_HandleTypeDef *huart = huartReceive->huart;
	DMA_HandleTypeDef *hdma_uart_rx = huartReceive->hdma_uart_rx;

    uint32_t isrflags   = READ_REG(huart->Instance->SR);
    uint32_t cr1its     = READ_REG(huart->Instance->CR1);
    uint32_t cr3its     = READ_REG(huart->Instance->CR3);

    if ((isrflags & UART_FLAG_RXNE) && !(isrflags & UART_FLAG_IDLE))//接收到数据
    {
        __HAL_UART_CLEAR_PEFLAG(huart);
    } else if (isrflags & UART_FLAG_IDLE) {

        __HAL_UART_CLEAR_PEFLAG(huart);

        if ((hdma_uart_rx->Instance->CR & DMA_SxCR_CT) == RESET) {
            /* Current memory buffer used is Memory 0 */

            //disable DMA
            //失效DMA
            __HAL_DMA_DISABLE(hdma_uart_rx);

            //get receive data length, length = set_data_length - remain_length
            //获取接收数据长度,长度 = 设定长度 - 剩余长度
            huartReceive->curNum = huartReceive->maxNum - hdma_uart_rx->Instance->NDTR;

            //reset set_data_lenght
            //重新设定数据长度
            hdma_uart_rx->Instance->NDTR = huartReceive->maxNum;

            //set memory buffer 1
            //设定缓冲区1
            hdma_uart_rx->Instance->CR |= DMA_SxCR_CT;

            //enable DMA
            //使能DMA
            __HAL_DMA_ENABLE(hdma_uart_rx);
			
			huartReceive->curBuf = huartReceive->buf1;
			huartReceive->dataDecode();
			
        } else {
            /* Current memory buffer used is Memory 1 */
            //disable DMA
            //失效DMA
            __HAL_DMA_DISABLE(hdma_uart_rx);

            //get receive data length, length = set_data_length - remain_length
            //获取接收数据长度,长度 = 设定长度 - 剩余长度
            huartReceive->curNum = huartReceive->maxNum - hdma_uart_rx->Instance->NDTR;

            //reset set_data_lenght
            //重新设定数据长度
            hdma_uart_rx->Instance->NDTR = huartReceive->maxNum;

            //set memory buffer 0
            //设定缓冲区0
            hdma_uart_rx->Instance->CR &= ~(DMA_SxCR_CT);

            //enable DMA
            //使能DMA
            __HAL_DMA_ENABLE(hdma_uart_rx);

			huartReceive->curBuf = huartReceive->buf2;
			huartReceive->dataDecode();
        }
    }else{
        HAL_UART_IRQHandler(huart);
    }
}