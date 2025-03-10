#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "M5Unified.h"
#include "angle.h"

// ターゲット（フィギュアスタンド）の MAC address
uint8_t targetAddress[] = {0x34, 0xB7, 0xDA, 0x57, 0x39, 0xD4};

typedef struct GATIsendData {
  float angle;
} GATIsendData;

struct MAGData {
  float x;
  float y;
  float z;
};

MAGData mag;
GATIsendData send;

// ピア（送信先）の情報を保持するための変数
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial.println("serial started");
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println("wifi");

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.println("ESP-NOW initialized");
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_register_send_cb(OnDataSent);

  // ピア（送信先）を登録
  memcpy(peerInfo.peer_addr, targetAddress, 6);
  peerInfo.channel = 0; // Wi-Fiのチャンネル
  peerInfo.encrypt = false; // 暗号化する or しない

  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("setup, OK");
}

void loop() {
  if (M5.Imu.update()) {
    M5.Imu.getMag(&mag.x, &mag.y, &mag.z); // 磁気データ取得
    send.angle = getAngle(mag.x, mag.y); // 角度計算
    // Send message via ESP-NOW
    Serial.println("send");
  }
  
  esp_err_t result = esp_now_send(targetAddress, (uint8_t *) &send, 4);
  
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(100);
}
