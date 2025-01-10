// #include <stdio.h>
// #include <stdlib.h>
// #include <cstdint>
// #include <string.h>
// #include <cstdio>
// #include <stdio.h>
// #include "aie_api/aie_types.hpp"
// #include "aie_api/aie_adf.hpp"
// #include <aie_api/utils.hpp>
// // #include <math.h>
// #include <time.h>
// #include <adf.h>
// #include <aie_api/aie.hpp>
// #include "adf/x86sim/streamApi.h"
// #include "adf/x86sim/streamStructs.h"
// #include "aie_api/aie_types.hpp"
#include "../kernels.h"







/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void cliq0(input_stream<float> *  __restrict bufin, output_stream<float>*  __restrict bufout)
{
    

    float table[4] = {0.0005,0.0095,0.0099,0.9801};

    float t1 = readincr(bufin);
    float t0 = readincr(bufin);
    float useless =0;
    useless = readincr(bufin);
    useless = readincr(bufin);

    
    table[0] = table[0] *t1;
    table[2] = table[2] *t1;

    table[1] = table[1] *t0;
    table[3] = table[3] *t0;


    writeincr(bufout,table[0]+table[2]); //t=1 
    writeincr(bufout,table[1]+table[3]) ;//t=0
    writeincr(bufout,0);
    writeincr(bufout,0);

    float ave=(table[0]+table[1]+table[2]+table[3])/4;
    for(int i=0;i<4;i++){
        table[i] /= ave;
    }


}