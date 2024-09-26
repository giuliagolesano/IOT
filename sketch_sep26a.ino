#define YELLOW_LED 13
#define RED_LED 11
#define GREEN_LED 12

void setup() {
  // put your setup code here, to run once:
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  delay(100);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  delay(100);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(100);
}
