#include <avr/sleep.h>
#include <TimerOne.h>

#define L1 11 //1
#define L2 2 //2
#define L3 3 //4
#define L4 4 //8
#define LS 9 
#define POT 10
#define B1 5
#define B2 6
#define B3 7
#define B4 8

bool pressed_1 = false;
bool pressed_2 = false;
bool pressed_4 = false;
bool pressed_8 = false;

int cont = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(LS, OUTPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  
  int target = number();
  Serial.print(target);

 Timer1.initialize(1000000); 
 Timer1.attachInterrupt(ledManagement);
}

void loop() {
  Serial.println(sum());
}

int number(){
  return random(0, 15);
}

void ledManagement(){
    if(digitalRead(B1) == HIGH){
    if(pressed_1){
      digitalWrite(L1, LOW);
    }else{
      digitalWrite(L1, HIGH);
    }
    pressed_1 = !pressed_1;
  }
  if(digitalRead(B2) == HIGH){
    if(pressed_2){
      digitalWrite(L2, LOW);
    }else{
      digitalWrite(L2, HIGH);
    }
    pressed_2 = !pressed_2;
  }
    if(digitalRead(B3) == HIGH){
    if(pressed_4){
      digitalWrite(L3, LOW);
    }else{
      digitalWrite(L3, HIGH);
    }
    pressed_4 = !pressed_4;
  }
    if(digitalRead(B4) == HIGH){
    if(pressed_8){
      digitalWrite(L4, LOW);
    }else{
      digitalWrite(L4, HIGH);
    }
    pressed_8 = !pressed_8;
  }
}

int sum(){
  int cont = 0;
  if(pressed_1){
    cont = cont + 1;
  }
  if(pressed_2){
    cont = cont + 2;
  }
  if(pressed_4){
    cont = cont + 4;
  }
  if(pressed_8){
    cont = cont + 8;
  }
  return cont;
}




