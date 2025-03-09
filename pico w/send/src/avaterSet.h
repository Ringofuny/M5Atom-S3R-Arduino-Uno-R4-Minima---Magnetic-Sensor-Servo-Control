#pragma once

#include <M5Unified.h>
#include <Avatar.h>
m5avatar::Avatar avatar;

void setupAvatar()
{
  avatar.setScale(0.4);
  avatar.setPosition(-56, -96);
  avatar.init();
}

void setUE() {
    avatar.setPosition(-46, -96);
}

void setRight() {
    avatar.setPosition(-56, -86);
}

void setdown() {
    avatar.setPosition(-66, -96);
}

void setLeft() {
    avatar.setPosition(-56, -106);
}

void setface(float angle) {
    if (angle > 45 && angle < 135) {
        setUE();   // 前進
    } else if (angle >= 135 || angle <= 45) {
        setdown(); // 後退
    } else if (angle < 45) {
        setLeft();  // 左旋回
    } else if (angle > 135) {
        setRight(); // 右旋回
    }
}