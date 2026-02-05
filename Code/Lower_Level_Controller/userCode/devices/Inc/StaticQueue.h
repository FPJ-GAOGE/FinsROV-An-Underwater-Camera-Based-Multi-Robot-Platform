/*******************************************************************************
 * Copyright (c) 2025.
 * IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
 * All rights reserved.
 ******************************************************************************/

#ifndef STATICQUEUE_HPP
#define STATICQUEUE_HPP

#include <cstdint>
#include <cstddef>
#include <array>
#include <cstring>
#include <type_traits>

template <size_t MAX_DATA_SIZE>
struct UartQueueElement
{
    std::array<uint8_t, MAX_DATA_SIZE> data{};
    uint16_t size = 0;
};

struct I2CQueueElementHeader
{
    uint16_t devAddress = 0;
    uint16_t size       = 0;
};

template <size_t N, size_t MAX_DATA_SIZE>
class FixedUartQueue
{
private:
    std::array<UartQueueElement<MAX_DATA_SIZE>, N> buffer{};
    size_t frontIdx   = 0;
    size_t rearIdx    = 0;
    size_t itemCount  = 0;

public:
    FixedUartQueue() = default;

    bool enqueue(const uint8_t *data, uint16_t size)
    {
        if (isFull() || size > MAX_DATA_SIZE)
        {
            return false;
        }
        auto &slot = buffer[rearIdx];
        std::memcpy(slot.data.data(), data, size);
        slot.size = size;

        rearIdx   = (rearIdx + 1) % N;
        ++itemCount;
        return true;
    }

    bool dequeue()
    {
        if (isEmpty())
        {
            return false;
        }
        // 可选：清零已出队元素内容
        buffer[frontIdx].size = 0;
        frontIdx  = (frontIdx + 1) % N;
        --itemCount;
        return true;
    }

    UartQueueElement<MAX_DATA_SIZE> &front()
    {
        // 调用者应先检查 isEmpty()
        return buffer[frontIdx];
    }

    const UartQueueElement<MAX_DATA_SIZE> &front() const
    {
        return buffer[frontIdx];
    }

    bool isEmpty() const { return itemCount == 0; }
    bool isFull()  const { return itemCount == N; }
    size_t size()  const { return itemCount; }
};

template <size_t N, size_t MAX_DATA_SIZE>
class FixedI2CQueue
{
private:
    struct I2CNode {
        I2CQueueElementHeader header{};
        std::array<uint8_t, MAX_DATA_SIZE> data{};
    };

    std::array<I2CNode, N> buffer{};
    size_t frontIdx   = 0;
    size_t rearIdx    = 0;
    size_t itemCount  = 0;

public:
    FixedI2CQueue() = default;

    bool enqueue(uint16_t devAddress, const uint8_t *data, uint16_t size)
    {
        if (isFull() || size > MAX_DATA_SIZE)
        {
            return false;
        }

        auto &slot = buffer[rearIdx];
        slot.header.devAddress = devAddress;
        slot.header.size       = size;
        std::memcpy(slot.data.data(), data, size);

        rearIdx   = (rearIdx + 1) % N;
        ++itemCount;
        return true;
    }

    bool dequeue()
    {
        if (isEmpty())
        {
            return false;
        }
        buffer[frontIdx].header.size = 0;
        frontIdx  = (frontIdx + 1) % N;
        --itemCount;
        return true;
    }

    I2CQueueElementHeader &frontHeader()
    {
        return buffer[frontIdx].header;
    }

    const I2CQueueElementHeader &frontHeader() const
    {
        return buffer[frontIdx].header;
    }

    uint8_t *frontData()
    {
        return buffer[frontIdx].data.data();
    }

    const uint8_t *frontData() const
    {
        return buffer[frontIdx].data.data();
    }

    bool isEmpty() const { return itemCount == 0; }
    bool isFull()  const { return itemCount == N; }
    size_t size()  const { return itemCount; }
};

#endif // STATICQUEUE_HPP
