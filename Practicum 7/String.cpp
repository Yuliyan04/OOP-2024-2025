#include "String.h"

void String::copyFrom(const String& other)
{
	capacity = other.capacity;
	size = other.size;
	data = new char[capacity + 1];
	strcpy(data, other.data);
}

void String::free()
{
	delete[] data;
	capacity = 0;
	size = 0;
}

unsigned getClosestPower2(size_t strSize)
{
	unsigned size = 1;
	while (size < strSize)
	{
		size = size << 1;
	}
	return std::max(size, 16u);
}

unsigned getAllocSize(const char* str)
{
	if (!str)
	{
		return 0;
	}

	int len = strlen(str);
	return getClosestPower2(len);
}


String::String(const char* str)
{
	if (!str)
	{
		return;
	}

	capacity = getAllocSize(str);
	size = strlen(str);
	data = new char[capacity + 1];
	strcpy(data, str);
}


String::String() :String("") {};

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

void String::resize(unsigned newSize)
{
	char* newData = new char[newSize + 1];
	strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = newSize;
}


const char* String::c_str() const
{
	return data;
}

unsigned String::getCapacity() const
{
	return capacity;
}

unsigned String::getSize() const
{
	return size;
}


char& String::operator[](size_t pos)
{
	return data[pos];
}

const char& String::operator[](size_t pos) const
{
	return data[pos];
}

String& String::operator+=(const String& rhs)
{
	if (getSize() + rhs.getSize() > capacity)
	{
		size_t newCapacity = getClosestPower2(size + rhs.size);
		resize(newCapacity);
	}

	strncat(data, rhs.c_str(), rhs.getSize());
	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String res = lhs;
	res += rhs;
	return res;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[1024];
	is >> buff;

	unsigned buffSize = strlen(buff);
	if (buffSize > str.getCapacity())
	{
		unsigned toResize = getAllocSize(buff);
		str.resize(toResize);
	}
	strcpy(str.data, buff);
	str.size = buffSize;
	return is;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.c_str();
	return os;
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
	return lhs > rhs || lhs == rhs;
}

bool operator<(const String& lhs, const String& rhs)
{
	return !(lhs >= rhs);
}

bool operator<=(const String& lhs, const String& rhs)
{
	return lhs < rhs || lhs == rhs;
}


String String::substr(size_t begin, size_t len) const
{
	if (begin + len > size)
	{
		return String("");
	}

	unsigned substrCap = getClosestPower2(len);
	char* substr = new char[substrCap + 1];
	for (size_t i = 0; i < len; i++)
	{
		substr[i] = data[begin + i];
	}

	String res(substr);
	delete[] substr;
	return res;
}