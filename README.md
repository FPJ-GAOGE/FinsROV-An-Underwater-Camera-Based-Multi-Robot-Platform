## FinsROV: an Underwater Camera-Based Multi-robot platform

[![Python](https://img.shields.io/badge/python-3.10-blue.svg)](https://docs.python.org/3/whatsnew/3.10.html)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/license/mit)
[![License](https://img.shields.io/badge/license-CC%20BY--SA%204.0-orange.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

FinsROV is a low-cost, open-source Underwater robot platform designed for underwater task and research in robotics and AI. The eight-thruster configuration effectively ensures the flexibility of the robot's omnidirectional movement, and the dual-gimbal platform provides ample hardware expansion space, which can be applied to task scenarios such as underwater object tracking and underwater target recognition. This project supports both Chinese and English languages, though some videos and documents are only available in Chinese (Maybe this is a great opportunity to learn Chinese LOL)

FinsROV是一台开源的低成本水下机器人平台，面向AI和机器人领域中的水下任务和研究针对性设计。八推进器结构有效的保证了机器人全向运动的的灵活性，双云台平台提供了充足的硬件扩展空间，可以运用于水下物体跟踪，水下目标识别等任务场景。本项目提供中英两种语言的支持，但部分视频和文件仅有中文支持

## Overview

The FinsROV consists of a waterproof compartment with its internal circuitry, 8 propellers, 4 servos, 4 water depth sensors, and various brackets in total, with the model shown as follows:

FinsROV整体包含防水仓及其内部电路、推进器 *8、舵机 *4、水深传感器 *4以及各个支架，模型如下：
<img width="1188" height="735" alt="image" src="https://github.com/user-attachments/assets/fe2c9f88-46f4-43ed-980f-b86c20867fb6" />

The waterproof compartment houses the basic circuitry for the submersible's operation, including 1 C-board, 1 I2C expansion board, 1 PWM expansion board, 1 power distribution board, and the connecting wires for them. The waterproof compartment connects to external circuits via cable-passing screw holes on its back, with the connection corresponding to each screw hole as follows:

防水仓内包含了潜器运行的基本电路，包括C板 *1、IIC扩展板 *1、PWM扩展板 *1、分电板 *1以及用于连接它们的电线。防水仓通过背部的穿线螺丝孔与外界电路进行连接，其中每个螺丝孔对应的连接为：
<img width="2607" height="1074" alt="image" src="https://github.com/user-attachments/assets/34963ad7-11ad-46b3-a1b1-de70d0e29ac5" />

<img width="1280" height="531" alt="防水仓" src="https://github.com/user-attachments/assets/68d546fd-b013-408e-a8cd-8d864b1ef431" />

FinsROV is equipped with two 2-DOF gimbals mounted on either side of the submersible respectively. Each gimbal consists of two servos, with a maximum rotation angle of -90° to 90° for each servo.

FinsROV配置了两个二自由度的云台、分别置于潜器的两侧，一个云台由两个舵机组成，每个舵机的最大旋转角度为（-90°~90°）
<img width="1149" height="536" alt="image" src="https://github.com/user-attachments/assets/ea0486d9-fa3c-4817-aedd-b60c8719ee71" />

We have open-sourced all structural components of the underwater robot, which can be found in the [Structure](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Structure) folder, with the corresponding STEP files provided. The robot’s structure can be modified using software such as Solidworks, and the relevant structural components can be manufactured by means including 3D printing and CNC machining. We welcome everyone to upgrade and modify this robot platform.

我们开源了水下机器人所有的结构件，在[Structure](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Structure)文件夹中，提供对应的STEP文件，通过Solidworks等软件，可以对机器人结构进行修改。通过3D打印或者CNC加工等不同的形式，都可以制造对应的结构件，我们欢迎大家对机器人平台进行升级和改造

## Parameters

<table style="width:100%; border-collapse: collapse;">
  <thead>
    <tr style="border: 1px solid #ddd;">
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">Category</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">Sub-item</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">Parameter</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">Supplementary Note</th>
    </tr>
  </thead>
  <tbody>
    <tr style="border: 1px solid #ddd;">
      <td rowspan="4" style="border: 1px solid #ddd; padding: 8px; background-color: #f5f5f5;"><strong>Specifications</strong></td>
      <td style="border: 1px solid #ddd; padding: 8px;">Dimensions (Length × Width × Height)</td>
      <td style="border: 1px solid #ddd; padding: 8px;">40cm*35cm*15cm</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Power & Endurance Time</td>
      <td style="border: 1px solid #ddd; padding: 8px;">Approx. 13.75W, Approx. 2h</td>
      <td style="border: 1px solid #ddd; padding: 8px;">Adapted to RC model batteries with xt30/60 interface</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Weight in Air</td>
      <td style="border: 1px solid #ddd; padding: 8px;">4.33Kg(v3.0), 4.85Kg(v3.1)</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Operating Depth</td>
      <td style="border: 1px solid #ddd; padding: 8px;">10-20m (Passed internal pressure test)</td>
      <td style="border: 1px solid #ddd; padding: 8px;">Passed internal pressure test</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td rowspan="6" style="border: 1px solid #ddd; padding: 8px; background-color: #f5f5f5;"><strong>Power System</strong></td>
      <td style="border: 1px solid #ddd; padding: 8px;">Maximum Acceleration in Still Water</td>
      <td style="border: 1px solid #ddd; padding: 8px;">4.6m/s²</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Maximum Speed in Still Water</td>
      <td style="border: 1px solid #ddd; padding: 8px;">Approx. 3m/s</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Maximum Angular Velocity of Steering in Still Water</td>
      <td style="border: 1px solid #ddd; padding: 8px;">5.7rad/s</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Control Frequency</td>
      <td style="border: 1px solid #ddd; padding: 8px;">150Hz</td>
      <td style="border: 1px solid #ddd; padding: 8px;">Can be adjusted according to actual needs</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Baud Rate</td>
      <td style="border: 1px solid #ddd; padding: 8px;">115200</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">Load Capacity</td>
      <td style="border: 1px solid #ddd; padding: 8px;">10-15N</td>
      <td style="border: 1px solid #ddd; padding: 8px;">-</td>
    </tr>
  </tbody>
</table>

<table style="width:100%; border-collapse: collapse;">
  <thead>
    <tr style="border: 1px solid #ddd;">
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">类别</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">子项</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">参数</th>
      <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">补充说明</th>
    </tr>
  </thead>
  <tbody>
    <tr style="border: 1px solid #ddd;">
      <td rowspan="4" style="border: 1px solid #ddd; padding: 8px; background-color: #f5f5f5;"><strong>规格</strong></td>
      <td style="border: 1px solid #ddd; padding: 8px;">尺寸（长×宽×高）</td>
      <td style="border: 1px solid #ddd; padding: 8px;">40cm*35cm*15cm</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">功率 续航时间</td>
      <td style="border: 1px solid #ddd; padding: 8px;">约13.75W，约2h</td>
      <td style="border: 1px solid #ddd; padding: 8px;">适配xt30/60接口的航模电池</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">空气中重量</td>
      <td style="border: 1px solid #ddd; padding: 8px;">4.33Kg(v3.0), 4.85Kg(v3.1)</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">作业深度</td>
      <td style="border: 1px solid #ddd; padding: 8px;">10-20m，已通过内压测试</td>
      <td style="border: 1px solid #ddd; padding: 8px;">已通过内压测试</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td rowspan="6" style="border: 1px solid #ddd; padding: 8px; background-color: #f5f5f5;"><strong>动力系统</strong></td>
      <td style="border: 1px solid #ddd; padding: 8px;">静水航行最大加速度</td>
      <td style="border: 1px solid #ddd; padding: 8px;">4.6m/s^2</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">静水航行最大速度</td>
      <td style="border: 1px solid #ddd; padding: 8px;">约3m/s</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">静水转向最大角速度</td>
      <td style="border: 1px solid #ddd; padding: 8px;">5.7rad/s</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">控制频率</td>
      <td style="border: 1px solid #ddd; padding: 8px;">150Hz</td>
      <td style="border: 1px solid #ddd; padding: 8px;">可以根据实际需要进行调整</td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">波特率</td>
      <td style="border: 1px solid #ddd; padding: 8px;">115200</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
    <tr style="border: 1px solid #ddd;">
      <td style="border: 1px solid #ddd; padding: 8px;">载荷</td>
      <td style="border: 1px solid #ddd; padding: 8px;">10-15N</td>
      <td style="border: 1px solid #ddd; padding: 8px;"></td>
    </tr>
  </tbody>
</table>

## BOM

The complete BOM of our robot is shown below. For regions where components can be directly purchased on Taobao, you may click the links directly (this is not an advertisement; you may purchase from other suppliers). For those with no access to Taobao, please refer to the following information. A downloadable version of the BOM is also available in the Structure folder.

我们机器人的完整BOM表格如下，对于能够直接通过淘宝采购零部件的地区，可以直接点链接（非广告，可以买别家的）。如果没有办法使用淘宝，可以参考一下内容。在Structure文件中也有对应可下载的BOM文件。

[中文版本](https://docs.google.com/spreadsheets/d/1fIgdKPsx-9QTdMGvk-Vg6hmxgAVsjg4v-JMBh90Yp5g/edit?gid=0#gid=0)

[English Version BOM](https://docs.google.com/spreadsheets/d/1fIgdKPsx-9QTdMGvk-Vg6hmxgAVsjg4v-JMBh90Yp5g/edit?gid=352875595#gid=352875595)

## Electronics
The complete wiring diagram for the robot's internal circuitry is shown below:

机器人内部电路的完整接线图如下：

<img width="1994" height="1200" alt="inside Electronics" src="https://github.com/user-attachments/assets/9dd84f9b-5fa3-4b54-88f9-8dc48d61bfce" />

External Wiring: 485: Green - A+ // Green-White - B- // Orange - GND

外部接线：485：绿-A+ // 绿白-B- // 橙-GND

Internal Wiring: C-board to I2C Expansion Board: Pins 2, 4, 6, and 8 of the IIC interface on the C-board are connected to GND, VCC, SCL, and SDA of the input terminal on the I2C expansion board (the side with 5 black base pins arranged in a row), respectively.

内部接线：C板接IIC扩展板：C板IIC接口的2、4、6、8号分别与IIC扩展板输入端（一侧并排5个黑色底座针脚）的GND、VCC、SCL、SDA相连
<img width="1197" height="324" alt="image" src="https://github.com/user-attachments/assets/d9d783e4-9902-47d3-96b0-ce0abd5396f7" />

I2C Expansion Board to Water Pressure Gauges: The GND, VCC, SCL and SDA of Ports 0 to 3 on the output terminal of the I2C Expansion Board (each port corresponding to 4 base pins of different colors arranged in a row) are connected to the black, red, green and white wires of the 4 water pressure gauges respectively.

IIC扩展板接水压计：IIC扩展板输出端0-3号端口（每个端口对应并排4个底座颜色不同的针脚）的GND、VCC、SCL、SDA分别与4个水压计的黑色、红色、绿色、白色线相连

I2C Expansion Board to PWM Expansion Board: The GND, VCC, SCL and SDA of Port 4 on the output terminal of the I2C Expansion Board are connected to the GND, VCC, SCL and SDA of the input terminal on the PWM Expansion Board (the side with 6 black base pins arranged in a row) respectively.

IIC扩展板接PWM扩展板：IIC扩展板输出端4号端口的GND、VCC、SCL、SDA分别与PWM扩展板输入端（一侧并排6个黑色底座针脚）的GND、VCC、SCL、SDA相连

<img width="579" height="486" alt="image" src="https://github.com/user-attachments/assets/eaca67df-8637-442a-9803-b3504d304920" />

C-board to PWM Expansion Board: Any 5V port of the PWM interface on the C-board is connected to the V+ of the input terminal on the PWM Expansion Board.

C板接PWM扩展板：C板PWM接口的任意一个5V端口与PWM扩展板输入端的V+相连
<img width="1128" height="426" alt="image" src="https://github.com/user-attachments/assets/b2edcb37-1fee-4348-8422-6d7a144375c6" />

Devices Inside/Outside the Waterproof Compartment: Manual soldering is overly complex due to numerous wirings, so the following pluggable terminal blocks are provided for easy wiring.

防水舱内与舱外设备：由于接线数量较多，如果手动焊接会非常复杂，因此配置了如下的接线端子，可以插拔并且方便接线。
<img width="1206" height="639" alt="image" src="https://github.com/user-attachments/assets/0dc01e12-81e7-49c2-ae50-458fe09b8f6b" />

There are 4 pcs of 6-pin sockets (large) for connecting propellers (each propeller has three wires for positive, negative and signal); 2 pcs of 6-pin sockets (small) for connecting servos (each servo has three wires for positive, negative and signal); 1 pc of 2-pin socket (large) for connecting the power supply (positive and negative poles); 1 pc of 7-pin socket (small) for connecting the serial port (3 wires for UART + 4 wires for SWD C-board program burning); the water depth sensor is connected via its own adapter board.

共有6针座（大）*4，连接推进器（一个推进器包含正、负、信号三根线）；6针座（小）*2，连接舵机（一个舵机包含正、负、信号三根线）；2针座（大），连接电源（正、负级）；7针座（小），连接串口（UART三线+SWD C板程序烧写线四线）；水深传感器使用自带的转接板连接。

Power Supply to C-board and Propellers: The external battery is connected to the power input port (No.8) of the internal C-board via a power cable, and any of the power output ports (No.9) on the C-board is connected to the power input ports of the 8 propellers (in parallel).

电源接C板和推进器：舱外电池通过电源线连接舱内C板电源输入端（8号），C板电源输出端（9号任意一个）连接8个推进器电源输入端（并联）
<img width="333" height="545" alt="image" src="https://github.com/user-attachments/assets/4cb6b7bf-2110-424a-acb1-654af6e473d6" />

C-board to STLink: The STLink is connected to the host computer for program burning and debugging. The external STLink is connected to the SWD download port of the internal C-board, with SWCLK, SWDIO, GND and 3.3V connected in a one-to-one correspondence.

C板接stlink：stlink连接上位机，用于程序烧写、调试.  舱外stlink连接舱内C板SWD下载线端口，SWCLK、SWDIO、GND、3.3V对应连接
<img width="1175" height="600" alt="image" src="https://github.com/user-attachments/assets/86bfafe5-aaa4-4ff0-aef9-eaf95f40d009" />

C-board to Serial Port: The serial port module is connected to the host computer for sending and receiving commands. The external serial port module is connected to UART6 of the internal C-board, with RX connected to TX, TX connected to RX, and GND connected to GND.

C板接串口：串口模块连接上位机，用于收发指令,舱外串口模块连接舱内C板UART6，RX接TX，TX接RX，GND接GND
<img width="1218" height="396" alt="image" src="https://github.com/user-attachments/assets/87e28afb-75b2-402b-9025-59e0b07dcc1f" />

Propellers to PWM Expansion Board: The signal input terminals of the 8 external propellers are connected respectively to the PWM terminals (yellow base pins) of Ports 0 to 7 on the output terminal of the internal PWM Expansion Board.

推进器接PWM扩展板：舱外8个推进器信号输入端分别连接舱内PWM扩展板输出端0-7号端口PWM端（黄色底座针脚）

Servos to PWM Expansion Board: The 4 external servos are connected to Ports 8 to 11 on the output terminal of the internal PWM Expansion Board respectively, with the negative poles connected to GND, the positive poles connected to V+, and the signal wires connected to PWM.

舵机接PWM扩展板：舱外4个舵机分别连接舱内PWM扩展板输出端8-11号端口，负极接GND，正极接V+，信号线接PWM
<img width="345" height="510" alt="image" src="https://github.com/user-attachments/assets/a7500fb7-db0c-4101-976f-ee934d6556e9" />

Water Pressure Gauges to Water Pressure Gauge Adapter Boards: The 4 external water pressure gauges connect to the 4 internal water pressure gauge adapter boards, which can be directly inserted into the terminals.

水压计接水压计转接板：舱外4个水压计连接舱内4个水压机转接板，直接插入端子即可

## Controller

All controller codes are stored in the [Lower level controller](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Lower_Level_Controller) and can be used with the Readme file. In this project, our lower-level controller is based on the DJI Robomaster C-board (STM32F4) and developed with Keil. For secondary development of the code, you need to download Keil MDK version 533 or later, and it depends on the file Keil.STM32F4xx_DFP.2.14.0.pack. Install dpinst_x86.exe (for 32-bit systems) or dpinst_amd64.exe (for 64-bit systems) from the STLink package. The process for wireless programmers is similar to that of wired programmers; simply select CMSIS-DAP Debugger when choosing the debug tool, and there is generally no need to modify the clock frequency. For better performance, we recommend using the [FINEMOTE框架](https://github.com/FINS-Fines/FineMote) developed by our laboratory (note: some hardware is not yet adapted). It is a powerful embedded development framework that will also be used synchronously in our new-generation underwater robots.

控制器代码都在[Lower level controller](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Lower_Level_Controller)文件夹中，可以配合Readme使用，本项目中我们的下位机是基于DJI Robomaster C板（STM32F4），使用Keil进行开发的。如果需要对代码进行二次开发，需要下载Keil MDK533以上版本。依赖Keil.STM32F4xx_DFP.2.14.0.pack文件。安装stlink中的dpinst_x86.exe（32位）或 dpinst_amd64.exe（64位）。无线烧写器与有线烧写器流程类似，在选择调试工具的时候改为选择CMSIS-DAP Debugger即可，一般不需要修改时钟频率。如果你想有更好的性能，推荐使用我们实验室开发的[FINEMOTE框架](https://github.com/FINS-Fines/FineMote)（部分硬件暂未适配），这是一种强大的嵌入式开发框架，我们新一代的水下机器人上也会同步使用该框架

## Wired-Joystick
In Wired-Joystick document

creat new environment, python version:[![Python](https://img.shields.io/badge/python-3.10-blue.svg)](https://docs.python.org/3/whatsnew/3.10.html)

新建虚拟环境，python版本3.10

输入指令
```console
$ pip install pyserial pygame
```
硬件连接：连接相机的网口与控制口的USB口
确认控制口的USB的COM号（可以在设备管理器里的端口（COM和LPT）项中查看），并在程序中进行修改
如果使用V3.3之前的普通usb相机版本，请运行7-usbCameraFullControl文件； 如果使用的是V3.3网络相机版本，请运行10-webCameraCombinedControl文件。

## Video 
only chinese educate

How to bulid the robot platform:

controller coding:

basic theory about underwater robot:[【面向水下机器人的动力学与运动学建模及控制器分析】](https://www.bilibili.com/video/BV1VXmQBRE2a/?share_source=copy_web&vd_source=898a23397484d4386766c76dfa58679f)

demo:[【目前可公开的情报：FINS第一代水下机器人】](https://www.bilibili.com/video/BV1oC41177Rn/?share_source=copy_web&vd_source=e6237e17b71511df8920049cd998c076)

## Note

1. 若启动时推进器啸叫，出现明显不正常声音，立刻停止潜器（输OFF），再重新启动（输ON），一般不需要断电。直到推进器声音正常
2. 若出现按按键，但潜器没有反应，直接断电重启

## Citation
If you find this code useful, we would appreciate if you would cite our paper:

如果你觉得我们的开源项目能够帮助到你，欢迎你引用我们的文章！并持续关注我们的后续研究：
```
@article{xu2025aucamp,
  title={Aucamp: An Underwater Camera-Based Multi-Robot Platform with Low-Cost, Distributed, and Robust Localization},
  author={Xu, Jisheng and Lin, Ding and Fong, Pangkit and Fang, Chongrong and Duan, Xiaoming and He, Jianping},
  journal={arXiv preprint arXiv:2506.09876},
  year={2025}
}
```
