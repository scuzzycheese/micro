all: test.exe testoo.exe

test.exe: test.c coroData.h
	gcc -g3 -o test.exe test.c

testoo.exe: testoo.c coroDataOO.h moo.o
	g++ -g3 -o testoo.exe testoo.c moo.o

moo.o: moo.cpp moo.h
	g++ -g3 -c -o moo.o moo.cpp

clean:
	rm -rf test.exe
	rm -rf testoo.exe
	rm -rf moo.o
