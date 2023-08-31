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

robo = DriveBase(esquerdaM, direitaM, 65, 160)

def qualCores():
    corDireita = sensorCorD.color()
    corEsquerda = sensorCorE.color()

def frente(velocidade, tempo=100):
    robo.drive_time(velocidade, 0, tempo)

def tras(velocidade, tempo=500):
    robo.drive_time(-velocidade, 0 , tempo)

def direita(velocidade):
    direitaM.run_time(velocidade, 600)

def direitaDeVez(velocidade):
    direitaM.run_time(velocidade, 1500)

def esquerda(velocidade):
    esquerdaM.run_time(velocidade, 600)

def esquerdaDeVez(velocidade):
    esquerdaM.run_time(velocidade, 1500)

def girarEsquerda(velocidade):
    direitaM.run_time(velocidade, 2000)
    esquerdaM.run_time(-velocidade, 2000)

def girarDireita(velocidade):
    direitaM.run_time(-velocidade, 2000)
    esquerdaM.run_time(velocidade, 2000)

def verificarFrente(tempo=600):
    esquerdaM.run_time(200, tempo)

teveVerdeD = False
teveVerdeE = False

ehCurvaRetaD = False
ehCurvaRetaE = False

temLinhaFrente = False

while True:
    ehCurvaRetaE = False
    ehCurvaRetaD = False
    temLinhaFrente = False

    corDireita = sensorCorD.color()
    corEsquerda = sensorCorE.color()

    if corDireita == Color.WHITE and corEsquerda == Color.WHITE:
        #D = branco e E = branco
        frente(150)
        continue

    if corDireita == Color.GREEN and corEsquerda == Color.GREEN:
        #D = verde e E = verde
        frente(150)
        continue
    
    if corDireita == Color.WHITE and corEsquerda == Color.GREEN:
        #D = ????? e E = verde
        teveVerdeE = True
        frente(600, 500)#metade do robo
        girarEsquerda(250)
        continue
    

    if corDireita == Color.GREEN and corEsquerda == Color.WHITE:
        #D = verde e E = ??????
        teveVerdeD = True
        frente(600, 500)#metade do robo
        girarDireita(250)
        continue

    if corDireita == Color.WHITE and corEsquerda == Color.BLACK:
        #D = verde e E = ??????
        #A LÓGICA DE VIRAR EM TODAS NÃO FUNCIONA, ABEL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        frente(100, 400)
        corEsquerda = sensorCorE.color()
        if corEsquerda == Color.GREEN or corEsquerda == Color.WHITE:
            ehCurvaRetaE = True
        tras(100, 400)
        
        #caso houve o verde
        if teveVerdeE:
            frente(600, 400)
            girarEsquerda(250)
            continue
        
        if not teveVerdeD:
            if temLinhaFrente:
                frente(150)

            if ehCurvaRetaE:
                frente(600, 400)#metade do robo
                girarEsquerda(250)
                

            if not ehCurvaRetaE:
                direita(300)
                
            continue

    if corDireita == Color.BLACK and corEsquerda == Color.WHITE: 
        #D = preto e E = branco

        frente(100, 400)
        corDireita = sensorCorD.color()
        if corDireita == Color.GREEN or corDireita == Color.WHITE:
            ehCurvaRetaD = True
        tras(100, 400)

        esquerdaM.run_time(200, 600)
        corEsquerda = sensorCorE.color()
        if corEsquerda == Color.BLACK:
            temLinhaFrente = True
        esquerdaM.run_time(-200, 600)


        #caso houve o verde
        if teveVerdeD:
            if ehCurvaRetaD:
                frente(600, 400)#metade do robo
                girarDireita(250)
            else:
                esquerda(300)
            continue
            
        if not teveVerdeD:
            if temLinhaFrente:
                frente(150)
                continue            

            #if ehCurvaRetaD:
            #     esquerdaDeVez(250)
            if ehCurvaRetaD:
                frente(600, 400)#metade do robo
                girarDireita(250)
                
            if not ehCurvaRetaD:
                esquerda(300)
            continue
            
    if corDireita == Color.BLACK and corEsquerda == Color.BLACK:
         #D = preto e E = branco
        frente(150)
        continue


    teveVerdeE = False
    teveVerdeD = False