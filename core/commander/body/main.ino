/*
Copyright 2018-2019. Donghyeok Tak
*/
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(tx, rx);

int bufferIndex = 0;

char targetIdArray[3];
int targetId;


void log(String s) return Serial.println("DEBUG:" + s)


void setup() {
    Serial.begin(9600);
    Bluetooth.begin(9600);
}


void loop() {
    // Read target class via bluetooth
    while (Bluetooth.available()) {
        targetIdArray[bufferIndex] = (char) Bluetooth.read();
        bufferIndex ++;
    }
    targetId = atoi(targetIdArray);
    log("Where I'll go is " + targetId);

    // Initialize buffer
    for (int i = 0; i < 4; i ++) {
        targetIdArray[i] = null;
    } bufferIndex = 0;
}