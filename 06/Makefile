CC=g++
FLAGS=-std=c++17 -Wall

all: format_test

test: format_test
	./format_test

format_test: test.cpp format.hpp
	$(CC) $(FLAGS) test.cpp -o format_test

clean:
	rm format_test