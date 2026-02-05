# Control Frame for the FinsROV Lower-Level Controller

# I. Project Overview

This project implements the lower-level control program for FinsROV. Its main functions include:

1. **Attitude sensing**: Sensor data from the **BMI088** (gyroscope + accelerometer) and the optional **IST8310** magnetometer are acquired via ``SPI + DMA``, and the MahonyAHRS algorithm is used to estimate attitude (quaternion / Euler angles).

2. **Depth and attitude-related estimation**: Four **MS5837-30BA** pressure sensors are read via ``I2C`` with temperature compensation, providing estimates of depth, pitch, and roll.

3. **Thruster control**: A **PCA9685** (PWM expansion board) drives 8 thrusters. The system supports depth closed-loop PID control and roll/pitch double-loop PID control, and also supports open-loop control via serial communication.

4. **Servo control**: A **PCA9685** expansion board drives 4 servos.

5. **Serial communication**: Commands are received via ``UART`` interrupts and then dispatched to each device module for parsing.
##
本项目为 FinsROV 下位机控制程序，主要功能包括：

1. 姿态感知：通过 SPI+DMA 读取 BMI088（陀螺仪+加速度计）+ IST8310（磁力计，可选）数据，并使用 MahonyAHRS 算法解算姿态（四元数/欧拉角）

2. 深度与姿态相关量估计：通过 I2C 读取 4 路 MS5837-30BA 水压计与温度补偿，得到深度/俯仰角/横滚角的估计量

3. 推进器控制：PCA9685（PWM 扩展板）控制 8 路推进器；支持深度闭环PID、横滚/俯仰角双环PID；支持串口通信开环控制

4. 舵机控制： PCA9685 扩展板控制 4 路舵机

5. 串口通信：通过 UART 中断接收命令，统一分发到各设备模块解析

# II. Overall System Architecture
## Unified Device Management (`Device` Framework)
In ``Usermain.h``, the system abstracts each hardware functional module as a ``Device`` class (interfaces: ``Init / Receive / Handle``) to uniformly manage all devices:

- ``Init()``: Initializes all devices. It is executed in the main program ``Usermain.cpp``, after the initialization of on-board (Robomaster-C board) devices.

- ``Receive()``: Invoked in the UART interrupt service routine ``HAL_UARTEx_RxEventCallback``. When serial data are received, they are stored in ``RxBuffer``.

- ``Handle()``: Periodically processes each device.

In ``Usermain.cpp``, devices are registered through a pointer array:
- IMU::imu  
- PressureSensor::pressure_sensor  
- Propeller_I2C  
- Servo_I2C  
- LED
##
在 ``Usermain.h`` 中，系统将各硬件功能模块抽象为 `Device` 类（接口包含 `Init / Receive / Handle`），用于统一管理所有设备：

- ``Init()``：将所有设备初始化，在主程序 ``Usermain.cpp`` 中执行，位于C板内部设备初始化之后

- ``Receive()``：在串口中断服务函数 ``HAL_UARTEx_RxEventCallback`` 中执行，串口收到数据时，将数据存入 ``RxBuffer``

- ``Handle()``：周期性处理各设备

在 ``Usermain.cpp`` 中，设备通过指针数组集中注册：

- IMU::imu  
- PressureSensor::pressure_sensor  
- Propeller_I2C  
- Servo_I2C  
- LED  

## Main Loop Scheduling

The system uses the **TIM1** periodic interrupt as the primary scheduler:

1. In ``HAL_TIM_PeriodElapsedCallback()``, when ``htim == &htim1``, the flag ``tick_XXXhz`` is set.

2. In the main loop ``while(1)``, this tick flag is checked:

    - Flag set → clear the flag → iterate over ``device[]`` and execute ``Handle()`` for each device.

    - Other .h/.cpp files inherit from the ``Device`` class to implement different device types (e.g., imu, pressure_sensor, propeller_i2c, servo_i2c, led) and provide concrete implementations of the above three pure virtual functions.
##
系统使用 **TIM1** 的周期中断作为主调度：

1. 在 ``HAL_TIM_PeriodElapsedCallback()`` 中，当 `htim == &htim1 `时置位 `tick_XXXhz`

