all: test.exe testoo.exe

test: test.c coroData.h
	gcc -g3 -O0 -o test test.c

testoo.exe: testoo.c moo.o fibre.o
	g++ -g3 -o testoo.exe testoo.c moo.o fibre.o

moo.o: moo.cpp moo.h
	g++ -g3 -c -o moo.o moo.cpp

fibre.o: fibre.cpp fibre.h
	g++ -g3 -c -o fibre.o fibre.cpp

clean:
	rm -rf test
	rm -rf testoo.exe
	rm -rf moo.o
	rm -rf fibre.o
