CC = g++

CFLAGS  = -Wall -std=c++11
DIR = ./tests/

all: main

tree.o: tree.cpp
	$(CC) $(CFLAGS) -Itests -c tree.cpp

main.o:  main.cpp tree.hpp
	$(CC) $(CFLAGS) -Itests -c main.cpp tree.hpp

tests.o: $(DIR)tests.cpp
	$(CC) $(CFLAGS) -Itests -c $(DIR)tests.cpp

main: main.o tree.o tests.o
	$(CC) $(CFLAGS) -Itests -o main main.o tree.o tests.o

clean:
	$(RM) main *.o *.hpp.gch