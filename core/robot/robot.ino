/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega
*/

#include <SoftwareSerial.h>

#define SERIAL_TIMEOUT 100

#define BLUETOOTH "Bluetooth"
#define DWM1000 "DWM1000"

#define Bluetooth_TX 2
#define Bluetooth_RX 3


SoftwareSerial Bluetooth(Bluetooth_TX, Bluetooth_RX);

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.
// Current position
float pos_x, pos_y;

// The range of the classrooms
float classroomRange[2];


size_t log(String TAG, String MESSAGE) {
  return Serial.println(TAG + " : " + MESSAGE);
}


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(SERIAL_TIMEOUT);
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

// 도착할 때 까지 계속 반복
void untilArrival() {
  while (!(classroomRange[0] < pos_x && classroomRange[1] >= pos_x)) {
    // DWM1000 위치신호 대기
    // http://www.hardcopyworld.com/ngine/aduino/index.php/archives/740
    if (Serial.available())
      pos_x = Serial.readString().toFloat();


    Serial.println("KEEP GOING...");

  }

  Serial.println("ARRIVED!!!");

}

void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available()) {
    setRange(Bluetooth.parseInt());
  }

  if (classroomRange[0] == classroomRange[1]) {
    log("ERROR", "Invalid range");
    return;
  }


  untilArrival();
  // TODO: 원점으로 돌아가기
}

void setRange(int id) {
  switch (id) {
    case 101:
      classroomRange[0] = 1.5; classroomRange[1] = 2.5;
      break;

    default:
      classroomRange[0] = 0; classroomRange[1] = 0;
  }
}
