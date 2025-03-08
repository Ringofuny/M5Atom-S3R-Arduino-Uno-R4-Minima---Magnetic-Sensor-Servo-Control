#include "data_recovery.h"

bool data_recovery::getRecoveryData(float *x, float *y, float *z)
{
    if (!(s_Serial.getSig(data))) {
        fail++;
    } else {
        fail = 0;
        *x = data[indata_group::X_group] / 100.0f;
        *y = data[indata_group::Y_group] / 100.0f;
        *z = data[indata_group::Z_group] / 100.0f;
        return true;
    }

    if (fail > 10) return false;
}
