void setup() {
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);

}

void loop() {
  digitalWrite(5, HIGH);
  delay(5000);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(5000);
  digitalWrite(7,LOW);
}