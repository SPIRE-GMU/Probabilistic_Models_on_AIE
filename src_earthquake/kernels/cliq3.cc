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
    

   float table[4] = {0.7,0.3,0.01,0.99};

    float b1=readincr(bufin0);
    float b0=readincr(bufin0);
    float useless =0;
    useless = readincr(bufin0);
    useless = readincr(bufin0);

    printf("clique3 read done");


    //update
    table[0]*=b1;
    table[2]*=b1;
    

    table[1]*=b0;
    table[3]*=b0;
    
    

    //normalize
    float ave=(table[0]+table[1]+table[2]+table[3])/4;
    for(int i=0;i<4;i++){
        table[i] /= ave;
    }


    writeincr(bufout0,table[0]+table[2]); // 
    writeincr(bufout0,table[1]+table[3]) ;//
    writeincr(bufout0,0) ;//
    writeincr(bufout0,0) ;//

        printf("clique3 forward propagation done");


    
printf("clique3 backward propagation done");


}