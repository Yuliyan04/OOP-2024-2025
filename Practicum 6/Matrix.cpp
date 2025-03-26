#include "Matrix.h"

void Matrix::copyFrom(const Matrix& other)
{
	n = other.n;
	m = other.m;

	mtx = new int* [other.n];
	for (size_t i = 0; i < n; i++)
	{
		mtx[i] = new int[m];
		for (size_t j = 0; j < m; j++)
		{
			mtx[i][j] = other.mtx[i][j];
		}
	}
}

void Matrix::free()
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] mtx[i];
	}

	delete[] mtx;
	mtx = nullptr;
	n = 0;
	m = 0;
}

void Matrix::makeMTX(size_t n, size_t m, int num)
{
	mtx = new int* [n];

	for (size_t i = 0; i < n; i++)
	{
		mtx[i] = new int[m];
		for (size_t j = 0; j < m; j++)
		{
			mtx[i][j] = num;
		}
	}
}

Matrix::Matrix()
{
	makeMTX(2, 2, 0);
}
	
Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Matrix::~Matrix()
{
	free();
}

Matrix::Matrix(size_t n, size_t m)
{
	makeMTX(n, m, 0);
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (n == other.n && m == other.m)
	{
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				mtx[i][j] += other.mtx[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (n == other.n && m == other.m)
	{
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				mtx[i][j] -= other.mtx[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (m == other.n)
	{
		Matrix result(n, other.m);

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < other.m; j++)
			{
				for (size_t k = 0; k < m; k++)
				{
					result.mtx[i][j] += mtx[i][k] * other.mtx[k][j];
				}
			}
		}

		*this = result;
	}
	return *this;
}

Matrix& Matrix::operator*=(int num)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			mtx[i][j] *= num;
		}
	}

	return *this;
}


bool operator==(const Matrix& lhs, const Matrix& rhs) 
{
	if (lhs.n == rhs.n && lhs.m == rhs.m)
	{
		for (size_t i = 0; i < lhs.n; i++)
		{
			for (size_t j = 0; j < lhs.m; j++)
			{
				if (lhs.mtx[i][j] != rhs.mtx[i][j])
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) 
{
	return !(lhs == rhs);
}


Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix res = lhs;
	res += rhs;
	return res;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix res = lhs;
	res -= rhs;
	return res;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix res = lhs;
	res *= rhs;
	return res;
}

Matrix operator*(int num, const Matrix& lhs)
{
	Matrix res = lhs;
	res *= num;
	return res;
}

const int* Matrix::operator[](size_t ind) const
{
	return mtx[ind];
}

int* Matrix::operator[](size_t ind)
{
	return mtx[ind];
}