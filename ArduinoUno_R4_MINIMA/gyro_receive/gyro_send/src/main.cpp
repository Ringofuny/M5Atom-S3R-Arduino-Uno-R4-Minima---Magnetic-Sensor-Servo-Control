#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <M5Unified.h>
#include "my_variable.h"
INPUT_DATA send;

#define RX_PIN 6
#define TX_PIN 5
#define SEND_DELAY 8

void GYRO_Send() {
  // for (int i = 0; i < 6; i++) {
  //   Serial1.write(send.data[i]);
  // }

  // 送信側 (2bit)
    for (int i = 0; i < 6; i++) {
      Serial1.write((uint8_t)(send.transport.data[i] >> 8));  // 上位バイト
      Serial1.write((uint8_t)(send.transport.data[i] & 0xFF));  // 下位バイト
    }
    Serial1.write('\r');                                      //CR
    Serial1.write('\n');                                      //LF
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
     Serial1.begin(38400, SERIAL_8N1, 6, 5);  // (RX, TX)
     auto cfg            = M5.config();
     cfg.serial_baudrate = 115200;
     M5.begin(cfg);
     Serial.println("setup, OK");
    }
 
 void loop(void)
 {
    if (M5.Imu.update()) {
      M5.Imu.getGyro(&send.gyro.x, &send.gyro.y, &send.gyro.z); // ジャイロデータ取得 
      send.transport.data[X] = static_cast<int16_t>(send.gyro.x * 100);
      send.transport.data[Y] = static_cast<int16_t>(send.gyro.y * 100);
      send.transport.data[Z] = static_cast<int16_t>(send.gyro.z * 100);
      Serial.printf("gx:%d  gy:%d  gz:%d\r\n", send.transport.data[X], send.transport.data[Y], send.transport.data[Z]);

      /*  データ送信  */
      send.transport.data[AF] = 0xAF; // 先頭データ
      send.transport.data[SUM] = send.transport.data[X] + send.transport.data[Y] + send.transport.data[Z]; // ジャイロデータ
      send.transport.data[ED] = 0xED; // 終端データ
      GYRO_Send();
    }

    delay(SEND_DELAY);
 }
