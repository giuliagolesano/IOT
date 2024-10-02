#define LED 13
#define BUTTON 2 

int released = 1;
int power = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(released && digitalRead(2) == HIGH){
    Serial.println(digitalRead(BUTTON));
    released = 0;
    if(power){
      digitalWrite(LED, LOW);
      power = 0;
    }else{
      digitalWrite(LED, HIGH);
      power = 1;
    }
  }else if(digitalRead(BUTTON) == LOW){
    released = 1;
  }
  Serial.println(digitalRead(BUTTON));
}
