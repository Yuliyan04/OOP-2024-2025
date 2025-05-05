#include "Student.h"


MyString Student::getName() const
{
	return name;
}

unsigned Student::getFN() const
{
	return fn;
}

unsigned Student::getYear() const
{
	return year;
}


void Student::setName(const MyString& name)
{
	if (validateName(name))
	{
		this->name = name;
	}
}

void Student::setYear(unsigned newYear)
{
	if (year >= 1 && year <= 6)
	{
		year = newYear;
	}
}

void Student::setFN(unsigned newFN)
{
	if (validateFN)
	{
		fn = newFN;
	}
}

bool Student::validateFN(unsigned fn) const
{
	//some logic for valid fn
}

bool Student::validateName(const MyString& name)
{
	//some logic for validating name string
}

void Student::print() const
{
	std::cout << name << std::endl;
	std::cout << fn << std::endl;
	std::cout << year << std::endl;
}