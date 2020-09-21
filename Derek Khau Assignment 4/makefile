CC = gcc
CFLAGS = -ansi -Wall -g -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)main

$(BINDIR)main: $(BINDIR)functions.o $(BINDIR)main.o
	$(CC) $(BINDIR)functions.o $(BINDIR)main.o -o $@

$(BINDIR)main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c -o $@

$(BINDIR)functions.o: $(SRCDIR)functions.c
	$(CC) $(CFLAGS) -c $(SRCDIR)functions.c -o $@

clean:
	rm bin/*.o ./bin/main

run:
	./bin/main
