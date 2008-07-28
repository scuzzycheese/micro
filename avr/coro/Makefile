all: test.exe testoo.exe

test.exe: test.c coroData.h
	gcc -g3 -o test.exe test.c

testoo.exe: testoo.c coroData.h moo.o
	g++ -g3 -o testoo.exe testoo.c moo.o

moo.o: moo.cpp moo.h
	g++ -g3 -o moo.o moo.cpp

clean:
	rm test.exe
	rm testoo.exe
