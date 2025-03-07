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

typedef struct {
    float gyro_X;
    float gyro_Y;
    float gyro_Z;
    uint16_t data[6];
} GYRO_DATA;

#endif