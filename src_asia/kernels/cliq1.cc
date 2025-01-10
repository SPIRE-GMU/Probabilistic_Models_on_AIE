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
// // #include <time.h>
// #include <adf.h>
// #include <aie_api/aie.hpp>
// #include "adf/x86sim/streamApi.h"
// #include "adf/x86sim/streamStructs.h"
// #include "aie_api/aie_types.hpp"
#include "../kernels.h"







/*************************************************/

// GMIO is suppoused to transfer the data in multiple of 32bit, or it renders deadlock when reading.
void cliq1(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1)
{
    

   float table[8] = {1,0,1,0,1,0,0,1};

    float le[4];

    for(int i=0;i<4;i++){
        le[i]=readincr(bufin1);
    }

    printf("clique1 read from c5 done");


    for(int i=0;i<8;i++){
        table[i] *=le[i%4];
    }

    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    writeincr(bufout0,table[0]+table[1]+table[2]+table[3]); //t=1 
    writeincr(bufout0,table[4]+table[5]+table[6]+table[7]); //t=1 
    writeincr(bufout0,0);
    writeincr(bufout0,0);

    printf("clique1 write to c0 done");


    float t1=readincr(bufin0);
    float t0=readincr(bufin0);
    float useless =0;
    useless = readincr(bufin0);
    useless = readincr(bufin0);

    printf("clique1 read from c0 done");

    for(int i=0;i<4;i++){
        table[i] *= t1;
        table[i+4] *=t0;
    }

    ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    for(int i=0;i<4;i++){
        writeincr(bufout1,table[i]+table[i+4]); //t=1 

    }

    printf("clique1 backword propagation done");



}