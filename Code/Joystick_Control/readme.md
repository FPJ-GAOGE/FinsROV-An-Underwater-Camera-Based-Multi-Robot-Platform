# 环境配置
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

# 硬件连接
1. 将ROV线缆的USB插头与电脑连接

2. 确保手柄与电脑连接（有线/无线适配器/蓝牙），可通过Win+R → 输入joy.cpl → 查看列表里有无控制器

3. 确保ROV与电源连接

# 代码配置
1. 运行前需修改代码中对应的串口通讯的端口号，即电脑识别的已插入的线缆USB插头的端口号（可以通过设备管理器 → 端口（COM和LPT）查看，比如COM11）
    确认端口号后在代码中找到以下语句：
    ```Python
    serial.open("COM28")   # 改成设备实际的 COM 号
    ```
    以上为例，则将COM28改为COM11：
    ```Python
    serial.open("COM11")
    ```
2. 运行`usbCameraFullControl`文件。操作按键为：start启动/关闭悬浮控制，十字键控制水平面前后左右运动，XY控制水平面旋转方向，AB控制上升下潜。注：目前速度为写死状态。
