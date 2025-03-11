#pragma once 
#include <math.h>

float getAngle(float x, float y) {
    float angle = atan2(y, x) * 180.0 / M_PI;  // ラジアン → 度 に変換

    if (angle < 0) {
        angle += 180.0;  // 負の角度を補正
    }
    return angle;
}
