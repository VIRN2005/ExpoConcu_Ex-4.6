CC = gcc
CFLAGS = -Wall -pthread
OBJ = main.o list.o rwlock.o

all: main

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS)

main.o: src/main.c src/list.h src/rwlock.h
	$(CC) -c src/main.c $(CFLAGS)

list.o: src/list.c src/list.h src/rwlock.h
	$(CC) -c src/list.c $(CFLAGS)

rwlock.o: src/rwlock.c src/rwlock.h
	$(CC) -c src/rwlock.c $(CFLAGS)

clean:
	rm -f *.o main
