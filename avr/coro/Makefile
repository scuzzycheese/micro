all: test.exe testoo.exe

test.exe: test.c coroData.h
	gcc -g3 -o test.exe test.c

testoo.exe: testoo.c moo.o fibre.o
	g++ -g3 -o testoo.exe testoo.c moo.o fibre.o

moo.o: moo.cpp moo.h
	g++ -g3 -c -o moo.o moo.cpp

fibre.o: fibre.cpp fibre.h
	g++ -g3 -c -o fibre.o fibre.cpp

clean:
	rm -rf test.exe
	rm -rf testoo.exe
	rm -rf moo.o
	rm -rf fibre.o
