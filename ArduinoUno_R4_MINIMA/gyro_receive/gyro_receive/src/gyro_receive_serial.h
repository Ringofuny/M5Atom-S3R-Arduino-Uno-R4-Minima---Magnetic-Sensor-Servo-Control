#ifndef gyro_receive_serial_H
#define gyro_receive_serial_H

#include <Arduino.h>
#include <stdbool.h>
#include "my_variable.h"

class gyro_receive_serial {
    public:
        /*シリアルを通してFEP02からコントローラーデータを読み取る関数。
        戻り値：失敗した場合　false/偽
                成功した場合　true/真
        引数：読み取れたデータを入れるサイズ11の文字列ポインター。
                失敗した場合は、渡されたデータが変更しない。
        */
        bool getSig(int16_t *data);
    private:
        struct data_buffer
        {
                int16_t data_temp[6];
        };

        struct  RCV_DATA{
                data_buffer transport;
        };

        #define RETRY_DEF 20
        int RETRY_MAX = RETRY_DEF;
};

#endif