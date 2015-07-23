assigment2 : mainProg.o bigint.o
	gcc -std=c99 bigint.o mainProg.o -o assignment2

bigint.o : bigint.c bigint.h
	gcc -std=c99 -c bigint.c -o bigint.o

clean :
	rm *.o