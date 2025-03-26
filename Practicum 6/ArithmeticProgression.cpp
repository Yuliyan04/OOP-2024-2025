#include "ArithmeticProgression.h"


ArithmeticProgression::ArithmeticProgression() : a1(1), d(1) {};

ArithmeticProgression::ArithmeticProgression(int a1, int d)
{
	this->a1 = a1;
	this->d = d;
}

ArithmeticProgression& ArithmeticProgression::operator+=(const ArithmeticProgression& other)
{
	a1 += other.a1;
	d += other.d;
	return *this;
}

ArithmeticProgression& ArithmeticProgression::operator-=(const ArithmeticProgression& other)
{
	a1 += other.a1;
	d += other.d;
	return *this;
}

ArithmeticProgression operator+(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	ArithmeticProgression res = lhs;
	res += rhs;
	return res;
}

ArithmeticProgression operator-(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs)
{
	ArithmeticProgression res = lhs;
	res -= rhs;
	return res;
}

ArithmeticProgression& ArithmeticProgression::operator+=(size_t n)
{
	a1 = a1 + n * d;
	return *this;
}

ArithmeticProgression operator+(const ArithmeticProgression& progression, size_t n)
{
	ArithmeticProgression res;
	res = progression;
	res += n;
	return res;
}

int ArithmeticProgression::operator[](size_t n) const
{
	return a1 + n * d;
}

double ArithmeticProgression::operator()(size_t n) const
{
	return (n / 2.0) * (2.0 * a1 + (n - 1) * d);
}