#include <iostream>
#include <cctype>
#include <cmath>
#include "bigint.h"

BigInt::BigInt()
{
	positive = true;
	number.push_back(0);
}

BigInt::BigInt(int32_t n)
{
	positive = (n >= 0) ? true : false;
	if (n / Base) {
		number.push_back(abs(n % Base));
		number.push_back(n / Base);
	} else {
		number.push_back(n);
	}
}

BigInt::BigInt(const std::string &s)
{
	positive = true;
	const size_t len = s.length();
	int32_t part;
	int32_t degree;
	int j;
	const char offset = '0';
	for (int i = len; i > 0; i -= 9) {
		part = 0;
		degree = 1;
		for (j = i - 1; (j >= i-9) && (j >= 0); j -= 1) {
			if (isdigit(s[j])) {
				part = (s[j] - offset)*degree + part;
				degree *= 10;
			} else {
				if ((s[j] == '-') && (j == 0)) {
					positive = false;
					if (part == 0) {
						number[number.get_size()-1] *= -1;
					} else {
						part *= -1;
					}
				} else {
					std::cerr << "Invalid input";
				}
			}
		}
		if ((part != 0) || (j > 0)) {
			number.push_back(part);
		}
	}
}

BigInt::BigInt(const BigInt &other){
	for (size_t i = 0; i < other.number.get_size(); ++i) {
		number.push_back(other.number[i]);
	}
	positive = other.sign();
}

BigInt::BigInt(BigInt &&other)
{
	positive = std::move(other.positive);
	number = std::move(other.number);
}

BigInt &BigInt::operator=(const BigInt &other)
{
	if (this == &other) {
		return *this;
	}
	number.clear();
	size_t size = other.number.get_size();
	for (size_t i = 0; i < size; ++i) {
		number.push_back(other.number[i]);
	}
	positive = other.sign();
	return *this;
}

BigInt &BigInt::operator=(BigInt &&other)
{
	if (this == &other) {
		return *this;
	}
	positive = std::move(other.positive);
	number = std::move(other.number);
	return *this;
}

bool BigInt::need_occupy(int32_t t_s, int32_t o_s, const BigInt &other) const
{
	if (t_s*o_s == -1) {
		if ((t_s == 1) && (*this > -other)) {
			return true;
		}
		if ((o_s == 1) && (-*this < other)) {
			return true;
		}
	}
	return false;
}

bool BigInt::negative_sign(int32_t t_s, int32_t o_s, const BigInt &other) const
{
	if ((t_s == -1) && (o_s == -1)) {
		return true;
	}
	if ((t_s == -1) && (*this < -other)) {
		return true;
	}
	if ((o_s == -1) && (-*this > other)) {
		return true;
	}
	return false;
}

void BigInt::insignificant_zeros()
{
	size_t size = number.get_size();
	for (int i = size - 1; i > 0; --i) {
		if (number[i] == 0) {
			number.pop_back();
		} else {
			break;
		}
	}
}

BigInt BigInt::operator+(const BigInt &other) const
{
	int32_t this_sign = (positive) ? 1 : -1;
	int32_t other_sign = (other.sign()) ? 1 : -1;
	bool occupy = need_occupy(this_sign, other_sign, other);
	BigInt res = other;
	int32_t shift = 0;
	size_t max_size = max(res.number.get_size(), number.get_size());

	for (size_t i = 0; (i < max_size) || (shift); ++i) {
		if (i > res.number.get_size() - 1) {
			res.number.push_back(0);
		}
		int32_t piece = abs(res.number[i])*other_sign + abs(number[i])*this_sign + shift;
		shift = ((piece < 0) && (occupy)) ? -1 : 0;
		if (piece / Base) {
			shift = piece / Base;
			res.number[i] = abs(piece % Base);
		} else {
			res.number[i] = abs(piece);
		}
	}
	res.insignificant_zeros();
	res.positive = true;
	if (negative_sign(this_sign, other_sign, other)) {
		res.number[res.number.get_size() - 1] *= -1;
		res.positive = false;
	}
	return res;
}

