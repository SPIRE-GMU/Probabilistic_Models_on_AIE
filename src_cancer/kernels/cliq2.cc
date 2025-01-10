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
    

   float table[4] = {0.9,0.1,0.2,0.8};


    float c1 = readincr(bufin0); //cliq5
    float c0 = readincr(bufin0);
    float useless =0;
    useless = readincr(bufin0);
    useless = readincr(bufin0);

    //update
    table[1]*=c1;
    table[3]*=c1;
    
    table[2]*=c0;
    table[0]*=c0;
      

    

    float ave=(table[0]+table[1]+table[2]+table[3])/4;
    for(int i=0;i<4;i++){
        table[i] /=ave;
    }

    printf("clique2 updating done");

    writeincr(bufout1,table[0]+table[2]);   
    writeincr(bufout1,table[1]+table[3]);    
    writeincr(bufout1,0);    
    writeincr(bufout1,0);    

    printf("clique2 transite le to cliq 3 done");

    c1 = readincr(bufin1); 
    c0 = readincr(bufin1);  
    useless = readincr(bufin1);
    useless = readincr(bufin1);

     printf("clique2 transition done");

    for(int i=0;i<2;i++){
        table[i] *= c1;
        table[i*2+1] *=c0;
    }

    ave=(table[0]+table[1]+table[2]+table[3])/4;
    for(int i=0;i<4;i++){
        table[i] /= ave;
    }

    writeincr(bufout0,table[0]+table[2]);
    writeincr(bufout0,table[1]+table[3]);
    writeincr(bufout0,0);
    writeincr(bufout0,0);
    

    


}