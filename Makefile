CFLAGS = -Wall -Wpedantic

all: clean build

build: main

main: MMU.o Z80.o

clean:
	rm -f *.o
