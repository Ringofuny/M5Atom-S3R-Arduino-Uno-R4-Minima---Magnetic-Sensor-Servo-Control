// ESP-NowはArduinoIDEのボードマネージャで "esp32 by espressif" を
// 入れておけば以下の2つのヘッダファイルをインクルードするだけで使用可能だよ。
#include <esp_now.h>
#include <WiFi.h>
#include "M5Unified.h"

// 送信データの構造体
struct ANGLEDATA {
  float angle;
};

ANGLEDATA received;

// ESP-Nowでデータを受信したときに呼び出されるコールバック関数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&received, incomingData, sizeof(received));
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.print("angle: ");
  Serial.println(received.angle);
}