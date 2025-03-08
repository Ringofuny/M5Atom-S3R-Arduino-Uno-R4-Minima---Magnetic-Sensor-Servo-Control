#include <Arduino.h>
#include "receive_serial.h"

receive_serial s_Serial;
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
        received.gyro.x = data[indata_group::X_group] / 100.0f;
        received.gyro.y = data[indata_group::Y_group] / 100.0f;
        received.gyro.z = data[indata_group::Z_group] / 100.0f;
        Serial.print("OK x: ");
        Serial.print(received.gyro.x);
        // Serial.print(data[X]);
        Serial.print(" y: ");
        Serial.print(received.gyro.y);
        // Serial.print(data[Y]);
        Serial.print(" z: ");
        Serial.println(received.gyro.z);
        // Serial.println(data[Z]);

        // Serial.print(" 1: ");
        // Serial.print(data[data_fellow::AF]);
        // Serial.print(" 2: ");
        // Serial.print(data[data_fellow::X]);
        // Serial.print(" 3: ");
        // Serial.print(data[data_fellow::Y]);
        // Serial.print(" 4: ");
        // Serial.print(data[data_fellow::Z]);
        // Serial.print(" 5: ");
        // Serial.print(data[data_fellow::SUM]);
        // Serial.print(" 6: ");
        // Serial.println(data[data_fellow::ED]);
    } else {
        fail++;
    }
    if (fail > 10) {
        // Serial.println("fail");
    }
}
