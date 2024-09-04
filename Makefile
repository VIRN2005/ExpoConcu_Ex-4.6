CC=gcc
CFLAGS=-pthread

all: main

main: main.c list.c rwlock.c
    $(CC) $(CFLAGS) -o main main.c list.c rwlock.c

clean:
    rm -f main