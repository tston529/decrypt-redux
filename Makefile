CC := g++
CXXFLAGS := -I./include --std=c++20 -g
SRC := src/*.cpp
DEPS := include/*.hpp
OBJS := freq.o
EXE := build/freq
TEST_EXE := build/run_tests

.PHONY: all run test clean

all: $(EXE) test

$(EXE): freq.cpp $(SRC) $(DEPS)
	mkdir -p build
	$(CC) $(CXXFLAGS) -o $(EXE) freq.cpp $(SRC)

$(TEST_EXE): tests/tests.cpp $(SRC) $(DEPS)
	$(CC) $(CXXFLAGS) -o $(TEST_EXE) tests/tests.cpp $(SRC)

run: $(EXE)
	$(EXE)

test: $(TEST_EXE)
	$(TEST_EXE)

clean:
	rm -rf build/