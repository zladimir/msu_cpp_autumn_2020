#include <iostream>
#include "allocator.h"

void check(char *p, bool mem_should_be_alloc)
{
	if (p == nullptr) {
		if (mem_should_be_alloc) {
			std::cout << "Incorrect behavior" << std::endl;
		}
	} else {
		if (!mem_should_be_alloc) {
			std::cout << "Incorrect behavior" << std::endl;
		}
	}
}

void test_1()
{
	std::cout << "Test 1" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(100);
	ptr = a.alloc(100);
	check(ptr, true);
}

void test_2()
{
	std::cout << "Test 2" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(10);
	ptr = a.alloc(3);
	check(ptr, true);
	ptr = a.alloc(2);
	check(ptr, true);
	ptr = a.alloc(5);
	check(ptr, true);
}

void test_3()
{
	std::cout << "Test 3" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(5);
	ptr = a.alloc(3);
	check(ptr, true);
	ptr = a.alloc(2);
	check(ptr, true);
	a.reset();
	ptr = a.alloc(2);
	check(ptr, true);
	ptr = a.alloc(1);
	check(ptr, true);
	ptr = a.alloc(2);
	check(ptr, true);
}

void test_4()
{
	std::cout << "Test 4" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(100);
	ptr = a.alloc(60);
	check(ptr, true);
	ptr = a.alloc(25);
	check(ptr, true);
	a.reset();
	ptr = a.alloc(45);
	check(ptr, true);
	ptr = a.alloc(45);
	check(ptr, true);
	ptr = a.alloc(5);
	check(ptr, true);
	ptr = a.alloc(50);
	check(ptr, false);
}

void test_5()
{
	std::cout << "Test 5" << std::endl;
	Allocator a;
	a.makeAllocator(900000000000);
}

void test_6()
{
	std::cout << "Test 6" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(60);
	ptr = a.alloc(45);
	check(ptr, true);
	a.makeAllocator(120);
	ptr = a.alloc(15);
	check(ptr, true);
}

int main(int argc, char const *argv[])
{
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	return 0;
}
