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
    

   float table[8] = {1,1,1,1,1,1,1,1};


    float e1 = readincr(bufin0); //cliq5
    float e0 = readincr(bufin0);
    float useless =0;
    useless = readincr(bufin0);
    useless = readincr(bufin0);

    //update
    table[0]*=e1;
    table[1]*=e1;
    table[4]*=e1;
    table[5]*=e1;

    table[2]*=e0;
    table[3]*=e0;
    table[6]*=e0;
    table[7]*=e0;    

    float lb11 = readincr(bufin1);//cliq3
    float lb10 = readincr(bufin1);
    float lb01 = readincr(bufin1);
    float lb00 = readincr(bufin1);

    table[0]*=lb11;
    table[2]*=lb11;
    table[1]*=lb01;
    table[3]*=lb01;

    table[4]*=lb10;
    table[6]*=lb10;
    table[5]*=lb00;
    table[7]*=lb00;


    float ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /=ave;
    }

    printf("clique2 updating done");

    writeincr(bufout0,table[0]+table[1]);   
    writeincr(bufout0,table[2]+table[3]);    
    writeincr(bufout0,table[4]+table[5]);    
    writeincr(bufout0,table[6]+table[7]);    

    printf("clique2 transite le to cliq 5 done");

    float le[4];
    for(int i=0;i<4;i++){
        le[i] = readincr(bufin0);
    }    

     printf("clique2 transition done");

    for(int i=0;i<8;i++){
        table[i] *= le[i/2];
    }

    ave=(table[0]+table[1]+table[2]+table[3]+table[4]+table[5]+table[6]+table[7])/8;
    for(int i=0;i<8;i++){
        table[i] /= ave;
    }

    writeincr(bufout1,table[0]+table[2]);
    writeincr(bufout1,table[1]+table[3]);
    writeincr(bufout1,table[4]+table[6]);
    writeincr(bufout1,table[5]+table[7]);
    

    writeincr(bufout0,table[0]+table[1]+table[4]+table[5]);
    writeincr(bufout0,table[2]+table[3]+table[6]+table[7]);

    writeincr(bufout0,0);
    writeincr(bufout0,0);


}