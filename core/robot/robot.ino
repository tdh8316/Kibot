/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega
*/

#include <SoftwareSerial.h>

// macro
#define SERIAL_TIMEOUT 100
#define x_min classroomRange[0]
#define x_max classroomRange[1]

#define GUIDING 1
#define BACKING -1
#define IDLE 0

#define BLUETOOTH "Bluetooth"
#define DWM1000 "DWM1000"

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.
// Current position
float pos_x, pos_y = 0;

// The range of the classrooms
float classroomRange[2] = {0, 0};


// Status
int status = IDLE;


size_t log(String TAG, String MESSAGE) {
  return Serial.println(TAG + " : " + MESSAGE);
}


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(SERIAL_TIMEOUT);
  Serial1.begin(9600); // Bluetooth

  // Initialize DCMotor
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.println("Bootstrap completed successfully.");
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

    case -1:
      x_min = 0; x_max = 0;
  }

  log("setRange", String(x_min) + "~" + String(x_max));
}

void loop() {
  // 블루투스 신호 대기
  if (Serial1.available()) setRange(Serial1.parseInt());
  // DWM1000 신호 대기
  if (Serial.available()) {
    float i = Serial.parseFloat();
    if (i != 0.0f) pos_x = i;
  }
  // 1-d guide; DO NOT DECLARE pos_y

  // Revert if range is invalid
  if (x_min == x_max) return;

  // Guide logic
  // 1차원 공간: (x_min < pos_x && x_max >= pos_x)
  // 2차원 공간: (x >= min_x && x <= max_x) && (y >= min_y && y <= max_y)

  if (!(x_min < pos_x && x_max >= pos_x)) status = GUIDING;
  else status = BACKING;

  if (status == GUIDING) {
    // 1차원 공간에 대한 안내논리
    // DWM1000 위치신호 대기

    log(DWM1000, "x=" + String(pos_x));

    if (pos_x <= x_min) {
      // 앞으로
    }
    else if (pos_x >= x_max) {
      // 뒤로
    }
    else status = BACKING;
  }

  if (status == BACKING) {
    if (pos_x < 1.0f) {
      status = IDLE;
    } else {
      // 뒤로
    }
  }

  delay(SERIAL_TIMEOUT);
}
