# Control Frame for lower-level machine FinsROV
# 一、项目简介
本项目为 FinsROV 下位机控制程序，主要功能包括：

1. 姿态感知：通过 SPI+DMA 读取 BMI088（陀螺仪+加速度计）+ IST8310（磁力计，可选）数据，并使用 Mahony AHRS 解算姿态（四元数/欧拉角）

2. 深度与姿态相关量估计：通过 I2C 读取 4 路 MS5837-30BA 水压计与温度补偿，得到深度/俯仰角/横滚角的估计量

3. 推进器控制：PCA9685（PWM 扩展板）控制 8 路推进器；支持深度闭环PID、横滚/俯仰角双环PID；支持串口通信开环控制

4. 舵机控制： PCA9685 扩展板控制 4 路舵机

5. 串口通信：通过 UART 中断接收命令，统一分发到各设备模块解析

# 二、系统总体架构
## 设备统一管理（Device框架）

在 `Usermain.h` 中，系统将各硬件功能模块抽象为 Device 类（接口包含 Init / Receive / Handle），用于统一管理所有设备：

- `Init()`：将所有设备初始化，在主程序 `usermain.cpp` 中执行，位于C板内部设备初始化之后

- `Receive()`：串口收到数据时，将数据存入 `RxBuffer`，在串口中断服务函数 `HAL_UARTEx_RxEventCallback` 中执行

- `Handle()`：周期性处理各设备

在 `Usermain.cpp` 中，设备通过指针数组集中注册：

- IMU::imu

- PressureSensor::pressure_sensor

- Propeller_I2C

- Servo_I2C

- LED

## 主循环调度

系统使用 TIM1 的周期中断作为主调度：

1. 在 `HAL_TIM_PeriodElapsedCallback()` 中，当 htim == &htim1 时置位 tick_XXXhz

2. 在主循环 while(1) 中检测该 tick 标志位：

    - 标志位置位 → 清零 → 遍历 device[]，依次执行每个设备的 `Handle()`

    - 其余.h文件.cpp文件：均继承device类，实现不同设备类型，包括 imu、pressure_sensor、propeller_i2c、servo_i2c、led等，并具体实现上述3个纯虚函数

## 串口接收
UART6 使用 `HAL_UARTEx_ReceiveToIdle_IT()` 接收，空闲触发 `HAL_UARTEx_RxEventCallback()`

在 UART6 的 Rx 回调里，对 device 数组中所有设备调用 `Receive()`

# 三、各模块说明
## IMU.cpp
1. 初始化 BMI088

2. SPI1 DMA 分段读取：

    - 读陀螺仪（Gyro）

    - 读加速度（Accel）

    - 读温度（Temp）

    - 读磁力计（Mag）

3. 进行零偏补偿与缩放：

    - `offset_correction()`

4. Mahony AHRS 计算四元数并转换欧拉角：

    - `MahonyAHRSupdate(...)`

    - `get_angle(...)`

5. 更新全局姿态（yaw/pitch/roll）：

    - `attitude_update()`

## Sensor.cpp
### Pressure Sensor
程序使用 4 个分布式 MS5837-30BA 水压计，通过 I2C 扩展板分时访问各传感器（每次读取某一路前先 `TCA_SetChannel(i)` 切换通道）

整体读取逻辑如下（`Handle_all()`）：

1. 发起温度转换（`GET_TEMPERATURE`）：

    依次切换到 4 路通道，给每个传感器发送“开始温度转换”的命令。

2. 读取温度结果并发起压力转换（`GET_PRESSURE`）：

    依次读取每路的温度转换结果，然后再依次给每路发送“开始压力转换”的命令。

3. 读取压力结果并计算深度（`CALCULATE`）：

    依次读取每路的压力转换结果，再进行补偿校准，得到该路的深度值。

## Propeller.cpp
### 推进器控制方式
使用 PCA9685 输出PWM，通道0-7分别对应 8 个推进器
### 推进器序号定义
- `InID[4]`：内圈（垂直推进器）映射到 PCA 通道

- `OutID[4]`：外圈（水平推进器）映射到 PCA 通道

- `Sign[8]`：每个推进器正反桨方向（+1/-1）
### 悬浮控制模式（flag_float）
开启后：

- 内圈推进器执行深度、横滚、俯仰闭环控制

- 外圈推进器执行开环平移/旋转（WASD/QE/Z）

关闭后：

- 所有推进器输出 InitPWM（停止）
### PID结构
- Depth：`DepthPID`

- Roll/Pitch：双环

    - 外环使用水压计差分：

        - `RollOutPID(Target_roll, pressure_roll_diff)`

        - `PitchOutPID(Target_pitch, pressure_pitch_diff)`

    - 内环使用 IMU 角速度：

        - Roll 内环用 `IMU::imu.attitude.neg_roll_v`（注意符号取反）

        - Pitch 内环用 `IMU::imu.attitude.pitch_v`

## Servo.cpp
  使用PWM扩展板控制舵机：

 - `Servo_I2C::Handle()`函数首先调用`TCA_SetChannel`函数选择I2C扩展板通道
  
- 再对每个舵机调用`PCA_Setpwm(uint8_t num, uint32_t on, uint32_t off)`函数，通过PWM信号的占空比控制角度。

## Extension.cpp：
无类型，仅有函数定义，用于处理I2C扩展板及PWM扩展板

# 四、串口通信协议
| 模块  | 命令                | 含义                 |
| --- | ----------------- | ------------------ |
| 推进器 | `ON` / `OFF`      | 开启/关闭悬浮控制        |
| 推进器 | `UP` / `DN`       | 目标深度 -1 / +1       |
| 推进器 | `H:<value>`       | 目标保持深度为（value/10）cm     |
| 推进器 | `W/S/A/D`         | 前/后/左/右            |
| 推进器 | `Q/E`             | 逆/顺时针旋转            |
| 推进器 | `Z`               | 外圈停止（悬停）         |
| 推进器 | `TES:pwm0..pwm7` | 直接写 8 路 PWM（测试）    |
| 舵机  | `MOT:p0,p1,p2,p3` | 4 路舵机 PWM          |
| 水压计 | `CA`              | 参数校准 |
| 水压计 | `VA`              | 返回水压计读数   |
