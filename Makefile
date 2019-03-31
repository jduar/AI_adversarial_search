CC=gcc
CFLAGS=-Wall -lm

main: main.c 4linha.h minmax.h alphabeta.h mytree.h montecarlo.h
	$(CC) -o main main.c $(CFLAGS)

clean:
	rm -rf *.o main
