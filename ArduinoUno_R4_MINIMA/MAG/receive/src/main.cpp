#include "data_recovery.h"

RECEIVE_DATA received;
data_recovery recovery;

int16_t data[6];
int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
}

void loop() {
    bool update_state = recovery.getRecoveryData(&received.mag.x, &received.mag.y, &received.mag.z);
    if (update_state) {
        Serial.print("OK x: ");
        Serial.print(received.gyro.x);
        Serial.print(" y: ");
        Serial.print(received.gyro.y);
        Serial.print(" z: ");
        Serial.println(received.gyro.z);
    } else {
        Serial.println("fail");
    }
}
