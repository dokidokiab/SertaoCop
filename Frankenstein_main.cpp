//biblioteca servo
#include <Servo.h>
#include <Arduino.h> //intelisense pra .ino
//pinos do HCSRO04
#define trig 10
#define echo 7
// bool 1 para preto
// bool 0 para branco 
//pinos do primeiro sensor IR
#define IR_esquerda A1
#define IResquerda 8
//pinos do segundo sensor IR
#define IR_direita A0
#define IRdireita 2
// Motor Esquerda connections
#define IN1 3
#define IN2 5
// Motor Direita connections
#define IN3 6
#define IN4 11
//pino servo
#define servo 10
// pino botão
#define botao 13 
//definição do nome do servo Servo.h
Servo garra; 

int leitura_IRLA, leitura_IRRA, velo, velo_giro; // define os valores inteiros 
bool leitura_botao, leitura_IRL, leitura_IRR; //define os valores booleanos 
float duracao; //define os valores decimais 

void sensorIRl(){
  //atualiza a leitura do sensor da esquerda
  leitura_IRL = digitalRead(IResquerda); //leitura digital sensor esquerda
  leitura_IRLA = analogRead(IR_esquerda); //leitra analogica sensor esquerda
}

void sensorIRR(){
  //atualiza o sensor da direita
  leitura_IRR = digitalRead(IRdireita); //leitra digital sensor direita
  leitura_IRRA = analogRead(IR_direita); //leitura analogica sensor direita
}

void movimento(int direcao, int velocidade){  // velocidade vai de 0 até 255
  // função que realiza o movimento em função da direção e velocidade
  switch (direcao){
    case 0://parado
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
      break;
    case 1://frente
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
      break;
    case 2://trás
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);  
      break;
    case 3:// direita
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
        break;
    case 4:// esquerda
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
      break;
    case 5://giro no proprio eixo pra direita
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
      break;
    case 6://giro no proprio eixo pra esquerda
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
  //movimenta o servo para o angulo q passou a função
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
  //pinos dos sensores IR 
  pinMode(IResquerda, INPUT);
  pinMode(IR_esquerda, INPUT);
  pinMode(IRdireita, INPUT);
  pinMode(IR_direita, INPUT);
  //biblioteca servo
  garra.attach(servo);
  //velocidade padrão
  velo = 150;
  velo_giro = 200;
  delay(1000);
}

void loop() {
  sensorIRl();
  sensorIRR();
  Serial.print("Sensor R digital: " + leitura_IRR);
  Serial.print("Sensor L digital: " + leitura_IRL);
  if(leitura_IRL == 0 && leitura_IRR == 0){
    movimento(0, velo);
    delay(250);
    movimento(1, velo);
  } 

  if(leitura_IRL == 1 && (leitura_IRR == 0 && leitura_IRR < 1)){
    movimento(0, velo);
    delay(500);
    movimento(3, velo_giro);
    delay(500);
  }

  if((leitura_IRL == 0 && leitura_IRL < 1) && leitura_IRR == 1){
    movimento(0, velo);
    delay(500);
    movimento(4, velo_giro);
    delay(500);
  } 
}