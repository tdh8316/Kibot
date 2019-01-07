/*
  Copyright 2018-2019. Donghyeok Tak
*/

#include <SoftwareSerial.h>

#define Bluetooth_TX 2
#define Bluetooth_RX 3

SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);


size_t log(String s) {
  return Serial.println("LOG:" + s);
}


void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
}


void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available()) {
    log(Bluetooth.parseInt());
  } else {
    log("Failed to connect Bluetooth");
  }
  delay(1000);
}
