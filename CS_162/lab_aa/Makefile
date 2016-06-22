# CS_162

# Lab Aa makefile

all : lab1-1 lab1-2

lab1-1 : average.cpp summation.cpp lab1-1.cpp lib_flip_display.cpp
	g++ average.cpp summation.cpp lab1-1.cpp lib_flip_display.cpp -DDebug -lncurses -o lab1-1

lab1-2 : summation.cpp lab1-2.cpp lib_flip_display.cpp
	g++ summation.cpp lab1-2.cpp lib_flip_display.cpp -DDebug -lncurses -o lab1-2

clean :
	rm -f lab1-1
	rm -f lab1-2
