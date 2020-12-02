CC=g++
FLAGS=-std=c++17 -Wall

all: pooltest

test: pooltest
	./pooltest

pooltest: test.cpp thread_pool.hpp
	$(CC) $(FLAGS) test.cpp -o pooltest -lpthread

clean:
	rm pooltest