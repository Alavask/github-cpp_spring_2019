#include "Matrix.h"

using namespace std;

Matrix::Proxi::Proxi(int* rest, size_t columns)
{
	_rest = rest;
	_columns = columns;
}

int& Matrix::Proxi::operator [] (const size_t column)
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

Matrix::Proxi Matrix::operator[](const size_t row)
{
	if (row >= _rows)
	{
		throw std::out_of_range("");
	}
	return(Proxi(values + _columns * row, _columns));
}

const Matrix::Proxi Matrix::operator[](const size_t row) const
{
	if (row >= _rows)
	{
		throw std::out_of_range("");
	}
	return(Proxi(values + _columns * row, _columns));
}