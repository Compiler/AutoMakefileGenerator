# AutoMakefileGenerator
- The goal is to create the makefile and only recompile .o files that have changed since last compilation. This works using a recursive n-ary linked list and changes the make file with each call to make.
- I made this because my game engine takes 65+ seconds to compile and when I change it to compile better, that involves taking more of my time to sort by precompiled headers.
