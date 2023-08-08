//teste codígo completo SC3 Frankstein

#include <Arduino.h> //intelisense pra .ino
//pinos do HCSRO04
#define trig 3
#define echo 7
//pinos leds teste distancia
#define vermelho 13
#define amarelo 12
#define verde  10
//pinos do primeiro sensor IR
#define led_diodo A0
#define led_preto 8 //provavelmente usar um pino digital pros 3 sensores IR 
// Motor A connections
#define IN1 4
#define IN2 5
// Motor B connections
#define IN3 7 // mudar
#define IN4 8 //mudar

int sensor_IR, ruido_Amb;
float duracao;

void motorAFrente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void motorAParar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motorBFrente() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorBStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
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
  pinMode(led_preto, OUTPUT);
  pinMode(led_diodo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Distancia: ");
  Serial.println(distancia());
  
  sensor_IR = analogRead(led_diodo);
  Serial.println(sensor_IR);

  if (distancia() > 0 && distancia() <= 20){
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  } else
  if (distancia() > 20 && distancia() <= 50){
    digitalWrite(amarelo, HIGH);
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
  } else
  if (distancia() > 50){
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
  }
  delay(1000);
}
