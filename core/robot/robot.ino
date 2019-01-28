/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega
*/

#include <SoftwareSerial.h>

#define SERIAL_TIMEOUT 100
#define BLUETOOTH_TX 2
#define BLUETOOTH_RX 3
#define IDLE "i"
#define WORKING "w"
#define GOBACK "g"

#define BLUETOOTH "Bluetooth"
#define DWM1000 "DWM1000"


SoftwareSerial Bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.
// Current position
float pos_x, pos_y;

// The range of the classrooms
float classroomRange[2];

// The state of the Kibot
String status = IDLE;


size_t log(String TAG, String MESSAGE) {
  return Serial.println(TAG + " : " + MESSAGE);
}


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(SERIAL_TIMEOUT);
  Bluetooth.begin(9600);

  // Initialize DCMotor
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
  float x_min = classroomRange[0];
  float x_max = classroomRange[1];
  // 1차원 공간: (x_min < pos_x && x_max >= pos_x)
  // 2차원 공간: (x >= min_x && x <= max_x) && (y >= min_y && y <= max_y)
  while (!(x_min < pos_x && x_max >= pos_x)) {
    // status = WORKING;
    // DWM1000 위치신호 대기
    // http://www.hardcopyworld.com/ngine/aduino/index.php/archives/740
    if (Serial.available())
      pos_x = Serial.readString().toFloat();

    if (pos_x < x_min) { // 앞으로
    }
    if (pos_x > x_max) {// 뒤로
    }
  }

  status = GOBACK;

}

void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available() && (status == IDLE || status == GOBACK)) {
    setRange(Bluetooth.parseInt());
    status = WORKING;
  }

  if (classroomRange[0] == classroomRange[1]) {
    log("ERROR", "Invalid range"); return;
  }

  if (status == WORKING) untilArrival();

  // 원점으로 돌아가기는 loop 함수 안에서 실행되어야 함 (돌아가는 도중 안내 요청 고려)
  if (status == GOBACK) Serial.println("GOING BACK...") // TODO: 원점으로 돌아가기

  status = IDLE;
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
