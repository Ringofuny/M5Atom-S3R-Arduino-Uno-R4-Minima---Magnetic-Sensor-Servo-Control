#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "M5AtomS3.h"
#include "data_recovery.h"

data_recovery recovery;
RECEIVE_DATA received;

int fail = 0;

// ターゲット（フィギュアスタンド）の MAC address
uint8_t targetAddress[] = {0x34, 0xB7, 0xDA, 0x57, 0x39, 0xD4};

typedef struct SendData {
  int16_t X;
  int16_t Y;
  int16_t Z;
} GATIsendData;

struct MAGData {
  int16_t x;
  int16_t y;
  int16_t z;
};

MAGData mag;
SendData send;

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
  Serial1.begin(38400, SERIAL_8N1, 6, 5);  // (RX, TX)
  Serial.println("serial started");
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println("wifi");
  
  // M5Stack初期化
  // Serial.println("M5Stack initialized");

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
  bool update_state = recovery.getRecoveryData(&received.mag.x, &received.mag.y, &received.mag.z);
  if (update_state) {
    fail = 0;
    send.X = received.mag.x;
    send.Y = received.mag.y;
    send.Z = received.mag.z;
    Serial1.write('O');
    Serial1.write('K');
    // Send message via ESP-NOW
  }  else {
    fail++;
  } 
  if (fail > 10) Serial.println("fail");
  
  Serial.print("Sending: ");
  Serial.print(send.X);
  Serial.print(" ");
  Serial.print(send.Y);
  Serial.print(" ");
  Serial.print(send.Z);
  Serial.print(" ");
  esp_err_t result = esp_now_send(targetAddress, (uint8_t *) &send, sizeof(send));
  
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  // delay(100);
}
