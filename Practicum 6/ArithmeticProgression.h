#pragma once
#include "Vector.h"


class ArithmeticProgression
{
	int a1;
	int d;

public:

	ArithmeticProgression();
	ArithmeticProgression(int a1, int d);

	ArithmeticProgression& operator+=(const ArithmeticProgression& other);
	ArithmeticProgression& operator+=(size_t n);
	ArithmeticProgression& operator-=(const ArithmeticProgression& other);
	int operator[](size_t n) const;
	double operator()(size_t n) const;

	friend ArithmeticProgression operator+(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs);
	friend ArithmeticProgression operator+(const ArithmeticProgression& progression, size_t n);
	friend ArithmeticProgression operator-(const ArithmeticProgression& lhs, const ArithmeticProgression& rhs);
};

