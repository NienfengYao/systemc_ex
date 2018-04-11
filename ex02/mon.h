#include "systemc.h"
#include <iomanip>

using namespace std;

SC_MODULE(mon) {
    sc_in<bool> A,B,F;
    sc_in<bool> Clk;

    void monitor() {
        cout << setw(10) << "Time";
        cout << setw(2) << "A";
        cout << setw(2) << "B";
        cout << setw(2) << "F" << endl;
        while(true) {
            cout << setw(10) << sc_time_stamp();
            cout << setw(2) << A.read();
            cout << setw(2) << B.read();
            cout << setw(2) << F.read() << endl;
            wait();
        }
    }
    SC_CTOR(mon) {
    	cout << "Constructing mon " << name() << endl;
        SC_THREAD(monitor);
        sensitive << Clk.pos();
    }
};
