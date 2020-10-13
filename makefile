CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++

all: main

main:
	$(CXX) $(CXXFLAGS) src/main.cpp -o bin/MakefileBuilder.exe