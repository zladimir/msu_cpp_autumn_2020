CC=g++
FLAGS=-std=c++17 -Wall

all: sort_test


test: sort_test
	./sort_test

sort_test: test.o filesort.o
	$(CC) $(FLAGS) -o sort_test test.o filesort.o -lpthread

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

filesort.o: filesort.cpp filesort.hpp
	$(CC) $(FLAGS) -c filesort.cpp

clean:
	rm *.o sort_test input output