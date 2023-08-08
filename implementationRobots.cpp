#include <Arduino.h>

// Motor connections
int enA = 3;  // Enable pin for Motor A
int in1 = 4;  // Input 1 pin for Motor A
int in2 = 5;  // Input 2 pin for Motor A
int enB = 6;  // Enable pin for Motor B
int in3 = 7;  // Input 1 pin for Motor B
int in4 = 8;  // Input 2 pin for Motor B

bool estaRodando = false;

void setup() {
  // Set all the motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Move the car forward
  moverFrente();
  delay(2000); // Delay for 2 seconds

  // Stop the car
  pararCarro();
  delay(1000); // Delay for 1 second

  // Move the car backward
  moverTras();
  delay(2000); // Delay for 2 seconds

  // Stop the car
  pararCarro();
  delay(1000); // Delay for 1 second

  // Turn the car left
  viraEsquerda();
  delay(2000); // Delay for 2 seconds

  // Stop the car
  pararCarro();
  delay(1000); // Delay for 1 second

  // Turn the car right
  viraDireita();
  delay(2000); // Delay for 2 seconds

  // Stop the car
  pararCarro();
  delay(1000); // Delay for 1 second
}

void passarObstaculo(){
    //Jeito mais fácil: Mover 18cm pra direita/esquerda depois 
    //pra frente, e então esquerda/direita voltando pra linha
    //e virando pra frente o robo novamente. Basicamente andar pelos
    //ladrilhos(não muito recomendável, pois o robô pode passar direto
    //caso a linha após tenha virado de direção. )

    //Jeito mais dificil: O robô vê o obstáculo e vira para esquerda/direita
    //anda um pouco, e vira a frente novamente pra conferir se o obstáculo
    //estiver lá ainda, se não estiver ele anda pra frente enquanto vira pra verificar
    //da mesma forma. e faz os movimentos de terminar usualmente, mas verificando.

    
}

// Function to move the car forward
void moverFrente() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

// Function to move the car backward
void moverTras() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

// Function to stop the car
void pararCarro() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

// Function to turn the car left
void viraEsquerda() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

// Function to turn the car right
void viraDireita() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}
