#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
// #include "M5Unified.h"
#include "M5AtomS3.h"
#include "angle.h"

// ターゲット（フィギュアスタンド）の MAC address
uint8_t targetAddress[] = {0x34, 0xB7, 0xDA, 0x57, 0x39, 0xD4};

typedef struct GATIsendData {
  float X;
  float Y;
  float Z;
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
  
  // M5Stack初期化
  AtomS3.begin();
  AtomS3.Imu.init();
  // M5.Imu.begin();
  Serial.println("M5Stack initialized");

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
  if (AtomS3.Imu.isEnabled()) {
    AtomS3.Imu.getMag(&mag.x, &mag.y, &mag.z); // 磁気データ取得
    send.X = mag.x;
    send.Y = mag.y;
    send.Z = mag.z;
    // Send message via ESP-NOW
  } else {
    Serial.println("IMU is not enabled");
  }
  
  Serial.print("Sending: ");
  Serial.print(send.X);
  Serial.print(" ");
  Serial.print(send.Y);
  Serial.print(" ");
  Serial.print(send.Z);
  Serial.println(" ");
  esp_err_t result = esp_now_send(targetAddress, (uint8_t *) &send, sizeof(send));
  
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(100);
}
