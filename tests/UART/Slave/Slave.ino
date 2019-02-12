void setup() {
  Serial.begin(115200);
  Serial.println("UART START");
}

void loop() {
  if (Serial.available()) {
    float i = Serial.parseFloat();
    Serial.println(i);
  }
}
