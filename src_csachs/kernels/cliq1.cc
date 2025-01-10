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
    

   float table[8] = {0.0002,0.00001,0.0057,0.141,0.0092,0.0006,0.001,0.9692};

    float le[4];

    for(int i=0;i<4;i++){
        le[i]=readincr(bufin0);
    }

    printf("clique1 read from pl done");


   
    
    writeincr(bufout1,table[0]+table[2]); //c=1 
    writeincr(bufout1,table[1]+table[3]); //t=1 
    writeincr(bufout1,table[4]+table[6]);
    writeincr(bufout1,table[5]+table[7]);

    printf("clique1 write to c0 done");


    float c1=readincr(bufin1);
    float c0=readincr(bufin1);
    float useless =0;
    useless = readincr(bufin1);
    useless = readincr(bufin1);

    printf("clique1 read from c0 done");

    for(int i=0;i<4;i++){
        table[i] *= c1;
        table[i+4] *=c0;
    }

    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    for(int i=0;i<4;i++){
        writeincr(bufout0,0); //t=1 

    }

    printf("clique1 backword propagation done");



}