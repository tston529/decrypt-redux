CC=g++
compile: freq.cpp helper.hpp frequency_setup.hpp
	$(CC) -o freq freq.cpp --std=c++20

compile_tests: tests/tests.cpp frequency_setup.hpp helper.hpp
	$(CC) -o tests/tests tests/tests.cpp --std=c++20 -I.

test: compile_tests
	tests/tests