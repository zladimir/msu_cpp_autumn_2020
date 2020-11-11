CC=g++
FLAGS=-std=c++17 -Wall

all: serializer_test

test: serializer_test
	./serializer_test

serializer_test: test.cpp serializer.hpp
	$(CC) $(FLAGS) test.cpp -o serializer_test

clean: 
	rm serializer_test

