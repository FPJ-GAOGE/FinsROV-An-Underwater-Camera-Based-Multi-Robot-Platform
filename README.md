<img width="960" height="556" alt="image" src="https://github.com/user-attachments/assets/dc544389-3cdc-4e68-832b-08e3d2075c98" />## FinsROV: an Underwater Camera-Based Multi-robot platform

[![Python](https://img.shields.io/badge/python-3.10-blue.svg)](https://docs.python.org/3/whatsnew/3.10.html)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/license/mit)
[![License](https://img.shields.io/badge/license-CC%20BY--SA%204.0-orange.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

FinsROV is a low-cost, open-source Underwater robot platform designed for underwater task and research in robotics and AI.

FinsROV是一台开源的低成本水下机器人平台，面向AI和机器人领域中的水下任务和研究针对性设计。八推进器结构有效的保证了机器人全向运动的的灵活性，双云台平台提供了充足的硬件扩展空间，

## Overview

本项目提供一台完整的低成本水下ROV，并包含非常高的可扩展性，可以运用于水下物体跟踪，水下

## Parameters

| 类别 | 子项 | 参数 | 补充说明 |
| :--- | :--- | :--- | :--- |
| **规格** | 尺寸（长×宽×高） | 40cm*35cm*15cm |  |
| **规格** | 功率 续航时间 | 约13.75W，约2h | 适配xt30/60接口的航模电池 |
| **规格** | 空气中重量 | 4.33Kg(v3.0), 4.85Kg(v3.1) |  |
| **规格** | 作业深度 | 10-20m，已通过内压测试 | 已通过内压测试 |
| **动力系统** | 静水航行最大加速度 | 4.6m/s^2 |  |
| **动力系统** | 静水航行最大速度 | 约3m/s |  |
| **动力系统** | 静水转向最大角速度 | 5.7rad/s |  |
| **动力系统** | 控制频率 | 60Hz | 可以根据实际需要进行调整 |
| **动力系统** | 波特率 | 9600 |  |
| **动力系统** | 载荷 | 10-15N |  |

## Structure

我们开源了水下机器人所有的结构件，提供对应的STEP文件，通过Solidworks等软件，可以对机器人结构进行修改。通过3D打印或者CNC加工等不同的形式，都可以制造对应的结构件

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
