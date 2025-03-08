#pragma once
#include "receive_serial.h"

class data_recovery {
    public:
        receive_serial s_Serial;
        RECEIVE_DATA received;
        bool getRecoveryData(float* x, float* y, float* z);
    private:
        int16_t data[6];
        int fail = 0;
};