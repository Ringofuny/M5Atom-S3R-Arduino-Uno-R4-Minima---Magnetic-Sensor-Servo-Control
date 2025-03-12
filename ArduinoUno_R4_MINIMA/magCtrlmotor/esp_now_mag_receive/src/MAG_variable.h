#pragma once

enum data_fellow {
    AF,
    X,
    Y,
    Z,
    SUM,
    ED
};

struct coordinate
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
};

struct data_buffer
{
    int16_t data[6];
};

struct  INPUT_DATA{
    coordinate mag;
    data_buffer transport;
};

