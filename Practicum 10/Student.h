#pragma once
#include "MyString.h"


class Student
{
	MyString name;
	unsigned fn;
	unsigned year;

public:

	void setName(const MyString& name);
	void setYear(unsigned newYear);
	void setFN(unsigned newFN);

	MyString getName() const;
	unsigned getFN() const;
	unsigned getYear() const;
	void print() const;

private:

	bool validateFN(unsigned fn) const;
	bool validateName(const MyString& name);
};

