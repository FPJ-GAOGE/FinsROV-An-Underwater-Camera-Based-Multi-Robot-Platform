## FinsROV: an Underwater Camera-Based Multi-robot platform

[![Python](https://img.shields.io/badge/python-3.10-blue.svg)](https://docs.python.org/3/whatsnew/3.10.html)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/license/mit)
[![License](https://img.shields.io/badge/license-CC%20BY--SA%204.0-orange.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

FinsROV is a low-cost, open-source Underwater robot platform designed for underwater task and research in robotics and AI. The eight-thruster configuration effectively ensures the flexibility of the robot's omnidirectional movement, and the dual-gimbal platform provides ample hardware expansion space, which can be applied to task scenarios such as underwater object tracking and underwater target recognition. This project supports both Chinese and English languages, though some videos and documents are only available in Chinese (Maybe this is a great opportunity to learn Chinese LOL)

FinsROV是一台开源的低成本水下机器人平台，面向AI和机器人领域中的水下任务和研究针对性设计。八推进器结构有效的保证了机器人全向运动的的灵活性，双云台平台提供了充足的硬件扩展空间，可以运用于水下物体跟踪，水下目标识别等任务场景。本项目提供中英两种语言的支持，但部分视频和文件仅有中文支持

## Overview

The FinsROV consists of a waterproof compartment with its internal circuitry, 8 propellers, 4 servos, 4 water depth sensors, and various brackets in total, with the model shown as follows:

FinsROV整体包含防水仓及其内部电路、推进器 x8、舵机 x4、水深传感器 x4以及各个支架，模型如下：
![Model](./Structure/Images/7b80ec35-c6fb-4c0f-8c48-df3105a3505e.png?raw=true)

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
      <td style="border: 1px solid #ddd; padding: 8px;">4.85Kg</td>
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
      <td style="border: 1px solid #ddd; padding: 8px;">4.85Kg</td>
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

我们机器人的完整BOM表格如下，对于能够直接通过淘宝采购零部件的地区，可以直接点击链接参考（不涉及任何广告，仅供参考）。在Structure文件中也有对应可下载的BOM文件。

[中文版本](https://docs.google.com/spreadsheets/d/1fIgdKPsx-9QTdMGvk-Vg6hmxgAVsjg4v-JMBh90Yp5g/edit?gid=0#gid=0)

[English Version BOM](https://docs.google.com/spreadsheets/d/1fIgdKPsx-9QTdMGvk-Vg6hmxgAVsjg4v-JMBh90Yp5g/edit?gid=352875595#gid=352875595)

## Controller

All controller codes are stored in the [Lower level controller](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Lower_Level_Controller) and can be used with the Readme file. In this project, our lower-level controller is based on the DJI Robomaster C-board (STM32F4) and developed with Keil. For secondary development of the code, you need to download Keil Version 5.38 or later, and it depends on the file Keil.STM32F4xx_DFP.2.14.0.pack. Install dpinst_x86.exe (for 32-bit systems) or dpinst_amd64.exe (for 64-bit systems) from the STLink package. The process for wireless programmers is similar to that of wired programmers; simply select CMSIS-DAP Debugger when choosing the debug tool, and there is generally no need to modify the clock frequency. For better performance, we recommend using the [FINEMOTE](https://github.com/FINS-Fines/FineMote) developed by our laboratory (note: some hardware is not yet adapted). It is a powerful embedded development framework that will also be used synchronously in our new-generation underwater robots.

控制器代码在[Lower level controller](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Lower_Level_Controller)文件夹中，配合Readme使用，本项目中我们的下位机是基于DJI Robomaster C板（STM32F4），使用Keil进行开发的。如果需要对代码进行二次开发，需要下载Keil 5.38以上版本。依赖Keil.STM32F4xx_DFP.2.14.0.pack文件。安装stlink中的dpinst_x86.exe（32位）或 dpinst_amd64.exe（64位）。无线烧写器与有线烧写器流程类似，在选择调试工具的时候改为选择CMSIS-DAP Debugger即可，一般不需要修改时钟频率。如果你想有更好的性能，推荐使用我们实验室开发的[FINEMOTE框架](https://github.com/FINS-Fines/FineMote)（部分硬件暂未适配），这是一种强大的嵌入式开发框架，我们新一代的水下机器人上也会同步使用该框架

## Wired-Joystick

Our robot platform supports a variety of host computer systems, including but not limited to Windows, Linux, macOS, Android, Raspberry Pi, etc. We recommend using a game Joystick for control. The relevant code is available in [Joystick_Control](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Joystick_Control) and should be used in conjunction with the Readme file.

我们的机器人平台支持多种上位机系统，包括但不限于windows，linux，Mac os，Android，树莓派等，我们推荐使用手柄进行控制。相关代码在[Joystick_Control](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Code/Joystick_Control)中，配合Readme使用

## Education

We provide a complete set of video tutorials for building the underwater vehicle. We sincerely apologize that these tutorials are only available on Bilibili with Chinese voice-overs and subtitles. We will also upload other relevant content, and we welcome you to subscribe to our [channel](https://space.bilibili.com/1188256336?spm_id_from=333.40164.0.0). Additionally, the [Making_Instructions](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Making_Instructions) folder also contains some documentation on the making instructions.

我们为制作潜器提供完整的视频教程，但是非常抱歉，相关教程上传至BiliBili且只有中文配音与字幕。我们也会上传其他相关的内容，[欢迎订阅](https://space.bilibili.com/1188256336?spm_id_from=333.40164.0.0)。同时，[Making_Instructions](https://github.com/FPJ-GAOGE/FinsROV-An-Underwater-Camera-Based-Multi-Robot-Platform/tree/main/Making_Instructions)中也包含部分制作说明文档。

How to bulid the robot platform & coding: [【上海交通大学】从0-1带你制作水下机器人](https://www.bilibili.com/video/BV13vcvzgEv3?p=11&vd_source=225e86b359e69725bfc871c2685a31c8)

Basic theory about underwater robot: [【面向水下机器人的动力学与运动学建模及控制器分析】](https://www.bilibili.com/video/BV1VXmQBRE2a/?share_source=copy_web&vd_source=898a23397484d4386766c76dfa58679f)

Demo: [【目前可公开的情报：FINS第一代水下机器人】](https://www.bilibili.com/video/BV1oC41177Rn/?share_source=copy_web&vd_source=e6237e17b71511df8920049cd998c076)

## Thank & Citation

This project acknowledges the contributions of Ding Lin, Jisheng Xu, Jiahao Lin, Yanqi Feng, Jiaming Guo and other students who are or have been part of the FINS-Underwater Group.

这个项目要感谢Ding Lin, Jisheng Xu, Jiahao Lin, Yanqi Feng, Jiaming Guo等来自或参与过FINS-Underwater Group的同学的贡献 

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
