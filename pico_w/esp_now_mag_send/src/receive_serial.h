#pragma once

#include <Arduino.h>
#include <stdbool.h>
#include "my_variable.h"

class receive_serial {
    public:
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
