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

// Time tracking for debouncing (stores last time each button was pressed)
unsigned long lastPressB1 = 0;
unsigned long lastPressB2 = 0;
unsigned long lastPressB3 = 0;
unsigned long lastPressB4 = 0;

//variables to manage the led fading LS in the initial state
int fadeAmount = 1;
int currIntensity = 100; 
bool fadingUp = true;

int target; //number to dial in each round
int score = 0;
int T1 = 20000;
int level = 1;
float F = 0.9;

unsigned long startTime;
const unsigned long debounceDelay = 50; // Debounce delay (time in milliseconds to wait before accepting a new press)

bool stopTheGame = false;
bool startGame = false;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

void setup() {
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
  enableInterrupt(B2, wakeUp, RISING);
  enableInterrupt(B3, wakeUp, RISING);
  enableInterrupt(B4, wakeUp, RISING);

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
    //fading in and out
    analogWrite(LS, currIntensity);
    if (fadingUp) {
      currIntensity += fadeAmount;
      if (currIntensity >= 255) {
        fadingUp = false;
        currIntensity = 255;
      }
    } else {
      currIntensity -= fadeAmount;
      if (currIntensity <= 0) {
        fadingUp = true;
        currIntensity = 0;
      }
    }

    lcd.begin(20,4);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to GMB!");
    lcd.setCursor(0, 1);
    lcd.print("Press B1 to Start");

    //after pressing b1 you can start the game then all variables are set
    //startGame became true
    if (digitalRead(B1) == HIGH) { 

      analogWrite(LS, 0); 

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

      switch(level) {
        case 1: F = 0.9; break;
        case 2: F = 0.7; break;
        case 3: F = 0.5; break;
        case 4: F = 0.3; break;
      }

    } else {
      //if 10 seconds pass without the B1 key is pressed arduino goes in deep sleeping
      if (millis() - startTime >= 10000) {

        lcd.clear();
        lcd.noBacklight();

        Serial.flush();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();

        //set the value of startGame to false to be sure that it falls into the while and starts fading LS again, 
        startGame = false;
        startTime = millis();
      }
    }
  }

  //At each loop cycle we check whether the number was entered correctly or if the maximum time has passed
  if(won(sum())){

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GOOD! Score: ");
    lcd.print(score);

    //reset buttons and leds
    resetButtons();
    delay(500);
    resetLeds();

    //re-set the variables for the next round and show the new target
    target = random(0,16);
    startTime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(target);

  }else if(millis() - startTime >= T1 ){

    digitalWrite(LS, HIGH);
    delay(1000);
    digitalWrite(LS, LOW);

    resetLeds();
    resetButtons();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("Final Score: ");
    lcd.print(score);
    delay(2000);
    lcd.clear();
    delay(10000);

    startGame = false;
    startTime = millis();
    score = 0;
    T1 = 20000;
    int potValue = analogRead(POT); 
    level = map(potValue, 0, 1023, 1, 4);

    switch(level) {
      case 1: F = 0.9; break;
      case 2: F = 0.7; break;
      case 3: F = 0.5; break;
      case 4: F = 0.3; break;
    }
  }
}

//function that manages the on and off of the led by means of the appropriate buttons, 
//for the composition of the number in track
void ledManagement(){
  unsigned long currentTime = millis();
  if (digitalRead(B1) == HIGH && (currentTime - lastPressB1 > debounceDelay) && startGame) {
    lastPressB1 = currentTime;
    pressed_8 = !pressed_8;
    digitalWrite(L1, pressed_8 ? HIGH : LOW);
  }
  if (digitalRead(B2) == HIGH && (currentTime - lastPressB2 > debounceDelay) && startGame) {
    lastPressB2 = currentTime;
    pressed_4 = !pressed_4;
    digitalWrite(L2, pressed_4 ? HIGH : LOW);
  }
  if (digitalRead(B3) == HIGH && (currentTime - lastPressB3 > debounceDelay) && startGame) {
    lastPressB3 = currentTime;
    pressed_2 = !pressed_2;
    digitalWrite(L3, pressed_2 ? HIGH : LOW);
  }
  if (digitalRead(B4) == HIGH && (currentTime - lastPressB4 > debounceDelay) && startGame) {
    lastPressB4 = currentTime;
    pressed_1 = !pressed_1;
    digitalWrite(L4, pressed_1 ? HIGH : LOW);
  }
}

//function to quickly calculate the value reached by variables that track the pressed buttons, 
//modified only in the above function
int sum() {
  int cont = 0;
  if (pressed_1) cont += 1;
  if (pressed_2) cont += 2;
  if (pressed_4) cont += 4;
  if (pressed_8) cont += 8;
  return cont;
}

//boolean function to determine whether or not the number is entered correctly
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
