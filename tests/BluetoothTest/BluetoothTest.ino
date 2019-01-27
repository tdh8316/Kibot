#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);   //bluetooth module Tx:Digital 2 Rx:Digital 3

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("Kibot Bluetooth test");
}

void loop() {
  if (BTSerial.available()) {
    Serial.println(String(BTSerial.parseInt()));
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}