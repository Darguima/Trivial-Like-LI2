CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses -ljson-c 

# Find all .c files
SOURCES := $(shell find ./src -type f -name '*.c')
# And convert them to .o files
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

triviallike: $(OBJECTS)
    # Compile main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
    # Delete recursively all objects (.o) files
	find . -type f -name '*.o' -delete

dev:
    # Clean, compile and run 
	make clean && make && make clean && ./triviallike


