# Variables
CC = gcc
CFLAGS = -Wall -pthread
SRCDIR = src
DEPS = $(SRCDIR)/rwlock.h $(SRCDIR)/list.h
OBJ = $(SRCDIR)/list.o $(SRCDIR)/main.o $(SRCDIR)/rwlock.o
EXEC = list_program

# Regla para compilar el ejecutable
all: $(EXEC)

# Regla para enlazar los archivos objeto
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Regla para compilar list.c en list.o
$(SRCDIR)/list.o: $(SRCDIR)/list.c $(DEPS)
	$(CC) $(CFLAGS) -c $(SRCDIR)/list.c -o $(SRCDIR)/list.o

# Regla para compilar main.c en main.o
$(SRCDIR)/main.o: $(SRCDIR)/main.c $(DEPS)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(SRCDIR)/main.o

# Regla para compilar rwlock.c en rwlock.o
$(SRCDIR)/rwlock.o: $(SRCDIR)/rwlock.c $(SRCDIR)/rwlock.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/rwlock.c -o $(SRCDIR)/rwlock.o

# Regla para limpiar archivos compilados
clean:
	rm -f $(EXEC) $(OBJ)
