#pragma once

enum data_fellow {
    AF = 0,
    X = 1,
    Y = 2,
    Z = 3,
    SUM = 4,
    ED = 5
};

enum indata_group {
    X_group = 0,
    Y_group = 1,
    Z_group = 2
};

struct coordinate
{
    float x;
    float y;
    float z;
};

struct RECEIVE_DATA {
    coordinate gyro;
    coordinate mag;
};
