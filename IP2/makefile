CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# creates all
all: module demo test

# (a) build the module .o from .h and .cpp
module: OrderedSet.o

OrderedSet.o: OrderedSet.cpp OrderedSet.h
	$(CXX) $(CXXFLAGS) -c OrderedSet.cpp -o OrderedSet.o

# (b) build demo
demo: demo_bin

demo_bin: demo.cpp OrderedSet.o
	$(CXX) $(CXXFLAGS) demo.cpp OrderedSet.o -o demo_bin

# (c) run demo
run_demo: demo_bin
	./demo_bin

# (d) build test
test: test_bin

test_bin: test.cpp OrderedSet.o
	$(CXX) $(CXXFLAGS) test.cpp OrderedSet.o -o test_bin

# (e) run test
run_test: test_bin
	./test_bin 2>&1 | tee log.txt

# (f) clean everything
clean:
	rm -f OrderedSet.o demo_bin test_bin log.txt

# (g) rebuild from scratch
rebuild: clean all

.PHONY: all module demo run_demo test run_test clean rebuild