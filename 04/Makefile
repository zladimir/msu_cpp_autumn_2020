CC=g++
FLAGS=-std=c++17 -Wall

all: bigint_test

test: bigint_test
	./bigint_test

bigint_test: test.o list.o bigint.o
	$(CC) $(FLAGS) -o bigint_test test.o list.o bigint.o

list.o: list.cpp list.h
	$(CC) $(FLAGS) -c list.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) $(FLAGS) -c bigint.cpp

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm *.o bigint_test