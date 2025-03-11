#pragma once

#define MODE 2 // 1->GYRO, 2->MAG

#if MODE == 1
    #include "GYRO_variable.h"
#elif MODE == 2
    #include "MAG_variable.h"
#else 
    #error "Mode error!"
#endif
