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
        M5.Imu.getMag(&send.mag.x, &send.mag.y, &send.mag.z); // 磁気データ取得 
        send.transport.data[data_fellow::AF] = 0xAF; // 先頭データ
        send.transport.data[data_fellow::X] = static_cast<int16_t>(send.mag.x * 100);
        send.transport.data[data_fellow::Y] = static_cast<int16_t>(send.mag.y * 100);
        send.transport.data[data_fellow::Z] = static_cast<int16_t>(send.mag.z * 100);
        // Serial.printf("gx:%d  gy:%d  gz:%d\r\n", send.transport.data[X], send.transport.data[Y], send.transport.data[Z]);
        
        /*  データ送信  */
        send.transport.data[data_fellow::SUM] = send.transport.data[data_fellow::X] 
                                              + send.transport.data[data_fellow::Y] 
                                              + send.transport.data[data_fellow::Z]; // 磁気データ
        send.transport.data[data_fellow::ED] = 0xED; // 終端データ
        GYRO_Send();
    }

    delay(SEND_DELAY);
 }
