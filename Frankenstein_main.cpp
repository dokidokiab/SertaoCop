  //biblioteca servo
#include <Servo.h>
#include <Arduino.h> //intelisense pra .ino
//pinos do HCSRO04 frontal
#define trig 10
#define echo 8
//pinos do sensor de distância lateral
#define trig1 9
#define echo1 13
// bool 1 para preto
// bool 0 para branco 
//pinos do primeiro sensor IR
#define IR_esquerda A5
#define IResquerda A2
//pinos do segundo sensor IR
#define IR_direita A3
#define IRdireita A1
// pinos do terceiro sensor IR
#define IRmeio A0 //não é necessária leitura analogica do sensor IR central 
// Motor Esquerda 
#define IN1 3
#define IN2 5
// Motor Direita 
#define IN3 6
#define IN4 11
// a velocidade do robo é aproximadamente 15cm/s (tenho minhas dúvidas)
//pinos servo
#define Astrolabio 2
#define Astrolabio2 4
//definição do nome do servo Servo.h
Servo garra; 
Servo pa;

int Preto, BrancoR, VerdeR, BrancoL, VerdeL; // Valores a serem definidos na mão no momento da calibragem.
// definição de todos os valores inteiros
int leitura_IRLA, leitura_IRRA, leitura_IRmeioA, valor_verde, valor_branco, valor_preto;
int velo, velo_giro, velo_min; 
//define os valores booleanos 
bool leitura_IRL, leitura_IRR, leitura_IRmeio;
//define os valores decimais 
float duracao, duracao1; 


void atualizar_sensores(){
  //atualiza a leitura dos sensores digitais
  leitura_IRL = digitalRead(IResquerda); //leitura digital sensor da esquerda
  leitura_IRR = digitalRead(IRdireita); //leitra digital sensor direita
  leitura_IRmeio = digitalRead(IRmeio); //leitra digital sensor central
}

void atualizar_sensoresA(){
  //atualiza a leitura dos sensores analogicos
  leitura_IRRA = analogRead(IR_direita); //leitura analogica sensor direita
  leitura_IRLA = analogRead(IR_esquerda); //leitra analogica sensor da esquerda
}

// velocidade vai de 0 até 255
void stop(int velocidade){//parado
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
}
void frente(int velocidade){//frente
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
}
void tras(int velocidade){//trás
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);  
}
void direita(int velocidade){// direita
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
}
void esquerda(int velocidade){ // esquerda
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
}
void proprio_eixoR(int velocidade){//giro no proprio eixo pra direita
      analogWrite(IN1, 0);
      analogWrite(IN2, velocidade);
      analogWrite(IN3, velocidade);
      analogWrite(IN4, 0);
}
void proprio_eixoL(int velocidade){//giro no proprio eixo pra esquerda
      analogWrite(IN1, velocidade);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, velocidade);
}

bool verdeL(){// Lê-se o valor analógico para checar o verde
  if(leitura_IRLA < Preto && leitura_IRLA > BrancoL);
  return leitura_IRLA < Preto && leitura_IRLA > BrancoL;
}
bool verdeR(){
  if(leitura_IRRA < Preto && leitura_IRRA > BrancoR);
  return leitura_IRRA < Preto && leitura_IRRA > BrancoR;
}

float distancia(){
  //define a função que obtem o valor da distância do sensor ultrassônico HCSR04
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  // gera o pulso que faz a medição da distância
  duracao = pulseIn(echo, HIGH); //mede o tempo que demora pra o pulso sair de low para high e retorna esse valor
  return (duracao*0.0343)/2; // converte o tempo de entre low-high para centímetros
}

float distancia1(){
  //define a função que obtem o valor da distância do sensor ultrassônico, HCSR04, lateral
  digitalWrite(trig1, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig1, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW); 
  // gera o pulso que faz a medição da distância
  duracao1 = pulseIn(echo1, HIGH); //mede o tempo que demora pra o pulso sair de low para high e retorna esse valor
  return (duracao1*0.0343)/2; // converte o tempo de entre low-high para centímetros
}

void UP_servo() { //define a função que movimenta o servo garra para o angulo 90 graus relativo a ela
  garra.write(90);
}

void DOWN_servo(){ // Abaixa a garra para a posição 0 graus relativa a ela
  garra.write(0);
}

void UP_servo1(){ //define a função que movimenta para cima o servo pa
  pa.write(90);  
}

void DOWN_servo1(){ // Abaixa a pa
  garra.write(0);
}

void Giro90L(){ //giro de 90 graus esquerda
  proprio_eixoL(velo_giro);
  delay(1340);
  stop(0);
}

void Giro90R(){//giro de 90 graus direita
  proprio_eixoR(velo_giro);
  delay(1340);
  stop(0);
}

void Giro90LL(){//giro de 90 graus em relação a linha
  do {proprio_eixoL(velo); //Delay de 1340 para meia volta
  }while(leitura_IRL == 1 && leitura_IRmeio == 0 && leitura_IRR == 0);
  }

void Giro90LR(){
  do {proprio_eixoR(velo); //Delay de 1340 para meia volta
  }while(leitura_IRL == 1 && leitura_IRmeio == 0 && leitura_IRR == 0);
  }

