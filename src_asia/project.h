#include <adf.h>
// #include "adf/new_frontend/adf.h"
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
//   kernel repeat_node;
    kernel cliq_0;     
    kernel cliq_1; 
    kernel cliq_2; 
    kernel cliq_3; 
    kernel cliq_4; 
    kernel cliq_5; 
 
public:
  input_gmio in;

  output_plio out0;
  output_gmio out;
  simpleGraph()
  {
    //in0 = input_plio::create(plio_32_bits, "data/input_1.txt");
    //in1 = input_plio::create(plio_32_bits, "data/input_1.txt");

    //out0 = output_plio::create(plio_32_bits, "data/output_1.txt");
    //out1 = output_plio::create(plio_32_bits, "data/output_2.txt");
    // repeat_node = kernel::create(repeat);
    cliq_0 = kernel::create(cliq0);
    cliq_1 = kernel::create(cliq1);
    cliq_2 = kernel::create(cliq2);
    cliq_3 = kernel::create(cliq3);
    cliq_4 = kernel::create(cliq4);
    cliq_5 = kernel::create(cliq5);

    in = input_gmio::create("in",256,2048); //burst_length
    out = output_gmio::create("out",256,2048);

    out0 = output_plio::create(plio_32_bits, "data/output_1.txt");
    //connect(in0.out[0], first.in[0]); 
    //dimensions(first.in[0]) = { 8 };
    //single_buffer(first.in[0]);               //uncomment for single buffer, by default double buffer will be used.
    //connect(first.out[0], out0.in[0]);
    //dimensions(first.out[0]) = { 8 };

    //lut0 = parameter::array (LUT);
    //connect<> (lut0, first);

    
    connect<stream> net0 (in.out[0], cliq_4.in[1]);
    connect<stream> net1 (cliq_4.out[0], cliq_3.in[1]); //
    connect<stream> net2 (cliq_3.out[0], cliq_2.in[1]); //
    connect<stream> net3 (cliq_2.out[0], cliq_5.in[1]); //
    connect<stream> net4 (cliq_5.out[0], cliq_1.in[1]); //
    connect<stream> net5 (cliq_1.out[0], cliq_0.in[0]); //

    connect<stream> net6 (cliq_0.out[0], cliq_1.in[0]); //
    connect<stream> net7 (cliq_1.out[1], cliq_5.in[0]); //
    connect<stream> net8 (cliq_5.out[1], cliq_2.in[0]); //
    connect<stream> net9 (cliq_2.out[1], cliq_3.in[0]); //
    connect<stream> net10 (cliq_3.out[1], cliq_4.in[0]); //
    connect<stream> net11 (cliq_4.out[1], out.in[0]); //
    connect<stream> net12 (cliq_4.out[1], out0.in[0]); //


    fifo_depth(net0) = 512;
    fifo_depth(net1) = 512;
    fifo_depth(net2) = 512;
    fifo_depth(net3) = 512;
    fifo_depth(net4) = 512;
    fifo_depth(net5) = 512;
    fifo_depth(net6 ) = 512;
    fifo_depth(net7 ) = 512;
    fifo_depth(net8 ) = 512;
    fifo_depth(net9 ) = 512;
    fifo_depth(net10) = 512;
    fifo_depth(net11) = 512;
    fifo_depth(net12) = 512;


  
    source(cliq_0) = "src/kernels/cliq0.cc";
    source(cliq_1) = "src/kernels/cliq1.cc";
    source(cliq_2) = "src/kernels/cliq2.cc";
    source(cliq_3) = "src/kernels/cliq3.cc";
    source(cliq_4) = "src/kernels/cliq4.cc";
    source(cliq_5) = "src/kernels/cliq5.cc";

    // runtime<ratio>(repeat_node) = 0.9;
    runtime<ratio>(cliq_0) = 0.9;
    runtime<ratio>(cliq_1) = 0.9;
    runtime<ratio>(cliq_2) = 0.9;
    runtime<ratio>(cliq_3) = 0.9;
    runtime<ratio>(cliq_4) = 0.9;
    runtime<ratio>(cliq_5) = 0.9;

    }
};

