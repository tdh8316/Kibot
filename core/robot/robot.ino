/*
  Copyright 2018-2019. Donghyeok Tak
  Required Arduino Mega 2560
  Kibot Main Processing Unit
*/

#if !defined(ARDUINO_AVR_MEGA2560)
#error "You must use the Arduino Mega 2560 board."
#endif

#define Bluetooth Serial1
#define print Serial.print
#define println Serial.println

#define x_min range[0]
#define x_max range[1]

const int SERIAL_TIMEOUT = 100; // ms

// On Arduino MEGA, the double implementation is exactly the same as the float, with no gain in precision.

// Current position (x, y)
float pos_x, pos_y = 0.0f;

// The range for the destination
float range[2] = {0, 0};

boolean isKibotBacking = false;


void setup() {
  // Start the serial communication in 115200 bps for compatibility with DWM1000
  Serial.begin(115200);
  println("This program is compiled at " __DATE__ " " __TIME__ ".");
  println("Starting Kibot...");

  print("  Change Serial timeout to 100ms...");
  Serial.setTimeout(SERIAL_TIMEOUT);
  println("[Done]");

  print("  Start Bluetooth...");
  Bluetooth.begin(9600);
  println("[Done]");

  // Initialize DC motor
  print("  Change pin mode used for DC motor...");
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  println("[Done]");

  println("  Everything is initialized.");
  println("The setup sequence is done. It took " + String(millis()) + "ms.\n");
}


void moveForward() {
  analogWrite(5, 0);
  analogWrite(6, 255);
  analogWrite(10, 0);
  analogWrite(11, 255);
}

void moveBack() {
  analogWrite(5, 255);
  analogWrite(6, 0);
  analogWrite(10, 255);
  analogWrite(11, 0);
}

void moveStop() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}


void setRange(int id = -1) {
  switch (id) {
    case 101:
      x_min = 2; x_max = 3;
      break;
    case 102:
      x_min = 3.5; x_max = 4.5;
      break;
    case 103:
      x_min = 5; x_max = 6;
      break;

    case -1:
      x_min = 0; x_max = 0;
      break;
  }
}


void loop() {

  // DWM1000 communicates with the Kibot in Serial.
  if (Serial.available()) {
    float x = Serial.parseFloat(); if (x != 0.0f) pos_x = x;
    // Only 1-d guidance is implemented.
  }

  // Kibot client communicates with the Kibot in Bluetooth
  if (Bluetooth.available()) {
    isKibotBacking = false;
    setRange(Bluetooth.parseInt());
  }

  if (isKibotBacking) {
    if (!pos_x < 1.5) moveBack();
    else isKibotBacking = false;
  }

  // If the range is invalid, it does not need to continue running
  if (x_min == x_max)
    return;

  /* Logic:
      1-d space: (x_min < pos_x && x_max >= pos_x) => in range
      2-d space: ((x_min < pos_x && x_max >= pos_x) && (y_min < pos_y && y_max >= pos_y)) => in range
  */

  if (pos_x < x_min) moveForward();
  else if (pos_x > x_max) moveBack();
  else {
    setRange();
    // The Kibot is in somewhere...
    moveStop();
    // Do something when arrive!
    delay(5000);
    isKibotBacking = true;
  }

  delay(SERIAL_TIMEOUT);
}
