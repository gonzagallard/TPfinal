PROGRAM=main
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
SDLFLAG=-lSDL2
LMFLAG=-lm

all: $(PROGRAM)
$(PROGRAM): main.o caracteres.o nave.o
	$(CC) $(CFLAGS) main.o caracteres.o nave.o -o $(PROGRAM) $(SDLFLAG) $(LMFLAG)
main.o: main.c caracteres.h config.h
	$(CC) $(CFLAGS) -c main.c
caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) -c caracteres.c
nave.o: nave.c nave.h config.h
	$(CC) $(CFLAGS) -c nave.c 
clean:
	rm -vf *.o $(PROGRAM)
.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

