#pragma once

#include <iostream>

class Proxy
{
	size_t col_count;
	int64_t *row;
public:
	Proxy(int64_t *r, size_t c);
	int64_t &operator[](size_t col);
	const int64_t &operator[](size_t col) const;

};

class Matrix
{
	int64_t **matrix;
	size_t row;
	size_t column;
public:
	Matrix(size_t r, size_t c);
	Matrix(const Matrix &other);
	size_t getRows() const;
	size_t getColumns() const;
	Matrix &operator=(const Matrix &other);
	bool operator==(const Matrix &B) const;
	bool operator!=(const Matrix &B) const;
	Proxy operator[](size_t r);
	Proxy operator[](size_t r) const;
	Matrix &operator*=(int64_t number);
	Matrix operator+(const Matrix &B);
	friend std::ostream &operator<<(std::ostream &out, const Matrix &A);
	~Matrix();
};

std::ostream &operator<<(std::ostream &out, const Matrix &A);