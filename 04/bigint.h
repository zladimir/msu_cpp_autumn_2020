#pragma once

#include <iostream>
#include "list.h"

class BigInt {
	List number;
	bool positive;
	const int32_t Base = 1000000000; 
public:
	BigInt();
	BigInt(int32_t n);
	BigInt(const std::string &s);
	BigInt(const BigInt &other);
	BigInt(BigInt &&other);
	BigInt &operator=(const BigInt &other);
	BigInt &operator=(BigInt &&other);
	BigInt operator+(const BigInt &other) const;
	BigInt operator-(const BigInt &other) const;
	BigInt operator-() const;
	BigInt operator*(const BigInt &other) const;
	bool need_occupy(int32_t t_s, int32_t o_s, const BigInt &other) const;
	bool negative_sign(int32_t t_s, int32_t o_s, const BigInt &other) const;
	void insignificant_zeros();
	bool operator==(const BigInt &other) const;
	bool operator!=(const BigInt &other) const;
	bool operator>(const BigInt &other) const;
	bool operator>=(const BigInt &other) const;
	bool operator<(const BigInt &other) const;
	bool operator<=(const BigInt &other) const;
	bool sign() const;
	friend std::ostream &operator<<(std::ostream &out, const BigInt &bigint);
	~BigInt() = default;
};

std::ostream &operator<<(std::ostream &out, const BigInt &bigint);
size_t max(size_t x, size_t y);
size_t number_of_digit(size_t part);