2. 在主循环 `while(1)` 中检测该 tick 标志位：

   - 标志位置位 → 清零 → 遍历 `device[]`，依次执行每个设备的 ``Handle()``

   - 其余.h文件.cpp文件：均继承`device`类，实现不同设备类型，包括 imu、pressure_sensor、propeller_i2c、servo_i2c、led等，并具体实现上述3个纯虚函数

## UART Reception

UART6 uses ``HAL_UARTEx_ReceiveToIdle_IT()`` for reception, and an idle event triggers ``HAL_UARTEx_RxEventCallback()``.

In the UART6 Rx callback, ``Receive()`` is invoked for all devices in the ``device[]`` array.
##
UART6 使用 ``HAL_UARTEx_ReceiveToIdle_IT()`` 接收，空闲触发 ``HAL_UARTEx_RxEventCallback()``

在 UART6 的 Rx 回调里，对 device 数组中所有设备调用 ``Receive()``

# III. Module Descriptions
## IMU.cpp

1. Initialize BMI088.

2. SPI1 DMA acquire in segment:
   - gyroscope (Gyro)
   - accelerometer (Accel)
   - temperature (Temp)
   - magnetometer (Mag)

3. Apply bias correction and scaling:
   - `offset_correction()`

4. Use MahonyAHRS to compute quaternions and convert to Euler angles:
   - ``MahonyAHRSupdate(...)``
   - ``get_angle(...)``

5. Update global attitude (yaw/pitch/roll):
   - ``attitude_update()``
##
1. 初始化 BMI088

2. SPI1 DMA 分段读取：

   - 读陀螺仪（Gyro）

   - 读加速度（Accel）

   - 读温度（Temp）

   - 读磁力计（Mag）

3. 进行零偏补偿与缩放：

   - ``offset_correction()``

4. Mahony AHRS 计算四元数并转换欧拉角：

   - ``MahonyAHRSupdate(...)``

   - ``get_angle(...)``

5. 更新全局姿态（yaw/pitch/roll）：

   - ``attitude_update()``

## Sensor.cpp

### Pressure Sensor
The program uses four distributed **MS5837-30BA** pressure sensors and accesses them in a time-multiplexed manner via an I2C expansion board (before reading each channel, ``TCA_SetChannel(i)`` is called to switch the channel).

The overall acquisition logic in ``Handle_all()`` is as follows:

1. Initiate temperature conversion (``GET_TEMPERATURE``):  
   Switch sequentially to the four channels and send a “start temperature conversion” command to each sensor.

2. Read temperature results and initiate pressure conversion (``GET_PRESSURE``):  
   Read the temperature conversion result for each channel, and then sequentially send a “start pressure conversion” command for each channel.

3. Read pressure results and compute depth (``CALCULATE``):  
   Read the pressure conversion result for each channel, then perform compensation and calibration to obtain the depth estimate for that channel.
##
程序使用 4 个分布式 **MS5837-30BA** 水压计，通过 I2C 扩展板分时访问各传感器（每次读取某一路前先 ``TCA_SetChannel(i)`` 切换通道）

整体读取逻辑如下（``Handle_all()``）：

1. 发起温度转换（``GET_TEMPERATURE``）：

   依次切换到 4 路通道，给每个传感器发送“开始温度转换”的命令。

2. 读取温度结果并发起压力转换（``GET_PRESSURE``）：

   依次读取每路的温度转换结果，然后再依次给每路发送“开始压力转换”的命令。

3. 读取压力结果并计算深度（``CALCULATE``）：

   依次读取每路的压力转换结果，再进行补偿校准，得到该路的深度值。

## Propeller.cpp

### Thruster Control Method
PWM output is generated by the PCA9685; channels 0–7 correspond to the 8 thrusters.

### Thruster Index Definition
- ``InID[4]``: Mapping of the inner ring (vertical thrusters) to PCA channels
- ``OutID[4]``: Mapping of the outer ring (horizontal thrusters) to PCA channels
- ``Sign[8]``: Rotation direction (CW/CCW) for each thruster (+1/−1)

### Hover Control Mode (``flag_float``)
When enabled:
- Inner-ring thrusters perform closed-loop control for depth, roll, and pitch.
- Outer-ring thrusters perform open-loop translation/rotation (WASD/QE/Z).

When disabled:
- All thrusters output InitPWM (stop).

