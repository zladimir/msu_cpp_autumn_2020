#include <iostream>
#include "bigint.h"
#include <cassert>

void test1()
{
	BigInt a = 1;
	BigInt b("123456789012345678901234567890");
	BigInt c = a * b + 2;
	assert(c == b + 2);
	BigInt d;
	d = std::move(c);
	a = d + b;
	std::cout << a << std::endl;
}

void test2()
{
	BigInt a(99384318);
	BigInt b = std::move(a);
	b = b*b;
	BigInt c("-23456200002345");
	BigInt d = c + b;
	BigInt res("9853786464322779");
	assert(d == res);
	assert((d > c) && (c < b));
	assert(c == d + c - d);
}

void test3()
{
	BigInt a(0);
	BigInt b("-999999999999999999");
	assert(a-b == -b);
	BigInt c("-123456789101213141516171819");
	BigInt d(-555);
	BigInt e("-123456789101213141516171264");
	assert(c-d == e);
	assert(c+c == c*2);
	BigInt f("-246913578202426283032343083");
	assert(c+e == f);
	e = 5;
	e = std::move(c);
}

void test4()
{
	BigInt a("3283213");
	BigInt b("3843213843284321531384321");
	BigInt c("12618089652051047148020910703373");
	assert(c == a*b);
	assert(a*b == -a*(-b));
	assert(-a*b == -b*a);
	BigInt d("354841386431831583");
	BigInt res("1363731328505016562019037448287581518810143");
	assert(d*b == res);
	BigInt e("1999999999");
	BigInt g("3999999996000000001");
	assert(-e*e == -g);
}

void test5() {
	BigInt a(0);
	std::cout << a << std::endl;
	BigInt b("0");
	std::cout << b << std::endl;
	BigInt c("135435184351313813184354843");
	std::cout << c-c << std::endl;
}

int main(int argc, char const *argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	std::cout << "success" << std::endl;

	return 0;
}