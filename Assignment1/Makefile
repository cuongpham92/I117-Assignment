CC = gcc
CFLAGS = -std=c99
OBJECTS = main.o queue.o listEph.o

main : $(OBJECTS)

main.o : main.c queue.h listEph.h
queue.o : queue.c queue.h listEph.h
listEph.o : listEph.c listEph.h
clean :
	rm *.o	