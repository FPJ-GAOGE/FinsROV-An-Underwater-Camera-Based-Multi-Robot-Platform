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

## Controller

本项目中

如果你想有更好的性能，我们推荐使用我们实验室开发的FINEMOTE框架，链接：
（部分硬件暂未适配）



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
