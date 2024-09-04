# Variables
CC = gcc
CFLAGS = -Wall -pthread
DEPS = rwlock.h list.h
OBJ = list.o main.o rwlock.o
EXEC = list_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

main.o: main.c list.h rwlock.h
	$(CC) $(CFLAGS) -c main.c

rwlock.o: rwlock.c rwlock.h
	$(CC) $(CFLAGS) -c rwlock.c

clean:
	rm -f $(EXEC) $(OBJ)
