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
void cliq5(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1)
{
    

   float table[4] = {0.98,0.02,0.05,0.95};

    float le[4];
   writeincr(bufout1,table[0]+table[1]); //e=1 
   writeincr(bufout1,table[2]+table[3]) ;//e=0
    writeincr(bufout1,0) ;//e=0
    writeincr(bufout1,0) ;//e=0

     printf("clique5 forward propogation done");

    
     for(int i=0;i<4;i++){
        le[i]=readincr(bufin1);
    }
     printf("clique5 readfrom clique2 done");


    for(int j=0;j<4;j++){
        writeincr(bufout0,le[j]);
    }

     printf("clique5 transition to cliq1 done");

    for(int i=0;i<4;i++){
        le[i]=readincr(bufin0);
    }

    for(int j=0;j<4;j++){
            writeincr(bufout1,le[j]);
    }

    printf("clique5 transitionn done");


    float e1=readincr(bufin1);
    float e0=readincr(bufin1);
    float useless =0;
    useless = readincr(bufin1);
    useless = readincr(bufin1);

    table[0] *= e1;
    table[1] *= e1;
    table[2] *= e0;
    table[3] *= e0;

    float ave=(table[0]+table[1]+table[2]+table[3])/4;
    for(int i=0;i<4;i++){
        table[i] /= ave;
    }
        printf("clique5 update done");

}