void verifica_verde(){
  atualizar_sensoresA();
  stop(0);
  tras(velo);
  delay(100);
  atualizar_sensoresA();
  if (verdeL()){
    atualizar_sensoresA();
    stop(25);
    Giro90LL();}
  else if (verdeR()){
    atualizar_sensoresA();
    stop(25);
    Giro90LR();
  }
  else if (verdeL() && verdeR()){
    atualizar_sensoresA();
    stop(25);
    Giro90R();
    Giro90R();
    frente(velo);
  }
}


void desviar(){
  distancia1();
  Giro90L();
  do{
    frente(velo);
    }while(distancia1() < 11.5);
  Giro90R();//invertido ao primeiro()
  frente(velo);
  delay(250);//tempo pra girar 90 graus)
  do{
    frente(velo);
    }while(distancia1() < 11.5);
  delay(200);//tempo pra superar o obstaculo)
  Giro90R();
  delay(200);//virar 90 graus)
  do{
    frente(velo);
    }while(leitura_IRL == 0 || (leitura_IRmeio == 0 || leitura_IRmeio == 1) || leitura_IRR == 0);
}

void leituracentral1(){
  if(leitura_IRL == 0 && leitura_IRR == 0){
    atualizar_sensores();
    atualizar_sensoresA();
    frente(velo);
    Serial.println("frente");
  }
  else if(leitura_IRL == 1 && leitura_IRR == 1){
    atualizar_sensores();  
    atualizar_sensoresA();
    verifica_verde();
    Serial.println("verifica verde");    
  }
  else if(leitura_IRL == 0 && leitura_IRR == 1){
    atualizar_sensoresA();
    atualizar_sensores();
    verifica_verde();
    Serial.println("verifica verde");
  }
  if(leitura_IRL == 1 && leitura_IRR == 0){
    atualizar_sensoresA();
    atualizar_sensores();
    verifica_verde();
    Serial.println("verifica verde");
  }
}

void leituracentral0(){
  if(leitura_IRL == 1 && leitura_IRR == 0){ // vai para a esquerda em torno do proprio eixo
    atualizar_sensores();
    atualizar_sensoresA();
    proprio_eixoL(velo_giro);
    Serial.println("proprio_eixoL");}

  if(leitura_IRL == 0 && leitura_IRR == 1){ // vai para a direita
    atualizar_sensores(); 
    atualizar_sensoresA();
    proprio_eixoR(velo_giro);
    Serial.println("proprio_eixoR");}

  if(leitura_IRL == 0 && leitura_IRR == 0){ // vai para a frente
    atualizar_sensores();
    atualizar_sensoresA();
    frente(velo);
    Serial.println("frente");}
  if(leitura_IRL == 1 && leitura_IRR == 1){

    verifica_verde();
    Serial.println("verifica verde");
  }
}

void setup() {
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
  //pinos dos sensores de distancia sendo os trig OUTPUT e os echo INPUT
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  //pinos dos sensores IR 
  pinMode(IResquerda, INPUT);
  pinMode(IR_esquerda, INPUT);
  pinMode(IRdireita, INPUT);
  pinMode(IR_direita, INPUT);
  pinMode(IRmeio, INPUT);
  
  //biblioteca servo

  //pinos dos servos
  pinMode(Astrolabio, OUTPUT);
  pinMode(Astrolabio2, OUTPUT);

  pa.attach(Astrolabio);
  garra.attach(Astrolabio2);

  //velocidade padrão
  velo = 140; 
  velo_giro = 188;
  velo_min = 0;

  // valor preto (mentira) -> (É tudo relativo) o preto tem a leitura analógica acima de 100
  Preto = 321;
  // Valores da calibragem das cores do sensor IR direito (A ser visto no momento da calibragem)
  BrancoR = 56;
  VerdeR = 60;

  // Valores da calibragem das cores do sensor IR esquerdo (A ser visto no momento da calibragem)
  BrancoL = 59;
  VerdeL = 55;

  frente(velo);
  
  garra.write(0);
  pa.write(0);
}

void loop() {
  atualizar_sensores();
  atualizar_sensoresA();
if(leitura_IRmeio == 1){ //Código para seguir linha inicial + situações de curvas
  leituracentral1();
} 

if(leitura_IRmeio == 0){ //curvas fora da encruzilhada
  atualizar_sensores();
  leituracentral0();
  }
  
distancia();
if(distancia() < 11.5 && distancia > 0){
  desviar();
}

//Imprimindo as leituras dos sensores para checagem de leitura e calibragem
/*if (verdeL() == true){
  Serial.println("VerdeL");
  delay(250);
} else if(verdeR() == true){
  Serial.println("VerdeR");
  delay(250);
} else {
  Serial.println("Sem verde");
  delay(250);
}
  Serial.print("Leitura IRR: ");
  Serial.println(leitura_IRR);
  delay(250);
  Serial.print("Leitura IRmeio: ");
  Serial.println(leitura_IRmeio);
  delay(250);
  Serial.print("Leitura IRL: ");
  Serial.println(leitura_IRL);
  delay(250);
  distancia1();
  Serial.print("Leitura Distancia1: ");
  Serial.println(distancia1());
  delay(250);
  distancia();
  Serial.print("Leitura Distancia: ");
  Serial.println(distancia());
  delay(250);
  Serial.print("Leitura IRRA: ");
  Serial.print(leitura_IRRA);
  delay(250);
  Serial.print("   |   Leitura IRLA: ");
  Serial.println(leitura_IRLA);
  delay(250);
*/
}