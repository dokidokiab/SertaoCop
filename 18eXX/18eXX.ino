#define motorA1  11
#define motorA2  10
#define motorB1  6
#define motorB2  5
#define sensor_infra1 2
#define sensor_infra2 3
#define sensor_infra3 4 
int velocidade = 100;
int teste = 0;
int sensor1;
int sensor2;
int sensor3;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(sensor_infra1, INPUT);
  pinMode(sensor_infra2, INPUT);
  pinMode(sensor_infra3, INPUT);
  Serial.begin(9600);
  delay(1500); // tempo parado antes de funcionar o código
}

void loop(){
  sensor1 = digitalRead(sensor_infra1);
  sensor2 = digitalRead(sensor_infra2);
  sensor3 = digitalRead(sensor_infra3);
  //sensor de distancia


  delay(10); // delay dos sensores 10
  if(sensor1 == 0 && sensor2 == 1 && sensor3 == 0){ // isso permite o robô seguir a linha preta indo para a frente
    teste = 0;
    movimento(1, velocidade);
  }else if((sensor1 == 1 && sensor2 == 0 && sensor3 == 0) || (sensor1 == 1 && sensor2 == 1 && sensor3 == 0)){ //isso permite o robô corrigir o movimento para a esquerda 
    teste = 1;
    movimento(6, int(velocidade));
  }else if((sensor1 == 0 && sensor2 == 0 && sensor3 == 1) || (sensor1 == 0 && sensor2 == 1 && sensor3 == 1)){ //isso permite o robô corrigir o movimento para a direita
    teste = -1;
    movimento(5, velocidade);
  }
  
}

void movimento(int direcao, int velocidade){  // velocidade vai de 0 até 255
  float p = 0.85; 

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
    case 2://ré
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
      analogWrite(motorB2, int(velocidade * p));
      break;
    case 6://giro no proprio eixo pra direita
      analogWrite(motorA1, 0);
      analogWrite(motorA2, int(velocidade*p));
      analogWrite(motorB1, velocidade);
      analogWrite(motorB2, 0);
      break;
      }
}
