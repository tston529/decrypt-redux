#!/bin/bash

if [[ $1 == "tests" ]]; then
	
g++ freq.cpp --std=c++20 -o freq
