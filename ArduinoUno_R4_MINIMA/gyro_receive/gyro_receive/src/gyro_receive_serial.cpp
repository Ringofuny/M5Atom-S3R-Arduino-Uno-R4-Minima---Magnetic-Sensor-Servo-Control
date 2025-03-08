#include "gyro_receive_serial.h"

bool gyro_receive_serial::getSig(int16_t *data)
{
  RCV_DATA receive;
  int16_t sum = 0;
  uint16_t retry = 0;

  retry = 0;
  while (!(Serial1.available() >= 12) && !(retry++ > RETRY_MAX))
      delayMicroseconds(500);

  if (retry > RETRY_MAX)
  { // 失敗した場合
      // Serial.println("STAGE 1 TIMEOUT");
      return false;
  }

  // シリアルバッファーにデータがありそうなデータ量がある時
  retry = 0;
  while (1)
  {
    uint8_t high_byte = Serial1.read();  // 上位バイトを受信
    uint8_t low_byte = Serial1.read();   // 下位バイトを受信
    receive.transport.data_temp[AF] = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元
    // receive.transport.data_temp[AF] = Serial1.read();

    if (receive.transport.data_temp[AF] == 0xAF)
    { // ヘッダーを見つけたらループから出る、タイムアウトで失敗
      break;
    }
    else retry++;

    if (retry > RETRY_MAX)
    { // タイムアウトの場合
      // Serial.println("STAGE 2 TIMEOUT");
      return false;
    }
  }

  retry = 0;

  while (!(Serial1.available() >= 10) && !(retry++ > RETRY_MAX)) // ヘッダー見つけたが、次のデータが入るまで待機、タイムアウトで失敗
    delayMicroseconds(500);

  if (retry > RETRY_MAX)
  { // タイムアウトの場合
    // Serial.println("STAGE 3 TIMEOUT");
    return false;
  }

  for (int i = 1; i < 4; ++i)
  {
    uint8_t high_byte = Serial1.read();  // 上位バイトを受信
    uint8_t low_byte = Serial1.read();   // 下位バイトを受信
    receive.transport.data_temp[i] = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元
    sum += receive.transport.data_temp[i];
  }

  uint8_t high_byte = Serial1.read();  // 上位バイトを受信
  uint8_t low_byte = Serial1.read();   // 下位バイトを受信
  receive.transport.data_temp[SUM] = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元

  uint8_t high_byte_ED = Serial1.read();  // 上位バイトを受信
  uint8_t low_byte_ED = Serial1.read();   // 下位バイトを受信
  receive.transport.data_temp[ED] = (int16_t)((high_byte_ED << 8) | low_byte_ED);  // 元の int16_t に復元
  // receive.transport.data_temp[ED] = Serial1.read();
  // sum check
  if (receive.transport.data_temp[SUM] == sum)
  {
    // 読み取り成功した場合
    memcpy(data, receive.transport.data_temp, 6);
    return true;
  }
}