#ifndef my_variable_h
#define my_variable_h

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
    float x;
    float y;
    float z;
};

struct data_buffer
{
    int16_t data[6];
};

struct  INPUT_DATA{
    coordinate gyro;
    data_buffer transport;
};



#endif