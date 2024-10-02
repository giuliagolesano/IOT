#define GREEN 13
#define YELLOW 12
#define RED 11
#define BUTTON 2

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  digitalWrite(GREEN, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
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
    delay(5000);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }
}