### PID Structure
- Depth: ``DepthPID``
- Roll/Pitch: double-loop
  - Outer loop uses pressure-sensor differential signals:
    - ``RollOutPID(Target_roll, pressure_roll_diff)``
    - ``PitchOutPID(Target_pitch, pressure_pitch_diff)``
  - Inner loop uses IMU angular rates:
    - Roll inner loop uses ``IMU::imu.attitude.neg_roll_v`` (note the sign inversion)
    - Pitch inner loop uses ``IMU::imu.attitude.pitch_v``

##
### 推进器控制方式
使用 PCA9685 输出PWM，通道0-7分别对应 8 个推进器


### 推进器序号定义
- ``InID[4]``：内圈（垂直推进器）映射到 PCA 通道
- ``OutID[4]``：外圈（水平推进器）映射到 PCA 通道
- ``Sign[8]``：每个推进器正反桨方向（+1/-1）

### 悬浮控制模式（`flag_float`）
开启后：
- 内圈推进器执行深度、横滚、俯仰闭环控制
- 外圈推进器执行开环平移/旋转（WASD/QE/Z）

关闭后：
- 所有推进器输出 InitPWM（停止）

### PID结构
- Depth：``DepthPID``
- Roll/Pitch：双环PID
  - 外环使用水压计差分：
    - ``RollOutPID(Target_roll, pressure_roll_diff)``
    - ``PitchOutPID(Target_pitch, pressure_pitch_diff)``
  - 内环使用 IMU 角速度：
    - Roll 内环用 ``IMU::imu.attitude.neg_roll_v``（注意符号取反）
    - Pitch 内环用 ``IMU::imu.attitude.pitch_v``

## Servo.cpp

Servos are controlled via the PWM expansion board:

- The ``Servo_I2C::Handle()`` function first calls ``TCA_SetChannel`` to select the I2C expansion channel.
- Then, for each servo, ``PCA_Setpwm(uint8_t num, uint32_t on, uint32_t off)`` is called to control the angle through the PWM duty cycle.
##
使用PWM扩展板控制舵机：

- ``Servo_I2C::Handle()``函数首先调用``TCA_SetChannel``函数选择I2C扩展板通道
  
- 再对每个舵机调用``PCA_Setpwm(uint8_t num, uint32_t on, uint32_t off)``函数，通过PWM信号的占空比控制角度。

## Extension.cpp

This file defines no class type and only contains function implementations for handling the I2C expansion board and the PWM expansion board.
##
无类型，仅有函数定义，用于处理I2C扩展板及PWM扩展板

# IV. Serial Communication Protocol

| Module | Command | Description |
| --- | --- | --- |
| Thrusters | ``ON`` / ``OFF`` | Enable/disable hovering control |
| Thrusters | ``UP`` / ``DN`` | Target depth −1 / +1 |
| Thrusters | ``H:<value>`` | Set target holding depth to (value/10) cm |
| Thrusters | ``W/S/A/D`` | Forward/backward/left/right |
| Thrusters | ``Q/E`` | Counterclockwise/clockwise rotation |
| Thrusters | ``Z`` | Stop outer-ring thrusters (hover) |
| Thrusters | ``TES:pwm0..pwm7`` | Directly write 8-channel PWM (test) |
| Servos | ``MOT:p0,p1,p2,p3`` | 4-channel servo PWM |
| Pressure sensors | ``CA`` | Parameter calibration |
| Pressure sensors | ``VA`` | Return pressure-sensor readings |
##
| 模块  | 命令                | 含义                 |
| --- | ----------------- | ------------------ |
| 推进器 | ``ON`` / ``OFF``      | 开启/关闭悬浮控制        |
| 推进器 | ``UP`` / ``DN``       | 目标深度 -1 / +1       |
| 推进器 | ``H:<value>``       | 目标保持深度为（value/10）cm     |
| 推进器 | ``W/S/A/D``         | 前/后/左/右            |
| 推进器 | ``Q/E``             | 逆/顺时针旋转            |
| 推进器 | ``Z``               | 外圈停止（悬停）         |
| 推进器 | ``TES:pwm0..pwm7`` | 直接写 8 路 PWM（测试）    |
| 舵机  | ``MOT:p0,p1,p2,p3`` | 4 路舵机 PWM          |
| 水压计 | ``CA``              | 参数校准 |
| 水压计 | ``VA``              | 返回水压计读数   |
