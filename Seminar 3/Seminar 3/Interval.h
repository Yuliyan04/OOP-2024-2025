#pragma once

class Interval
{
	int a;
	int b;

public:
	Interval() : a(0), b(0) {};
	Interval(int a, int b);
	
	void setA(int a);
	void setB(int b);

	int getA() const;
	int getB() const;

	unsigned getIntervalLength() const;
	bool isFromInterval(int n) const;
	unsigned getPrimesCount() const;
	unsigned palindromesCount() const;
	unsigned getUniqueDigitsNumbers() const;
	bool areBegAndEndPowersOfTwo() const;
	Interval intersection(const Interval& other) const;
	bool isIntervalFromInterval(const Interval& other) const;

private:
	void mark(bool* arr, size_t size, int mark) const;
	void fill(bool* arr, size_t size) const;
	bool isPalindrome(int n) const;
	bool hasUniqueDigits(int n) const;
	bool isPowerOfTwo(int n) const;
};

