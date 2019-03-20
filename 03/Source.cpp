#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#define check_equal(x, y)  do { if ((x) != y) std::cout << "line " << __LINE__ << ": expected " << y << " got " << (x) << '\n'; } while(0)
#define check(cond) do { if (!(cond)) std::cout << "line " << __LINE__ << ": " << #cond << '\n'; } while(0)
#define check_throw(expr, err) do { try { expr; } catch (const err&) { break ; } catch (...) { } std::cout << "line " << __LINE__ << '\n'; } while(0)


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
		Proxi(int* rest, size_t columns)
		{
			_rest = rest;
			_columns = columns;
		}

		int& operator [] (const int column)
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

		int& operator [] (const int column) const
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

		int* _rest;
		size_t _columns;
	};
	Proxi operator [] (const int row);
	Proxi operator [] (const int row) const;
	Matrix operator *= (const int multiplier);
	bool operator != (const Matrix& a);
	bool operator == (const Matrix& a);

private:
	size_t _rows;
	size_t _columns;
	int* values;
};

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
	delete values;
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
			return true;
		}
	}
	return false;
}

Matrix Matrix::operator*=(const int multiplier)
{
	for (size_t i = 0; i < _rows * _columns; i++)
	{
		values[i] *= multiplier;
	}
	return *this;
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

int main()
{
	int n = 0;

	Matrix m1(2, 3);
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			m1[row][col] = ++n;
		}
	}

	check_equal(m1[0][0], 1);
	check_equal(m1[0][1], 2);
	check_equal(m1[0][2], 3);
	check_equal(m1[1][0], 4);
	check_equal(m1[1][1], 5);
	check_equal(m1[1][2], 6);

	check_equal(m1.getRows(), 2);
	check_equal(m1.getColumns(), 3);

	check_throw(m1[0][3], std::out_of_range);
	check_throw(m1[2][0], std::out_of_range);

	m1 *= 2;

	const Matrix& m2 = m1;

	check_equal(m2[0][0], 1 * 2);
	check_equal(m2[0][1], 2 * 2);
	check_equal(m2[0][2], 3 * 2);
	check_equal(m2[1][0], 4 * 2);
	check_equal(m2[1][1], 5 * 2);
	check_equal(m2[1][2], 6 * 2);

	Matrix m3(0, 0);
	check_throw(m3[0][0], std::out_of_range);

	const Matrix& m4 = m1;

	Matrix m5(2, 3);

	check(m1 == m1);
	check(m1 != m3);
	check(m1 == m4);
	check(m1 != m5);

	std::cout << "done\n";

	return 0;
}