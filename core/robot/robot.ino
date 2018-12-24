/*
  Copyright 2018-2019. Donghyeok Tak
*/

#include <SoftwareSerial.h>

#define tx 1
#define rx 2


class _Guide {
  public:
    int target;
    void setTarget(int id);
    float getCurrentPos();
    bool isArrived();
};


_Guide Guide;
SoftwareSerial Bluetooth(tx, rx);


bool isGuidanceDone = true;


void _Guide::setTarget(int _target_pos) {
  target = _target_pos;
}
float _Guide::getCurrentPos() {
  // TODO: DWM1000
}
bool _Guide::isArrived() {
  // TODO: DWM1000
}


void log(String s) {
  Serial.println("DEBUG:" + s);
}


void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
}


void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available() && isGuidanceDone) {
    Guide.setTarget(Bluetooth.parseInt());
    isGuidanceDone = false;
  }

  // 안내
  while (!isGuidanceDone) {
    if (Guide.getCurrentPos() < Guide.target) {
      // TODO: GO STRAIGHT
    }

    if (Guide.isArrived()) {
      // TODO: OUTPUT
      // TODO: GO HOME
      isGuidanceDone = true;
    }
  }
}