BigInt BigInt::operator-(const BigInt &other) const
{
	return (-other + *this); 
}

BigInt BigInt::operator-() const
{
	BigInt res(number[0]);
	size_t size = number.get_size();
	for (size_t i = 1; i < size; ++i)
	{
		res.number.push_back(number[i]);
	}
	res.number[size - 1] *= -1;
	res.positive = !(sign());
	return res;
}

BigInt BigInt::operator*(const BigInt &other) const
{
	int32_t shift = 0;
	int64_t piece;
	BigInt res(0);
	BigInt tmp_res(0);
	for (size_t i = 0; i < number.get_size(); ++i) {
		for (size_t j = 0; j < other.number.get_size(); ++j) {
			if (j + i > tmp_res.number.get_size() - 1) {
				tmp_res.number.push_back(0);
			}

			piece = static_cast<int64_t>(abs(other.number[j]))*static_cast<int64_t>(abs(number[i]));
			piece += static_cast<int64_t>(abs(shift));
			shift = abs(piece / Base);

			if (shift) {
				tmp_res.number[j+i] = abs(piece % Base);
			} else {
				tmp_res.number[j+i] = abs(piece);
			}
		}
		if (shift) {
			tmp_res.number.push_back(shift);
		}
		res = tmp_res + res;
		tmp_res = 0;
		for (size_t m = 0; m < i; ++m) {
			tmp_res.number.push_back(0);
		}
		shift = 0;
	}
	res.positive = true;
	bool eq_sign = (this->sign() == other.sign());
	if (!eq_sign) {
		res.number[res.number.get_size() - 1] *= -1;
		res.positive = false;
	}
	return res;
}

bool BigInt::operator==(const BigInt &other) const
{
	bool res = true;
	int32_t i = max(other.number.get_size() , number.get_size()) - 1;
	while ((res) && (i >= 0)) {
		if (other.number[i] != number[i]) {
			return false;
		}
		i = i - 1;
	}
	return res;
}

bool BigInt::operator!=(const BigInt &other) const
{
	return (!(*this == other));
}

bool BigInt::operator>(const BigInt &other) const
{
	bool res = false;
	size_t size = number.get_size();
	size_t other_size = other.number.get_size();
	if (size == other_size) {
		for (int i = size - 1; i >= 0; --i) {
			if (number[i] < other.number[i]) {
				return false;
			}
			if (number[i] > other.number[i]) {
				return true;
			}
		}
	}
	if (size < other_size) {
		if (!other.sign()) {
			return true;
		}
	}
	if (size > other_size) {
		if (sign()) {
			return true;
		}
	}
	return res;
}

bool BigInt::operator>=(const BigInt &other) const
{
	return ((*this > other) || (*this == other));
}

bool BigInt::operator<(const BigInt &other) const
{
	return (!(*this > other) && (*this != other));
}

bool BigInt::operator<=(const BigInt &other) const
{
	return (!(*this > other));
}

bool BigInt::sign() const
{
	return positive;
}

size_t number_of_digit(int32_t part)
{
	size_t i = 0;
	if (part == 0){
		return 1;
	}
	while (part) {
		part /= 10;
		i++;
	}
	return i;
}

std::ostream &operator<<(std::ostream &out, const BigInt &bigint)
{
	const size_t size = bigint.number.get_size();
	for (int i = size - 1; i >= 0; --i) {
		int32_t digits = number_of_digit(bigint.number[i]);
		if ((static_cast<size_t>(i) != size - 1) && (digits < 9)) {
			for (int j = 0; j < 9-digits; ++j)
			{
				std::cout << 0;
			}
		}
		std::cout << bigint.number[i];
	}
	return out;
}

size_t max(size_t x, size_t y)
{
	return (x > y) ? x : y;
}