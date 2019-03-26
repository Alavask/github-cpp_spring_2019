#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

class Matrix
{
public:
	Matrix(size_t rows, size_t columns);
	size_t getRows();
	size_t getColumns();
	~Matrix();
	struct Proxi
	{
		Proxi(int* rest, size_t columns);
		int& operator [] (const size_t column) const;
		int* _rest;
		size_t _columns;
	};
	const Proxi operator [] (const size_t row) const;
	Matrix& operator *= (const int multiplier);
	bool operator != (const Matrix& a);
	bool operator == (const Matrix& a);

private:
	size_t _rows;
	size_t _columns;
	int* values;
};