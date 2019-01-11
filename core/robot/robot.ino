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

  // DC모터
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void moveForward() {
  analogWrite(5, 0);
  analogWrite(6, 150);
  analogWrite(10, 0);
  analogWrite(11, 150);
}

void moveStop() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}


void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available()) {
    log(String(Bluetooth.parseInt()));
    moveForward();
  }
}
