#pragma once
#include <iostream>
#include <fstream>

class String
{
	char* data;
	size_t capacity;
	size_t size;
public:

	String(const char* str);

	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	const char* c_str() const;
	unsigned getCapacity() const;
	unsigned getSize() const;
	String substr(size_t begin, size_t len) const;

	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	String& operator+=(const String& rhs);

	friend String operator+(const String& lhs, const String& rhs);
	friend std::istream& operator>>(std::istream& is, String& str);
	friend std::ostream& operator<<(std::ostream & os, const String& str);

private:
	
	void copyFrom(const String& other);
	void free();
	void resize(unsigned newSize);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
