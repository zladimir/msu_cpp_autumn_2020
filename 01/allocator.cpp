#include "allocator.h"
#include <iostream>

Allocator::Allocator()
{
	max_size_ = 0;
	available_size_ = 0;
	memory_begin_ = nullptr;
	offset_ = nullptr;
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (memory_begin_ == nullptr) {
		try {
			memory_begin_ = new char[maxSize];
			max_size_ = maxSize;
			available_size_ = maxSize;
			offset_ = memory_begin_;
		} 
		catch(const std::bad_alloc &e) {
			std::cout << "ERROR:  \t" << e.what() << std::endl;
		}
	} else {
		std::cout << "WARNING:\tYou can't change the size of the allocator" << std::endl;
	}
}

char *Allocator::alloc(size_t size)
{
	if (size <= available_size_) {
		char *tmp = offset_;
		offset_ += size;
		available_size_ -= size;
		return tmp;
	} else {
		return nullptr;
	}
}

void Allocator::reset()
{
	available_size_ = max_size_;
	offset_ = memory_begin_;
	return;
}

Allocator::~Allocator()
{
	delete[] memory_begin_;
}
