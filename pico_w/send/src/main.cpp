#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "avaterSet.h"
#include "angle.h"
#include "my_variable.h"
INPUT_DATA send;

#define RX_PIN 6
#define TX_PIN 5
#define SEND_DELAY 8

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

 void setup(void)
 {
    delay(2000);
    // setupAvatar();
    Serial1.begin(38400, SERIAL_8N1, 6, 5);  // (RX, TX)
    auto cfg            = M5.config();
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);
    Serial.println("setup, OK");
    M5.Lcd.setTextSize(1.5);
}
 
 void loop(void)
 { 
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.fillRect(0, 20, M5.Lcd.width(), 20, BLACK);
    if (Serial1.available() != -1) {
        if (M5.Imu.update()) {
            M5.Imu.getMag(&send.mag.x, &send.mag.y, &send.mag.z); // 磁気データ取得 
            send.transport.data[data_fellow::AF] = 0xAF; // 先頭データ
            send.transport.data[data_fellow::X] = static_cast<int16_t>(send.mag.x * 100);
            send.transport.data[data_fellow::Y] = static_cast<int16_t>(send.mag.y * 100);
            send.transport.data[data_fellow::Z] = static_cast<int16_t>(send.mag.z * 100);
            
            /*  データ送信  */
            send.transport.data[data_fellow::SUM] = send.transport.data[data_fellow::X] 
            + send.transport.data[data_fellow::Y] 
            + send.transport.data[data_fellow::Z]; // 磁気データ
            send.transport.data[data_fellow::ED] = 0xED; // 終端データ
            // setface(getAngle(send.mag.x, send.mag.y));
            MAG_Send();
            Serial.printf("gx:%d  gy:%d  gz:%d\r\n", send.transport.data[X], send.transport.data[Y], send.transport.data[Z]);
            if (Serial1.read() & 0x4F) {
                if (Serial1.read() & 0x4B) {
                    M5.Lcd.println("OK ");
                    M5.Lcd.printf("gx:%d\ngy:%d\ngz:%d\r\n", send.transport.data[X], send.transport.data[Y], send.transport.data[Z]);
                }
            }
        } 
    } else {
        M5.Lcd.println("NO ");
    }
    delay(SEND_DELAY);
 }
