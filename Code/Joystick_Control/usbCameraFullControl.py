import pygame
import cv2
import numpy as np
import serialPort

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

class TextPrint:
    def __init__(self):
        self.reset()
        self.font = pygame.font.Font(None, 20)

    def print(self, screen, textString):
        textBitmap = self.font.render(textString, True, BLACK)
        screen.blit(textBitmap, [self.x, self.y])
        self.y += self.line_height

    def reset(self):
        self.x = 10
        self.y = 10
        self.line_height = 15

    def indent(self):
        self.x += 10

    def unindent(self):
        self.x -= 10

pygame.init()

size = [940, 480]
screen = pygame.display.set_mode(size)

pygame.display.set_caption("My Joystick and Camera")


cap = cv2.VideoCapture(0)

serial = serialPort.SerialPort()
serial.open("COM28")  # 确保这里的 COM 口是正确的

done = False

clock = pygame.time.Clock()

pygame.joystick.init()

textPrint = TextPrint()

isHovering = False

flagLastNoAction = 0

currentDepth = 300

# 现在的舵机PWM值
aaaa=1500
bbbb=1500
cccc=1500
dddd=1500

moveAxis = False


# -------- Main Program Loop -----------
while not done:
    user_action = False  # Reset user action flag for each loop iteration

    # EVENT PROCESSING STEP
    for event in pygame.event.get():  # User did something
        if event.type == pygame.QUIT:  # If user clicked close
            done = True  # Flag that we are done so we exit this loop

        # Possible joystick actions:
        # JOYAXISMOTION JOYBALLMOTION JOYBUTTONDOWN JOYBUTTONUP JOYHATMOTION
        if event.type == pygame.JOYBUTTONDOWN:
            user_action = True
            print("Joystick button pressed: {}".format(event.button))
            if event.button == 7:  #切换悬浮状态
                if isHovering:
                    serial.send("OFF")
                    isHovering = False
                else:
                    serial.send("ON")
                    isHovering = True
            if event.button == 0:  #上浮
                serial.send("UP")
            if event.button == 1:  #下潜
                serial.send("DN")
            if event.button == 8:  #左边舵机归位
                aaaa=1500
                bbbb=1500
                serial.send("MOT:{},{},{},{}".format(aaaa, bbbb, cccc, dddd))
            if event.button == 9:  #右边舵机归位
                cccc=1500
                dddd=1500
                serial.send("MOT:{},{},{},{}".format(aaaa,bbbb,cccc,dddd))

        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released: {}".format(event.button))

    # DRAWING STEP
    screen.fill(WHITE)
    textPrint.reset()

    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    if joystick.get_button(2) == 1:
        serial.send("Q")
        user_action = True
    if joystick.get_button(3) == 1:
        serial.send("E")
        user_action = True
    if joystick.get_button(0) == 1:
        user_action = True
    if joystick.get_button(1) == 1:
        user_action = True

    # 十字按键
    the_hat = joystick.get_hat(0)
    if the_hat[0] == 0 and the_hat[1] == 1:
        serial.send("W")
        user_action = True
    if the_hat[0] == -1 and the_hat[1] == 0:
        serial.send("A")
        user_action = True
    if the_hat[0] == 0 and the_hat[1] == -1:
        serial.send("S")
        user_action = True
    if the_hat[0] == 1 and the_hat[1] == 0:
        serial.send("D")
        user_action = True

    # 左手摇杆    控制舵机时发送MOT:aaaa,bbbb,cccc,dddd
    # 其中aaaa为左上舵机PWM，bbbb为左下，cccc为右上，dddd为右下
    # 范围500-2500，默认值1500，角度-90度至90度
    leftH_axis = joystick.get_axis(0)
    leftV_axis = joystick.get_axis(1)
    if abs(leftV_axis) > 0.5:  # 点头
        aaaa = max(min(int(aaaa + leftV_axis * 20), 2000), 1000)
        user_action = True
        moveAxis = True
    if abs(leftH_axis) > 0.5:  # 摇头
        bbbb = max(min(int(bbbb - leftH_axis * 20), 2500), 500)
        user_action = True
        moveAxis = True

    # 右手摇杆    控制舵机时发送MOT:aaaa,bbbb,cccc,dddd
    # 其中aaaa为左上舵机PWM，bbbb为左下，cccc为右下，dddd为右上
    # 范围500-2500，默认值1500，角度-90度至90度
    rightH_axis = joystick.get_axis(2)
    rightV_axis = joystick.get_axis(3)
    if abs(rightV_axis) > 0.5: #点头
        cccc = max(min(int(cccc - rightV_axis * 20), 2000), 1000)
        user_action = True
        moveAxis = True
    if abs(rightH_axis) > 0.5: #摇头
        dddd = max(min(int(dddd - rightH_axis * 20), 2500), 500)
        user_action = True
        moveAxis = True

    # 当前设置的深度
    textPrint.print(screen, "Current Depth: {}".format(currentDepth))

    def pwmToAngle(num):
        return 180*(num-500)/2000-90

    # 当前设置的舵机角度
    textPrint.print(screen, "Left horizontal: {}".format(pwmToAngle(aaaa)))
    textPrint.print(screen, "Lfet vertical: {}".format(pwmToAngle(bbbb)))
    textPrint.print(screen, "Right horizontal: {}".format(pwmToAngle(cccc)))
    textPrint.print(screen, "Right vertical: {}".format(pwmToAngle(dddd)))

    # Get the name from the OS for the controller/joystick
    name = joystick.get_name()
    textPrint.print(screen, "Joystick name: {}".format(name))

    axes = joystick.get_numaxes()
    textPrint.print(screen, "Number of axes: {}".format(axes))
    textPrint.indent()

    for i in range(axes):
        axis = joystick.get_axis(i)
        textPrint.print(screen, "Axis {} value: {:>6.3f}".format(i, axis))
    textPrint.unindent()

    buttons = joystick.get_numbuttons()
    textPrint.print(screen, "Number of buttons: {}".format(buttons))
    textPrint.indent()

    for i in range(buttons):
        button = joystick.get_button(i)
        textPrint.print(screen, "Button {:>2} value: {}".format(i, button))
    textPrint.unindent()

    hats = joystick.get_numhats()
    textPrint.print(screen, "Number of hats: {}".format(hats))
    textPrint.indent()

    for i in range(hats):
        hat = joystick.get_hat(i)
        textPrint.print(screen, "Hat {} value: {}".format(i, str(hat)))
    textPrint.unindent()

    # Capture a frame from the camera
    ret, frame = cap.read()
    if ret:
        # Convert the frame to a format that pygame can display
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
        cv2.flip(frame,1,frame)
        frame = cv2.resize(frame, (480, 640))
        frame = pygame.surfarray.make_surface(frame)

        # Blit the frame onto the screen, right shifted by 300 pixels
        screen.blit(frame, (300, 0))

    # Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # If no user action, send 'Z' via serial
    if not user_action:
        if not flagLastNoAction:
            serial.send("Z")
            flagLastNoAction = 1
    else:
        flagLastNoAction = 0

    if moveAxis:
        serial.send("MOT:{},{},{},{}".format(aaaa,bbbb,cccc,dddd))
        moveAxis = False

    # Limit to 30 frames per second
    clock.tick(30)

# Release the camera and close the window
cap.release()
serial.close()  # 关闭串口
pygame.quit()