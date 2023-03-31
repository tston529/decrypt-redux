CC := g++
CXXFLAGS := -I./include --std=c++20
DEPS := include/helper.hpp include/frequency_setup.hpp
OBJS := freq.o
EXE := build/freq
TEST_EXE := build/run_tests

.PHONY: all run test clean

all: $(EXE) test

$(EXE): freq.cpp $(DEPS)
	mkdir -p build
	$(CC) $(CXXFLAGS) -o $(EXE) freq.cpp 

$(TEST_EXE): tests/tests.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -o $(TEST_EXE) tests/tests.cpp

run: $(EXE)
	$(EXE)

test: $(TEST_EXE)
	$(TEST_EXE)

clean:
	rm -rf build/