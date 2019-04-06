CC=gcc
CFLAGS=-lm -g

main: main.c 4linha.h minmax.h alphabeta.h mytree.h monte_carlo.h
	$(CC) -o main main.c $(CFLAGS)

clean:
	rm -rf *.o main
