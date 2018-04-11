#include "systemc.h"
#include "stim.h"
#include "exor2.h"
#include "mon.h"

#define WAVEFORM_TRACING	// support waveform tracing

int sc_main(int argc, char* argv[])
{
  sc_signal<bool> ASig, BSig, FSig;
  //sc_clock TestClk("TestClock", 10, SC_NS,0.5);
  sc_clock TestClk("TestClock", 10, SC_NS,0.5, 1, SC_NS);

  stim Stim1("Stimulus");
  Stim1.A(ASig);
  Stim1.B(BSig);
  Stim1.Clk(TestClk);

  exor2 DUT("exor2");
  DUT.A(ASig);
  DUT.B(BSig);
  DUT.F(FSig);

  mon Monitor1("Monitor");
  Monitor1.A(ASig);
  Monitor1.B(BSig);
  Monitor1.F(FSig);
  Monitor1.Clk(TestClk);

#ifdef WAVEFORM_TRACING
  sc_trace_file* Tf;
  Tf = sc_create_vcd_trace_file("traces");
  //((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);
  ((vcd_trace_file*)Tf)->set_time_unit(1, SC_NS);
  //Tf->set_time_unit(1, SC_NS);
  sc_trace(Tf, ASig  , "A" );
  sc_trace(Tf, BSig  , "B" );
  sc_trace(Tf, FSig  , "F" );
  sc_trace(Tf, DUT.S1, "S1");
  sc_trace(Tf, DUT.S2, "S2");
  sc_trace(Tf, DUT.S3, "S3");
#endif
  sc_start();  // run forever
#ifdef WAVEFORM_TRACING
  sc_close_vcd_trace_file(Tf);
#endif

  return 0;

}
