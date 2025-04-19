#pragma once
#include <iostream>


class Registration
{
	char* number;
	bool isValidNumber(const char* number) const;

public:

	Registration(const Registration& other);
	Registration(Registration&& other) noexcept;
	Registration& operator=(const Registration& other);
	Registration& operator=(Registration&& other) noexcept;
	~Registration();

	Registration(const char* str);

	const char* getNumber() const;

private:

	void copyFrom(const Registration& other);
	void moveFrom(Registration&& other);
	void free();
};

bool operator==(const Registration& lhs, const Registration& rhs);
bool operator!=(const Registration& lhs, const Registration& rhs);