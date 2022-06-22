PROGRAM=main
CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic
LDFLAGS=-lSDL2

all: $(PROGRAM)
$(PROGRAM): main.o caracteres.o
	$(CC) $(CFLAGS) main.o caracteres.o -o $(PROGRAM) $(LDFLAGS)
main.o: main.c caracteres.h config.h
	$(CC) $(CFLAGS) -c main.c
caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) -c caracteres.c
clean:
	rm -vf *.o $(PROGRAM)
.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

