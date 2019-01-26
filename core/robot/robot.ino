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

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.
float pos_x, pos_y, pos_destination;


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
    log(BLUETOOTH, String(Bluetooth.parseFloat()));
  }

  // DWM1000 위치신호 대기
  // http://www.hardcopyworld.com/ngine/aduino/index.php/archives/740
  if (Serial.available()) {
    log(DWM1000, String(Serial.parseFloat()));
  }
}
