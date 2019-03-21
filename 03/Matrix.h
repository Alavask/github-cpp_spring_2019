#pragma once

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