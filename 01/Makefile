CC=g++
FLAGS=-std=c++17 -Wall

all: allocator

test: allocator
	./allocator

allocator: test.o allocator.o
	$(CC) $(FLAGS) -o allocator test.o allocator.o

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) allocator.cpp -c

clean:
	rm *.o allocator
