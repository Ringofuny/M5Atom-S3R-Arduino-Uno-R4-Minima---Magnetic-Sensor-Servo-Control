#include <Arduino.h>
#include <M5Unified.h>
#include "my_variable.h"
INPUT_DATA send;

#define RX_PIN 6
#define TX_PIN 38
#define SEND_DELAY 8

void GYRO_Send() {
  // for (int i = 0; i < 6; i++) {
  //   Serial2.write(send.data[i]);
  // }

  // 送信側 (2bit)
    Serial2.write(send.transport.data[AF]);
    for (int i = 1; i < 4; i++) {
      Serial2.write((int8_t)(send.transport.data[i] >> 8));  // 上位バイト
      Serial2.write((int8_t)(send.transport.data[i] & 0xFF));  // 下位バイト
    }
    Serial2.write(send.transport.data[SUM]);
    Serial2.write(send.transport.data[ED]);
  /* // 受信側 (2bit)
    int16_t received_value;
    uint8_t high_byte = Serial1.read();  // 上位バイトを受信
    uint8_t low_byte = Serial1.read();   // 下位バイトを受信

    received_value = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元
  */ 
}

 void setup(void)
 {
     delay(2000);
     auto cfg            = M5.config();
     cfg.serial_baudrate = 115200;
     M5.begin(cfg);
     delay(500); // LCD の I2C 通信を安定させるための遅延
     Serial2.begin(38400, SERIAL_8N1, RX_PIN, TX_PIN);  // UART2で外部デバイスと通信
     pinMode(18, OUTPUT);
     digitalWrite(18, LOW);
     Serial.println("setup, OK");
 }
 
 void loop(void)
 {
    if (M5.Imu.update()) {
      M5.Imu.getGyro(&send.gyro.x, &send.gyro.y, &send.gyro.z); // ジャイロデータ取得 
      send.transport.data[X] = static_cast<int16_t>(send.gyro.x * 100);
      send.transport.data[Y] = static_cast<int16_t>(send.gyro.y * 100);
      send.transport.data[Z] = static_cast<int16_t>(send.gyro.z * 100);
      Serial.printf("gx:%d  gy:%d  gz:%d\r\n", send.gyro.x, send.gyro.y, send.gyro.z);

      /*  データ送信  */
      send.transport.data[AF] = 0xAF; // 先頭データ
      send.transport.data[SUM] = send.transport.data[X] + send.transport.data[Y] + send.transport.data[Z]; // ジャイロデータ
      send.transport.data[ED] = 0xED; // 終端データ
      GYRO_Send();
    }

    delay(SEND_DELAY);
 }
