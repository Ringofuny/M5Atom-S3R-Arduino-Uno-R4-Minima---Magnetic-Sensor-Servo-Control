#include "data_recovery.h"
#include "angle.h"
#include <Servo.h>
Servo servo;
Servo back_servo;

RECEIVE_DATA received;
data_recovery recovery;

int16_t data[6];
int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
    servo.attach(9);
    back_servo.attach(10);
}

void loop() {
    bool update_state = recovery.getRecoveryData(&received.mag.x, &received.mag.y, &received.mag.z);
    if (update_state) {
        fail = 0;
        float angle = getAngle(received.mag.x, received.mag.y);
        Serial.print("OK x: ");
        Serial.print(received.mag.x);
        Serial.print(" y: ");
        Serial.print(received.mag.y);
        Serial.print(" z: ");
        Serial.print(received.mag.z);
        Serial.print(" angle: ");
        Serial.println(angle);
        servo.write(angle);
        back_servo.write(fabs(180-angle));
    } else {
        fail++;
    } 
    if (fail > 10) Serial.println("fail");
}

/*
    |-----------|
    | 2       1 |
    |           |
    |           |
    | 3       4 |
    |-----------|

    1,2 -> back_servo
    3,4 -> servo

*/
