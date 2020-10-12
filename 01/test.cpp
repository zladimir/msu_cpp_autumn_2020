#include <iostream>
#include "allocator.h"

bool check(char *p)
{
	if (p == nullptr){
		std::cout << "WARNING:\tYou can not allocate that much memory" << std::endl;
		return 1;
	} else {
		return 0;
	}
}

void test_1()
{
	std::cout << "Test 1" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(100);
	ptr = a.alloc(100);
	check(ptr);
}

void test_2()
{
	std::cout << "Test 2" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(10);
	ptr = a.alloc(3);
	check(ptr);
	ptr = a.alloc(2);
	check(ptr);
	ptr = a.alloc(5);
	check(ptr);
}

void test_3()
{
	std::cout << "Test 3" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(5);
	ptr = a.alloc(3);
	check(ptr);
	ptr = a.alloc(2);
	check(ptr);
	a.reset();
	ptr = a.alloc(2);
	check(ptr);
	ptr = a.alloc(1);
	check(ptr);
	ptr = a.alloc(2);
	check(ptr);
}

void test_4()
{
	std::cout << "Test 4" << std::endl;
	char *ptr;
	Allocator a;
	a.makeAllocator(100);
	ptr = a.alloc(60);
	check(ptr);
	ptr = a.alloc(25);
	check(ptr);
	a.reset();
	ptr = a.alloc(45);
	check(ptr);
	ptr = a.alloc(45);
	check(ptr);
	ptr = a.alloc(5);
	check(ptr);
	ptr = a.alloc(50);
	check(ptr);
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
	check(ptr);
	a.makeAllocator(120);
	ptr = a.alloc(15);
	check(ptr);
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
