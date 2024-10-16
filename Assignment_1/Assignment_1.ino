#include <avr/sleep.h>
#include <TimerOne.h>

#define L1 1 //1
#define L2 2 //2
#define L3 3 //4
#define L4 4 //8
#define LS 9 
#define POT 10
#define B1 5
#define B2 6
#define B3 7
#define B4 8
//LiquidCrystal lcd();

int pressed_1 = 0; //off
int pressed_2 = 0; //off
int pressed_4 = 0; //off
int pressed_8 = 0; //off
int start = 0;
int status = 0; //1 is a victory, 0 is a lose.
int scores = 0;
int time = 15000;
int f;

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
  pinMode(POT, INPUT);
  int target = number();
  //lcd.begin(16,2);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(level);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  int cont = 0;
  int t = 0;
  do{
    initialState();
    cont = cont + 1000;
    if(cont<10000){ //INVECE DI CONT USIAMO UN TIMER DELLA LIBRERIA !!
      while(digitalRead(B1) == LOW){
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
      }
      start = 1
      sleep_disable();
    }
  }while(digitalRead(B1) == LOW || start == 0);

  //lcd.print("Go!");
  scores = 0;
  //lcd.print(target);
  while(t < times){ //INVECE DI T USIAMO UN TIMER DELLA LIBRERIA!
    ledmanagement();
  }
  if(sum() == targer){
    status = 1;
  }else{
    status = 0;
  }
  message();
  */
}

//COME SI FA A FERMARE IL GIOCO?
void message(){
  if(status){
    scores = scores +  100;
    //lcd.print("GOOOD! Score: "+ scores);
    time = time - f;
  }else{
    digitalWrite(LS, HIGH);
    delay(1000);
    digitalWrite(LS, LOW);
    //lcd.print("Game Over - Final Scores" + scores);
    delay(10000);
  }
}

//function to randomically choose a number between 0 and 15
int number(){
  return random(0, 15);
}

//funtion to manage the switching the LEDs on or off
void ledManagement(){
    if(digitalRead(B1) == HIGH){
    if(pressed_1){
      digitalWrite(L1, LOW);
      pressed_1 = 0;
    }else{
      digitalWrite(L1, HIGH);
      pressed_1 = 1;
    }
  }
  if(digitalRead(B2) == HIGH){
    if(pressed_2){
      digitalWrite(L2, LOW);
      pressed_2 = 0;
    }else{
      digitalWrite(L2, HIGH);
      pressed_2 = 1;
    }
  }
    if(digitalRead(B3) == HIGH){
    if(pressed_4){
      digitalWrite(L3, LOW);
      pressed_4 = 0;
    }else{
      digitalWrite(L3, HIGH);
      pressed_4 = 1;
    }
  }
    if(digitalRead(B4) == HIGH){
    if(pressed_8){
      digitalWrite(L4, LOW);
      pressed_8 = 0;
    }else{
      digitalWrite(L4, HIGH);
      pressed_8 = 1;
    }
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

void initialstate(){
  //lcd.print("Welcome to GMB! Press B1 to Start");
  digitalWrite(LS, HIGH);
  delay(500);
  digitalWrite(LS, LOW);
  delaY(500);
}

void level(){
  //SISTEMARE I CASE IN BASE A QUALI SONO I VALORI DEL POTENZIOMETRO, VEDERE STAMPA
  //QUESTA COSA VA FATTA IN UN LOOP?
  int pot_level = analogRead(POT);
  int current;
  if (pot_level != current){
    current = pot_level;
    int intensity = map(current, 0, 1023, 0, 255);
    Serial.println(current);
    switch(pot_level){
      case 1: f=250;
        break;
      case 2: f=500;
        break;
      case 3: f=750;
        break;
      case 4: f=1000;
        break;
      default: f=250;
        break;
    }
  }
}