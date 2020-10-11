#include <iostream>

class Allocator
{
	size_t max_size_, available_size_;
	char *memory_begin_, *offset_;
public:
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};