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
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void setDuty(int D) {
    analogWrite(A4, D);
    analogWrite(A5, D);
}

void stop() {
    setDuty(250);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

void GO_GO() {
    setDuty(250);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void back_back() {
    setDuty(250);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}
void right() {
    setDuty(250);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void left() {
    setDuty(250);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}

void loop() {
    bool update_state = recovery.getRecoveryData(&received.mag.x, &received.mag.y, &received.mag.z);
    if (update_state) {
        fail = 0;
        float angle_XY = getAngle(received.mag.x, received.mag.y);
        float angle_YZ = getAngle(received.mag.y, received.mag.z);
        float angle_XZ = getAngle(received.mag.x, received.mag.z);
        Serial.print("OK x: ");
        Serial.print(received.mag.x);
        Serial.print(" y: ");
        Serial.print(received.mag.y);
        Serial.print(" z: ");
        Serial.print(received.mag.z);
        Serial.print(" angle1: ");
        Serial.print(angle_XY);
        Serial.print(" angle2: ");
        Serial.print(angle_YZ);
        Serial.print(" angle3: ");
        Serial.println(angle_XZ);

        // 角度に応じた動作
        if (received.mag.y > -50 && received.mag.y < 250) {
            GO_GO();   // 前進
        } else if (received.mag.y <= -150 || received.mag.y > 250) {    
            back_back(); // 後退
        } else if (received.mag.z > 0) {
            left();  // 左旋回
        } else if (received.mag.z < 0) {
            right(); // 右旋回
        } else if (received.mag.y < -50 && received.mag.y > -150) {
            stop();
        } 
    } else {
        fail++;
    } 
    if (fail > 10) {
        Serial.println("fail");
        stop();
    }
}

