/*
Copyright 2018-2019. Donghyeok Tak
*/
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(tx, rx);

int targetId;


void log(String s) {
    Serial.println("DEBUG:" + s)
}


void setup() {
    Serial.begin(9600);
    Bluetooth.begin(9600);
}


void loop() {
    // Read target class via bluetooth
    if (Bluetooth.available()) {
        targetId = Bluetooth.parseInt();
    }
    log("Where I'll go is " + String(targetId));
}