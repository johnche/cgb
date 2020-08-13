CFLAGS = -Wall -Wpedantic

all: clean build

build: main

main: MMU.o CPU.o

run: build
	./main bgbtest.gb

clean:
	rm -f *.o
