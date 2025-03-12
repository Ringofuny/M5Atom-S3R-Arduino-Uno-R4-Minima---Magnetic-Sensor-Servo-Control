#include "data_recovery.h"
#include "angle.h"

RECEIVE_DATA received;
data_recovery recovery;

int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
}

void setDuty(int D) {
    analogWrite(6, D);
    analogWrite(7, D);
}

void stop() {
    setDuty(160);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

void GO_GO() {
    setDuty(160);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void back_back() {
    setDuty(160);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}
void right() {
    setDuty(160);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void left() {
    setDuty(160);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
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
            GO_GO();   // 前進
        } else if (angle >= 135 || angle <= 45) {    
            back_back(); // 後退
        } else if (angle < 45) {
            left();  // 左旋回
        } else if (angle > 135) {
            right(); // 右旋回
        }
    } else {
        fail++;
    } 
    if (fail > 10) {
        Serial.println("fail");
        stop();
    }
}

