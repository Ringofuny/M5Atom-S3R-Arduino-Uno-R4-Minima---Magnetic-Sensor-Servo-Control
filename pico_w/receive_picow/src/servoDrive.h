#pragma once
#include <Servo.h>

Servo servo1; // サーボオブジェクト作成
Servo servo2;
Servo servo3;
Servo servo4;

const int servo1Pin = 2;
const int servo2Pin = 3;
const int servo3Pin = 4;
const int servo4Pin = 5;

// サーボモータ設定
int minUs = 500;
int maxUs = 2400;

unsigned long lastUpdate = 0;  // 最後にサーボを更新した時間
const int stepDelay = 500;      // 各ステップの遅延時間（ms）
const int servoStepSize = 2;    // 1回の更新で動かす角度

int targetAngles[4] = {90, 90, 90, 90};  // 目標角度
int currentAngles[4] = {90, 90, 90, 90}; // 現在の角度

int stepIndex = 0;

int mae[4][4] = {
    {90,  60, 120,  90}, // Step 0
    { 60,  120,  60,  120}, // Step 1
    { 60,  60,  60,  60}, // Step 2
    { 120, 60, 120, 60}, // Step 3
};

int usiro[4][4] = {
    { 90,  120,  60,  90}, // Step 5 (リセット)
    { 120, 60,  120, 60}, // Step 4
    { 120, 90,  90, 60}, // Step 3
    { 60,  60,  60,  60}, // Step 2
};

int right[3][4] = {
    {120, 60, 60, 120},
    {120, 90, 90, 120},
    {90,  90, 90,  90},
};

int left[3][4] = {
    {60,  120, 120,  60},
    {60,   90,  90,  60},
    {90,   90,  90,  90},
};

    // サーボを滑らかに動かす
void mae_move() {
    unsigned long now = millis();
    if (now - lastUpdate >= stepDelay) {
        lastUpdate = now;

        // 目標角度を更新
        for (int i = 0; i < 4; i++) {
        targetAngles[i] = mae[stepIndex][i];
        }

        // 次のステップへ進む
        stepIndex++;
        if (stepIndex >= 4) {
        stepIndex = 0; // 繰り返し
        }
    }

    // サーボを少しずつ動かす
    for (int i = 0; i < 4; i++) {
        if (currentAngles[i] < targetAngles[i]) {
        currentAngles[i] += servoStepSize;
        if (currentAngles[i] > targetAngles[i]) currentAngles[i] = targetAngles[i];
        } else if (currentAngles[i] > targetAngles[i]) {
        currentAngles[i] -= servoStepSize;
        if (currentAngles[i] < targetAngles[i]) currentAngles[i] = targetAngles[i];
        }
    }

    // サーボに反映
    servo1.write(currentAngles[0]);
    servo2.write(currentAngles[1]);
    servo3.write(currentAngles[2]);
    servo4.write(currentAngles[3]);
}

    // サーボを滑らかに動かす
void usiro_move() {
    unsigned long now = millis();
    if (now - lastUpdate >= stepDelay) {
        lastUpdate = now;

        // 目標角度を更新
        for (int i = 0; i < 4; i++) {
        targetAngles[i] = usiro[stepIndex][i];
        }

        // 次のステップへ進む
        stepIndex++;
        if (stepIndex >= 4) {
        stepIndex = 0; // 繰り返し
        }
    }

    // サーボを少しずつ動かす
    for (int i = 0; i < 4; i++) {
        if (currentAngles[i] < targetAngles[i]) {
        currentAngles[i] += servoStepSize;
        if (currentAngles[i] > targetAngles[i]) currentAngles[i] = targetAngles[i];
        } else if (currentAngles[i] > targetAngles[i]) {
        currentAngles[i] -= servoStepSize;
        if (currentAngles[i] < targetAngles[i]) currentAngles[i] = targetAngles[i];
        }
    }

    // サーボに反映
    servo1.write(currentAngles[0]);
    servo2.write(currentAngles[1]);
    servo3.write(currentAngles[2]);
    servo4.write(currentAngles[3]);
}

    // サーボを滑らかに動かす
void right_move() {
    unsigned long now = millis();
    if (now - lastUpdate >= stepDelay) {
        lastUpdate = now;

        // 目標角度を更新
        for (int i = 0; i < 4; i++) {
        targetAngles[i] = right[stepIndex][i];
        }

        // 次のステップへ進む
        stepIndex++;
        if (stepIndex >= 3) {
        stepIndex = 0; // 繰り返し
        }
    }

    // サーボを少しずつ動かす
    for (int i = 0; i < 4; i++) {
        if (currentAngles[i] < targetAngles[i]) {
        currentAngles[i] += servoStepSize;
        if (currentAngles[i] > targetAngles[i]) currentAngles[i] = targetAngles[i];
        } else if (currentAngles[i] > targetAngles[i]) {
        currentAngles[i] -= servoStepSize;
        if (currentAngles[i] < targetAngles[i]) currentAngles[i] = targetAngles[i];
        }
    }

    // サーボに反映
    servo1.write(currentAngles[0]);
    servo2.write(currentAngles[1]);
    servo3.write(currentAngles[2]);
    servo4.write(currentAngles[3]);
}

    // サーボを滑らかに動かす
void left_move() {
    unsigned long now = millis();
    if (now - lastUpdate >= stepDelay) {
        lastUpdate = now;

        // 目標角度を更新
        for (int i = 0; i < 4; i++) {
        targetAngles[i] = left[stepIndex][i];
        }

        // 次のステップへ進む
        stepIndex++;
        if (stepIndex >= 3) {
        stepIndex = 0; // 繰り返し
        }
    }

    // サーボを少しずつ動かす
    for (int i = 0; i < 4; i++) {
        if (currentAngles[i] < targetAngles[i]) {
        currentAngles[i] += servoStepSize;
        if (currentAngles[i] > targetAngles[i]) currentAngles[i] = targetAngles[i];
        } else if (currentAngles[i] > targetAngles[i]) {
        currentAngles[i] -= servoStepSize;
        if (currentAngles[i] < targetAngles[i]) currentAngles[i] = targetAngles[i];
        }
    }

    // サーボに反映
    servo1.write(currentAngles[0]);
    servo2.write(currentAngles[1]);
    servo3.write(currentAngles[2]);
    servo4.write(currentAngles[3]);
}

void servoset() { 
    servo1.attach(servo1Pin, minUs, maxUs);
    servo2.attach(servo2Pin, minUs, maxUs);
    servo3.attach(servo3Pin, minUs, maxUs);
    servo4.attach(servo4Pin, minUs, maxUs);
}