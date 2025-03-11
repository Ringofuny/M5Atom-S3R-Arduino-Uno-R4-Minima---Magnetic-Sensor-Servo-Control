#include "data_recovery.h"

bool data_recovery::getRecoveryData(float *x, float *y, float *z)
{
    if (!(s_Serial.getSig(data))) {
        return false;
    } else {
        fail = 0;
        *x = data[indata_group::X_group];
        *y = data[indata_group::Y_group];
        *z = data[indata_group::Z_group];
        return true;
    }
}
