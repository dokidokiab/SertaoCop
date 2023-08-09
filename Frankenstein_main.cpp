//biblioteca servo
//##################
//### FUNCIONOU! ###
//##################
#include <Servo.h>
#include <Arduino.h> //intelisense pra .ino
//pinos do HCSRO04
#define trig 3
#define echo 7
//pinos leds teste distancia
#define vermelho 13
#define amarelo 12
#define verde  10
//pinos do primeiro sensor IR
#define IR_a A1
#define IR 8
//pinos do segundo sensor IR
#define IR_b A0
#define IR2 2
// Motor A connections
#define IN1 9
#define IN2 6
// Motor B connections
#define IN3 5
#define IN4 3 
//pino servo
#define servo 11

//definição do nome do servo Servo.h
Servo garra; 

int leitura_IR1,leitura_IR1A;
float duracao;

void sensorIR1(){
  leitura_IR1 = digitalRead(IR);
  Serial.println(leitura_IR1);
  delay(500);
  leitura_IR1A = analogRead(IR_a);
  Serial.println(leitura_IR1A);
  delay(500);

}

void sensorIR2(){
  leitura_IR1 = digitalRead(IR2);
  Serial.println(leitura_IR1);
  delay(500);
  leitura_IR1A = analogRead(IR_b);
  Serial.println(leitura_IR1A);
  delay(500);

}

void movimento(int direcao, int velocidade){  // velocidade vai de 0 até 255
  switch (direcao){
    case 0://parado
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
      break;
    case 1://frente
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);
      break;
    case 2://trás
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);  
      break;
    case 3:// esquerda
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
        break;
    case 4://direita
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);
      break;
    case 5://giro no proprio eixo pra esquerda
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
      break;
    case 6://giro no proprio eixo pra direita
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);
      break;
  }
 
}

float distancia(){
  //define a função que obtem o valor da distância do sensor de distância HCSR04
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  // gera o pulso que faz a medição da distância

  duracao = pulseIn(echo, HIGH); //mede o tempo que demora pra o pulso sair de low para high e retorna esse valor
  return (duracao*.0343)/2; // converte o tempo de entre low-high para centímetros
}

void mover_servo(int angulo) {
  //define a função que movimenta o servo
  garra.write(angulo);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //seta os motores como output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //seta os motores para começarem parados
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //pinos do sensor de distancia  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  //pinos do sensor   
  pinMode(IR, INPUT);
  pinMode(IR_a, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR_b, INPUT);
  garra.attach(servo);
}

void loop() {
  movimento(0, 0);
  movimento(1, 100);
  delay(500);
  movimento(0, 0);
  movimento(5, 100);
  delay(500);
}