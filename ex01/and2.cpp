# include <systemc.h>

SC_MODULE(AND2) {
	sc_in< sc_uint<1> >		a, b;  // bit-accurate
	sc_out< sc_uint<1> >	f;
	sc_in<bool>	clk;

	void func(){
		f.write(a.read() & b.read());
	}

	SC_CTOR(AND2){  // Constructor
		SC_METHOD(func);
		sensitive << clk.neg();
	}

	~AND2(){
		// Destructor
		sc_stop();
	}
};

AND2 *top = NULL;
int sc_main(int argc, char* argv[])
{
	top = new AND2("top");
	sc_start();
	return 0;
}
