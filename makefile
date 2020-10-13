CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++ -I src/

all: main

main:
	$(CXX) $(CXXFLAGS) -c src/EngineName/OtherFolder/OtherFolderFile.cpp -o bin/OtherFolderFile.o
	$(CXX) $(CXXFLAGS) -c src/EngineName/Test/TestFile.cpp -o bin/TestFile.o
	$(CXX) $(CXXFLAGS) bin/TestFile.o bin/OtherFolderFile.o src/main.cpp -o bin/MakefileBuilder.exe
	./bin/MakefileBuilder