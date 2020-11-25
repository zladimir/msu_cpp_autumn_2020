CC=g++
FLAGS=-std=c++17 -Wall

all: vector

test: vector
	./vector

vector: test.cpp myvector.hpp
	$(CC) $(FLAGS) test.cpp -o vector

clean:
	rm vector