#include "StringVector.h"

unsigned getNextPower2(unsigned num)
{
	unsigned res = 1;
	while (res < num)
	{
		res = res << 1;
	}
	return res;
}

void StringVector::copyFrom(const StringVector& other)
{
	capacity = other.capacity;
	size = other.size;
	collection = new String[capacity];
	for (size_t i = 0; i < size; i++)
	{
		collection[i] = other.collection[i];
	}
}

void StringVector::free()
{
	delete[] collection;
	collection = nullptr;
	capacity = 0;
	size = 0;
}

void StringVector::resize(unsigned num)
{
	capacity = num;
	String* newCollection = new String[capacity];
	
	for (size_t i = 0; i < size; i++)
	{
		newCollection[i] = collection[i];
	}

	delete[] collection;
	collection = newCollection;
}


StringVector::StringVector() :collection(nullptr), capacity(0), size(0) {};

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

StringVector& StringVector::operator=(const StringVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StringVector::~StringVector()
{
	free();
}

void StringVector::push_back(const String& toPush)
{
	if (size == capacity)
	{
		resize(getNextPower2(capacity));
	}
	collection[size] = toPush;
	size++;
}

void StringVector::pop_back(const String& toPop)
{
	collection[size].~String();
	size--;
}

void StringVector::insert(const String& toInsert, size_t pos)
{
	if (size == capacity)
	{
		resize(getNextPower2(capacity));
	}
	collection[size] = toInsert;
	size++;
	for (size_t i = pos; i < size; i++)
	{
		std::swap(collection[i], collection[size]);
	}
}

void StringVector::erase(const String& toErase, size_t pos)
{
	size--;
	for (size_t i = pos; i < size; i++)
	{
		std::swap(collection[i], collection[i + 1]);
	}
	collection[pos].~String();
}

void StringVector::clear()
{
	String* newCollection = new String[capacity];
	delete[] collection;
	collection = newCollection;
	size = 0;
}

const String& StringVector::operator[](size_t pos) const
{
	return collection[pos];
}

String& StringVector::operator[](size_t pos)
{
	return collection[pos];
}

unsigned StringVector::getSize() const
{
	return size;
}

bool StringVector::empty() const
{
	return size == 0;
}