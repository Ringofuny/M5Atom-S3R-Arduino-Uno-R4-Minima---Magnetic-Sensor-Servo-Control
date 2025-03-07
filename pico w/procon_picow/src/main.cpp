#include "tusb.h"  // TinyUSBライブラリ
#include "Arduino.h"

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(10);
    Serial.println("TinyUSB Host Initialized");
}

void loop() {
    tuh_task();  // USBホスト処理を実行
    delay(500);
}
