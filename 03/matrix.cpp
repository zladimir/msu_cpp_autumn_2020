#include "matrix.h"
#include <iostream>

Matrix::Matrix(size_t r, size_t c)
{
	row = r;
	column = c;
	matrix = new int64_t *[row];
	for (size_t i = 0; i < row; ++i) {
		matrix[i] = new int64_t[column];
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix &other)
{
	row = other.row;
	column = other.column;
	matrix = new int64_t *[row];
	for (size_t i = 0; i < row; ++i) {
		matrix[i] = new int64_t[column];
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			matrix[i][j] = other[i][j];
		}
	}
}

Matrix &Matrix::operator=(const Matrix &other)
{
	if (this == &other) {
		return *this;
	}
	if ((row != other.row) || (column != other.column)) {
		std::cerr << "The matrices must be the same size" << std::endl;
		return *this;
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			matrix[i][j] = other[i][j];
		}
	}
	return *this;
}

size_t Matrix::getRows() const
{
	return row;
}

size_t Matrix::getColumns() const
{
	return column;
}

bool Matrix::operator==(const Matrix &B) const
{
	if ((row != B.row) || (column != B.column)) {
		return false;
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			if (B[i][j] != matrix[i][j]) {
				return false;
			}
		}
	}
	return true;
}

Matrix &Matrix::operator*=(int64_t number)
{
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			matrix[i][j] *= number;
		}
	}
	return *this;

}

bool Matrix::operator!=(const Matrix &B) const
{
	return (!(*this == B));
}

Proxy Matrix::operator[](size_t r)
{
	if (r >= row) {
		throw std::out_of_range("");
	}
	return Proxy(matrix[r], column);
}

Proxy Matrix::operator[](size_t r) const
{
	if (r >= row) {
		throw std::out_of_range("");
	}
	return Proxy(matrix[r], column);
}

Matrix Matrix::operator+(const Matrix &B) const
{
	Matrix res(B.row, B.column);
	if ((B.row == row) && (B.column == column)) {
		for (size_t i = 0; i < B.row; ++i)	{
			for (size_t j = 0; j < B.column; ++j) {
				res[i][j] = matrix[i][j] + B[i][j];
			}
		}
	} else {
		std::cerr << "Matrix addition is not possible" << std::endl;
	}
	return res;
}

std::ostream &operator<<(std::ostream &out, const Matrix &A)
{
	for (size_t i = 0; i < A.row; ++i) {
		for (size_t j = 0; j < A.column; ++j) {
			out << A[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}


Matrix::~Matrix()
{
	for (size_t i = 0; i < row; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

Proxy::Proxy(int64_t *r, size_t c)
{
	row = r;
	col_count = c;
}

int64_t &Proxy::operator[](size_t col)
{
	if (col >= col_count) {
		throw std::out_of_range("");
	}
	return row[col];
}

const int64_t &Proxy::operator[](size_t col) const
{
	if (col >= col_count) {
		throw std::out_of_range("");
	}
	return row[col];
}