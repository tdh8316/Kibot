/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega
*/

#include <SoftwareSerial.h>

#define BLUETOOTH "Bluetooth"
#define DWM1000 "DWM1000"

#define Bluetooth_TX 2
#define Bluetooth_RX 3


SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);


size_t log(String TAG, String MESSAGE) {
  return Serial.println(TAG + ":" + MESSAGE);
}


void setup() {
  Serial.begin(115200);
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
    log(BLUETOOTH, String(Bluetooth.parseInt()));
  }

  // DWM1000 위치신호 대기
  if (Serial.available()) {
    log(DWM1000, String(Serial.parseFloat());
  }
}
