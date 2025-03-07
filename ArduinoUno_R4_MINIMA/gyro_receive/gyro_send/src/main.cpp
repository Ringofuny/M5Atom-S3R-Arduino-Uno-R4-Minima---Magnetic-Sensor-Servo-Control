#include <Arduino.h>
#include "M5Unified.h"
#include "my_variable.h"

GYRO_DATA send;

void gyroData() {
  auto data = M5.Imu.getImuData();
  send.gyro_X = data.gyro.x * 100;  // 100倍して整数化
  send.gyro_Y = data.gyro.y * 100;
  send.gyro_Z = data.gyro.z * 100;
}

void sendData() {
  send.data[AF] = 0xAF;
  send.data[X] = (uint16_t)send.gyro_X;
  send.data[Y] = (uint16_t)send.gyro_Y;
  send.data[Z] = (uint16_t)send.gyro_Z;
  send.data[SUM] = send.data[X] + send.data[Y] + send.data[Z];
  send.data[ED] = 0xED;

  for (int i = 0; i < 6; i++) {
    Serial1.write((uint8_t)(send.data[i] >> 8));  // 上位バイト
    Serial1.write((uint8_t)(send.data[i] & 0xFF));  // 下位バイト
  }
}

void setup(void) {
  delay(2000);
  auto cfg            = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);
  Serial.println("Setup OK");  // シリアル動作チェック用
  Serial1.begin(38400, SERIAL_8N1, 5, 39);  // (RX=5, TX=39)
  Wire.begin(45, 0, 100000);  // SDA=45, SCL=0, クロック100 kHz
}

void loop(void) {
  auto imu_update = M5.Imu.update();
  if (imu_update) {
    gyroData();
    sendData();
    Serial.printf("gx:%2f  gy:%2f  gz:%2f\r\n", send.gyro_X / 100.0, send.gyro_Y / 100.0, send.gyro_Z / 100.0);
  }
}
