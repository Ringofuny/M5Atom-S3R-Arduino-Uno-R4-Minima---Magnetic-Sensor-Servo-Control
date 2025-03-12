#include "data_recovery.h"

bool data_recovery::getRecoveryData(float *x, float *y, float *z)
{
    if (!(s_Serial.getSig(data))) {
        return false;
    } else {
        fail = 0;
        *x = (float)(data[indata_group::X_group]) / 100.0;
        *y = (float)(data[indata_group::Y_group]) / 100.0;
        *z = (float)(data[indata_group::Z_group]) / 100.0;
        return true;
    }
}
