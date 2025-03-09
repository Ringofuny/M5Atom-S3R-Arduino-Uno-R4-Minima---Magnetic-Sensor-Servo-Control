#include "data_recovery.h"
#include "angle.h"
#include "servoDrive.h"

RECEIVE_DATA received;
data_recovery recovery;

int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
    servoset();
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
        // 角度に応じた動作
        if (angle > 45 && angle < 135) {
            mae_move();   // 前進
        } else if (angle >= 135 || angle <= 45) {
            usiro_move(); // 後退
        } else if (angle < 45) {
            left_move();  // 左旋回
        } else if (angle > 135) {
            right_move(); // 右旋回
        }
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

    1 -> A0
    2 -> A1
    3 -> A2
    4 -> A3
*/
