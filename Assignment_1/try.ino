#include <avr/sleep.h>
#include <TimerOne.h>
//#include <LiquidCrystal.h>

#define L4 11 //1
#define L3 2 //2
#define L2 3 //4
#define L1 4 //8
#define LS 9 
#define POT A3
#define B4 5
#define B3 6
#define B2 7
#define B1 8

bool pressed_1 = false;
bool pressed_2 = false;
bool pressed_4 = false;
bool pressed_8 = false;

int target;
int score = 0;
int T1 = 20000;
unsigned long startTime;
bool startGame = false;
int level = 1;
float F = 0.9;
bool stopTheGame = false;

//LiquidCrystal lcd();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //lcd.begin(16,2);

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

  //NON FUNZIONA IL RISVEGLIO DALLA SLEEP
  attachInterrupt(digitalPinToInterrupt(B1), wakeUp, RISING);
  startTime = millis();

  /*
  lcd.clear();
  lcd.print("Welcome to GMB!");
  lcd.setCursor(0, 1);  // Move to second line
  lcd.print("Press B1 to Start");
  */

  while(!startGame){
    digitalWrite(LS, HIGH);
    delay(500);
    digitalWrite(LS, LOW);
    delay(500);
    if (digitalRead(B1) == HIGH) { 
      startGame = true;
      target = random(0,16);
      Serial.println("Target: ");
      Serial.println(target);

      int potValue = analogRead(POT); 
      level = map(potValue, 0, 1023, 1, 4);
      delay(2000);
      Serial.println("level: ");
      Serial.println(level);
      switch(level) {
        case 1: F = 0.9; break;
        case 2: F = 0.7; break;
        case 3: F = 0.5; break;
        case 4: F = 0.3; break;
      }
      Serial.println("difficulty: ");
      Serial.println(F);
      Serial.println("time: ");
      Serial.println(T1);
      delay(1000);
      /*
      lcd.clear();
      lcd.print("Level: ");
      lcd.print(level);
      lcd.setCursor(0, 1);
      lcd.print("Go!");
      delay(2000);
      */

    } else {
      if (millis() - startTime >= 10000) {
          Serial.println("sleeping");
          enterDeepSleep();
      }
    }
  }
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(ledManagement);
}

void loop() {
  if(stopTheGame == false){
    if(won(sum())){
      /*
      lcd.clear();
      lcd.print("GOOD! Score: ");
      lcd.print(score);
      */
      Serial.println("GOOD, SCORE: ");
      Serial.println(score);
      resetButtons();
      delay(500);
      resetLeds();
      target = random(0,16);
      Serial.println("Target: ");
      Serial.println(target);
      startTime = millis();
    }else if(millis() - startTime >= T1 ){
      /*
      lcd.clear();
      lcd.print("Game Over!");
      lcd.setCursor(0, 1); 
      lcd.print("Score: ");
      lcd.print(score);
      delay(10000);
      */
      Serial.println("time over! ");
      stopTheGame = true;
      resetButtons();
    }
  }else{
    Serial.println("you cant play");
  }
}

void ledManagement(){
  /*
  lcd.clear();
  lcd.print("Target: ");
  lcd.print(target);
  */
  if(digitalRead(B1) == HIGH){
    if(pressed_8){
      digitalWrite(L1, LOW);
    }else{
      digitalWrite(L1, HIGH);
    }
    pressed_8 = !pressed_8;
  }
  if(digitalRead(B2) == HIGH){
    if(pressed_4){
      digitalWrite(L2, LOW);
    }else{
      digitalWrite(L2, HIGH);
    }
    pressed_4 = !pressed_4;
  }
  if(digitalRead(B3) == HIGH){
    if(pressed_2){
      digitalWrite(L3, LOW);
    }else{
      digitalWrite(L3, HIGH);
    }
    pressed_2 = !pressed_2;
  }
  if(digitalRead(B4) == HIGH){
    if(pressed_1){
      digitalWrite(L4, LOW);
    }else{
      digitalWrite(L4, HIGH);
    }
    pressed_1 = !pressed_1;
  }
}

int sum() {
  int cont = 0;
  if (pressed_1) cont += 1;
  if (pressed_2) cont += 2;
  if (pressed_4) cont += 4;
  if (pressed_8) cont += 8;
  return cont;
}

bool won(int cont) {
  if (cont == target) {
    score += 100;
    T1 = T1 * F;
    Serial.println("you have second: ");
    Serial.println(T1);
    return true;
  } else {
    return false;
  }
}

void resetButtons(){
  pressed_1 = false;
  pressed_2 = false;
  pressed_4 = false;
  pressed_8 = false;
}

void resetLeds(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
}

void wakeUp(){
  while(!startGame){
    digitalWrite(LS, HIGH);
    delay(500);
    digitalWrite(LS, LOW);
    delay(500);
    if (digitalRead(B1) == HIGH) { 
      startGame = true;
      target = random(0,16);
      Serial.println("Target: ");
      Serial.println(target);

      int potValue = analogRead(POT); 
      level = map(potValue, 0, 1023, 1, 4);
      delay(5000);
      Serial.println("level: ");
      Serial.println(level);
      switch(level) {
        case 1: F = 0.9; break;
        case 2: F = 0.7; break;
        case 3: F = 0.5; break;
        case 4: F = 0.3; break;
      }
      Serial.println("difficulty: ");
      Serial.println(F);
      Serial.println("time: ");
      Serial.println(T1);
      delay(1000);
      /*
      lcd.clear();
      lcd.print("Level: ");
      lcd.print(level);
      lcd.setCursor(0, 1);
      lcd.print("Go!");
      delay(2000);
      */
    }
  }
}

void enterDeepSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}


