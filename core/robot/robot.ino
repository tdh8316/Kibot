/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega
*/

#include <SoftwareSerial.h>

// macro
#define SERIAL_TIMEOUT 100
#define BLUETOOTH_TX 2
#define BLUETOOTH_RX 3
#define x_min classroomRange[0]
#define x_max classroomRange[1]

#define BLUETOOTH "Bluetooth"
#define DWM1000 "DWM1000"


SoftwareSerial Bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.
// Current position
float pos_x, pos_y = 0;

// The range of the classrooms
float classroomRange[2] = {0, 0};


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

// DC Motor
void moveForward() {
  analogWrite(5, 0);
  analogWrite(6, 150);
  analogWrite(10, 0);
  analogWrite(11, 150);
}

// DC Motor
void moveStop() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}


void setRange(int id = -1) {
  switch (id) {
    case 101:
      x_min = 1.5; x_max = 2.5;
      break;

    default:
      x_min = 0; x_max = 0;
  }
}

void loop() {
  // 블루투스 신호 대기
  if (Bluetooth.available()) {
    setRange(Bluetooth.parseInt());
  }

  delay(SERIAL_TIMEOUT);

  // Revert if range is invalid
  if (x_min == x_max) {
    log("DENINED", "Invalid range"); return;
  }

  // Guide logic
  // 1차원 공간: (x_min < pos_x && x_max >= pos_x)
  // 2차원 공간: (x >= min_x && x <= max_x) && (y >= min_y && y <= max_y)

  while (!(x_min < pos_x && x_max >= pos_x)) {
    // 1차원 공간에 대한 안내논리
    // DWM1000 위치신호 대기
    // http://www.hardcopyworld.com/ngine/aduino/index.php/archives/740
    if (Serial.available())
      pos_x = Serial.readString().toFloat();

    log(DWM1000, String(pos_x));

    if (pos_x < x_min) { // 앞으로
    }
    if (pos_x > x_max) {// 뒤로
    }

    delay(SERIAL_TIMEOUT);
  }

  // Init after arrive
  x_min = 0;
  x_max = 0;
}
