# Environment Setup
1. Required third-party libraries: pyserial, pygame, opencv

2. It is recommended to manage the virtual environment with **Anaconda**:

    2.1 Open Anaconda Prompt
    
    2.2 Create a new virtual environment (Python 3.10):
    ```bash
    conda create -n FinsROV python=3.10
    ```

    2.3 Activate the environment:
    ```bash
    conda activate FinsROV
    ```

    2.4 Install the required libraries:
    ```bash
    pip install pyserial pygame
    pip install opencv-python
    ```   
#
1. 需要安装的第三方库：pyserial, pygame, opencv

2. 建议使用Anaconda管理虚拟环境：

    2.1 打开Anaconda Prompt 

    2.2 新建虚拟环境（python版本3.10）
    ```bash
    conda create -n FinsROV python=3.10
    ```
    2.3 激活创建的虚拟环境：
    ```bash
    conda activate FinsROV
    ```
   
    2.4 安装第三方库：
    ```bash
    pip install pyserial pygame
    pip install opencv-python
    ```

# Hardware Connection
1. Connect the USB plug of the ROV tether cable to the computer.

2. Ensure the joystick is connected to the computer (wired / wireless dongle / bluetooth).
You may verify detection via: Win + R → type `joy.cpl` → check whether the controller appears in the list.

3. Ensure the ROV is connected to the power supply.

#
1. 将ROV线缆的USB插头与电脑连接

2. 确保手柄与电脑连接（有线/无线适配器/蓝牙），可通过Win+R → 输入joy.cpl → 查看列表里有无控制器

3. 确保ROV与电源连接

# Code Configuration
1. Before running the program, update **the serial communication port in the code** to match **the COM port assigned to the tether’s USB interface** (check via Device Manager → Ports (COM & LPT), e.g., COM11).
    After confirming the COM port, locate the following line in the code:
    ```Python
    serial.open("COM28")   # replace with the actual COM port on your device
    ```
    For example, if the detected port is COM11, modify it as follows:
    ```Python
    serial.open("COM11")
    ```
2. Run the `usbCameraFullControl` file. The control mapping is as follows:

    Start: enable/disable hover control

    D-pad: planar motion (forward/backward/left/right)

    X / Y: planar rotation direction

    A / B: ascend / descend

    Note: the speed is currently hard-coded.
#
1. 运行前需修改代码中对应的串口通讯的端口号，即电脑识别的已插入的线缆USB插头的端口号（可以通过设备管理器 → 端口（COM和LPT）查看，比如COM11）
    确认端口号后在代码中找到以下语句：
    ```Python
    serial.open("COM28")   # 改成设备实际的 COM 号
    ```
    以上为例，则将COM28改为COM11：
    ```Python
    serial.open("COM11")
    ```
2. 运行`usbCameraFullControl`文件。操作按键为：start启动/关闭悬浮控制，十字键控制水平面前后左右运动，XY控制水平面旋转方向，AB控制上升下潜。\
注：目前速度为写死状态。

# Note
1. If the propellers whine or make obvious abnormal noises on startup, stop the robot immediately (set to OFF) and restart it (set to ON). Power off is generally unnecessary. Repeat the above steps until the propellers operate with normal noises.
2. If the robot fails to respond to button presses, power it off and restart it directly.
3. When controlling via the joystick, ensure that any serial debugging tool is closed to prevent the UART port from being occupied, which may cause joystick control to fail.

#
1. 若启动时推进器啸叫，出现明显不正常声音，立刻停止潜器（输OFF），再重新启动（输ON），一般不需要断电。直到推进器声音正常。
2. 若出现按按键，但潜器没有反应，直接断电重启。
3. 使用手柄控制时注意关闭串口调试助手，避免串口占用导致手柄控制失效。
