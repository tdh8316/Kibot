/*
  Copyright 2018-2019. Donghyeok Tak
*/

#include <SoftwareSerial.h>

#define Bluetooth_TX 1
#define Bluetooth_RX 2

SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);


size_t log(String s) {
  return Serial.println("LOG:" + s);
}


void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
}


void loop() {
  Guide = new GuideCore;
  // 블루투스 신호 대기
  if (Bluetooth.available()) {
    Guide.begin(Bluetooth.parseInt());
  }

  while (Guide.isDone) {

  }
}
