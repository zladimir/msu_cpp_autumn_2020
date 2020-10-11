#include <iostream>
#include "allocator.h"

bool check(char *p)
{
	if (p == nullptr){
		std::cout << "-\nWARNING:\tYou can not allocate that much memory" << std::endl;
		return 1;
	} else {
		std::cout << static_cast<void *>(p) << std::endl;
		return 0;
	}
}

void alloc_command_printer(char *p, size_t num_bytes)
{
	std::cout << "COMMAND:\talloc(" << num_bytes << ")\nANSWER: \tpointer to begin of memory: ";
	check(p);
}

void test_1(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tEasy case" << std::endl;
	char *ptr;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	ptr = a.alloc(size);
	alloc_command_printer(ptr, size);
}

void test_2(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tA few of the alloc" << std::endl;
	char *ptr;
	int num_bytes;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	num_bytes = 3;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 2;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 5;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
}

void test_3(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tA few of the alloc with reset()" << std::endl;
	char *ptr;
	int num_bytes;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	num_bytes = 3;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 2;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	std::cout << "COMMAND:\treset()" << std::endl;
	a.reset();
	num_bytes = 2;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 1;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 2;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
}

void test_4(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tNot enough memory for alloc" << std::endl;
	char *ptr;
	int num_bytes;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	num_bytes = 60;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 115;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	std::cout << "COMMAND:\treset()" << std::endl;
	a.reset();
	num_bytes = 45;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 45;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 50;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 5;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
}

void test_5(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tNot enough memory for initialization" << std::endl;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
}

void test_6(size_t size)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << "TEST:\t\tmakeAllocator change case" << std::endl;
	char *ptr;
	int num_bytes;
	Allocator a;
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	num_bytes = 45;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	std::cout << "COMMAND:\tmakeAllocator(" << size << ")" << std::endl;
	a.makeAllocator(size);
	num_bytes = 25;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
	num_bytes = 15;
	ptr = a.alloc(num_bytes);
	alloc_command_printer(ptr, num_bytes);
}

int main(int argc, char const *argv[])
{
	test_1(100);
	test_2(10);
	test_3(5);
	test_4(100);
	test_5(900000000000);
	test_6(60);
	return 0;
}
