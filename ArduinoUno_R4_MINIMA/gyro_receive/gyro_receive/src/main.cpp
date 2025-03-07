#include <Arduino.h>
#include "Arduino_de_Serial.h"

Arduino_de_Serial s_Serial;
uint8_t data[6];
int fail = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(115200);
}

void loop() {
    if (s_Serial.getSig(data)) {
        fail = 0;
        Serial.println("OK");
    } else {
        fail++;
    }
    if (fail > 10) {
        // Serial.println("fail");
    }
}
