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


# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.


# Create your objects here.
ev3 = EV3Brick()


# Write your program here.
ev3.speaker.beep()


#sensores
sensorUltrassonico = UltrasonicSensor(Port.S2)
sensorCorD = ColorSensor(Port.S1)
sensorCorE = ColorSensor(Port.S4)
sensorGiroscopio = GyroSensor(Port.S3)

#motores
esquerdaM = Motor(Port.D)
direitaM = Motor(Port.A)

	
corDireita = ""
corEsquerda = ""

contGiro = 0

robo = DriveBase(esquerdaM, direitaM, 65, 160)

def qualCores():
    corDireita = sensorCorD.color()
    corEsquerda = sensorCorE.color()

def frente(velocidade, tempo=100):
    robo.drive_time(velocidade, 0, tempo)
    contGiro = 0

def tras(velocidade):
    robo.drive_time(-velocidade, 0 , 500)
    contGiro = 0

def direita(velocidade):
    direitaM.run_time(velocidade, 200)

def direitaDeVez(velocidade):
    direitaM.run_time(velocidade, 1500)

def esquerda(velocidade):
    esquerdaM.run_time(velocidade, 200)

def esquerdaDeVez(velocidade):
    esquerdaM.run_time(velocidade, 1500)

def girarEsquerda(velocidade):
    direitaM.run_time(velocidade, 1350)
    esquerdaM.run_time(-velocidade, 1350)

def girarDireita(velocidade):
    direitaM.run_time(-velocidade, 1350)
    esquerdaM.run_time(velocidade, 1350)

teveVerdeD = False
teveVerdeE = False

naoPretoDepoisD = False
naoPretoDepoisE = False


while True:
    

    naoPretoDepoisE = False
    naoPretoDepoisD = False

    corDireita = sensorCorD.color()
    corEsquerda = sensorCorE.color()

    if corDireita == Color.WHITE and corEsquerda == Color.WHITE:
        #D = branco e E = branco
        frente(100)
        contGiro = 0
        continue

    if corDireita == Color.GREEN and corEsquerda == Color.GREEN:
        #D = verde e E = verde
        frente(100)
        contGiro = 0
        continue
    
    if corDireita != Color.GREEN and corEsquerda == Color.GREEN:
        #D = ????? e E = verde
        teveVerdeE = True
        continue

    if corDireita == Color.GREEN and corEsquerda != Color.GREEN:
        #D = verde e E = ??????
        teveVerdeD = True
        continue

    if corDireita == Color.WHITE and corEsquerda == Color.BLACK:
        #D = verde e E = ??????
        
        #frente(100)
        #if corDireita == Color.WHITE and corEsquerda != Color.BLACK:
        #    naoPretoDepoisE = True
        #tras(100)
        
        if teveVerdeE:
            frente(700, 500)
            girarEsquerda(300)
            continue
        
        else:
            print("HAAAAAAAAAAAAAHAHHAAHHAHA")
            #if temPretoDepois:
            #    direitaDeVez(300)
            if contGiro == 0:
                frente(700, 500)
                girarEsquerda(300)
                contGiro+=1
            else:
                direita(300)
            continue

    if corDireita == Color.BLACK and corEsquerda == Color.WHITE:
        #frente(100)
        #if corDireita != Color.BLACK  and corEsquerda == Color.WHITE:
        #    naoPretoDepoisD = True
        #tras(100)

        if teveVerdeD:
            frente(700, 500)
            girarDireita(250)
            continue
            
        else:
            print("HAAAAAAAAAAAAAHAHHAAHHAHA")

            #if naoPretoDepoisD:
            #     esquerdaDeVez(300)
            if contGiro == 0:
                frente(700, 500)
                girarDireita(250)
                contGiro+=1
            else:
                esquerda(300)
            continue
            

    teveVerdeE = False
    teveVerdeD = False
    
