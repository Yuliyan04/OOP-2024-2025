#pragma once

class Matrix
{
	int** mtx;
	size_t n;
	size_t m;

public:
	Matrix(size_t n, size_t m);

	Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	const int* operator[](size_t ind) const;
	int* operator[](size_t ind);
	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(int num);
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(int num, const Matrix& lhs);
	friend bool operator==(const Matrix& lhd, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

private:

	void copyFrom(const Matrix& other);
	void free();
	void makeMTX(size_t n, size_t m, int num);
};

