## FinsROV: an Underwater Camera-Based Multi-robot platform

[![Python](https://img.shields.io/badge/python-3.10-blue.svg)](https://docs.python.org/3/whatsnew/3.10.html)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/license/mit)
[![License](https://img.shields.io/badge/license-CC%20BY--SA%204.0-orange.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

FinsROV is a low-cost, open-source Underwater robot platform designed for underwater task and research in robotics and AI.

FinsROV是一台开源的低成本水下机器人平台，面向AI和机器人领域中的水下任务和研究针对性设计。八推进器结构有效的保证了机器人全向运动的

## Overview

本项目提供一台完整的低成本水下ROV，并包含非常高的可扩展性，可以运用于水下物体跟踪，水下



## Controller

本项目中嵌入式框架使用我们实验室开发的FINEMOTE框架，链接：



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

How to bulid the robot platform:

coding:

basic theory about underwater robot:[【面向水下机器人的动力学与运动学建模及控制器分析】](https://www.bilibili.com/video/BV1VXmQBRE2a/?share_source=copy_web&vd_source=898a23397484d4386766c76dfa58679f)

demo:



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
