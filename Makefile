CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: src/main.o src/mapa.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm src/*.o

dev:
	make && ./jogo && make clean
