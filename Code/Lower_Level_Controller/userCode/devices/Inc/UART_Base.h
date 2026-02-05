/*******************************************************************************
 * Copyright (c) 2024.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef FINEMOTE_UARTBASELITE_H
#define FINEMOTE_UARTBASELITE_H

#include "Usermain.h"
#include "StaticQueue.h"

#define TX_QUEUE_SIZE 20
constexpr size_t UART_MAX_DATA_SIZE = 32;

constexpr UART_HandleTypeDef *uartHandleList[] = {nullptr, &huart1, nullptr, nullptr, nullptr, nullptr, &huart6};

template <uint8_t ID>
class UARTBaseLite
{
public:
    static UARTBaseLite &GetInstance()
    {
        static UARTBaseLite instance;
        return instance;
    }

    void Handle()
    {
        TxLoader();
    }

    void Transmit(uint8_t *data, uint16_t size)
    {
        if (txQueue.isFull())
        {
            txQueue.dequeue();
        }
        if (!txQueue.enqueue(data, size))
        {
            return;
        }
        TxLoader();
    }

    void OnTxDone()
    {
        isTxFinished = true;
        TxLoader();
    }

private:
    UARTBaseLite() = default;

    void TxLoader()
    {
        if (!txQueue.isEmpty() && isTxFinished)
        {
            auto &elem = txQueue.front();
            HAL_UART_Transmit_IT(uartHandleList[ID], const_cast<uint8_t*>(elem.data.data()), elem.size);
            isTxFinished = false;
            txQueue.dequeue();
        }
    }

    FixedUartQueue<TX_QUEUE_SIZE, UART_MAX_DATA_SIZE> txQueue;
    volatile bool isTxFinished = true;
};


#endif // FINEMOTE_UARTBASELITE_H