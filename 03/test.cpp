#include "matrix.h"
#include <iostream>
#include <cassert>

void test1()
{
	Matrix a(3, 4);
	a[1][1] = 3;
	a[2][3] = -4;
	a[0][0] = 1;
	a *= 3;
	assert((a[1][1] == 9) && (a[2][3] == -12) && (a[0][0] == 3));
	assert((a.getRows() == 3));
	assert((a.getColumns() == 4));
	Matrix b = a;
	b[0][1] = 15;
	bool equality = (a == b);
	assert(equality == 0);
}

void test2()
{
	Matrix a(3, 2);
	a[0][0] = 1; a[0][1] = 2;
	a[1][0] = 3; a[1][1] = 4;
	a[2][0] = 5; a[2][1] = 6;
	Matrix b = a + a;
	assert(b[1][0] == 2*a[1][0]);
}

void test3()
{
	const size_t rows = 5;
	const size_t cols = 3;
	Matrix m(rows, cols);
	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);
	m[1][2] = 5;
	m *= 3;
	Matrix m1(rows, cols);
	if (m1 == m)
	{
		std::cerr << "Wrong answer" << std::endl;
	}
	Matrix m2 = m1 + m;
	std::cout << m2;
}

void test4()
{
	Matrix c(3, 4);
	try {
		int64_t value = c[60][60];
		std::cout << value << std::endl;
	}
	catch(const std::out_of_range &e) {
		std::cerr << e.what() << std::endl;
	}
	Matrix a(3, 4);
	Matrix b(3, 4);
	a[2][3] = 9;
	b[2][3] = 7;
	c = a + b;
	assert(c[2][3] == 16);
}

int main(int argc, char const *argv[])
{
	test1();
	test2();
	test3();
	test4();
	return 0;
}