#ifndef my_variable_H
#define my_variable_H

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

struct RECEIVE_DATA {
    coordinate gyro;
};

#endif