#ifndef Arduino_de_Serial_H
#define Arduino_de_Serial_H

#include <Arduino.h>
#include <stdbool.h>
#include "teigi.h"

class Arduino_de_Serial {
    public:
    /*シリアルを通してFEP02からコントローラーデータを読み取る関数。
    戻り値：失敗した場合　false/偽
            成功した場合　true/真
    引数：読み取れたデータを入れるサイズ11の文字列ポインター。
            失敗した場合は、渡されたデータが変更しない。
    */
    bool getSig(uint8_t *data);

    private:
    #define RETRY_DEF 20
    int RETRY_MAX = RETRY_DEF;
};

#endif