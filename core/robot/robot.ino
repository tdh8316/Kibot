/*
  Copyright 2018-2019. Donghyeok Tak
*/

#include <SoftwareSerial.h>

#define Bluetooth_TX 1
#define Bluetooth_RX 2

SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);


class GuideCore {
  public:
  // Attribute
  void init(void);
  void begin(int);
  void send();

  // Property
  bool isDone;
  bool isArrived;
  
  private:
  int getPos(void);
  int _target;
};

void GuideCore::begin(int target) {
  _target = target;
  isDone = false;
  isArrived = false;
}
void GuideCore::init() {
  // TODO: 초기 지점으로 되돌아가기
}
int GuideCore::getPos() {
  // TODO
  return 0;
}


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

  while (true) {
    if (Guide.isArrived) {
      Guide.init(); break;
    } else {
      
    }
  }
}
