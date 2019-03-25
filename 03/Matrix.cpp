#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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

Matrix::Proxi::Proxi(int* rest, size_t columns)
{
	_rest = rest;
	_columns = columns;
}

int& Matrix::Proxi::operator [] (const size_t column) const
{
	if (column >= _columns)
	{
		throw std::out_of_range("");
	}
	else
	{
		return _rest[column];
	}
}

Matrix::Matrix(size_t rows, size_t columns)
{
	_rows = rows;
	_columns = columns;

	values = new int[_rows * _columns]();
}

size_t Matrix::getRows()
{
	return _rows;
}

size_t Matrix::getColumns()
{
	return _columns;
}

Matrix::~Matrix()
{
	delete[] values;
}

bool Matrix::operator != (const Matrix& a)
{
	return !(this == &a);
}

bool Matrix::operator == (const Matrix& a)
{
	if (_rows == a._rows&&_columns == a._columns)
	{
		for (size_t i = 0; i < _rows * _columns; i++)
		{
			if (values[i] != a.values[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

Matrix& Matrix::operator*=(const int multiplier)
{
	for (size_t i = 0; i < _rows * _columns; i++)
	{
		values[i] *= multiplier;
	}
	return *this;
}

const Matrix::Proxi Matrix::operator[](const size_t row) const
{
	if (row >= _rows)
	{
		throw std::out_of_range("");
	}
	return(Proxi(values + _columns * row, _columns));
}