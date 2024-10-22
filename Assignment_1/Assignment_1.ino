#include <avr/sleep.h>
#include <TimerOne.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>

#define L4 11 //binary value 1
#define L3 2 //binary value 2
#define L2 3 //binary value 4
#define L1 4 //binary value 8
#define LS 9 //red led that pulse in the initial and lost state
#define POT A3 //potentiometer for the level
#define B4 5 //button for the binary value 1
#define B3 6 //button for the binary value 2
#define B2 7 //button for the binary value 4
#define B1 8 //button for the binary value 8

//variables that keep track of the LEDs on to facilitate the sum
bool pressed_1 = false; 
bool pressed_2 = false;
bool pressed_4 = false;
bool pressed_8 = false;

int fadeAmount;
int currIntensity;
int target;
int score = 0;
int T1 = 20000;
unsigned long startTime;
bool startGame = false;
int level = 1;
float F = 0.9;
bool stopTheGame = false;
bool oneSleep = false;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

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
  enableInterrupt(B1, wakeUp, RISING);
  startTime = millis();
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(ledManagement);
}

void loop() {
  //the initialization state is identified by the false startgame variable
  //until it is possible to start rounds
  while(startGame == false){

    /*
    analogWrite(LS, currIntensity);   
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
      fadeAmount = -fadeAmount ; 
    }     
    delay(15);  */
    digitalWrite(LS, HIGH);
    delay(500);
    digitalWrite(LS, LOW);
    delay(500);

    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to GMB!");
    lcd.setCursor(0, 1);
    lcd.print("Press B1 to Start");

    //after pressing b1 you can start the game then all variables are set
    //startGame became true
    if (digitalRead(B1) == HIGH) { 

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Go!");
      delay(1000);

      startGame = true;
      startTime = millis();
      target = random(0,16);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(target);

      int potValue = analogRead(POT); 
      level = map(potValue, 0, 1023, 1, 4);
      delay(2000);
      switch(level) {
        case 1: F = 0.9; break;
        case 2: F = 0.7; break;
        case 3: F = 0.5; break;
        case 4: F = 0.3; break;
      }
    } else {
      //onesleep represents whether or not sleep has already occurred, 
      //which, according to the specifications, occurs only once
      //millis() - startTime represents the time since the start of the programme
      if (millis() - startTime >= 10000 && oneSleep == false) {
        lcd.clear();
        lcd.noBacklight();
        oneSleep = true;
        Serial.flush();
        delay(1000);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        //set the value of startGame to false to be sure that it falls into the while and starts fading LS again, 
        //also sure that it will not go into sleep because onesleep is set to true
        startGame = false;
      }
    }
    delay(1000);
  }

  //once lost, the possibility to make new rounds is blocked by stopTheGame variable, 
  //if it is set to true, no more allows to establish any result
  if(stopTheGame == false){
    if(won(sum())){

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GOOD! Score: ");
      lcd.print(score);

      resetButtons();
      delay(500);
      resetLeds();
      target = random(0,16);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(target);

      startTime = millis();
    }else if(millis() - startTime >= T1 ){
      digitalWrite(LS, HIGH);
      delay(1000);
      digitalWrite(LS, LOW);
      resetLeds();


      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over!");
      lcd.setCursor(0, 1); 
      lcd.print("Score: ");
      lcd.print(score);
      delay(5000);
      lcd.clear();
      lcd.noBacklight();

      stopTheGame = true;
      resetButtons();
    }
  }
}

void ledManagement(){
  if (digitalRead(B1) == HIGH && startGame) {
      digitalWrite(L1, pressed_8 ? LOW : HIGH);
      pressed_8 = !pressed_8;
  }
  if (digitalRead(B2) == HIGH) {
      digitalWrite(L2, pressed_4 ? LOW : HIGH);
      pressed_4 = !pressed_4;
  }
  if (digitalRead(B3) == HIGH) {
      digitalWrite(L3, pressed_2 ? LOW : HIGH);
      pressed_2 = !pressed_2;
  }
  if (digitalRead(B4) == HIGH) {
      digitalWrite(L4, pressed_1 ? LOW : HIGH);
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

void wakeUp() {}