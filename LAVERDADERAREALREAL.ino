#include <SoftwareSerial.h>

int IN1 = 8;     
int IN2 = 9;     
int IN3 = 10;     
int IN4 = 11;
int s = 0;   
int pulsador = 5;
int demora = 2;

int relay = 2;

int paso [8][4]
{
  {0, 0, 1, 1},
  {0, 0, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {1, 0, 0, 0},
  {1, 0, 0, 1},
  {0, 0, 0, 1},
};

void setup(){
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(relay, OUTPUT); 
  Serial.begin(9600); 
  pinMode(pulsador,INPUT_PULLUP);
}

char Incoming_value;

void motorCC(){
  digitalWrite(relay, HIGH); 
  Serial.println("Relay accionado");
  delay(500);          
  
  digitalWrite(relay, LOW); 
  Serial.println("Relay no accionado");
  delay(500);           
}

void repartir(int cantCartas, int cantJugadores) {
  digitalWrite(relay, HIGH); 
  Serial.println("Relay accionado");
  delay(500);
  digitalWrite(relay, LOW); 
  Serial.println("Relay no accionado");
  delay(500); 
  int giros = cantCartas * cantJugadores - 1;
  float pasosG = 512 / cantJugadores;

  for(int n = 0 ; n < giros ; n++){
    for(int i = 0 ; i < pasosG ; i++){
      for(int j = 0 ; j < 8 ; j++){
        digitalWrite(IN1, paso[j][0]);
        digitalWrite(IN2, paso[j][1]);
        digitalWrite(IN3, paso[j][2]);
        digitalWrite(IN4, paso[j][3]);
        delay(demora);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }
    }
    delay(1000);
    motorCC();
  } 
  if (pulsador == HIGH ) {
  Serial.println("aca lol");
  digitalWrite(relay, HIGH); 
  delay(500);
  digitalWrite(relay, LOW); 
  delay(500); 
  int giros = cantCartas * cantJugadores - 1;
  float pasosG = 512 / cantJugadores;

  for(int n = 0 ; n < giros ; n++){
    for(int i = 0 ; i < pasosG ; i++){
      for(int j = 0 ; j < 8 ; j++){
        digitalWrite(IN1, paso[j][0]);
        digitalWrite(IN2, paso[j][1]);
        digitalWrite(IN3, paso[j][2]);
        digitalWrite(IN4, paso[j][3]);
        delay(demora);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }
    }
    delay(1000);
    motorCC();
  }
  pulsador = LOW;
  }
}
  


int inputs[2]; // Array que almacena los datos enviados
// El primer elemento es el juego y el segundo la cant de jugadores. ["Truco", "2"]
int cont = 0;

void loop(){
  int estado = !digitalRead(pulsador);
  Serial.println(estado);
  if(estado == HIGH){
    repartir(inputs[0], inputs[1]);
  }
  if(Serial.available()>0) {
    if(Incoming_value == '/'){
    exit(0);
  }
    if (cont == 2) {
    repartir(inputs[0], inputs[1]);
    cont = 0;
   }
   Incoming_value = Serial.read();
   inputs[cont] = Incoming_value - '0';
   cont++;
   
   Serial.println(Incoming_value); 
}
}
