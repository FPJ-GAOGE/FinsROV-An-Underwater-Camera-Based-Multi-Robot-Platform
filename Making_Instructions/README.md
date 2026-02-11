# Making Instructions
The waterproof compartment houses the basic circuitry for the submersible's operation, including 1 C-board, 1 I2C expansion board, 1 PWM expansion board, and the connecting wires for them. The waterproof compartment connects to external circuits via cable-passing screw holes on its back, with the connection corresponding to each screw hole as follows:

防水仓内包含了潜器运行的基本电路，包括C板 x1、IIC扩展板 x1、PWM扩展板 x1以及用于连接它们的电线。防水仓通过背部的穿线螺丝孔与外界电路进行连接，其中每个螺丝孔对应的连接为：

![Wire](./Images/337707bc-6bd9-4c74-b155-716a861c906f.png?raw=true)

## Electronics
The complete wiring diagram for the robot's internal circuitry is shown below:

机器人内部电路的完整接线图如下：

![Wire_in](./Images/8039e562-dc80-4d54-b2de-2b728531822c.png?raw=true)


### Internal Wiring
C-board to I2C Expansion Board: Pins 2, 4, 6, and 8 of the IIC interface on the C-board are connected to GND, VCC, SCL, and SDA of the input terminal on the I2C expansion board (the side with 5 black base pins arranged in a row), respectively.

C板接IIC扩展板：C板IIC接口的2、4、6、8号分别与IIC扩展板输入端（一侧并排5个黑色底座针脚）的GND、VCC、SCL、SDA相连
<img width="1197" height="324" alt="image" src="https://github.com/user-attachments/assets/d9d783e4-9902-47d3-96b0-ce0abd5396f7" />

I2C Expansion Board to Water Pressure Gauges: The GND, VCC, SCL and SDA of Ports 0 to 3 on the output terminal of the I2C Expansion Board (each port corresponding to 4 base pins of different colors arranged in a row) are connected to the black, red, green and white wires of the 4 water pressure gauges respectively.

IIC扩展板接水压计：IIC扩展板输出端0-3号端口（每个端口对应并排4个底座颜色不同的针脚）的GND、VCC、SCL、SDA分别与4个水压计的黑色、红色、绿色、白色线相连

I2C Expansion Board to PWM Expansion Board: The GND, VCC, SCL and SDA of Port 4 on the output terminal of the I2C Expansion Board are connected to the GND, VCC, SCL and SDA of the input terminal on the PWM Expansion Board (the side with 6 black base pins arranged in a row) respectively.

IIC扩展板接PWM扩展板：IIC扩展板输出端4号端口的GND、VCC、SCL、SDA分别与PWM扩展板输入端（一侧并排6个黑色底座针脚）的GND、VCC、SCL、SDA相连

<img width="579" height="486" alt="image" src="https://github.com/user-attachments/assets/eaca67df-8637-442a-9803-b3504d304920" />

C-board to PWM Expansion Board: Any 5V port of the PWM interface on the C-board is connected to the V+ of the input terminal on the PWM Expansion Board.

C板接PWM扩展板：C板PWM接口的任意一个5V端口与PWM扩展板输入端的V+相连

<img width="1128" height="426" alt="image" src="https://github.com/user-attachments/assets/b2edcb37-1fee-4348-8422-6d7a144375c6" />

### Inside/Outside Devices Connection
Manual soldering is overly complex due to numerous wirings, so the following terminal blocks are provided for easy wiring.

防水舱内与舱外设备：由于接线数量较多，如果手动焊接会非常复杂，因此配置了如下的接线端子，方便接线。

![Terminal_block](./Images/65a80ee5-c591-4b9c-a4c4-a7b3ef23d753.png?raw=true)

Power Supply to C-board and Propellers: The external battery is connected to the power input port (No.8) of the internal C-board via a power cable, and any of the power output ports (No.9) on the C-board is connected to the power input ports of the 8 propellers (in parallel) through a terminal block.

电源接C板和推进器：舱外电池通过电源线连接舱内C板电源输入端（8号），C板电源输出端（9号任意一个）通过极限段子连接8个推进器电源输入端（并联）

<img width="333" height="545" alt="image" src="https://github.com/user-attachments/assets/4cb6b7bf-2110-424a-acb1-654af6e473d6" />

C-board to Programmer: The wireless programmer is connected to the host computer for firmware programming and debugging.The exterior cabin wireless programmer connects to the interior cabin wireless programmer via the SWD download port on the C‑Board, with SWCLK, SWDIO, GND, and 3.3V pins connected correspondingly.

C板接烧写器：无线烧写器连接上位机，用于程序烧写、调试.  舱外无线烧写器连接舱内舱内无线烧写器，通过C板SWD下载线端口，SWCLK、SWDIO、GND、3.3V对应连接

C-board to Serial Port: The UART6 interface of the C‑Board is connected to the host computer via a TTL‑to‑422 module and a 422‑to‑USB module, for command transmission and reception.

C板接串口：C板UART6接口通过TTL转422模块、422转USB模块连接上位机，用于收发指令。

Propellers to PWM Expansion Board: The signal input terminals of the 8 external propellers are connected respectively to the PWM terminals (yellow base pins) of Ports 0 to 7 on the output terminal of the internal PWM Expansion Board.

推进器接PWM扩展板：舱外8个推进器信号输入端分别连接舱内PWM扩展板输出端0-7号端口PWM端（黄色底座针脚）。

Servos to PWM Expansion Board: The 4 external servos are connected to Ports 8 to 11 on the output terminal of the internal PWM Expansion Board respectively, with the negative poles connected to GND, the positive poles connected to V+, and the signal wires connected to PWM.

舵机接PWM扩展板：舱外4个舵机分别连接舱内PWM扩展板输出端8-11号端口，负极接GND，正极接V+，信号线接PWM。

Water Pressure Gauges to Water Pressure Gauge Adapter Boards: The 4 external water pressure gauges connect to the 4 internal water pressure gauge adapter boards, which can be directly inserted into the terminals.

水压计接水压计转接板：舱外4个水压计连接舱内4个水压机转接板，直接插入端子即可。