#include <Arduino.h>
#include "gyro_receive_serial.h"

gyro_receive_serial s_Serial;
RECEIVE_DATA received;
int16_t data[6];
int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
}

void loop() {
    if (s_Serial.getSig(data)) {
        fail = 0;
        received.gyro.x = data[X] / 100.0f;
        received.gyro.y = data[Y] / 100.0f;
        received.gyro.z = data[Z] / 100.0f;
        // Serial.print("OK x: ");
        // Serial.print(received.gyro.x);
        // Serial.print(data[X]);
        // Serial.print(" y: ");
        // Serial.print(received.gyro.y);
        // Serial.print(data[Y]);
        // Serial.print(" z: ");
        // Serial.println(received.gyro.z);
        // Serial.println(data[Z]);

        Serial.print(" 1: ");
        Serial.print(data[AF]);
        Serial.print(" 2: ");
        Serial.print(data[X]);
        Serial.print(" 3: ");
        Serial.print(data[Y]);
        Serial.print(" 4: ");
        Serial.print(data[Z]);
        Serial.print(" 5: ");
        Serial.print(data[SUM]);
        Serial.print(" 6: ");
        Serial.println(data[ED]);
    } else {
        fail++;
    }
    if (fail > 10) {
        // Serial.println("fail");
    }
}
