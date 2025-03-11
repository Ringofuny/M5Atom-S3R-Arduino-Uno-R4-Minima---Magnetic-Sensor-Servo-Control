// ESP-NowはArduinoIDEのボードマネージャで "esp32 by espressif" を
// 入れておけば以下の2つのヘッダファイルをインクルードするだけで使用可能だよ。
#include <esp_now.h>
#include <WiFi.h>
#include "M5Unified.h"
#include "MAG_variable.h"
INPUT_DATA send;

#define SEND_DELAY 8
unsigned long pre = 0;

struct ReceiveData {
  int16_t X;
  int16_t Y;
  int16_t Z;
};

ReceiveData received;

void MAG_Send() {
  Serial1.write((uint8_t)send.transport.data[data_fellow::AF]);  // ヘッダー 0xAF (1バイト)

  // X, Y, Z, SUM (int16_t なので2バイトずつ送信)
  for (int i = 1; i <= 4; i++) {
      Serial1.write((uint8_t)(send.transport.data[i] >> 8));  // 上位バイト
      Serial1.write((uint8_t)(send.transport.data[i] & 0xFF));  // 下位バイト
  }

  Serial1.write((uint8_t)send.transport.data[data_fellow::ED]);  // フッター 0xED (1バイト)
  Serial1.write('\r');  // CR
  Serial1.write('\n');  // LF

  Serial1.flush();  // **送信完了を待つ**
}

// ESP-Nowでデータを受信したときに呼び出されるコールバック関数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&received, incomingData, sizeof(received));
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8N1, 6, 5);  // (RX, TX)
  
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
  unsigned long now = millis();
  send.transport.data[data_fellow::AF] = 0xAF; // 先頭データ
  send.transport.data[data_fellow::X] = (received.X);
  send.transport.data[data_fellow::Y] = (received.Y);
  send.transport.data[data_fellow::Z] = (received.Z);
  Serial.printf("gx:%d  gy:%d  gz:%d\r\n", send.transport.data[X], send.transport.data[Y], send.transport.data[Z]);
  
  /*  データ送信  */
  send.transport.data[data_fellow::SUM] = send.transport.data[data_fellow::X] 
                                        + send.transport.data[data_fellow::Y] 
                                        + send.transport.data[data_fellow::Z]; // 磁気データ
  send.transport.data[data_fellow::ED] = 0xED; // 終端データ
  // setface(getAngle(send.mag.x, send.mag.y));
  if(now - pre > SEND_DELAY) {
    MAG_Send();
    Serial.println("OK");
  }
}