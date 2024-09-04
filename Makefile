CC=gcc
CFLAGS=-pthread

all: main

main: main.o list.o rwlock.o
    $(CC) $(CFLAGS) -o main main.o list.o rwlock.o

main.o: main.c list.h rwlock.h
    $(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
    $(CC) $(CFLAGS) -c list.c

rwlock.o: rwlock.c rwlock.h
    $(CC) $(CFLAGS) -c rwlock.c

clean:
    rm -f main main.o list.o rwlock.o