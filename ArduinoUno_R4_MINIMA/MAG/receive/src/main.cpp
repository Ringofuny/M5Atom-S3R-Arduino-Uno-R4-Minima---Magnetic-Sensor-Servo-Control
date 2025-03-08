#include "data_recovery.h"
#include "angle.h"

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
        fail = 0;
        Serial.print("OK x: ");
        Serial.print(received.mag.x);
        Serial.print(" y: ");
        Serial.print(received.mag.y);
        Serial.print(" z: ");
        Serial.print(received.mag.z);
        Serial.print(" angle: ");
        Serial.println(getAngle(received.mag.x, received.mag.y));
    } else {
        fail++;
    } 
    if (fail > 10) Serial.println("fail");
}
