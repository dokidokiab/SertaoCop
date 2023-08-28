angulo = sensorGiroscopio.angle()
    if angulo > 180:
        sensorGiroscopio.reset_angle(0)
    print(angulo)



















    
    if corDireita == Color.WHITE and corEsquerda == Color.WHITE:
        #D = branco e E = branco
        frente(100)
        continue

    if corDireita == Color.GREEN and corEsquerda == Color.GREEN:
        #D = verde e E = verde
        frente(100)
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
        #if corDireita == Color.WHITE and corEsquerda == Color.BLACK:
        #    temPretoDepoisE = True
        #tras(100)
        
        if teveVerdeE:
            direitaDeVez(300)
            continue
        
        else:
            direita(300)
            continue

    if corDireita == Color.BLACK and corEsquerda == Color.WHITE:

        if teveVerdeD:
            esquerdaDeVez(300)
            continue
            
        else:
            esquerda(300)
            continue
            