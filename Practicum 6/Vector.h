#pragma once
#include <fstream>


class Vector
{
	int* vector;
	size_t size;

public:

	Vector(const int* arr, size_t size);

	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void serializeBin(const char* filename) const;
	Vector deserializeBin(const char* filename);

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(int scalar);
	int& operator[](size_t ind);
	const int& operator[](size_t ind) const;
	friend Vector operator+(const Vector& lhs, const Vector& rhs);
	friend Vector operator-(const Vector& lhs, const Vector& rhs);
	friend Vector operator*(int scalara, const Vector& lhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector& other);
	friend std::istream& operator>>(std::istream& is, Vector& v);

	size_t getSize() const;
	bool isZero() const;

private:

	void copyFrom(const Vector& other);
	void free();
};