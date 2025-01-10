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
void cliq2(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1)
{
    

   float table[8] = {0.9,0.1,0.05,0.95,0.25,0.3,0.2,0.25};


    float c1 = readincr(bufin0); //cliq5
    float c0 = readincr(bufin0);
    float useless =0;
    useless = readincr(bufin0);
    useless = readincr(bufin0);

    //update
    for(int i=0;i<4;i++){
        table[i] *=c1;
        table[i+4]*=c0;
    }
   

    

    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /=ave;
    }

    printf("clique2 updating done");

    for(int i=0;i<4;i++){
        writeincr(bufout1,table[i*2]+table[i*2+1]);   
    }
 
    printf("clique2 transite le to cliq 3 done");

    float eo[4];
    for(int i=0;i<4;i++){
        eo[i]= readincr(bufin1); 
    }
   

     printf("clique2 transition done");

    for(int i=0;i<4;i++){
        table[i] *= eo[i];
        table[i*2+1] *=eo[i];
    }

    ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    writeincr(bufout0,table[0]+table[2]+table[1]+table[3]);
    writeincr(bufout0,table[4]+table[5]+table[6]+table[7]);
    writeincr(bufout0,0);
    writeincr(bufout0,0);
    

    


}