#include "systemc.h"
#include "stack_if.h"

// this class implements the virtual functions
// in the interfaces
class stack
: public sc_module,
  public stack_write_if, public stack_read_if
{
private:
  char data[20];
  int top;                 // pointer to top of stack

public:
  // constructor
  stack(sc_module_name nm) : sc_module(nm), top(0)
  {
  }

  bool stack::nb_write(char c)
  {
    if (top < 20)
    {
      data[top++] = c;
      return true;
    }
    return false;
  }

  void stack::reset()
  {
    top = 0;
  }

  bool stack::nb_read(char& c)
  {
    if (top > 0)
    {
      c = data[--top];
      return true;
    }
    return false;
  }

  void stack::register_port(sc_port_base& port_,
                            const char* if_typename_)
  {
    cout << "binding    " << port_.name() << " to "
         << "interface: " << if_typename_ << endl;
  }
};
