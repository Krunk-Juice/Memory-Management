CC = g++
#CFLAGS = -c -Wall
CFLAGS = -c

all: mm

mm: main.o
	$(CC) main.o -o mm

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *o mm