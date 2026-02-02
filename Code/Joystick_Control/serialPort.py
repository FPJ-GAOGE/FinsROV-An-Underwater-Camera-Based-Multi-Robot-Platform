import numpy as np
import serial


class SerialPort:
    def __init__(self):
        self.ser = serial.Serial()
        self.ser.baudrate = 115200
        self.ser.bytesize = 8
        self.ser.stopbits = 1
        self.ser.parity = "E"

    def status(self):
        return self.ser.isOpen()

    def open(self, port_name):
        self.ser.port = port_name  # 用户设置serial口
        try:
            self.ser.open()
        except:
            return False

        # isOpen()函数来查看串口的开闭状态
        return self.ser.isOpen()

    def close(self):
        try:
            self.ser.close()
        except:
            return False

        return not self.ser.isOpen()

    def send(self, data):
        if self.ser.isOpen():
            write_len = self.ser.write(data.encode('utf-8'))  # 编码
            return True
        else:
            return False

    def receive(self):
        if self.ser.isOpen():
            data = self.ser.readline().decode('utf-8')
            return data
        else:
            return False
