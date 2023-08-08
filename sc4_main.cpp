//teste codígo completo SC3 Frankstein

#include <Arduino.h> //intelisense pra .ino
#include <Wire.h>
#include <Adafruit_APDS9960.h>

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
#define motorA1 4
#define motorA2 5
// Motor B connections
#define motorB1 7 // mudar
#define motorB2 8 //mudar

int sensor_IR, ruido_Amb;
float duracao;
Adafruit_APDS9960 apds;

//"/home/dokidokiabr/Documents/arduino-1.8.19-linuxaarch64/arduino-1.8.19/tools/**",
//              "/home/dokidokiabr/Documents/arduino-1.8.19-linuxaarch64/arduino-1.8.19/hardware/arduino/avr/cores/arduino",
//              "/home/dokidokiabr/Documents/arduino-1.8.19-linuxaarch64/arduino-1.8.19/hardware/arduino/avr/variants/**"


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


  if (!apds.begin()) {
    Serial.println("No se pudo inicializar el APDS-9960. Compruebe la conexión.");
    while (1);
  }

  Serial.println("APDS-9960 listo para recibir comandos.");
  
  // Habilitar el sensor de color
  apds.enableColor(true);
  //apds.enableColorInterrupt();
  //apds.setInterrupt(false);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

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

  // Leer los valores de color
  uint16_t red, green, blue, clear;
  /*
  if (apds.getColorData(&red, &green, &blue, &clear)) {
    Serial.println("Error al leer los valores de color");
    return;
  }*/

  apds.getColorData(&red, &green, &blue, &clear);
  //apds.setLED(apds9960LedDrive_t drive, apds9960LedBoost_t boost);
  uint16_t colorTemperature =  apds.calculateColorTemperature(red, green, blue);
  //Serial.print(apds.calculateLux(red, green, blue)+"");
  //Serial.print(colorTemperature+"");
  
  Serial.print("Rojo: ");
  Serial.print(red);
  Serial.print(" Verde: ");
  Serial.print(green);
  Serial.print(" Azul: ");
  Serial.print(blue);
  Serial.print(" Clear: ");
  Serial.println(clear);

}
