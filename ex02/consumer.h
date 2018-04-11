#include "systemc.h"
#include "stack_if.h"

class consumer : public sc_module
{
public:

  sc_port<stack_read_if> in;
  sc_in<bool> Clock;

  void do_reads()
  {
    int i = 0;
    char c;
    while (true)
    {
      wait();             // for clock edge
      if (in->nb_read(&c)
        cout << "R " << c << " at "
             << sc_time_stamp() << endl;
      i = (i+1) % 32;
    }
  }

  SC_CTOR(consumer)
  {
    SC_THREAD(do_reads);
    sensitive << Clock.pos();
  }
};
