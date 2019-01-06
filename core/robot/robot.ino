/*
  Copyright 2018-2019. Donghyeok Tak
*/

#include <SoftwareSerial.h>
#include "Guide.hpp"

#define Bluetooth_TX 1
#define Bluetooth_RX 2

SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);
Guide Guide();



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
    Guide.begin(Bluetooth.parseInt());
  }

  while (true) {
    // TODO: Guide logic
  }
}
