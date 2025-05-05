#pragma once
#include <iostream>

class String
{
	char* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const String& other);
	void resize(unsigned newCapacity);
public:
	String();
	String(const char* str);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	size_t getSize() const;
	size_t getCapacity() const;

	const char* c_str() const;

	char& operator[](unsigned index);
	const char& operator[](unsigned indexs) const;

	String& operator+=(const String& other);

	friend String operator+(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);

	String substr(unsigned begin, unsigned howMany);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);