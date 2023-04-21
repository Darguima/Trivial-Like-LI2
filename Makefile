CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

# $(SRCS:.c=.o) => will compile all .c files to a .o file with the same name

jogo: $(SRCS:.c=.o)
# Compile main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
# Delete recursively all objects (.o) files
	find . -type f -name '*.o' -delete

dev:
# Clean, compile and run 
	make clean && make && make clean && ./jogo
