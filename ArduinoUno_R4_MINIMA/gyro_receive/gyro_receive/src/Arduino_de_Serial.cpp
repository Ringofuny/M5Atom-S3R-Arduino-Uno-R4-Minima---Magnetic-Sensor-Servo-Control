#include "Arduino_de_Serial.h"

bool Arduino_de_Serial::getSig(uint8_t *data)
{
  uint8_t data_temp[6];
  unsigned char sum = 0;
  uint16_t retry = 0;

  retry = 0;
  while (!(Serial1.available() >= 6) && !(retry++ > RETRY_MAX))
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
    data_temp[AF] = Serial1.read();

    if (data_temp[AF] == 0xAF)
    { // ヘッダーを見つけたらループから出る、タイムアウトで失敗
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

  while (!(Serial1.available() >= 5) && !(retry++ > RETRY_MAX)) // ヘッダー見つけたが、次のデータが入るまで待機、タイムアウトで失敗
    delayMicroseconds(500);

  if (retry > RETRY_MAX)
  { // タイムアウトの場合
    Serial.println("STAGE 3 TIMEOUT");
    return false;
  }

  for (int i = 1; i < 4; ++i)
  {
    data_temp[i] = Serial1.read();
    sum += data_temp[i];
  }
  data_temp[SUM] = Serial1.read();
  data_temp[ED] = Serial1.read();

  // sum check
  if (data_temp[SUM] == sum)
  {
    // 読み取り成功した場合
    memcpy(data, data_temp, 6);
    return true;
  }
}