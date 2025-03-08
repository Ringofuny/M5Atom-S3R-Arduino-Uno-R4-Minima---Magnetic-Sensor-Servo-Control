#include "receive_serial.h"

bool receive_serial::getSig(int16_t *data)
{
  RCV_DATA receive;
  int16_t sum = 0;
  uint16_t retry = 0;

  retry = 0;
  while (!(Serial1.available() >= 10) && !(retry++ > RETRY_MAX))
      delayMicroseconds(500);

  if (retry > RETRY_MAX)
  { // 失敗した場合
      Serial.println("STAGE 1 TIMEOUT");
      return false;
  }

  // シリアルバッファーにデータがありそうなデータ量がある時
  retry = 0;
  while (1)
  {
    uint8_t header = Serial1.read();   // 下位バイトを受信
    if (header == 0xAF)
    { // ヘッダーを見つけたらループから出る、タイムアウトで失敗
      receive.transport.data_temp[data_fellow::AF] = 0xAF;
      break;
    }
    else retry++;

    if (retry > RETRY_MAX)
    { // タイムアウトの場合
      Serial.println("STAGE 2 TIMEOUT");
      return false;
    }
  }

  retry = 0;

  while (!(Serial1.available() >= 9) && !(retry++ > RETRY_MAX)) // ヘッダー見つけたが、次のデータが入るまで待機、タイムアウトで失敗
    delayMicroseconds(500);

  if (retry > RETRY_MAX)
  { // タイムアウトの場合
    Serial.println("STAGE 3 TIMEOUT");
    return false;
  }

  for (int i = 1; i <= 3; ++i)
  {
    uint8_t high_byte = Serial1.read();  // 上位バイトを受信
    uint8_t low_byte = Serial1.read();   // 下位バイトを受信
    receive.transport.data_temp[i] = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元
    sum += receive.transport.data_temp[i];
  }

  uint8_t high_byte = Serial1.read();  // 上位バイトを受信
  uint8_t low_byte = Serial1.read();   // 下位バイトを受信
  receive.transport.data_temp[data_fellow::SUM] = (int16_t)((high_byte << 8) | low_byte);  // 元の int16_t に復元

  // ED を受信
  uint8_t ed_byte = Serial1.read();
  if (ed_byte != 0xED) {
      return false;  // もしEDが間違っていたらエラー
  }
  receive.transport.data_temp[data_fellow::ED] = 0xED;
  // sum check
  if (receive.transport.data_temp[SUM] == sum)
  {
    // 読み取り成功した場合
    memcpy(data, &receive.transport.data_temp[1], 4 * sizeof(int16_t));
    return true;
  }
}