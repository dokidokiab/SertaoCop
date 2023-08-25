#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
                                 InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile


# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.


# Create your objects here.
ev3 = EV3Brick()


# Write your program here.
ev3.speaker.beep()


#sensores
sensorUltrassonico = UltrasonicSensor(Port.S1)
sensorCorD = ColorSensor(Port.S2)
sensorCorE = ColorSensor(Port.S4)

#motores
esquerda = Motor(Port.D)
direita = Motor(Port.A)


corDireita = ""
corEsquerda = ""

roda = 85
axle = 180

robo = DriveBase(left, right, 65, 160)

olhos = ImageFile.ANGRY

#aceleração (accelaration)
acce = 200

def qualCores():
    corDireita = sensorCorD.color()
    corEsquerda = sensorCorE.color()

def frente(velocidade):
    robo.drive_time(velocidade, 0, 500)

def tras(velocidade):
    robo.drive_time(-velocidade, 0 , 500)

def direita(velocidade):
    direita.run_time(velocidade, 500)

def esquerda(velocidade):
    esquerda.run_time(velocidade, 500)




while True:
    #print(sensor_1.distance())

    frente(200)

    if corDireita == Color.WHITE and corEsquerda == Color.WHITE:

    elif corDireita != Color.WHITE:
        if corDireita == Color.BLACK:
        elif corDireita == Color.GREEN:
            if corEsquerda == Color.GREEN:
                frente(200)
            else:
                frente(50)
                direita(50)


    elif corEsquerda != Color.WHITE:
        if corEsquerda == Color.BLACK:
        elif corEsquerda == Color.GREEN:
            if corDireita == Color.GREEN:
                frente(200)
            else:
                frente(50)
                esquerda(50)
    else:




  