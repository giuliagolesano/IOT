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

int target;
int score = 0;
int T1 = 20000;
unsigned long startTime;
bool startGame = false;

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

  //NON FUNZIONA IL RISVEGLIO DALLA SLEEP
  attachInterrupt(digitalPinToInterrupt(B1), wakeUp, RISING);
  startTime = millis();

  while(!startGame){
    digitalWrite(LS, HIGH);
    delay(500);
    digitalWrite(LS, LOW);
    delay(500);
    Serial.println("B1 NOT PRESSED");
    if (digitalRead(B1) == HIGH) { 
        startGame = true;
	      target = random(0,16);
        Serial.println("B1 PRESSED");
    } else {
      if (millis() - startTime >= 10000) {
          Serial.println("SLEEPING");
          enterDeepSleep();
      }
    }
  }

 Timer1.initialize(1000000); 
 Timer1.attachInterrupt(ledManagement);
}

void loop() {
  Serial.println("...");
}

void ledManagement(){
  Serial.println("GO!");
  Serial.println(target);
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

  Serial.println(digitalRead(B1));
  Serial.println(digitalRead(B2));
  Serial.println(digitalRead(B3));
  Serial.println(digitalRead(B4));

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
        return true;
    } else {
        return false;
    }
}

void resetGame() {
    resetButtons();
    target = random(0,16);
}

void resetButtons(){
  pressed_1 = false;
  pressed_2 = false;
  pressed_4 = false;
  pressed_8 = false;
}

void wakeUp(){}

void initialState(){
    /*
    lcd.clear();
    lcd.print("Welcome to GBM!");
    lcd.print("Press B1 to Start");
    */
    digitalWrite(LS, HIGH);
    delay(500);
    digitalWrite(LS, LOW);
    delay(500);

    if (digitalRead(B1) == HIGH) { 
        startGame = true;
	      target = random(0,16);
        return;
    } else {
        if (millis() - startTime >= 10000) {
            enterDeepSleep();
        }
    }
}

void enterDeepSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    Serial.println("wake up");
    sleep_disable();
}

