#include <LiquidCrystal.h>
#include <Wire.h>

#define GREEN_P 13
#define YELLOW_P 12
#define RED_P 11
#define BUTTON 2
#define GREEN 10
#define YELLOW 9
#define RED 8

void setup() {

  // put your setup code here, to run once:
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
    pinMode(GREEN_P, OUTPUT);
  pinMode(YELLOW_P, OUTPUT);
  pinMode(RED_P, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  digitalWrite(GREEN, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN_P, LOW);
  digitalWrite(YELLOW_P, LOW);
  digitalWrite(RED_P, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON) == HIGH){
    delay(1000);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    delay(2000);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(RED_P, LOW);
    digitalWrite(GREEN_P, HIGH);
    delay(3000);
    digitalWrite(GREEN_P, LOW);
    digitalWrite(YELLOW_P, HIGH);
    delay(2000);
    digitalWrite(YELLOW_P, LOW);
    digitalWrite(RED_P, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }
}
