#include "Vector.h"


void Vector::copyFrom(const Vector& other)
{
	vector = new int[other.size];
	size = other.size;

	for (size_t i = 0; i < size; i++)
	{
		vector[i] = other.vector[i];
	}
}

void Vector::free()
{
	delete[] vector;
	size = 0;
	vector = nullptr;
}



Vector::Vector()
{
	size = 3;
	vector = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		vector[i] = 0;
	}
}

Vector::Vector(const Vector& other)
{
	copyFrom(other);
}


Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Vector::~Vector()
{
	free();
}

Vector::Vector(const int* arr, size_t size) :Vector()
{
	if (!arr)
	{
		return;
	}

	this->size = size;
	vector = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		vector[i] = arr[i];
	}
}


void Vector::serializeBin(const char* filename) const
{
	if (!filename)
	{
		return;
	}

	std::ofstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		return;
	}

	file.write((const char*)& size, sizeof(size));
	file.write((const char*)vector, sizeof(int) * size);

	file.close();
}

Vector Vector::deserializeBin(const char* filename)
{
	if (!filename)
	{
		return {};
	}

	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		return {};
	}

	size_t size;
	file.read((char*)&size, sizeof(size));

	int* arr = new int[size];
	file.read((char*)arr, sizeof(int) * size);

	Vector res(arr, size);
	file.close();

	return res;
}


std::ostream& operator<<(std::ostream& os, const Vector& other)
{
	for (size_t i = 0; i < other.size; i++)
	{
		if (i == other.size - 1)
		{
			os << other.vector[i];
		}

		os << other.vector[i] << ", ";
	}
	return os;
}



Vector& Vector::operator+=(const Vector& other)
{
	if (other.size == size)
	{
		for (size_t i = 0; i < size; i++)
		{
			vector[i] += other.vector[i];
		}
	}
	return *this;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	if (lhs.size == lhs.size)
	{
		Vector res = lhs;
		res += rhs;

		return res;
	}
	return {};
}

Vector& Vector::operator-=(const Vector& other)
{
	if (other.size == size)
	{
		for (size_t i = 0; i < size; i++)
		{
			vector[i] -= other.vector[i];
		}
	}
	return *this;
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	if (lhs.size == lhs.size)
	{
		Vector res = lhs;
		res -= rhs;

		return res;
	}
	return {};
}

Vector& Vector::operator*=(int scalar)
{
	for (size_t i = 0; i < size; i++)
	{
		vector[i] *= scalar;
	}
	return *this;
}

Vector operator*(int scalar, const Vector& lhs)
{
	Vector res = lhs;
	res *= scalar;

	return res;
}

std::istream& operator>>(std::istream& is, Vector& v)
{
	size_t size;
	is >> size;

	int* vector = new int[size];
	for (size_t i = 0; i < v.size; i++)
	{
		is >> vector[i];
	}

	if (size > 0)
	{
		v.free();
		v.vector = vector;
		v.size = size;
	}

	return is;
}

size_t Vector::getSize() const
{
	return size;
}

bool Vector::isZero() const
{
	for (size_t i = 0; i < size; i++)
	{
		if (vector[i] != 0)
		{
			return false;
		}
	}
	return true;
}

const int& Vector::operator[](size_t ind) const
{
	return vector[ind];
}

int& Vector::operator[](size_t ind)
{
	return vector[ind];
}