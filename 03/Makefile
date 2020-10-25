CC=g++
FLAGS=-std=c++17 -Wall

all: matrix_test

test: matrix_test
	./matrix_test

matrix_test: test.o matrix.o
	$(CC) $(FLAGS) -o matrix_test test.o matrix.o

matrix.o: matrix.cpp matrix.h
	$(CC) $(FLAGS) -c matrix.cpp

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm *.o matrix_test