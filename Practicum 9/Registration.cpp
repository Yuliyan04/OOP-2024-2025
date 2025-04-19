#include "Registration.h"


bool Registration::isValidNumber(const char* number) const
{
	int firstLettersCount = 0;
	while (*number >= 'A' && *number <= 'Z')
	{
		firstLettersCount++;
		number++;
	}

	int digitsCount = 0;
	while (*number >= '0' && *number <= '9')
	{
		digitsCount++;
		number++;
	}

	int lastLettersCount = 0;
	while (*number >= 'A' && *number <= 'Z')
	{
		lastLettersCount++;
		number++;
	}

	if ((firstLettersCount == 1 || firstLettersCount == 2) && (digitsCount == 4) && (lastLettersCount == 2))
	{
		return true;
	}
	return false;
}


void Registration::copyFrom(const Registration& other)
{
	number = new char[strlen(other.number) + 1];
	strcpy(number, other.number);
}

void Registration::moveFrom(Registration&& other)
{
	number = other.number;
	other.number = nullptr;
}

void Registration::free()
{
	delete[] number;
}


Registration::Registration(const Registration& other)
{
	copyFrom(other);
}

Registration::Registration(Registration&& other)
{
	moveFrom(std::move(other));
}

Registration& Registration::operator=(const Registration& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Registration& Registration::operator=(Registration&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Registration::~Registration()
{
	free();
}


Registration::Registration(const char* str)
{
	if (!str)
	{
		throw std::invalid_argument("The string is nulptr");
	}

	if (isValidNumber(str))
	{
		number = new char[strlen(str) + 1];
		strcpy(number, str);
	}
	else
	{
		throw std::invalid_argument("The string is not valid number");
	}
}


const char* Registration::getNumber() const
{
	return number;
}


bool operator==(const Registration& lhs, const Registration& rhs)
{
	if (strcmp(lhs.getNumber(), rhs.getNumber()) == 0)
	{
		return true;
	}
	return false;
}

bool operator!=(const Registration& lhs, const Registration& rhs)
{
	return !(lhs == rhs);
}
