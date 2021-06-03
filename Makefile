# Compila o programa inteiro

# Variávies
CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall

# Regra : dependências
all: listaDeDados.o main.o
	$(CC) $(CFLAGS) main.o lib/listaDeDados.o -lm -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

listaDeDados.o: lib/listaDeDados.h
	$(CC) $(CFLAGS) -c lib/listaDeDados.c -o lib/listaDeDados.o

clean:
	rm *.o
	rm lib/*.o

run:
	./main

debug: listaDeDados.o main.o
	$(CC) $(CFLAGS) -g main.o lib/listaDeDados.o -lm -o main
