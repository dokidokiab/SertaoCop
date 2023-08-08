void movimento(int direcao, int velocidade){  // velocidade vai de 0 até 255


  switch (direcao){
    case 0://parado
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    case 1://frente
      analogWrite(motorA1, velocidade);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, velocidade);
      analogWrite(motorB2, 0);
      break;
    case 2://de ré
      analogWrite(motorA1, 0);
      analogWrite(motorA2, velocidade);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, velocidade);  
      break;
        case 3:// esquerda
      analogWrite(motorA1, velocidade);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
        break;
        case 4://direita
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, velocidade);
      analogWrite(motorB2, 0);
        break;
        case 5://giro no proprio eixo pra esquerda
      analogWrite(motorA1, velocidade);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, velocidade);
        break;
        case 6://giro no proprio eixo pra direita
      analogWrite(motorA1, 0);
      analogWrite(motorA2, velocidade);
      analogWrite(motorB1, velocidade);
      analogWrite(motorB2, 0);
        break;
  }
 
}
