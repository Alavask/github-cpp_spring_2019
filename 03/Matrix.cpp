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
		int& operator [] (const int column);
		int& operator [] (const int column) const;
		int* _rest;
		size_t _columns;
	};
	Proxi operator [] (const int row);
	Proxi operator [] (const int row) const;
	const void operator *= (const int multiplier) const;
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

int& Matrix::Proxi::operator [] (const int column)
{
	if (column < 0 || column >= _columns)
	{
		throw std::out_of_range("");
	}
	else
	{
		return _rest[column];
	}
}

int& Matrix::Proxi::operator [] (const int column) const
{
	if (column < 0 || column >= _columns)
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

	values = new int[_rows * _columns];
	memset(values, 0, _rows * _columns * sizeof(int));
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

const void Matrix::operator*=(const int multiplier) const
{
	for (size_t i = 0; i < _rows * _columns; i++)
	{
		values[i] *= multiplier;
	}
	return;
}

Matrix::Proxi Matrix::operator[](const int row)
{
	if (row < 0 || row >= _rows)
	{
		throw std::out_of_range("");
	}
	return(Proxi(values + _columns * row, _columns));
}

Matrix::Proxi Matrix::operator[](const int row) const
{
	if (row < 0 || row >= _rows)
	{
		throw std::out_of_range("");
	}
	return(Proxi(values + _columns * row, _columns));
}