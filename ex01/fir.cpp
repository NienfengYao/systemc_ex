#include "fir.h"

// Coefficients for each FIR
const sc_uint<8> coef[5] = {
	18, 77, 107, 77, 18
}; 

// FIR Main thread
void fir::fir_main(void)
{
	// FIR instance
	sc_int<16> taps[5];

	// Reset protocol
	for(int i=0; i++; i<5){
		taps[i] = 0;
	}

	// Initialize handshake
	inp_rdy.write(0);
	outp_vld.write(0);
	outp.write(0);
	wait();  // wait one cycle in systemC

	// FIR filter
	while(true){
		sc_uint<16> in_val;
		sc_uint<16> out_val;

#if 0 // Test hanging simulation
		wait(10000000);
#endif 
		inp_rdy.write(1);
		do {
			wait();
		} while (!inp_vld.read());
		in_val = inp.read();
		inp_rdy.write(0);

		// Read input into shift register
		for(int i=5-1; i>0; i--){
			taps[i] = taps[i-1];
		}
		taps[0] = in_val;

		// Perform multiply ans accumulate
		for(int i=0; i<5; i++){
			out_val += coef[i] * taps[i];
		}

		outp_vld.write(1);
		outp.write(out_val);
		do {
			wait();
		} while (!outp_vld.read());
	}
}
