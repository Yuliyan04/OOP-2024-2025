#include "MyString.h"
#include <algorithm>
#pragma warning (disable : 4996)

void String::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void String::copyFrom(const String& other)
{
	capacity = other.capacity;
	data = new char[capacity];
	strcpy(data, other.data);
	size = other.size;
}

void String::resize(unsigned newCapacity)
{
	char* newData = new char[newCapacity + 1];
	strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

static unsigned roundToPowerOfTwo(unsigned v)
{
	unsigned res = 1;
	while (res < v)
	{
		res *= 2;
	}

	return res;
}

static unsigned getMaxResizeCapacity(unsigned v)
{
	return std::max(roundToPowerOfTwo(v), 16u);
}


String::String() : String("") {}

String::String(const char* str)
{
	if (!str)
		str = "";

	size = strlen(str);
	capacity = getMaxResizeCapacity(size);
	data = new char[capacity];
	strcpy(data, str);
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

String::~String()
{
	free();
}

size_t String::getSize() const
{
	return size;
}

size_t String::getCapacity() const
{
	return capacity - 1;
}

const char* String::c_str() const
{
	return data;
}

char& String::operator[](unsigned index)
{
	return data[index];
}

const char& String::operator[](unsigned index) const
{

	return data[index];
}

String& String::operator+=(const String& other)
{
	if (size + other.size + 1 > capacity)
		resize(getMaxResizeCapacity(size + other.size));

	strncat(data, other.data, other.size);

	size += other.size;

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String res(lhs);
	res += rhs;

	return res;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.data;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[1024];
	is >> buff;

	size_t buffStringSize = strlen(buff);
	if (buffStringSize >= str.capacity)
		str.resize(getMaxResizeCapacity(buffStringSize));

	strcpy(str.data, buff);
	str.size = buffStringSize;

	return is;
}

String String::substr(unsigned begin, unsigned howMany)
{
	if (begin + howMany > size)
		return String("");

	String res;
	res.capacity = getMaxResizeCapacity(howMany + 1);
	res.data = new char[res.capacity];
	strncat(res.data, data + begin, howMany);
	res.size = howMany;

	return res;
}


bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
