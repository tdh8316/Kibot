#define SERIAL_TIMEOUT 100

float pos_x = 0.0f;

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

void moveForward() {
  analogWrite(5, 0);
  analogWrite(6, 200);
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

void loop() {
  // DWM1000 신호 대기
  if (Serial.available()) {
    float i = Serial.parseFloat();
    if (i != 0.0f) pos_x = i;
  }

  if (pos_x >= 2.5) {
    moveForward();
  } else {
    moveStop();
  }

}
