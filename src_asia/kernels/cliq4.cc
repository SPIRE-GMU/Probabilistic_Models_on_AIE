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
void cliq4(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1)
{
    

   float table[8] = {0.9,0.1,0.7,0.3,0.8,0.2,0.1,0.9};

   float start ;
   for(int i=0;i<4;i++){
       start = readincr(bufin1);
   }

   writeincr(bufout0,table[0]+table[1]+table[4]+table[5]); //b=1 
   writeincr(bufout0,table[2]+table[3]+table[6]+table[7]) ;//b=0
    writeincr(bufout0,0);
    writeincr(bufout0,0);

    printf("clique4 write done");

   float b1= readincr(bufin0);
   float b0 = readincr(bufin0);

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
    
        printf("clique4 update done");

    float end =0;
    for(int i=0;i<4;i++){
        writeincr(bufout1,end);

    }


}