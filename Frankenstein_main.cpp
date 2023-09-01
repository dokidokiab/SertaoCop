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
#define IRmeio A0 //não é necessária leitura analogica do sensor IR 
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

int Preto, BrancoR, VerdeR, BrancoL, VerdeL; //
// Valores a serem definidos na mão no momento da calibragem.
// definição de todos os valores
// define os valores inteiros 
int distanciaF, deslocamento;
int leitura_IRLA, leitura_IRRA, leitura_IRmeioA, valor_verde, valor_branco, valor_preto;
int velo, velo_giro, velo_min; 
bool leitura_IRL, leitura_IRR, leitura_IRmeio; //define os valores booleanos 
float duracao, duracao1; //define os valores decimais 

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
void stop(int espera){//parado
      analogWrite(IN1, 0);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
      delay(espera);
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

bool verdeL(){// valor do verde = 47 e 48 no teste
  return leitura_IRLA < Preto && leitura_IRLA > BrancoL;
}
bool verdeR(){ // Valor do verde
  return leitura_IRRA < Preto && leitura_IRRA > BrancoR;
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

float distancia1(){
  //define a função que obtem o valor da distância do sensor de distância HCSR04
  digitalWrite(trig1, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig1, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW); 
  // gera o pulso que faz a medição da distância
  duracao1 = pulseIn(echo1, HIGH); //mede o tempo que demora pra o pulso sair de low para high e retorna esse valor
  return (duracao1*.0343)/2; // converte o tempo de entre low-high para centímetros
}

void UP_servo() {
  //define a função que movimenta o servo 
  garra.write(90);
}

void DOWN_servo(){ // Abaixa a garra
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
  }while((leitura_IRL != 0) && (leitura_IRmeio != 1) && (leitura_IRR != 1) );}

void Giro90LR(){
  do {proprio_eixoR(velo); //Delay de 1340 para meia volta
  }while((leitura_IRL != 0) && (leitura_IRmeio != 1) && (leitura_IRR != 1) );}

void verifica_verde(){
  atualizar_sensores();
  stop(250);
  tras(velo);
  if (leitura_IRLA < valor_verde){
    stop(250);
  } 
}

void desviar(){
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
  //pinos dos sensores de distancia  
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
  UP_servo();
  

  //velocidade padrão
  velo = 90; //MÍNIMA
  velo_giro = 150;
  velo_min = 0;

  // valor preto (mentira)
  Preto = 100;
  // Valores da calibragem das cores do sensor IR direito
  BrancoR = 46;
  VerdeR = 47;

  // Valores da calibragem das cores do sensor IR esquerdo
  BrancoL = 50;
  VerdeL = 52;
}

void loop() {
  atualizar_sensores();

  if(leitura_IRmeio == 1 && leitura_IRL == 0 && leitura_IRR == 0){ //Código para seguir linha inicial
      frente(velo);
  }
  else if(leitura_IRmeio == 1 && (leitura_IRL == 1 || leitura_IRR == 1)){ //cuvas encruzilhadas
    atualizar_sensores();
    stop(250);
    if(verdeL()){
      stop(250);
      proprio_eixoL(velo_giro);}
    else if(verdeR()){
      stop(250);
      proprio_eixoR(velo_giro);}
    else if((leitura_IRL == 1) && (leitura_IRR == 0)){ // vai para a esquerda
      //Serial.println("esquerda");
      stop(250);
      proprio_eixoL(velo_giro);}
    else if((leitura_IRL == 0) && (leitura_IRR == 1)){ // vai para a direita
      //Serial.println("direita");
      stop(250);
      proprio_eixoR(velo_giro);}
    else if((leitura_IRL == 0) && (leitura_IRR == 0)){
      frente(velo);}
    else if((leitura_IRL == 1) && (leitura_IRR == 1)){
      stop(250);
      tras(velo);
      delay(50);
      atualizar_sensores();
      if((leitura_IRL == 1) && (leitura_IRR == 0)){
        stop(250);
        Giro90L();
      }
      else if((leitura_IRL == 0) && (leitura_IRR == 1)){
        stop(250);
        Giro90R();
      }
      else if((leitura_IRL == 1) && (leitura_IRR == 1)){
        do{
          stop(250);
          proprio_eixoL(velo_giro);
        } while((leitura_IRL == 1) && (leitura_IRmeio == 0) && (leitura_IRR == 1));
      }
    }
    //else{
    //  frente(velo);
    //}
    atualizar_sensores();
    }
  
  if(leitura_IRmeio == 0){ //curvas fora da encruzilhada
    //delay(250);
    atualizar_sensores();
    if((leitura_IRL == 1) && (leitura_IRR == 0)){ // vai para a esquerda em torno do proprio eixo
      //Serial.println("esquerda");
      proprio_eixoL(velo_giro);} 
    else if((leitura_IRL == 0) && (leitura_IRR == 1)){ // vai para a direita 
      //Serial.println("direita");
      proprio_eixoR(velo_giro);}
    else if((leitura_IRL == 0) && (leitura_IRR == 0)){ // vai para a frente 
      //Serial.println("frente");
      frente(velo_giro);}
    atualizar_sensores();}

//Imprimindo as leituras dos sensores
    Serial.print("Leitura IRRA: ");
    Serial.print(leitura_IRRA);
    Serial.println(" | ");
    delay(250);
    Serial.print("Leitura IRLA: ");
    Serial.print(leitura_IRLA);
    Serial.println(" | ");
    delay(250);
    Serial.print("Leitura IRR: ");
    Serial.print(leitura_IRR);
    Serial.println(" | ");
    delay(250);
    Serial.print("Leitura IRmeio: ");
    Serial.print(leitura_IRmeio);
    Serial.println(" | ");
    delay(250);
    Serial.print("Leitura IRL: ");
    Serial.print(leitura_IRL);
    Serial.println(" | ");
    delay(250);
    distancia1();
    Serial.print("Leitura Distancia1: ");
    Serial.print(distancia1());
    Serial.println(" | ");
    delay(250);
    distancia();
    Serial.print("Leitura Distancia: ");
    Serial.println(distancia());
    delay(250);
  
}