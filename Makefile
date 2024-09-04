CC = gcc
CFLAGS = -Wall -pthread
OBJ = main.o list.o rwlock.o
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: src/main.c src/list.h src/rwlock.h
	$(CC) $(CFLAGS) -c src/main.c

list.o: src/list.c src/list.h src/rwlock.h
	$(CC) $(CFLAGS) -c src/list.c

rwlock.o: src/rwlock.c src/rwlock.h
	$(CC) $(CFLAGS) -c src/rwlock.c

clean:
	rm -f $(OBJ) $(EXEC)
