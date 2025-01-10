#ifndef spline_h
#define spline_h

#include <adf.h>

// len is the len of message, new_len should be pckaged message
void cliq0(input_stream<float> *  __restrict bufin, output_stream<float>*  __restrict bufout);
void cliq1(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1);
void cliq2(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1);
void cliq3(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1);
void cliq4(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1);
void cliq5(input_stream<float> *  __restrict bufin0, output_stream<float>*  __restrict bufout0,input_stream<float> *  __restrict bufin1, output_stream<float>*  __restrict bufout1);

// void repeat(input_stream<float> * __restrict bufin, output_stream<float>* __restrict bufout);




#endif
