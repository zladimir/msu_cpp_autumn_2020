CC=g++
FLAGS=-std=c++17 -Wall

all: parser

test: parser
	./parser

parser: token_parser.o test.o
	$(CC) $(FLAGS) -o parser token_parser.o test.o

token_parser.o: token_parser.cpp token_parser.h
	$(CC) $(FLAGS) token_parser.cpp -c

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -c

clean:
	rm *.o parser
