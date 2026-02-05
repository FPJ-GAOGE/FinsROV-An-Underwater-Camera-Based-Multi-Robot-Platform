需要修改的部分：Usercode/Device/Inc和Usercode/Device/Src

Usermain:
Usermain.h中Device类的三个函数Init、Handle、Receive分别用于初始化、周期性处理和串口接收处理，每个设备类型均继承Device类
Usermain.cpp中将需要使用的设备类型实例均列入设备指针数组device，随后在定时器中断函数、串口中断函数和主函数起始处，分别调用每个设备的Handle、Receive和Init函数

※ Usermain.h中需修改串口长度上限、各器件数量
※ Usermain.cpp中需修改设备总数，并将需要使用的设备类型列入device数组


Propeller:
内含两个类型Propeller和Propeller_i2c，分别为由C板PWM控制和由扩展版PWM控制的推进器
Propeller_i2c类型在Init中初始化PID参数及扩展版配置，在Handle中的float_ctrl函数进行悬浮状态的pitch、roll、z（深度）三个参数的PID控制，在Receive中处理串口接收

※ Propeller_i2c::Init中需修改pitch、roll、z三组PID参数
※ Propeller_i2c::Init和Propeller_i2c::Handle中需修改推进器对应的PWM扩展版接口
※ Propeller_i2c::float_ctrl中需修改目标深度和控制各自由度运动对应的推进器编号
※ Propeller_i2c::Receive中需修改串口通信协议


Servo:
内含两个类型Servo和Servo_i2c，分别为由C板PWM控制和由扩展版PWM控制的舵机

※ Servo_i2c::Init和Servo_i2c::Handle中需修改舵机对应的PWM扩展版接口
※ Servo_i2c::Receive中需修改串口通信协议


Sensor：
内含两个类型PressureSensor和Sonar，分别处理水压计和声呐数据
PressureSensor类型在Init中输入水压计坐标，并多次测量水上压强数据，得到压强的零偏值，在Handle中测量水下压强数据，通过Update_plane计算水面方程，并得出pitch、roll、z（深度）的测量值

※ PressureSensor::Init中需修改4个水压计的坐标


Buzzer：
内含Buzzer类型，用于处理蜂鸣器，初始化完成后响一声，提示初始化完成


Extension：
无类型，仅有函数定义，用于处理I2C扩展板及PWM扩展板


IMU：
内含IMU类型，处理加速度计、陀螺仪、磁力计数据，使用Mahony或Madgwick算法解算位姿，attitude结构体存储姿态数据，position结构体存储加速度、速度、位置数据
由于陀螺仪存在累计误差，目前使用不包含陀螺仪的数据定时校正输出结果


LED：
内含LED类型，用于处理LED灯，产生呼吸灯效果


Legacy:
关于测量电池电量和flash读写等，暂时没用


Watchdog:
内含Watchdog类型，若使用看门狗，则2秒内未收到串口数据，程序自动重启
