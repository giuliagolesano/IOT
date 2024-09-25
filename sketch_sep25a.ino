  int cont = 0;
  
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("alive " + cont);
  delay(1000);
  cont ++ ;  
}
