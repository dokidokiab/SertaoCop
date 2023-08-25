#!/usr/bin/env pybricks-micropython
from pybricks import ev3brick as brick
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
                                 InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile
import time


#objetos
ev3 = EV3Brick()

#sensores
sensor_1 = UltrasonicSensor(Port.S1)
sensor_color = ColorSensor(Port.S2)

#motores
left = Motor(Port.D)
right = Motor(Port.A)

olhos = ImageFile.ANGRY

roda = 85
axle = 180

cont = 0 

robo = DriveBase(left, right, 65, 160)

#aceleração (accelaration)
acce = 200

def game_over():
    brick.display.clear()
    brick.display.text("GAME OVER", (60, 50))

while True:
    #print(sensor_1.distance())

    robo.drive(acce, 0)

    #raiva
    brick.display.image(olhos)


    if sensor_1.distance() < 150:

        #left.run_angle(1000, 100)
        #left.stop()
        #right.stop()
        
        acce += 200
    
    else:
        acce = 300 

    
    if sensor_color.color() != Color.WHITE and sensor_color.color() != Color.BLUE:
        robo.stop()
        brick.sound.file(SoundFile.UH_OH)
        olhos = ImageFile.DIZZY
        cont += 1

        if cont >= 18:
            game_over()
            brick.sound.file(SoundFile.BOING)            
            wait(3000)
            break
    
    else: 
        olhos = ImageFile.ANGRY
  
        
    """
    robo.turn(180)
    robo.drive_time(100, 0, 1000)
    """
    
    if Button.DOWN in ev3.buttons.pressed():
        acce-=100

    if Button.UP in ev3.buttons.pressed():
        acce+=100
        
