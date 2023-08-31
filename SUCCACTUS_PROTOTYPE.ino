//teste codígo completo SC3 Frankstein

//#include <Arduino.h> //intelisense pra .ino
//#include <Wire.h>
#include <Adafruit_APDS9960.h>

//pinos do HCSRO04
#define TRIGGER_PIN 28
#define ECHO_PIN 26

//pinos do primeiro sensor IR
#define led_diodo1 22
#define led_preto1 9 //provavelmente usar um pino digital pros 2 sensores IR 

//pinos do primeiro sensor IR
#define led_diodo2 24
#define led_preto2 8 //provavelmente usar um pino digital pros 2 sensores IR 

// Motor A connections
#define motorA1 4
#define motorA2 5
// Motor B connections
#define motorB1 6 // mudar
#define motorB2 7 //mudar

int sensor_IR1;
int sensor_IR2;

float duracao;
Adafruit_APDS9960 apds;

bool isGreenRTrue, isGreenLTrue;


float distancia(){

  //define a função que obtem o valor da distância do sensor de distância HCSR04
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER_PIN, HIGH); 
  delayMicroseconds(10); 

  digitalWrite(TRIGGER_PIN, LOW); 

  // gera o pulso que faz a medição da distância

  duracao = pulseIn(ECHO_PIN, HIGH); //mede o tempo que demora pra o pulso sair de low para high e retorna esse valor
  return (duracao*.0343)/2; // converte o tempo de entre low-high para centímetros
}

void setup() {
  // SERIAL INICIADO
  Serial.begin(9600);
  //PINOS DO SENSOR ULTRASSÔNICO
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //PINOS DOS SENSORES INFRAVERMELHO   
  pinMode(led_preto1, OUTPUT);
  pinMode(led_diodo1, INPUT);

  pinMode(led_preto2, OUTPUT);
  pinMode(led_diodo2, INPUT);

  //INICIA O APDS
  if (!apds.begin()) {
    Serial.println("No se pudo inicializar el APDS-9960. Compruebe la conexión.");
    while (1);
  }

  Serial.println("APDS-9960 listo para recibir comandos.");
  
  //HABILITA O SENSOR DE COR
  apds.enableColor(true);
}

void movimento(int direcao, int velocidade){  // velocidade vai de 0 até 255
  switch (direcao){
    case 0://parado
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
      break;
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
 /*
void identificarVerde(bool Verde){
  if(green > blue && green > red){
    Verde = true;
    }
  else{
    Verde = false;
    }
}
*/
void loop() {
  movimento(1, 100);
  /*
  if (apds.getColorData(&red, &green, &blue, &clear)) {
    Serial.println("Error al leer los valores de color");
    return;
  }
  // Leer los valores de color
  uint16_t red, green, blue, clear;
  apds.getColorData(&red, &green, &blue, &clear);
  //apds.setLED(apds9960LedDrive_t drive, apds9960LedBoost_t boost);
  uint16_t colorTemperature =  apds.calculateColorTemperature(red, green, blue);
  //Serial.print(apds.calculateLux(red, green, blue)+"");
  //Serial.print(colorTemperature+"");

  sensor_IR1 = analogRead(led_diodo1);
  sensor_IR2 = analogRead(led_diodo2);
  //
  if (sensor_IR1 && sensor_IR2){
    //caso tudo preto, vai pra tras e vê se tem verde
    movimento(2, 100);

    //esquerdista looking for VERDINHO
    movimento(3, 50);
    delay(1000);
    movimento(0, 0);
    identificarVerde(isGreenLTrue);
    
    delay(1000);

    movimento(4, 50);
    delay(1000);

    //conservador looking for VERDINHO

    movimento(4, 50);
    delay(1000);
    movimento(0, 0);
    identificarVerde(isGreenRTrue);

    delay(1000);

    if(isGreenRTrue && isGreenRFalse){
      movimento(1, 200);

    }
    else if(isGreenRTrue){
      movimento(4, 50);
      movimento(1, 200);
      
    }
    else if(isGreenLTrue){
      movimento(3, 50);
      movimento(1, 200);
    }
    else{
      movimento(1, 200);

    }
  }
  //procurar verde na esquerda
  else if(sensor_IR1){
    movimento(2, 100);

    movimento(3, 50);
    movimento(0, 0);
    identificarVerde();
    if(isGreenLTrue){

    }else{
      movimento(4, 50);
    }

  }
  //procurar verde na direita
  else if(sensor_IR2){
    movimento(2, 100);

    movimento(4, 50);
    movimento(0, 0);
    identificarVerde();
    if(isGreenRTrue){

    }else{
      movimento(3, 50);
    }

  }
  else{
    movimento(1, 200);

  }

  


  
  
  

  delay(2000);
  */
}
