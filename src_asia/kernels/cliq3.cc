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
void cliq3(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1)
{
    

   float table[8] = {0.03,0.0015,0.02,0.0035,0.27,0.1485,0.18,0.3465};

    float b1=readincr(bufin1);
    float b0=readincr(bufin1);
    float useless =0;
    useless = readincr(bufin1);
    useless = readincr(bufin1);

    printf("clique3 read done");


    //update
    table[0]*=b1;
    table[1]*=b1;
    table[4]*=b1;
    table[5]*=b1;

    table[2]*=b0;
    table[3]*=b0;
    table[6]*=b0;
    table[7]*=b0;

    //normalize
    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }


    writeincr(bufout0,table[0]+table[1]); //lb=11 
    writeincr(bufout0,table[2]+table[3]) ;//lb=00
    writeincr(bufout0,table[4]+table[5]) ;//lb=01
    writeincr(bufout0,table[6]+table[7]) ;//lb=00

        printf("clique3 forward propagation done");


    float lb11 = readincr(bufin0);
    float lb10 = readincr(bufin0);
    float lb01 = readincr(bufin0);
    float lb00 = readincr(bufin0);

    table[0]*=lb11;
    table[1]*=lb11;
    table[4]*=lb01;
    table[5]*=lb01;

    table[2]*=lb10;
    table[3]*=lb10;
    table[6]*=lb00;
    table[7]*=lb00;

    ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    writeincr(bufout1,table[0]+table[1]+table[4]+table[5]);
    writeincr(bufout1,table[2]+table[3]+table[6]+table[7]);
    writeincr(bufout1,0);
    writeincr(bufout1,0);

printf("clique3 backward propagation done");


}