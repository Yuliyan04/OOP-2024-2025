#include "Interval.h"

void Interval::setA(int a)
{
	if (a <= b)
	{
		this->a = a;
	}
}

void Interval::setB(int b)
{
	if (a <= b)
	{
		this->b = b;
	}
}

Interval::Interval(int a, int b)
{
	setA(a);
	setB(b);
}

int Interval::getA() const
{
	return a;
}

int Interval::getB() const
{
	return b;
}

unsigned Interval::getIntervalLength() const
{
	return b - a;
}

bool Interval::isFromInterval(int n) const
{
	return n >= a && n <= b;
}

void Interval::mark(bool* arr, size_t size, int mark) const
{
	for (int i = mark * 2; i < size; i += mark)
	{
		arr[i] = false;
	}
}

void Interval::fill(bool* arr, size_t size) const
{
	arr[0] = false;
	arr[1] = false;

	for (size_t i = 2; i < size; i++)
	{
		arr[i] = true;
	}
}

unsigned Interval::getPrimesCount() const
{
	bool* eratosthenes = new bool[b + 1];
	fill(eratosthenes, b + 1);
	
	for (int i = 2; i * i < b; i++)
	{
		if (eratosthenes[i]) 
		{
			mark(eratosthenes, b + 1, i);
		}
	}

	unsigned count = 0;
	for (int i = a; i <= b; i++)
	{
		if (eratosthenes[i])
		{
			count++;
		}
	}

	delete[] eratosthenes;
	return count;
}


bool Interval::isPalindrome(int n) const
{
	unsigned original = n;
	int toCompare = 0;
	int mult = 1;

	while (n != 0)
	{
		toCompare = (toCompare * mult) + n % 10;
		mult *= 10;
		n /= 10;
	}

	return toCompare == original;
}

unsigned Interval::palindromesCount() const
{
	unsigned count = 0;

	for (int i = a; i <= b; i++)
	{
		if (isPalindrome(i))
		{
			count++;
		}
	}
	return count;
}

bool Interval::hasUniqueDigits(int n) const
{
	int digitsOccurs[10]{ 0 };

	while (n != 0)
	{
		unsigned currDigit = n % 10;
		digitsOccurs[currDigit]++;
		n /= 10;
	}

	for (int i = 0; i <= 9; i++)
	{
		if (digitsOccurs[i] > 1)
		{
			return false;
		}
	}

	return true;
}

unsigned Interval::getUniqueDigitsNumbers() const
{
	unsigned count = 0;
	
	for (int i = a; i <= b; i++)
	{
		if (hasUniqueDigits(i))
		{
			count++;
		}
	}

	return count;
}

bool Interval::isPowerOfTwo(int n) const
{
	int countOfOnes = 0;

	while (n != 0)
	{
		if (n % 2 == 1)
		{
			countOfOnes++;
		}

		if (countOfOnes > 1)
		{
			return false;
		}

		n /= 10;
	}
	return true;
}

bool Interval::areBegAndEndPowersOfTwo() const
{
	return isPowerOfTwo(a) && isPowerOfTwo(b);
}

Interval Interval::intersection(const Interval& other) const
{
	if (!isFromInterval(other.a))
	{
		return {};
	}

	int newA = a > other.a ? a : other.a;
	int newB = b < other.b ? b : other.b;

	Interval res(newA, newB);
	return res;
}

bool Interval::isIntervalFromInterval(const Interval& other) const
{
	return other.a >= a && other.b <= b;
}