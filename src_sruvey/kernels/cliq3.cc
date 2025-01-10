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
void cliq3(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0)
{
    

   float table[8] = {0.7,0.3,0.01,0.99,0.25,0.2,0.3,0.25};

    float o_r[4];
    for(int i=0;i<4;i++){
        o_r[i] = readincr(bufin0);
    }
    printf("clique3 read done");


    //update
   for(int i=0;i<4;i++){
        table[i] *= o_r[i];
        table[i*2+1] *=o_r[i];
    }
    
    

    //normalize
    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }


 for(int i=0;i<4;i++){
        writeincr(bufout0,table[i*2]+table[i*2+1]);   
    }

        printf("clique3 forward propagation done");


    
printf("clique3 backward propagation done");


}