//#include <Arduino.h>


#Define IrL
#Define IrR

// Definir os pinos para os motores
const int motorA1Pin = 2;   // Pino 2 para a direção do motor A
const int motorA2Pin = 3;   // Pino 3 para a direção do motor A
const int motorAPWM = 9;    // Pino 9 para a velocidade do motor A
const int motorB1Pin = 4;   // Pino 4 para a direção do motor B
const int motorB2Pin = 5;   // Pino 5 para a direção do motor B
const int motorBPWM = 10;   // Pino 10 para a velocidade do motor B

// Definir os pinos para o sensor ultrassônico
const int triggerPin = 7;    // Pino de saída do trigger
const int echoPin = 8;       // Pino de entrada do echo
const int obstacleDistance = 20;  // Distância mínima para detectar um obstáculo (ajuste conforme necessário)

// Criar uma instância do objeto NewPing para o sensor ultrassônico
NewPing sonar(triggerPin, echoPin);

void setup() {
  // Configurar os pinos como saídas
  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(motorAPWM, OUTPUT);
  pinMode(motorB1Pin, OUTPUT);
  pinMode(motorB2Pin, OUTPUT);
  pinMode(motorBPWM, OUTPUT);
}

void loop() {
  getDistance();
  
  // Avançar
  forward();
  delay(2000);  // Aguardar 2 segundos

  // Girar à esquerda
  turnLeft();
  delay(1000);  // Aguardar 1 segundo

  // Girar à direita
  turnRight();
  delay(1000);  // Aguardar 1 segundo

  // Parar
  stop();
  delay(2000);  // Aguardar 2 segundos
}

int getDistance() {
  // Realizar a leitura da distância do sensor ultrassônico
  int distance = sonar.ping_cm();

  // Retornar a distância em centímetros
  return distance;
}

void forward() {
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
  digitalWrite(motorB1Pin, HIGH);
  digitalWrite(motorB2Pin, LOW);

  analogWrite(motorAPWM, 255);  // Definir velocidade do motor A
  analogWrite(motorBPWM, 255);  // Definir velocidade do motor B
}

void backward() {
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
  digitalWrite(motorB1Pin, LOW);
  digitalWrite(motorB2Pin, HIGH);

  analogWrite(motorAPWM, 255);  // Definir velocidade do motor A
  analogWrite(motorBPWM, 255);  // Definir velocidade do motor B
}

void turnLeft() {
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
  digitalWrite(motorB1Pin, HIGH);
  digitalWrite(motorB2Pin, LOW);

  analogWrite(motorAPWM, 200);  // Definir velocidade do motor A
  analogWrite(motorBPWM, 200);  // Definir velocidade do motor B
}

void turnRight() {
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
  digitalWrite(motorB1Pin, LOW);
  digitalWrite(motorB2Pin, HIGH);

  analogWrite(motorAPWM, 200);  // Definir velocidade do motor A
  analogWrite(motorBPWM, 200);  // Definir velocidade do motor B
}

void stop() {
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, LOW);
  digitalWrite(motorB1Pin, LOW);
  digitalWrite(motorB2Pin, LOW);

  analogWrite(motorAPWM, 0);  // Desligar motor A
  analogWrite(motorBPWM, 0);  // Desligar motor B
}
