# Compile without Makefile
# 	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/systemc-2.3.0/lib-linux64
# 	g++ -g -o main main.cpp fir.cpp tb.cpp -I. -I/usr/local/systemc-2.3.0/include -L/usr/local/systemc-2.3.0/lib-linux64 -lsystemc -lstdc++ -lm
# 		-g  Produce debugging information in the operating system's native format (stabs, COFF, XCOFF, or DWARF 2).  GDB can work with this debugging information.

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/systemc-2.3.0/lib-linux64

SYSTEMC=/usr/local/systemc-2.3.0
SYSTEMC_ARCH=linux64
# SYSTEMC_ARCH=linux

# Libraries directories.
LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)
@echo LIB_DIRS = #(LIB_DIRS)

# Include directories
INCLUDE_DIRS = -I. -I$(SYSTEMC)/include

# header files used. for dependency checking
HEADERS = fir.h tb.h

# source files used. for dependency checking
SOURCES= main.cpp fir.cpp tb.cpp

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS= -lsystemc -lstdc++ -lm
TESTS= main

all: $(TESTS)
	./$(TESTS)
	@make cmp_result

$(TESTS): $(DEPENDENCIES)
	g++ -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS)

.PHONY: clean
clean:
	rm -rf $(TESTS) *.o *.dat

# The cmp_result target comapres the simulation results with the 
# golden results. The testbench writes out the results file (output.dat)
# in the simulation configuration directory. The cmp_result target is
# automatically run at the end of each simulations.

GOLD_DIR = ./golden
GOLD_FILE = $(GOLD_DIR)/ref_output.dat

# diff 
# -w, --ignore-all-space
#               ignore all white space
cmp_result:
	@echo "********************************************************"
	@if diff -w $(GOLD_FILE) ./output.dat ; then \
		echo "SIMULATION PASSED"; \
	else \
		echo "SIMULATION FAILED"; \
	fi
	@echo "********************************************************"
